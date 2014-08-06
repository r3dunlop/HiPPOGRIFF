/*
 * TFragmentWriter.hh
 *
 *  Created on: Jul 19, 2014
 *      Author: rdunlop
 */

#include<string>
#include"TFile.h"
#include"TTree.h"
#include"TFragmentQueue.hh"

#ifndef TFRAGMENTWRITER_HH_
#define TFRAGMENTWRITER_HH_

class TFragmentWriter{
public:
	TFragmentWriter(std::string,TFile*, TTree*);
	~TFragmentWriter(){};

public:
	bool FillTree();

private:
	std::string QName;
	void* fLeaf = nullptr;

	TTree* fTree;

	//increase maximum tree size to 10GB
	static const Long64_t GByte = 1073741824L;

	static const int BufferSize = 1024000;
	static const Int_t split = 99;

};



#endif /* TFRAGMENTWRITER_HH_ */
