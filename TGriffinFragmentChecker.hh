/*
 * TGriffinFragmentChecker.hh
 *
 *  Created on: Jul 17, 2014
 *      Author: rdunlop
 */

#ifndef TGRIFFINFRAGMENTCHECKER_HH_
#define TGRIFFINFRAGMENTCHECKER_HH_

#include <string>
#include <exception>

#include "TFragmentQueue.hh"
#include "TGriffinFragment.hh"
#include "Settings.hh"

class MyException {
public:
	MyException(const char* failure,uint32_t val):failureMode(failure),value(val){}
	MyException(uint32_t val,const char* failure):failureMode(failure),value(val){}

	const char* failureMode;
	const uint32_t value;

};

class TGriffinFragmentChecker {
public:
	TGriffinFragmentChecker(){};
	~TGriffinFragmentChecker(){};

	void Check(std::string);

private:
	inline bool CheckFlags();
	inline bool CheckDataType(TGriffinFragment*);
	inline bool CheckTrailer();
	inline bool CheckChannelTriggerID();
	inline bool CheckPileupHits();

	void BadFrag();
	void BadFrag(std::string);

	void Clear();
	void DataDump(uint32_t*, uint32_t);

	bool badFrag_flag = false; //Can't be a field if we want to multi-thread

};



#endif /* TGRIFFINFRAGMENTCHECKER_HH_ */
