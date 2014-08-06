/*
 * MidasEventParser.cc
 *
 *  Created on: Apr 24, 2014
 *      Author: rdunlop
 */

#include "MidasEventParser.hh"

MidasEventParser::MidasEventParser(TFile* file) :
fRootFile(file),
header_flag(false),
channelTrigger_flag(false),
deadtime_flag(false),
trailer_flag(false),
mSize(0),
dataword(NULL){

	//This stuff is here right now for testing. It might leave in the future and go into a "quick analyzer function"....
	hPulseHeight = new TH1F("PulseHeight_raw","Raw Pulse Heights",102400,0,200);//There will be on of these for each detector though
	hPulseHeight->SetBit(TH1::kCanRebin);
	hCFD = new TH1F("CFD_raw","Raw CFD",1024,0,200);
	hCFD->SetBit(TH1::kCanRebin);
	hTimeStamp = new TH1F("TimeStamp_raw","Raw Time Stamp",400,0,20);
	hTimeStamp->SetBit(TH1::kCanRebin);//May go back and bin Time-stamps relative to cycle start
	hAddress = new TH1F("Address_raw","Addresses",200000,0,200000);
	hAddress->SetBit(TH1::kCanRebin);

	//This check shouldn't be a check, but may give us a clue to the electronic dead time (per Adam in the ELog)
	for(int i = 0; i<16384; i++){
		channelTriggerID_check[i] = 0;
	}
}

MidasEventParser::~MidasEventParser(){

	hPulseHeight->Write();
	hCFD->Write();
	hTimeStamp->Write();
	hAddress->Write();

	delete hPulseHeight;
	delete hCFD;
	delete hTimeStamp;
	delete hAddress;
}


