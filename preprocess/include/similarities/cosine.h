#ifndef COSINE_H
#define COSINE_H

#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include "similarity_base.h"
using namespace std;

class cosine: public similarity_base
{
public:
	cosine();
	~cosine();
	int Process();
protected:
	// Graph *mCounter;
	map<int,double> mNorma;

private:
	int AccumulateRatings();
	int GenerateSimUserMatrix();
	int CalculateNorma();
	// unordered_map<int,int> GetDistinctElements(Vertex *listX, Vertex *listY);
};


#endif