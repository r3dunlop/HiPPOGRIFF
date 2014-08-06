/*
 * MidUnpack.cc
 *  Created on: Apr 23, 2014
 *      Author: Ryan Dunlop
 *      Email:	rdunlop@uoguelph.ca
 *      Goal:	The Goal for this code is to be readable to someone who is not necessarily a strong progammer
 *      while still being efficient and reliable
 */

#include <iostream>
#include <iomanip>
#include <map>

#include "TFile.h"
#include "TTree.h"
#include "TStopwatch.h"
#include "TApplication.h"
#include "TFragmentQueue.hh"
#include "TGriffinFragmentChecker.hh"
#include "TFragmentWriter.hh"

#include "MidasEventParser.hh"
#include "Settings.hh"
#include "TMidasEvent.h"
#include "TMidasFile.h"

//#define NDEBUG //This turns off the assert statements used for debugging
#define DEBUG

int main(int argc, char **argv)
{

	//Name the application for root environment
	int appargc = 2;
	char *appName= new char[20];	  sprintf(appName,"MidUnpack");
	char *appOpt= new char[20];	  sprintf(appOpt,"-b");

	char *appargv[] = {appName,appOpt};
	TApplication *myApp = new TApplication(appName,&appargc,appargv);//This is to create a name for the TEvn/Settings environvments (for now)

	delete [] appName;
	delete [] appOpt;

	//Perform some command-line checks
	//Get command-line arguments
	if (argc <= 1)
	    {
	        std::cout << "Usage: " << argv[0] << " <Filename>(.mid)" << std::endl;
	        exit(1);
	    }

	//Read in first command line argument
	std::string midasFileName = argv[1];

	//Check to see if we are actually reading in a .mid file
	std::string::size_type idx;
	std::string extension;
	idx = midasFileName.rfind(".");
    if(idx != std::string::npos) {
    	extension = midasFileName.substr(idx+1);
    }
    else{
    	std::cerr << "No extension found" << std::endl;
    	return 1;
    }
    if(extension != "mid"){
    	std::cerr<<"Failed to find .mid extension"<<std::endl;
    	return 1;
    }

	//Will need to use first argument as input mid file.
	std::string rootFileName;
	char const *pchar = midasFileName.c_str();

	///////////////   Create File Manager   //////////////////
	TMidasFile *mfile = new TMidasFile;
	if(!(mfile->Open(pchar))){
		std::cerr << "Could not find " << midasFileName << std::endl;
		exit(1);
	}

	//Done checks, start setting things up
	size_t nofEvents = 0;
	const char* mySettingsName = "./exp_config.in";

	//Read in Configuration file
	Settings *mySettings;
	mySettings = Settings::GetInstance();
	mySettings->Read(mySettingsName);
	//Print Settings to screen
	mySettings->Print();

	//Set up root file.
	if(rootFileName.empty()) {
	    rootFileName = midasFileName.substr(0,idx);
	    rootFileName.append("_frag.root"); //Write out midasFileName_frag.root
	    std::cout<<"created root file name '"<<rootFileName<<"' from midas file name '"<<midasFileName<<"'"<<std::endl;
	}

	TFile rootFile(rootFileName.c_str(),"recreate");

	if(!rootFile.IsOpen()) {
		std::cerr<<"Failed to open root file '"<<rootFileName<<"' for writing"<<std::endl;
	    return 1;
	}

	TTree tree("fragmentTree","Fragment Tree");

	///////////////	  variables needed   	///////////////////
	TStopwatch *watch = new TStopwatch;

	//Create Midas events for the parser
	TMidasEvent *mEvent = new TMidasEvent;
	TMidasEvent *mHeader = new TMidasEvent; //ODB stuff is jammed in here

	///////////////   Get the File Header   ///////////////////
	mfile->Read(mHeader);
	mHeader->Print();

	////////////// Create Event Parser  ////////////////////
	MidasEventParser *eventParser = new MidasEventParser(&rootFile);

	//////////////  Initialize Variables    ///////////////////
	uint32_t totalEvents = 0;
	size_t oldPosition = 0;

	//Output run information
    std::cout<<"Start time: "<<std::dec<<mHeader->GetTimeStamp()<<std::dec<<std::endl
	<<"Number of bytes in header: "<<mHeader->GetDataSize() <<std::dec<<std::endl
	<<"Starting main loop:"<<std::endl
	<<std::endl;


    ////////////////      Main Loop        ////////////////////

    while(mfile->Read(mEvent) && (totalEvents < mySettings->GetMaxEventNumber() || mySettings->GetMaxEventNumber()==0)){
    	//zero the old event
    	//if we succeed in reading the event from file, we process it

    	//Currently only one type of Midas Event type == 1
    	//Need to tell the code that we are on a new cycle when we are on a new cycle
    	totalEvents++;
    	if(!mEvent)
    		return false;

    	//fMidasEventsProcessed++;
		//int NumFragsFound = 0;
		void *dataword;
		int banksize = 0;
		//int testnumber = 0;
		//int tFinQ_before = 0;
		switch(mEvent->GetEventId()){
			case 1:
			//This reads in a griffin event since these functions are written for TIG and GRIF DAQs
			banksize = mEvent->LocateBank(NULL, "GRF1", &dataword);
			if(banksize){
				try {
					//mEvent->SetBankList();
					//mEvent->Print();
					if(eventParser->Parse((uint32_t*)dataword,banksize,mEvent->GetSerialNumber(),mEvent->GetTimeStamp())){
						break;
					}
					//Put a counter up so we know how close we are to reading completion
					if(totalEvents%100000 == 0) {
						//std::cout<<std::setw(5)<<std::fixed<<std::setprecision(1)<<(100.*mEvent->Get)/fileManager.Size()<<"%: read "<<totalEvents<<" events ("<<totalEvents/watch.RealTime()<<" events/s = "<<totalEvents/100000*(fileManager.Position()-oldPosition)/watch.RealTime()/(1024)<<" kiB/s)\r"<<std::flush;
			  //      	oldPosition = fileManager.Position();
			   //     	watch.Continue();
					}
					//mevent->Print("a");
				//	fTotalFragments += TParser::instance()->GriffinDATAToFragment((unsigned int*)ptr,banksize,mevent->GetSerialNumber(),mevent->GetTimeStamp());
					//printf(DYELLOW "==========================================" RESET_COLOR  "\n");
					}
				catch (const std::bad_alloc&) { }
			}
				break;
			default:
				break;
		};

        if(nofEvents > 0 && totalEvents >= nofEvents) {
        	break;
        }
    }
    TGriffinFragmentChecker *myFragChecker = new TGriffinFragmentChecker;

    myFragChecker->Check("parsedQ");

    //done with frag checking
    delete myFragChecker;

    //Might change all of this to be one writer that gets different Q's passed and references
    //different branches.

    //Write out the good tree
	TTree goodTree("goodFragmentTree","Good Fragment Tree");
    //Create a fragment writer
    TFragmentWriter *myGoodFragWriter = new TFragmentWriter("goodQ",&rootFile, &goodTree);
    while(myGoodFragWriter->FillTree()); //Fill tree until Q is empty
    //Write out tree
    goodTree.Write();

    //Write out the bad tree. Might want to write this out in "MIDAS words" so that we can
    //try to recover the error.
	TTree badTree("badFragmentTree","Bad Fragment Tree");
    //Create a fragment writer
    TFragmentWriter *myBadFragWriter = new TFragmentWriter("badQ",&rootFile, &badTree);
    while(myBadFragWriter->FillTree()); //Fill tree until Q is empty
    //Write out tree
    badTree.Write();

    std::cout << std::dec;

    //std::cout<<"Reached end of file after "<<totalEvents<<" events from "<<fileManager.Position()<<" bytes out of "<<fileManager.Size()<<" bytes."<<std::endl;

    std::cout << "There were " << eventParser->GetNBadEvents() << " bad events out of " << eventParser->GetNEvents() << " (" << (1. - (double)(eventParser->GetNBadEvents())/(double)(eventParser->GetNEvents()) )*100. << "% Good)" << std::endl;

    std::cout << "Total Dead Time: " << eventParser->GetTotalDeadTime()*10.0/1000.0 << " us" << std::endl;
    //Live time seems to be counting far too high
    std::cout << "Total Live Time: " << eventParser->GetTotalTime()*10.0/1000000000.0 << " s" << std::endl;//Something is wrong here
    std::cout << "Live Fraction: " << eventParser->GetLiveFraction()*100.0 << " %" << std::endl;

    /////////////    End of Sort Cleanup    /////////////////////
	delete eventParser;
	delete mEvent;
	delete mHeader;

	mfile->Close();
	tree.Write();
	rootFile.Close();
	delete myBadFragWriter;
	delete myGoodFragWriter;
	delete myApp;
	delete mfile;
	delete watch;

	return 0;

}


