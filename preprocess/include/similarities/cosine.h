#ifndef COSINE_H
#define COSINE_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "similarity_base.h"
using namespace std;

class cosine: public similarity_base
{
public:
	cosine();
	~cosine();
	int Process();
protected:
	vector<double> *mNorma;

private:
	int GenerateSimUserMatrix();
	int CalculateNorma();
	double setCik(int fIndex, int sIndex);
};


#endif