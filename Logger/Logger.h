/************************************************************************
*
*   Description: face detection
*
*   Author & Data: JY Liu, 2015/12/26
*
************************************************************************/

#pragma once

#include <iostream>
using namespace std;
#include <string>

class Logger{
	string logFilename;
public:
	Logger(string logFilename);
	~Logger();
};

//exe -> dll?