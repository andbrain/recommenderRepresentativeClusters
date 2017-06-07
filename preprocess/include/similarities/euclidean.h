#ifndef EUCLIDEAN_H
#define EUCLIDEAN_H

#include <iostream>
#include <string>
#include <cmath>
#include "similarity_base.h"
using namespace std;

class euclidean: public similarity_base
{
public:
	euclidean();
	~euclidean();
	int Process();
protected:
	// Graph *mCounter; //accumulate diffs between ratings

private:
	int AccumulateRatings();
	int GenerateSimUserMatrix();
	// unordered_map<int,int> GetDistinctElements(Vertex *listX, Vertex *listY);
};


#endif