bool MidasEventParser::Parse(uint32_t *dword,uint32_t mS, uint32_t mSerialNumber, uint64_t mTime){
	//Will probably pass in an instance of TFragQ to Parse, singleton or a copy?

	//One MIDAS event can contain up to 100 physics events or as few as 1
	//These variables are members of EventProcessor for easy access by postcheckers, datadumpers, etc...
	dataword = dword;//These variables are definitely not thread-safe
	mSize = mS;		//Might be as simple as not keeping them as class fields
					//As well as the GrifFrag variable, and pass them by reference

	uint32_t nHits = 0; //Keep Track of the number of KValues in the data.
						//This should be available in the tree information
	std::cout << "mSize "<< mSize << std::endl;

	TGriffinFragment* GrifFrag  = new TGriffinFragment();

	GrifFrag->midasTimeStamp = mTime; //This will be used to estimate live/dead fractions etc.

	//We will be parsing events here and sending them to a TFragmentQ which will then be sent to checkers and to writers.
	//This needs to done carefully to avoid over-stepping memory bounds
	for(unsigned int wordcount = 0; wordcount<mSize; wordcount++){
		switch(((*(dataword+wordcount) & PacketMask)  >> PacketShift)){
		  case(kHeader):
				GrifFrag->Clear();
		  	  	this->Clear();	//Clear out the event-by-event processor
				//IF WE HIT A NEW HEADER MID EVENT WE SHOULD RESET THE EVENT AND DECIDE WHAT TO DO WITH THE LAST
				//Set Various properties and do error checks
				SetNFilterPatterns(*(dataword+wordcount),GrifFrag);
				SetDataType(*(dataword+wordcount),GrifFrag);
				SetPileupType(*(dataword+wordcount),GrifFrag);
				SetAddress(*(dataword+wordcount),GrifFrag);
				SetDetectorType(*(dataword+wordcount),GrifFrag);
				//Move to the next word where PPG should be stored
				wordcount++;
				SetPPGPattern(*(dataword+wordcount),GrifFrag);
				//Move to the next word where Master Filter ID should be stored
				wordcount++;
				SetMasterFilterID(*(dataword+wordcount),GrifFrag);
				//Move to the next word where Master Filter Pattern should be stored
				wordcount++;
				SetMasterFilterPattern(*(dataword+wordcount),GrifFrag);

				if(!header_flag){
					header_flag = true;
				}
				else{
					BadFrag("Multiple header events without a trailer!");//Maybe not a bad frag?
				}
				break;
		  case(kChannelTrigger):
				SetChannelTriggerID(*(dataword+wordcount),GrifFrag);

				if(!channelTrigger_flag){
					channelTrigger_flag = true;
				}
				else{
					BadFrag("Multiple channel trigger packets without a trailer!");
				}
				break;
		  case(kLowerTimestamp):
				SetLowerTimestamp(*(dataword+wordcount),GrifFrag);
		  	  	if(!lowTimestamp_flag){
		  	  		lowTimestamp_flag = true;
		  	  	}
				else{
					BadFrag("Multiple low time stamp packets without a trailer!");
				}
				break;
		  case(kWaveform):
				SetWaveForm(*(dataword+wordcount),GrifFrag);
				break;
		  case(kDeadtime):
				//Make sure that the last word is the trailer
				//if((*(dataword+wordcount+2*GetPileupType()) & PacketMask)  >> PacketShift == trailer){
				//Need a way to make this recognize it's a bad frag, but then record as much info as
				//possible in the griff frag to go into the bad tree
					SetDeadTime(*(dataword+wordcount),GrifFrag);
					SetUpperTimestamp(*(dataword+wordcount),GrifFrag);
					deadtime_flag = true;
					//Loop over pileup type
					while(nHits < GetPileupType()){// && bank.GotData()){// && IsGoodFrag()){
						wordcount++;
						//Move to the next word where the upper K-value and Pulse Height should be stored
						//I should find out if we should reject an entire MIDAS event if a single K/PH value is bad
						SetHighKBits(*(dataword+wordcount),GrifFrag);
						SetPulseHeight(*(dataword+wordcount),GrifFrag);
						wordcount++;
						//Move Forward to the next word where the lower K-value and CFD Timing should be stored
						SetLowKBits(*(dataword+wordcount),GrifFrag);
						SetCFDTiming(*(dataword+wordcount),GrifFrag);
						nHits++;
						GrifFrag->hitNumber++;
						//I might want to check the trailer stuff first and then start processing events at this level?
						//We need to start Qing up events before the trailer. Up to three per "event"

					}
			  	  	if(!deadtime_flag){
			  	  		deadtime_flag = true;
			  	  	}
					else{
						BadFrag("Multiple dead time packets without a trailer!");
					}
			//	}
			//	else{
			//		BadFrag();
			//	}
				break;
		  case(kTrailer):
				CheckTrailerWord(*(dataword+wordcount),GrifFrag);
				trailer_flag = true;

				//These methods are a little sketchy right now
				//Not completely sure what the event-by-event structure will looks like
				if(IsGoodFrag()){
					//Need to write events at this point
				}
				else{
					nBadEvents++;
					nBadPileups += GetPileupType();
					std::cout << std::endl;
				}


				if(IsGoodFrag()){
					TFragmentQueue::GetPtr("parsedQ")->AddToQueue(GrifFrag);
				}
				else
				{
					//This is for basic checks before the Event Checker
					TFragmentQueue::GetPtr("badQ")->AddToQueue(GrifFrag);
				}

				nEvents++;
				Clear(); //Clear the eventProcessor and Get ready for the next event

				break;
		  default:
			  std::cout << "Non-Packet Type = " << std::hex << *(dataword+wordcount) << std::endl;
			  wordcount++;
		}
	}

	return true;
}

void MidasEventParser::DataDump(uint32_t *dataword, uint32_t mSize){
		for(uint16_t i =0; i< mSize; i++){
			std::cout << std::hex<< *(dataword + i) << " "<< std::endl ;//Maybe there is an easy way to highlite headers, trailers, bad words?
		}
}

void MidasEventParser::SetWaveForm(uint32_t& dataword,TGriffinFragment* GrifFrag){
	nWaveFormWords++; //This is all that is happening here for now, Allison will be working on this?
	//May put a flag in here which removes the writing of waveform data
	GrifFrag->wavebuffer.push_back((dataword & WaveFormMask) >> WaveFormShift );
}

void MidasEventParser::SetNFilterPatterns(uint32_t& dataword,TGriffinFragment* GrifFrag){

	std::cout << ((dataword & NFilterPatternsMask) >> NFilterPatternsShift ) << std::endl;
	GrifFrag->numberFilters = ((dataword & NFilterPatternsMask) >> NFilterPatternsShift );

//	std::cout << "The Filter Pattern is: " << nFilterPatterns << std::endl;
}

