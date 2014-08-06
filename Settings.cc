/*
 * Settings.cc
 *
 *  Created on: Jun 6, 2014
 *      Author: rdunlop
 */
#include "Settings.hh"

//Might have to consider a mutex
bool Settings::instanceFlag = false;
Settings* Settings::single = NULL;
Settings* Settings::GetInstance()
{
    if(!instanceFlag)
    {
        single = new Settings();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

Settings::~Settings(){
	delete env;
    instanceFlag = false;

}

bool Settings::Read(const char* name){

	//Create configuration environment
	env = new TEnv(name);

	//Cycled data
	const char *cycleflagName = "Cycles";
	cycles_flag = env->GetValue(cycleflagName,false);

	//Read in if we should kill the code on an error
	const char* errorkill_flag_name = "ErrorKill";
	errorKill_flag = env->GetValue(errorkill_flag_name,true);

	//Read in the max event number (probably only going to be used in troubleshooting)
	const char* maxeventnumberName = "MaxEventNumber";
	maxEventNumber = env->GetValue(maxeventnumberName,0);

	const char* verbName = "Verbosity";
	verb = env->GetValue(verbName,0);


	//Read in HPGe detector ON/OFF flag
	for(int i = 0; i<16;i++){
		std::string s = "HPGe" + std::to_string(i) ;
		char const *pchar = s.c_str();
		goodHPGe_flag[i] = env->GetValue(pchar,true);
	}

	return true; //this will change for checks of file existence etc..


}


void Settings::Print(){

	//Print whether the data is in cycles mode
	std::cout << "CYCLES: ";
	if(cycles_flag == true)
		std::cout << "ON" << std::endl;
	else
		std::cout << "OFF" << std::endl;

	//Print error Killing flag
	std::cout << "Exit Program on an Error?: ";
	if(errorKill_flag == true)
		std::cout << "YES" << std::endl;
	else
		std::cout << "NO" << std::endl;

	//Print HPGe detector ON/OFF Flag
	for(int i = 0; i<16;i++){
		std::string s = "HPGe" + std::to_string(i) ;
		char const *pchar = s.c_str();

		if(goodHPGe_flag[i] == true)
			std::cout << pchar<<" is ON" << std::endl;
		else
			std::cout << pchar<<" is OFF" << std::endl;
	}

	//Print out the Maximum event number being sorted
	if(maxEventNumber > 0)
		std::cout << "Sorting the first " << maxEventNumber << " events" << std::endl;
	else
		std::cout << "Sorting all events" << std::endl;
}

