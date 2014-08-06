/*
 * TFragmentWriter.cc
 *
 *  Created on: Jul 19, 2014
 *      Author: rdunlop
 */

#include "TFragmentWriter.hh"


TFragmentWriter::TFragmentWriter(std::string QueueName, TFile* file, TTree* tree):QName(QueueName),fTree(tree){
	// Create one branch. If splitlevel is Set, event is a superbranch
	// creating a sub branch for each data member of the Fragment object.

	//I think this is causing the root issues. Name these differently based on the QName
	fTree->Branch("tgriffinfragment","TGriffinFragment", &fLeaf,BufferSize,split); //Put things in at the Event level
	fTree->BranchRef();
	fTree->SetMaxTreeSize(10*GByte);
}

bool TFragmentWriter::FillTree(){

	//Might be a better way to do this check so we don't have to be locking all the time
	//But also, maybe not
	if(TFragmentQueue::GetPtr(QName)->Size() == 0){
		return false;
	}

	#ifdef DEBUG
	std::cout << "Writing " << QName << std::endl;
	#endif

	//Might have to lock the leaf and tree from here to return?
	fLeaf = TFragmentQueue::GetPtr(QName)->GetFront();
	fTree->Fill();
	TFragmentQueue::GetPtr(QName)->Pop();

 //I believe this should delete the pointers to the GRIF frags that were
 //created on the heap in the parser. Unless I build histograms after this,
 //this should be the last place where the fragments are required.

	return TFragmentQueue::GetPtr(QName)->Size();//returns false if empty, true if not


}