void MidasEventParser::SetDataType(uint32_t& dataword,TGriffinFragment* GrifFrag){
	GrifFrag->dataType = ((dataword & DataTypeMask) >> DataTypeShift);

//	std::cout << "The Data Type is: " << dataType << std::endl;

	if(dataType >4 || dataType <1)
	{
		std::cerr << "The Data Type of: " << dataType << " does not exist" << std::endl;
		BadFrag();
		//exit(-1);
	}
}

void MidasEventParser::SetAddress(uint32_t& dataword,TGriffinFragment* GrifFrag){
	GrifFrag->channelAddress = ((dataword & AddressMask) >> AddressShift);
//	std::cout  << "The Address is: " << address << std::endl;

	hAddress->Fill(GrifFrag->channelAddress);
	//Find Sub-addresses
	//This may need to communicate with ODB in order to put the right detector information in the right place/do the appropriate "does this detector even exist? checks"
	mAddress =	(address & MasterMask) >> MasterShift;
	sAddress = (address & SlaveMask) >> SlaveShift;
	cAddress = (address & DigitizerMask) >> DigitizerShift;
}

void MidasEventParser::SetDetectorType(uint32_t& dataword,TGriffinFragment* GrifFrag){
	GrifFrag->detectorType = ((dataword & DetectorTypeMask) >> DetectorTypeShift);

	//if(mySettings->env->GetValue("Verbosity",1) == 1)
	//std::cout << "The Detector Type is: " << detectorType << std::endl;
}

void MidasEventParser::SetPileupType(uint32_t& dataword,TGriffinFragment* GrifFrag){
	GrifFrag->numberPileups = ((dataword & PileupTypeMask) >> PileupTypeShift);
	pileupType = GrifFrag->numberPileups;
//	std::cout << "The Pileup Type is: " << pileupType << std::endl;

	if(GrifFrag->numberPileups > 3)
	{
		std::cerr << "Too Many Hits = " << pileupType << std::endl;
		BadFrag();
		//exit(-1);
	}
	else if(GrifFrag->numberPileups < 1)
	{
		std::cerr << "Zero or negative hits = " << pileupType << std::endl;
		BadFrag();
		//exit(-1);
	}
}

void MidasEventParser::SetPPGPattern(uint32_t& dataword,TGriffinFragment* GrifFrag){
	GrifFrag->ppg = ((dataword & PPGPatternMask) >> PPGPatternShift);
//	std::cout << "The PPG Pattern is: " << PPGPattern << std::endl;

	//The PPG Pattern is only 30 bits long and must contain a fixed leading 00.
	if((dataword >> 30) != 0){
		std::cerr << "PPG Pattern exceeds 30 bits = 0x" << std::hex << dataword << std::endl;
		WrongPacket(dataword,"PPG Pattern");
		BadFrag();
		exit(1);
	}
	//If End of Cycle
	endOfCycleFlag = true;


}

void MidasEventParser::SetMasterFilterID(uint32_t& dataword,TGriffinFragment* GrifFrag){
	GrifFrag->filterId = ((dataword & MasterFilterIDMask) >> MasterFilterIDShift);
//	std::cout << "The Master Filter ID is: " << masterFilterID << std::endl;

	//This check might be used later
/*	if(masterFilterID != masterFilterID_check){
		std::cout << "Master Filter ID did not increment properly: " << masterFilterID << " expected " << masterFilterID_check << std::endl;
		masterFilterID_check = masterFilterID;
		//exit(1);
	}
	masterFilterID_check++;
*/

	//The master Filter ID is only 31 bits long and must contain a fixed, leading 0.
	if((dataword >> 31) != 0){
		std::cerr << "The Master Filter ID should be 31 bits = 0x" << std::hex << dataword << std::endl;
		WrongPacket(dataword,"Master Filter ID");
		BadFrag();
		//exit(1);
	}
}

void MidasEventParser::SetMasterFilterPattern(uint32_t& dataword,TGriffinFragment* GrifFrag){
	GrifFrag->filterPattern = ((dataword & MasterFilterPatternMask) >> MasterFilterPatternShift);
//	std::cout << "The Master Filter Pattern is: " << masterFilterPattern << std::endl;

	//The master Filter ID is only 30 bits long and must contain a fixed, leading 0.
	if((dataword >> 30) != 0){
		std::cerr << "The Master Filter ID should be 30 bits = 0x" << std::hex << dataword << std::endl;
		WrongPacket(dataword,"Master Filter Pattern");
		BadFrag();
	}
}

