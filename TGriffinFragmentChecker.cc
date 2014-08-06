/*
 * TGriffinFragmentChecker.cc
 *
 *  Created on: Jul 17, 2014
 *      Author: rdunlop
 */

#include "TGriffinFragmentChecker.hh"

void TGriffinFragmentChecker::Check(std::string QName){

	this->Clear();
	TGriffinFragment tmpGriffinFrag;
//	tmpGriffinFrag = TFragmentQueueMap::instance()->PopFragment(QName);

	//We perform all of these checks. If there is an issue we will throw an exception so we do not
	//have to perform all of the checks on a bad fragment.
	try{
		CheckFlags();
		CheckDataType();
		CheckTrailer();
		CheckChannelTriggerID();
		CheckPileupHits();
		//etc...
	}
	//This catch might contain some information on what made the fragment bad
	catch(char const* failure){
		if(Settings::GetInstance()->GetErrorKillFlag()){
			std::cerr << "Bad Event: " << failure << std::endl; //Event number?
			exit(1);
		}
	//Put event in BadQ if we threw

	}


}

void TGriffinFragmentChecker::Clear(){
	badFrag_flag = false;
}

bool TGriffinFragmentChecker::CheckFlags(){

	throw("Bad Flags");
	return true;

}

bool TGriffinFragmentChecker::CheckDataType(){

	throw("Bad Data Type")
	return true;

}

bool TGriffinFragmentChecker::CheckTrailer(){

	throw("Bad Trailer");
	return true;

}

bool TGriffinFragmentChecker::CheckChannelTriggerID(){
	return true;
}

bool TGriffinFragmentChecker::CheckPileupHits(){
	throw("Bad Pileup Hits");
	return true;
}

void TGriffinFragmentChecker::BadFrag(){
	badFrag_flag = true;
	if(Settings::GetInstance()->GetErrorKillFlag()){
		//We will have different type of errors here
	}

}

