/*
 * EventFormat.hh
 *
 *  Created on: May 2, 2014
 *      Author: rdunlop
 */

#ifndef EVENTFORMAT_HH_
#define EVENTFORMAT_HH_

//////////////////////////////////////////////////////////////////////
////															  ////
////  			List of Packet Type Identifiers					  ////
////                                                              ////
//////////////////////////////////////////////////////////////////////

//The first 4 bits of some 32-bit words contain a packet-type identifier.
//These can be used to ensure correct identification of data words and
//appropriate use of the words. An example of identifying a Header word type
// (The same method is used to get all packet-type identifiers):

//		Word I			Mask		Shift		Hex Result		Decimal result
//	0x8074A998	&	0xF0000000	>>	28		=	0x8			=		8

//A full list of packet types is listed here:
//	Packet Type			Packet Type				Name
//		(Hex)				(Dec)
//		0x8					8					Header word (Start of Event)
//		0x9					9					Channel Trigger ID word
//		0xA					10					Timestamp Upper bits word
//		0xB					11					Deadtime and Timestamp Lower bits word
//		0xC					12					Waveform
//		0xD					13					Unassigned
//		0xE					14					Trailer Word (End of Event)
//		0xF					15					Unassigned


//////////////////////////////////////////////////////////////////////
////															  ////
////  			List of Bit Masks and Bit Shifts				  ////
////                                                              ////
//////////////////////////////////////////////////////////////////////

//A full list of bit masks is listed here (See below for meanings):

//		Mask			Shift			Name
//	0x0F000000			24				Number of Filter Patterns
//	0x000E0000			21				Data Type
//	0x001FFF80			7				Address
//	0x00000078			3				Detector Type
//	0x00000007			0				Pile-Up Type
//	0x0FFFFFFF			0				PPG Pattern
//	0x7FFFFFFF			0				Master Filter ID
//	0x7FFFFFFF			0				Master Filter Pattern
//	0x0FFFFFFF			0				Channel Trigger ID
//	0x0FFFFFFF			0				Time Stamp Lower bits
//	0x00003FFF			0				Time Stamp Upper bits
//	0x0FFFC000			14				Deadtime
//	0x7C000000			26				K Value Lower bits
//	0x7C000000			26				K Value Upper bits
//	0x3FFFFFFF			0				Pulse Height Signal
//	0x3FFFFFFF			0				CFD Timing Signal



//////////////////////////////////////////////////////////////////////
////															  ////
////  				Definitions for HiPPOGRIF					  ////
////                                                              ////
//////////////////////////////////////////////////////////////////////


enum packetType {
	kHeader 			= 8,
	kChannelTrigger 	= 9,
	kLowerTimestamp		= 10,
	kDeadtime			= 11,
	kWaveform			= 12,
	kTrailer			= 14
};

//Header Mask and shift
const uint32_t PacketMask 				= 0xF0000000; //Header mask
const uint16_t PacketShift 				= 28;

//////////////////////    Filter Patterns     /////////////////////////
//Number of Filter patterns provided in word I as bits 24-27.
const uint32_t NFilterPatternsMask 		= 0x0F000000;
const uint16_t NFilterPatternsShift 	= 24;
// Results:
// 1 = 1 pattern word
// 2 = 2 pattern word
// 3 = 3 pattern word


//////////////////////       Data Type	      /////////////////////////
//Data Type provided in word I as bits 21-23.
const uint32_t DataTypeMask		 	= 0x00E00000;
const uint16_t DataTypeShift 		= 21;
// Results:
// 1 = GRIF-16
// 2 = GRIF-4G
// 3 = GRIF-C Slave
// 4 = GRIF-C Master


//////////////////////        Address	      /////////////////////////
//The Address is provided in word I as bits 7 to 20. This indicates which channel on
//which the module has provided this event fragment
const uint32_t AddressMask			= 0x0003FFF0;// 0x001FFF80;
const uint16_t AddressShift			= 4;

//The properties can be extracted from the above word as follows
const uint32_t MasterMask			= 0x00003C00;
const uint16_t MasterShift			= 10;
const uint32_t SlaveMask			= 0x000003C0;
const uint16_t SlaveShift			= 6;
const uint32_t DigitizerMask		= 0x0000003F;
const uint16_t DigitizerShift		= 0;


//////////////////////     Detector Type     /////////////////////////
//Provided in word I as bits 3 to 6. Indicates which detector type has generated this
//event fragment and is used primarily in master filter decisions.
const uint32_t DetectorTypeMask		= 0x0000000F;
const uint16_t DetectorTypeShift	= 0;

//Results:
// 00 HPGe Clovers (Low Gain)
// 01 HPGe Clovers (High Gain)
// 02 SCEPTAR and ZDS
// 03 DANTE (Energy)
// 04 DANTE (TAC)
// 05 PACES
// 06 DESCANT
// 07 BGO for HPGe
// 08 BGO for DANTE

//////////////////////     Pile-up Type     /////////////////////////
//Indicates how many hits were recorded within the evaluation window, with the maximum
//being 3 hits in one window. The Pile-Up Type is provided in word I as bits 0-2.
const uint32_t PileupTypeMask		= 0x00000007;
const uint16_t PileupTypeShift  	= 0;
//Results:
// 1 = 1 Hit
// 2 = 2 Hits
// 3 = 3 Hits


