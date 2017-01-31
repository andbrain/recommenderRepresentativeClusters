#ifndef SIMILARITY_BASE_H
#define SIMILARITY_BASE_H

#include <iostream>
#include <unordered_map>
#include "types.h"
#include "graph.h"
#include <algorithm>

#define MAX_RATING 5

using namespace std;

class similarity_base
{
public:
	similarity_base();
	~similarity_base();
	
	void SetMatrix(Graph *ratings, Graph *sim);
	void SetElementsSize(int elementsSize);
	virtual int Process() = 0;
	Graph* GetMatrix();
protected:
	Graph *mRatings, *mSim;
	int mElementsSize;

	void LoadSimTypes();
	void GetSimType(string sim_name);
	int SetPreferencesMedian(vector<double> *tmpS);
};

#endif