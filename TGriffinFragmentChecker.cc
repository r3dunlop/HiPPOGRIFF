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

	CheckFlags();
	CheckDataType();
	CheckTrailer();
	CheckChannelTriggerID();
	CheckPileupHits();
	//etc...
}

void TGriffinFragmentChecker::Clear(){
	badFrag_flag = false;
}

bool TGriffinFragmentChecker::CheckFlags(){

	return true;

}

bool TGriffinFragmentChecker::CheckDataType(){

	return true;

}

bool TGriffinFragmentChecker::CheckTrailer(){

	return true;

}

bool TGriffinFragmentChecker::CheckChannelTriggerID(){
	return true;
}

bool TGriffinFragmentChecker::CheckPileupHits(){
	return true;
}

void TGriffinFragmentChecker::BadFrag(){
	badFrag_flag = true;
	if(Settings::GetInstance()->GetErrorKillFlag()){
		//We will have different type of errors here
	}

}

