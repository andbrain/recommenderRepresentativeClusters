#ifndef SIMILARITY_BASE_H
#define SIMILARITY_BASE_H

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include "types.h"
#include "mat.h"

#define MAX_RATING 5

using namespace std;

class similarity_base
{
public:
	similarity_base();
	~similarity_base();
	
	void SetMatrix(mat *ratings, mat *sim);
	virtual int Process() = 0;
	mat* GetMatrix();
protected:
	mat *mRatings, *mSim;
	int mElementsSize;

	void LoadSimTypes();
	void GetSimType(string sim_name);
	int SetPreferencesMedian(vector<double> *tmpS);
};

#endif