void MidasEventParser::SetChannelTriggerID(uint32_t& dataword,TGriffinFragment* GrifFrag){
	GrifFrag->triggerId = ((dataword & ChannelTriggerIDMask) >> ChannelTriggerIDShift);
	address = GrifFrag->triggerId ;

	//This may not always increment properly, especially in the high rate experiments
	//The reason for this is data being lost between the GRIFF-C and GRIFF-16 cards
	//We can however use the jump in the channelTrigger ID to calculate an effective deadtime
	//and 'correct' for this effect. This may be a VERY important check to do, and do properly.

		if(GrifFrag->triggerId != channelTriggerID_check[address]){
			std::cout << "Channel Trigger ID did not increment properly at address: " <<std::hex<< address << ": " <<std::dec << GrifFrag->triggerId << " expected " << channelTriggerID_check[address] << std::endl;
			channelTriggerID_check[address] = GrifFrag->triggerId;
			//exit(1);
		}

		channelTriggerID_check[address]++;


//	std::cout << "The Channel Trigger ID is: " << channelTriggerID << std::endl;
}

void MidasEventParser::SetLowerTimestamp(uint32_t& dataword,TGriffinFragment* GrifFrag){
	GrifFrag->timeStampLow = ((dataword & TimestampLMask) >> TimestampLShift);
//	std::cout << "The Time Stamp (low bits) is: " << lowTimestamp << std::endl;
	lowTimestamp_flag = true;


	//Don't build this on the fly. Build it after the fact
	//Stitch the 42-bit timestamp toGether
	if(highTimestamp_flag && lowTimestamp_flag){
		GrifFrag->timeStamp = (GrifFrag->timeStampHigh<< 28) | GrifFrag->timeStampLow;
		hTimeStamp->Fill(GrifFrag->timeStamp);
	}
}

void MidasEventParser::SetUpperTimestamp(uint32_t& dataword,TGriffinFragment* GrifFrag){
	GrifFrag->timeStampHigh = ((dataword & TimestampHMask) >> TimestampHShift);
//	std::cout << "The Time Stamp (high bits) is: " << highTimestamp << std::endl;
	highTimestamp_flag = true;

	//Don't build this on the fly. Build it after the fact
	//Stitch the 42-bit timestamp toGether
	if(highTimestamp_flag && lowTimestamp_flag){
		GrifFrag->timeStamp = (GrifFrag->timeStampHigh<< 28) | GrifFrag->timeStampLow;
		hTimeStamp->Fill(GrifFrag->timeStamp);
	}
}

void MidasEventParser::SetDeadTime(uint32_t& dataword,TGriffinFragment* GrifFrag){
	GrifFrag->deadTime = ((dataword & DeadTimeMask) >> DeadTimeShift);
	totalDeadTime+=deadTime;
//	std::cout << "The Deadtime is: " << deadTime << std::endl;
}

void MidasEventParser::SetHighKBits(uint32_t& dataword,TGriffinFragment* GrifFrag){
	GrifFrag->kHigh = ((dataword & KValueMask) >> KValueShift);
	highKbits_flag = true;

	//highKbits = 4;//REMOVE

	//The K value and CFD data are only 31 bits long and must contain a fixed, leading 0.
	if((dataword >> 31) != 0){
		std::cerr << "The K/CFD data should be 31 bits = 0x" << std::hex << dataword << std::endl;
		WrongPacket(dataword,"K Value High bits");
		BadFrag();
	}
}

void MidasEventParser::SetLowKBits(uint32_t& dataword,TGriffinFragment* GrifFrag){
	GrifFrag->kLow = ((dataword & KValueMask) >> KValueShift);
	lowKbits_flag = true;

	//The K value and CFD data are only 31 bits long and must contain a fixed, leading 0.
	if((dataword >> 31) != 0){
		std::cerr << "The K/Pulse Height data should be 31 bits = 0x" << std::hex << dataword << std::endl;
		WrongPacket(dataword,"K Value Low bits");
		BadFrag();
	}

	//Stitch the 10-bit K-Value toGether
	//Again, do this right before the event Gets thrown into the tree, like the timestamp
	//Make K multiple hits different events? ***********************
	if(highKbits_flag){
		KValue.push_back((GrifFrag->kHigh << 5) | GrifFrag->kLow);
		//ReSet the flags
		lowKbits_flag = false;
		highKbits_flag = false;
	}
}

