/*
 * MidasEventParser.hh
 *
 *  Created on: Jun 28, 2014
 *      Author: rdunlop
 */

#ifndef MIDASEVENTPARSER_HH_
#define MIDASEVENTPARSER_HH_

#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <map>
#include <Set>
#include <cmath>
#include <stdio.h>
#include <stddef.h>

#include "TFile.h"
#include "TH1F.h"

#include "EventFormat.hh"
#include "Settings.hh"
#include "TGriffinFragment.hh"
#include "TFragmentQueue.hh"

#include "MidasInterface/include/TMidasFile.h"
#include "MidasInterface/include/TMidasEvent.h"

class MidasEventParser {
public:
	MidasEventParser(TFile*);
	~MidasEventParser();

	bool Parse(uint32_t*,uint32_t, uint32_t, uint64_t);

	inline void SetNFilterPatterns(uint32_t&,TGriffinFragment*);
	inline void SetDataType(uint32_t&,TGriffinFragment*);
	inline void SetAddress(uint32_t&,TGriffinFragment*);
	inline void SetDetectorType(uint32_t&,TGriffinFragment*);
	inline void SetPileupType(uint32_t&,TGriffinFragment*);
	inline void SetPPGPattern(uint32_t&,TGriffinFragment*);
	inline void SetMasterFilterID(uint32_t&,TGriffinFragment*);
	inline void SetMasterFilterPattern(uint32_t &,TGriffinFragment*);
	inline void SetChannelTriggerID(uint32_t&,TGriffinFragment*);
	inline void SetLowerTimestamp(uint32_t&,TGriffinFragment*);
	inline void SetUpperTimestamp(uint32_t&,TGriffinFragment*);
	inline void SetDeadTime(uint32_t&,TGriffinFragment*);
	inline void SetLowKBits(uint32_t&,TGriffinFragment*);
	inline void SetHighKBits(uint32_t&,TGriffinFragment*);
	inline void SetPulseHeight(uint32_t&,TGriffinFragment*);
	inline void SetCFDTiming(uint32_t&,TGriffinFragment*);
	inline void SetWaveForm(uint32_t&,TGriffinFragment*);

	void CheckTrailerWord(uint32_t&,TGriffinFragment*);

	void Clear();

	inline bool IsGoodFrag();
	inline bool IsBadFrag();

	uint32_t GetNBadEvents(){return nBadEvents;}
	uint32_t GetNEvents(){return nEvents;}
	uint16_t GetTotalDeadTime(){return totalDeadTime;}
	uint64_t GetTotalTime(){return (timestamp - firstTime);}
	double GetLiveFraction(){return (1.0-(double)(totalDeadTime)/((double)(timestamp - firstTime)));}

	uint16_t GetPileupType(){
		return pileupType;
	}

private:
	TFile* fRootFile;

	bool header_flag;			//Has been put into TGFrag
	bool channelTrigger_flag;	//Has been put into TGFrag
	bool deadtime_flag;			//Has been put into TGFrag
	bool trailer_flag;			//Has been put into TGFrag

	uint32_t mSize;
	uint32_t* dataword;

	//I only want properties of Hits in here.
	//Need to rewrite so that Process events contains most of this information and decodes it into the minimal event information.
	uint16_t nFilterPatterns = 0;
	uint16_t dataType = 0;
	uint16_t address = 0;
	uint16_t mAddress = 0;
	uint16_t sAddress = 0;
	uint16_t cAddress = 0;
	uint16_t detectorType = 0;
	uint16_t pileupType = 0;
	uint32_t PPGPattern = 0;
	uint32_t masterFilterID = 0;
	uint32_t masterFilterPattern = 0;
	uint32_t channelTriggerID = 0;
	uint32_t lowTimestamp = 0;
	uint16_t highTimestamp = 0;
	uint64_t timestamp = 0;
	uint16_t deadTime = 0;
	uint16_t highKbits = 0;
	uint16_t lowKbits = 0;
	std::vector<uint16_t> KValue;
	std::vector<uint32_t> pulseHeight;
	std::vector<uint32_t> CFDTiming;
	std::vector<uint32_t> waveformWords;

	uint32_t masterFilterID_check = 0;
	uint32_t channelTriggerID_check[16384];

	//Counters
	uint16_t nWaveFormWords = 0;
	uint32_t nBadEvents 	= 0;
	uint32_t nBadPileups 	= 0;
	uint32_t nEvents 		= 0;
	uint64_t firstTime 		= 0;
	uint16_t totalDeadTime 	= 0;

	bool endOfCycleFlag = false; //A new cycle reGets counters so need to figure out how to deal with this in the checker

	bool lowTimestamp_flag = false;
	bool highTimestamp_flag = false;
	bool lowKbits_flag = false;
	bool highKbits_flag = false;
	bool badFrag_flag = false;		//Has been put into TGFrag
	bool firstevent_flag = true;

	void GetTimestamp();
	void ClearFlags();
	void GoodFrag();
	void BadFrag();
	void BadFrag(std::string);
	void WrongPacket(uint32_t&,std::string);

private:

	inline void DataDump(uint32_t*, uint32_t);

	TH1F *hPulseHeight;
	TH1F *hCFD;
	TH1F *hTimeStamp;
	TH1F *hAddress;
};

#endif /* MIDASEVENTPARSER_HH_ */
