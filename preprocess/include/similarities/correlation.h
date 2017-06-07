#ifndef CORRELATION_H
#define CORRELATION_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "similarity_base.h"
using namespace std;

class correlation: public similarity_base
{
public:
	correlation();
	~correlation();
	int Process();
protected:
	vector<double> *mNorma;
	vector<double> *mMean;

private:
	int GenerateSimUserMatrix();
	int CalculateNorma();
	int CalculateMean();
	double setCik(int fIndex, int sIndex);
};


#endif