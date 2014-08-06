/*
 * TGriffinFragmentChecker.hh
 *
 *  Created on: Jul 17, 2014
 *      Author: rdunlop
 */

#ifndef TGRIFFINFRAGMENTCHECKER_HH_
#define TGRIFFINFRAGMENTCHECKER_HH_

#include <string>

#include "TFragmentQueue.hh"
#include "TGriffinFragment.hh"
#include "Settings.hh"

class TGriffinFragmentChecker {
public:
	TGriffinFragmentChecker(){};
	~TGriffinFragmentChecker(){};

	void Check(std::string);

private:
	bool CheckFlags();
	bool CheckDataType();
	bool CheckTrailer();
	bool CheckChannelTriggerID();
	bool CheckPileupHits();

	void BadFrag();
	void BadFrag(std::string);

	void Clear();
	void DataDump(uint32_t*, uint32_t);

	bool badFrag_flag = false; //Can't be a field if we want to multi-thread

};



#endif /* TGRIFFINFRAGMENTCHECKER_HH_ */
