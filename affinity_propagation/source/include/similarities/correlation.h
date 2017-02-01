#ifndef CORRELATION_H
#define CORRELATION_H

#include <iostream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <map>
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
	map<int,double> mNorma;
	map<int,double> mMean;

private:
	int AccumulateRatings();
	int GenerateSimUserMatrix();
	int CalculateNorma();
	int CalculateMean();
	unordered_map<int,int> GetDistinctElements(Vertex *listX, Vertex *listY);
};


#endif