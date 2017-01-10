#ifndef ML2K_H
#define ML2K_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include "dataset_base.h"
#include "util.h"
#include "graph.h"

#define MAX_RATING 5

using namespace std;

class ml2k: public Dataset_Base
{
public:
	ml2k(string path);
	~ml2k();
	int Process();
	Graph* GetMatrix();
private:
	string mRatingFile;
	fstream mFs;
	Graph *mRatings, *mSim, *mCounter, mMovies;
	void Initialize();
	int LoadRatings();
	int AccumulateRatings();
	int GenerateSimUserMatrix();
	int SetPreferencesMedian(vector<double> *tmpS);
	void CreateTrainFile(double percTrain);
};


#endif