#ifndef AVERAGE_H
#define AVERAGE_H

#include <iostream>
#include <string>
#include "similarity_base.h"
using namespace std;

class average: public similarity_base
{
public:
	average();
	~average();
	int Process();
protected:
	// Graph *mCounter;

private:
	int AccumulateRatings();
	int GenerateSimUserMatrix();
};


#endif