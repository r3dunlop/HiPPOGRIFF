/*
 * TFragmentQueue.cc
 *
 *  Created on: Jul 17, 2014
 *      Author: pcbender
 */

#include "TFragmentQueue.hh"

std::mutex TFragmentQueue::All;
std::mutex TFragmentQueue::Sorted;

ClassImp(TFragmentQueue)

TFragmentQueue::TFragmentQueue()	{
	//printf(DRED "\n\tFragment Queue Created." RESET_COLOR "\n");
	fFragsInQueue = 0;

	sw = new TStopwatch();
	sw->Start();

	fStop = false;

	Clear();

	//StartStatusUpdate();

}

TFragmentQueue::~TFragmentQueue()	{	}


void TFragmentQueue::Clear(Option_t *opt)	{
	bool locked =false;
	if(!fFragmentQueue.empty())	{
		while(!TFragmentQueue::All.try_lock())	{
			//do nothing
		}
		locked = true;
	}

	if(fFragsInQueue != 0)	{
//		if(strncmp(opt,"force",5))	{
		//	printf(RED "\n\tWarning, discarding %i Fragemnts!" RESET_COLOR  "\n",fFragsInQueue);
			while(!fFragmentQueue.empty()){
				fFragmentQueue.pop();
			}
			fFragsInQueue = 0;
//		}
//		else	{
//			printf(RED "\n\tCan not reset Q Counters; %i Fragments still in Queue!!" RESET_COLOR  "\n",fFragsInQueue);
//			return;
//		}
	}

	fragments_in  = 0;
	fragments_out = 0;

	fTotalFragsIn = 0;
	fTotalFragsOut = 0;

	sw->Reset();

	if(locked)
		TFragmentQueue::All.unlock();
	return;
}


void TFragmentQueue::StartStatusUpdate()	{
	fStatusUpdateOn = true;

	std::thread statusUpdate(&TFragmentQueue::StatusUpdate, this);
	statusUpdate.detach();

}

void TFragmentQueue::StopStatusUpdate()	{
	fStatusUpdateOn = false;
}

void TFragmentQueue::Add(TGriffinFragment *frag)	{

    //when we move to multithreaded parsing, these three lines will
    //need to move inside the lock.  pcb.
	fragment_id_map[frag->triggerId]++;
	frag->fragmentId = fragment_id_map[frag->triggerId];

		while(!TFragmentQueue::Sorted.try_lock())	{
			//do nothing
		}

		fFragmentQueue.push(frag);

		fTotalFragsIn++;
		fFragsInQueue++;
		fragments_in++;
		//sorted.unlock();

		TFragmentQueue::Sorted.unlock();

	//printf("Adding frag:\t%i\tNumber in Q = %i\n",frag->MidasId,fFragsInQueue);
}


TGriffinFragment *TFragmentQueue::Get()	{

    //std::unique_lock<std::mutex> sorted(Sorted,std::defer_lock);
    //sorted.lock();
	while(TFragmentQueue::Sorted.try_lock())	{
		//do nothing
	}


	TGriffinFragment *frag = (fFragmentQueue.back());

    	TFragmentQueue::Sorted.unlock();
	//printf("\tGetting frag:\t%i\tNumber in Q = %i\n",frag->MidasId,fFragsInQueue);
	return frag;
}

void TFragmentQueue::Pop()	{
    //std::unique_lock<std::mutex> sorted(Sorted,std::defer_lock);
    //sorted.lock();
	while(!TFragmentQueue::Sorted.try_lock())	{
		//do nothing
	}

	TGriffinFragment *frag = (fFragmentQueue.front());
	fFragmentQueue.pop();
	fFragsInQueue--;
	fragments_out++;
	//fTotalFragsOut++;
	TFragmentQueue::Sorted.unlock();
	delete frag;
}

TGriffinFragment *TFragmentQueue::PopFragment()
{
	//std::unique_lock<std::mutex> sorted(Sorted,std::defer_lock);
	//sorted.lock();
	while(!TFragmentQueue::Sorted.try_lock())	{
		//do nothing
	}

	TGriffinFragment *frag = fFragmentQueue.front();
	if(frag)	{
		fFragmentQueue.pop();
		fFragsInQueue--;
		fragments_out++;
		fTotalFragsOut++;
	}
    TFragmentQueue::Sorted.unlock();
	return frag;
}

int TFragmentQueue::Size()	{
	return fFragsInQueue;
}

void TFragmentQueue::CheckStatus()	{
	//std::unique_lock<std::mutex> all(All,std::defer_lock);
	//all.lock();
	while(!TFragmentQueue::All.try_lock())	{
		//do nothing
	}


//	printf( BLUE   "# Fragments currently in Q = %d" RESET_COLOR "\n",Size());
//	printf( DGREEN "# Fragments currently in T = %d" RESET_COLOR "\n",RootIOManager::instance()->TreeSize());

//	printf( BLUE   "# Total Fragments put in Q     = %d" RESET_COLOR "\n",fTotalFragsIn);
//	printf( DGREEN "# Total Fragments taken from Q = %d" RESET_COLOR "\n",fTotalFragsOut);

	TFragmentQueue::All.unlock();
	return;
}

void TFragmentQueue::StatusUpdate()	{

	float time = 0;
	float frag_rate_in = 0;
	float frag_rate_out = 0;

	 //std::unique_lock<std::mutex> all(All,std::defer_lock);


	while(fStatusUpdateOn)	{
		//printf("Fragments in que: %i\n",frag_q_ptr->Size());
		time = sw->RealTime();
		frag_rate_in = fragments_in/time;
		frag_rate_out = fragments_out/time;
		while(!TFragmentQueue::All.try_lock()){
			//do nothing
		}

//		printf(BLUE "\n\tfrags rate in  = %.2f/sec, nqueue = %d\n" RESET_COLOR,frag_rate_in, Size());
//		printf(DGREEN "\tfrags rate out = %.2f/sec, ntree  = %d\n" RESET_COLOR,frag_rate_out, RootIOManager::instance()->TreeSize());
		TFragmentQueue::All.unlock();
//		TThread::ps();
		ResetRateCounter();
		sw->Start();
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	}
	//TThread::CleanUp();
}

void TFragmentQueue::ResetRateCounter()	{
	//std::unique_lock<std::mutex> all(All,std::defer_lock);
	//all.lock();
	while(!TFragmentQueue::All.try_lock())	{
		//do nothing
	}

	fragments_in	=	0;
	fragments_out	= 	0;
	TFragmentQueue::All.unlock();
}
void TFragmentQueue::AddToQueue(TGriffinFragment* ptr2frag){
	Add(ptr2frag);
}