void MidasEventParser::SetPulseHeight(uint32_t& dataword,TGriffinFragment* GrifFrag){

	pulseHeight.push_back((dataword & PulseHeightMask) >> PulseHeightShift);

	hPulseHeight->Fill((dataword & PulseHeightMask) >> PulseHeightShift);

	//std::cout << "PH = " << ((dataword & PulseHeightMask) >> PulseHeightShift) << std::endl;

}

void MidasEventParser::SetCFDTiming(uint32_t& dataword,TGriffinFragment* GrifFrag){

	CFDTiming.push_back((dataword & CFDTimingMask) >> CFDTimingShift);
	hCFD->Fill((dataword & CFDTimingMask) >> CFDTimingShift);
}

void MidasEventParser::CheckTrailerWord(uint32_t& dataword,TGriffinFragment* GrifFrag){
	//The event trailer should be an exact replica of the lower time stamp. If they do not match something went wrong
	if(channelTriggerID != ((dataword & ChannelTriggerIDMask) >> ChannelTriggerIDShift)){
		std::cout << "Event trailer != Channel Trigger ID! " << ((dataword & ChannelTriggerIDMask) >> ChannelTriggerIDShift) << " != " << channelTriggerID << std::endl;
		BadFrag();
		//exit(1);
	}
}

bool MidasEventParser::IsGoodFrag(){
	return !badFrag_flag;
}

void MidasEventParser::GoodFrag(){
	badFrag_flag = false;
}

void MidasEventParser::BadFrag(){
	badFrag_flag = true;
	if(Settings::GetInstance()->GetErrorKillFlag()){
		DataDump(dataword,mSize);
		//exit(1);
	}

}

void MidasEventParser::BadFrag(std::string badstring){
	badFrag_flag = true;
	std::cerr << badstring << std::endl;
	if(Settings::GetInstance()->GetErrorKillFlag()){
		std::cout << *dataword << " " <<  *(dataword+1) << std::endl; //Something weird here
		DataDump(dataword,mSize);
		//exit(1);
	}
}

void MidasEventParser::WrongPacket(uint32_t& dataword,std::string expectedPacketType){
	//Tries to identify the wrong packet type

	std::cerr << "Wrong Packet Type for " << expectedPacketType << " = " << ((dataword & PacketMask) >> PacketShift) <<  std::endl;
	BadFrag();

	//Attempt to figure out what happened and possibly correct
	switch((dataword & PacketMask) >> PacketShift){
		case(kHeader):
			break;
		case(kChannelTrigger):
			break;
		case(kLowerTimestamp):
			break;
		case(kDeadtime):
			break;
		case(kWaveform):
			break;
		case(kTrailer):
			std::cout << "Trailer Came Early!" << std::endl;
			break;
	}
}

void MidasEventParser::Clear(){
	//Copies of these are probably unnecessary.
	//Just fill a tmp Griffin fragment on the fly and push it back into a TFragQ
	nFilterPatterns = 0;
	dataType = 0;
	address = 0;
	mAddress = 0;
	sAddress = 0;
	cAddress = 0;
	detectorType = 0;
	pileupType = 0;
	PPGPattern = 0;
	masterFilterID = 0;
	masterFilterPattern = 0;
	channelTriggerID = 0;
	lowTimestamp = 0;
	highTimestamp = 0;
	timestamp = 0;
	deadTime = 0;
	highKbits = 0;
	lowKbits = 0;
	KValue.clear();
	pulseHeight.clear();
	CFDTiming.clear();
	waveformWords.clear();

	header_flag = false;
	channelTrigger_flag = false;
	deadtime_flag  = false;
	trailer_flag = false;

	nWaveFormWords = 0;

	ClearFlags();
}

void MidasEventParser::ClearFlags(){
	//These flags will be non-static members of the TGriffinfragment class
	lowTimestamp_flag = false;
	highTimestamp_flag = false;
	lowKbits_flag = false;
	highKbits_flag = false;
	badFrag_flag = false;
}


