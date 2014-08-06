/*
 * Settings.hh
 *
 *  Created on: Apr 24, 2014
 *      Author: rdunlop
 */

#ifndef SETTINGS_HH_
#define SETTINGS_HH_

#include "TEnv.h"
#include <string>
#include <iostream>
#include <stddef.h>

class Settings{
private:
    static bool instanceFlag;
    static Settings *single;
    Settings()
    {
        //private constructor
    }
public:
    static Settings* GetInstance();
    void method();
    ~Settings();

public:
	void Print();
	bool Read(const char *);

	bool GetCyclesFlag(){return cycles_flag;};
	bool GetErrorKillFlag(){return errorKill_flag;};
	uint16_t GetMaxEventNumber(){return maxEventNumber;};

	uint16_t verb = 0;
	TEnv* env = nullptr;

private:
	bool goodHPGe_flag[16];
	bool cycles_flag = false;
	bool errorKill_flag = true;
	uint32_t maxEventNumber = 0;

};


#endif /* SETTINGS_HH_ */
