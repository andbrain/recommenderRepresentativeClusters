#ifndef DATASET_BASE_H
#define DATASET_BASE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include "graph.h"

#define MAX_RATING 5

using namespace std;

class Dataset_Base //interface for dataset's
{
public:
	Dataset_Base(string base_path);
	virtual ~Dataset_Base(); //let destructor enable for children classes
	int Process(); //pure virtual function for processing dataset
	Graph* GetMatrix();
	Graph* GetRatings();
protected:
	string mPath;
	fstream mFs;
	int mQtdMovies;
	Graph *mRatings, *mSim;
	void Initialize();
	int SetPreferencesMedian(vector<double> *tmpS);
	void CreateTrainFile(double percTrain);
	virtual int LoadRatings() = 0;
};

#endif