#ifndef SIMILARITY_BASE_H
#define SIMILARITY_BASE_H

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include "types.h"
#include "mat.h"

#define MAX_RATING 5

using namespace std;

class similarity_base
{
public:
	similarity_base();
	virtual ~similarity_base();
	
	void SetMatrix(mat *ratings);
	void SetSecElementsSize(int secElementSize);
	virtual int Process() = 0;
	mat* GetMatrix();
protected:
	mat *mRatings, *mSim;
	int mSecElementSize;

	void LoadSimTypes();
	void GetSimType(string sim_name);
};

#endif