/*
 * TGriffinFragmentChecker.cc
 *
 *  Created on: Jul 17, 2014
 *      Author: rdunlop
 */

#include "TGriffinFragmentChecker.hh"

bool TGriffinFragmentChecker::Check(std::string QName){

	if(TFragmentQueue::GetPtr(QName)->Size() == 0){
		return false;
	}
	this->Clear();
	//I think there are pointer scope problems with TFragmentQueue!!!!!!!
	TGriffinFragment *tmpGriffinFrag = TFragmentQueue::GetPtr(QName)->PopFragment();

	std::cout << tmpGriffinFrag->channelAddress << std::endl;

	//We perform all of these checks. If there is an issue we will throw an exception so we do not
	//have to perform all of the checks on a bad fragment.
	try{
		CheckFlags();
		CheckDataType(tmpGriffinFrag);
		CheckTrailer();
		CheckChannelTriggerID();
		CheckPileupHits();
		//etc...
	}
	//This catch might contain some information on what made the fragment bad
	catch(MyException const& e){
		BadFrag();
		if(Settings::GetInstance()->GetErrorKillFlag()){
			std::cerr << "Bad Event: " << e.failureMode << "=" << e.value << std::endl; //Event number?
			exit(1);
		}
	//Put event in BadQ if we threw

	}

	return TFragmentQueue::GetPtr(QName)->Size();

}

void TGriffinFragmentChecker::Clear(){
	badFrag_flag = false;
}

bool TGriffinFragmentChecker::CheckFlags(){

	return true;

}

bool TGriffinFragmentChecker::CheckDataType(TGriffinFragment* frag){

	if(frag->dataType >4 || frag->dataType <1)
	{
		throw MyException("Data Type", frag->dataType);
	}

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

