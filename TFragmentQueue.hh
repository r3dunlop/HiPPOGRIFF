/*
 * TFragmentQueue.hh
 *
 *  Created on: Jul 17, 2014
 *      Author: pcbender
 */

#ifndef TFRAGMENTQUEUE_HH_
#define TFRAGMENTQUEUE_HH_

#include <stdio.h>
#include <queue>
#include <map>
#include "Multiton.hh"

#ifndef __CINT__
#define _GLIBCXX_USE_NANOSLEEP 1
#include <thread>
#include <mutex>
#endif

#include"TObjArray.h"
#include"TStopwatch.h"

#include "TGriffinFragment.hh"

class TFragmentQueue : public Multiton<TFragmentQueue>, public TObject {

	public:
		TFragmentQueue();
		virtual ~TFragmentQueue();

	private:
		std::queue<TGriffinFragment*> fFragmentQueue;
		int fFragsInQueue;

		TObjArray *fFragmentStorage;

		void StatusUpdate();
		bool fStatusUpdateOn;

		bool fStop;

		int fragments_in;
		int fragments_out;

		TStopwatch *sw;
		void ResetRateCounter();

		unsigned int fTotalFragsIn;
		unsigned int fTotalFragsOut;

		std::map<int,int> fragment_id_map;


#ifndef __CINT__
#ifndef NO_MUTEX
	public:
		static std::mutex All;
		static std::mutex Sorted;
#endif
#endif

	public:
		void Add(TGriffinFragment*);

		TGriffinFragment *Get();
		TGriffinFragment *GetFront();

		void Pop();
		TGriffinFragment *PopFragment();

		int Size();

		void StartStatusUpdate();
		void StopStatusUpdate();
		void CheckStatus();

		unsigned int GetTotalFragsIn() { return fTotalFragsIn;}
		unsigned int GetTotalFragsOut()	{	return fTotalFragsOut;}

		bool Running() { return !fStop;}
		void Stop() { fStop = true;}

		void Clear(Option_t *opt = "");

		void AddToQueue(TGriffinFragment*);

	public:
		ClassDef(TFragmentQueue,0);
};


#endif /* TFRAGMENTQUEUE_HH_ */