//////////////////////      PPG Pattern     /////////////////////////
//The PPG patter is a recording of the Programmable Patter Generator status at the time
//that the threshold crossing occurred, and is provided in word II as 30 bits. The pattern
//represents, for example, if the beam were being delivered or if it was blocked for decay
//counting etc.
const uint32_t PPGPatternMask		= 0x0FFFFFFF;
const uint16_t PPGPatternShift  	= 0;


//////////////////////    Master Filter ID    /////////////////////////
//Provided in word III as 31 bits. The master filter ID is an event counter which is reset
//as the start of a run and increments by 1 each time a new event master filter condition
//is passed in the master filter algorithm in the Master GRIF-C. The Maximum is 2147483649
//above which the counter will wrap around.

const uint32_t MasterFilterIDMask   = 0x7FFFFFFF;
const uint16_t MasterFilterIDShift	= 0;


//////////////////////    Master Filter Patt    /////////////////////////
//The Filter Pattern which was passed in word 4 as 30 bits. If multiple filter conditions
//were passed by this fragment then there will be multiple Filter Pattern words written out.

const uint32_t MasterFilterPatternMask     = 0x7FFFFFFF;
const uint16_t MasterFilterPatternShift	= 0;


//////////////////////  Channel Trigger ID  /////////////////////////
//The Channel Trigger ID is provided in word V as the 28 lower bits. The Channel Trigger
//ID is event counter which is reset at the start of the run and increments by 1 each time
//a new threshold crossing occurs for this channel on the GRIF-16 or GRIF-4G. The word type
//is identified in the 4 upper bits as type 9 (header).
const uint32_t ChannelTriggerIDMask = 0x0FFFFFFF;
const uint16_t ChannelTriggerIDShift= 0;


//////////////////////       Timestamp      /////////////////////////
//The timestamp is stored in two separate words as the lower 28 bits and 14 bits of two words,
//word VI and word VII, respectively. Word VI is the lower bits of the Timestamp and Word VII
//is the upper bits of the Timestamp. The type is identified in the 4 upper bits of both words
//as type 10 for the lower bits and 11 for the upper bits.
//Header Result:
// 10 = lower bits
// 11 = upper bits
const uint32_t TimestampHMask     	= 0x00003FFF;
const uint16_t TimestampHShift   	= 0;

const uint32_t TimestampLMask    	= 0x0FFFFFFF;
const uint16_t TimestampLShift   	= 0;
//The upper and lower bits can then be combined into the final 42 bit time stamp. The Timestamp
//is in units of 10 nanoseconds and has a resets after 509 days or after a GRIF-C power cycle.
//The 28 lower bits are also stored in the event trailer.


//////////////////////       DeadTime      /////////////////////////
//We aren't sure how we are going to deal with deadtime yet. The data format is as follows:
//The deadtime for each event is provided as bits 14-27 of word VIII. The type is identified
//in the 4 upper bits as type 11.
//Header Result: 11.
const uint32_t DeadTimeMask			= 0x0FFFFC00;
const uint16_t DeadTimeShift		= 14;
//Result
// ### = Deadtime in units of 10 ns with a maximum of 16383 ns.


//////////////////////       K-Values      /////////////////////////
//The 10 bits of the K value are provided in words VIII and IX as bits 26-30.
const uint32_t KValueMask			= 0x7C000000;
const uint16_t KValueShift			= 26;
//The upper and lower bits of the K value can then be combined to make the full K value. This is
//done in two steps by shifting the upper bits and adding the lower bits.


//////////////////////     Pulse Height    /////////////////////////
//The pulse height signal is provided in word VIII as the 26 lower bits, which represent Pulse
//height 1. The maximum is 67108863 and is in units of ADC channels. For Pile-Up events the charge
//value of the secondary interactions are given in words X and XII.
const uint32_t PulseHeightMask		= 0x03FFFFFF;
const uint32_t PulseHeightShift 	= 0;


//////////////////////   CFD Timing Signal  /////////////////////////
//The timing from a CFD algorithm is provided in word IX as the 26 lower bits. The max value is
//67108863 and is in units of 10 ns. For Pile-Up events the CFD timing values of the secondary
//interactions are given in words XI and XIII.
const uint32_t CFDTimingMask		= 0x03FFFFFF;
const uint32_t CFDTimingShift  		= 0;


//////////////////////     Event Trailer    /////////////////////////
//The Event Trailer is provided in word XIV and it indicates the end of the event fragment. The type
//is identified in the 4 upper bits as type 14.
//Header Result: 14
//The 28 lower bits of the timestamp is repeated in the event trailer. This can be used as an
//additional check to ensure the event is not corrupted.
const uint32_t EventTrailerMask		= 0x0FFFFFFF;
const uint32_t EventTrailerShift	= 0;


//////////////////////     WaveForm Data    /////////////////////////
//The Waveform data is provided in multiple words, the number of which depends on the waveform length.
//Waveform data words can be identified by their type which is in the 4 upper bits of each word as
//type 0. The waveform Data values are in units of ADC bins.
//Header Result: 12
const uint32_t WaveFormMask			= 0xF0000000;
const uint32_t WaveFormShift		= 28;


#endif /* EVENTFORMAT_HH_ */
