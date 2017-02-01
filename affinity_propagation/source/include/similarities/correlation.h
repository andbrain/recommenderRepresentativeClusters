#ifndef CORRELATION_H
#define CORRELATION_H

#include <iostream>
#include <string>
#include "similarity_base.h"
using namespace std;

class correlation: public similarity_base
{
public:
	correlation();
	~correlation();
	int Process();
protected:
	Graph *mCounter;

private:
	int AccumulateRatings();
	int GenerateSimUserMatrix();
};


#endif