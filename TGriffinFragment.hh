/*
 * TGriffinFragment.hh
 *
 *  Created on: Jun 28, 2014
 *      Author: rdunlop and pcbender
 */

#ifndef TGRIFFINFRAGMENT_HH_
#define TGRIFFINFRAGMENT_HH_

#if __APPLE__
#ifdef __CINT__
#undef __GNUC__
typedef char __signed;
typedef char int8_t;
#endif
#endif

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <utility>
#include <stdint.h>

#include "TObject.h"
#include "TString.h"

//This Class contains GRIFFIN specific fragment information
//This is done for better integration into GRSISpoon
class TGriffinFragment : public TObject {
public:
	TGriffinFragment();
	~TGriffinFragment(){ std::cout << "Deleting fragment" << std::endl;}

	uint16_t hitNumber;
	uint32_t ppg;
	uint16_t deadTime;
	uint16_t detectorType;
	uint16_t numberFilters;
	uint32_t timeStampLow;          //
	uint16_t timeStampHigh;         //
	uint32_t filterId;
	uint32_t filterPattern;
	uint32_t chargeCal;             //
	uint32_t timeToTrig;
	uint16_t kHigh;
	uint16_t kLow;
	uint16_t k;
	uint16_t numberPileups;

	uint64_t midasTimeStamp;		//
	uint32_t midasId;				//
	uint32_t triggerId;				//
	uint32_t fragmentId;			//
	uint32_t triggerBitPattern;		//

	uint32_t channelAddress;		//
	uint32_t cfd;
	uint32_t charge;

	uint64_t timeStamp;

	std::vector<uint32_t> wavebuffer;

	short odbType;                 //

	std::string channelName;    //
	int channelNumber;           //


	short dataType;
	std::string digitizerType;  //

//void clear();
	void Clear(const Option_t * /* option */="");                //!
//	void Print(const Option_t * /* option */="") const;          //! //Need to re-institute this function


	void SetTimeStamp();         								//!

	//in order to use root sort function when the fragments are in arrays
	//puts newset id at the beginning of the array, older ids at the end.
	bool IsSortable() const { return kTRUE; };             		//!
//	int Compare(const TObject * obj) const;      //! compare by trigger and fragment id




//Here we keep the non-static (not written into root) members
//These are mostly for event checking
private:
	bool header_flag;					//!
	bool channelTrigger_flag;			//!
	bool deadtime_flag;					//!
	bool trailer_flag;					//!
	bool badfrag_flag;					//!

	ClassDef(TGriffinFragment,1)		//

};


#endif /* TGriffinFragment_HH_ */
