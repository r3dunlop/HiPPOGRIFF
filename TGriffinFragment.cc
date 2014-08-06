/*
 * TGriffinFragment.cc
 *
 *  Created on: Jun 27, 2014
 *      Author: rdunlop and pcbender
 */
#include "TGriffinFragment.hh"

ClassImp(TGriffinFragment)

TGriffinFragment::TGriffinFragment() :
	hitNumber(0),
	ppg(0),
	deadTime(0),
	detectorType(9999),
	numberFilters(0),
	timeStampLow(-1),
	timeStampHigh(-1),
	filterId(0),
	filterPattern(0),
	chargeCal(0.0),
	timeToTrig(-9999),
	kHigh(0),
	kLow(0),
	k(0),
	numberPileups(0),
	midasTimeStamp(0),
	midasId(0),
	triggerId(0),
	fragmentId(0),
	triggerBitPattern(0),
	channelAddress(-1),
	cfd(-1),
	charge(-1),
	timeStamp(-1),
	odbType(0),
	channelName("XXXXXXXXXX"),
	channelNumber(-1),
	dataType(0),
	digitizerType("XXXXXXXXXXXXX"),
	header_flag(false),
	channelTrigger_flag(false),
	deadtime_flag(false),
	trailer_flag(false),
	badfrag_flag(false) {

	if (!wavebuffer.empty())
		wavebuffer.clear();
}

void TGriffinFragment::SetTimeStamp(){
	timeStamp = (timeStampHigh << 28) | timeStampLow;
}

void TGriffinFragment::Clear(const Option_t* )
//void TGriffinFragment::clear()
{
   odbType = 0;
   channelName = "XXXXXXXXXX";
   channelNumber = -1;
   timeToTrig = -9999;
   chargeCal = 0.0;
   timeStampLow = -1;
   timeStampHigh = -1;
   hitNumber = 0;
   ppg = 0;
   deadTime = 0;
   detectorType = -9999;
   numberFilters = 0;
   filterId = 0;
   filterPattern = 0;
   kHigh = 0;
   kLow = 0;
   k = 0;
   numberPileups = 0;
   dataType = 0;
   digitizerType = "XXXXXXXXXXXXX";
   midasTimeStamp = 0;
   midasId = 0;
   triggerId = 0;
   fragmentId = 0;
   triggerBitPattern = 0;
   channelAddress = -1;
   cfd = -1;
   charge = -1;
   timeStamp = -1;

   if (!wavebuffer.empty())
      wavebuffer.clear();

   //waveform.SetBit(TH1::kCanRebin);

}
