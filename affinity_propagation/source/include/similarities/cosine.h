#ifndef COSINE_H
#define COSINE_H

#include <iostream>
#include <string>
#include "similarity_base.h"
using namespace std;

class cosine: public similarity_base
{
public:
	cosine();
	~cosine();
	int Process();
protected:
	Graph *mCounter;

private:
	int AccumulateRatings();
	int GenerateSimUserMatrix();
};


#endif