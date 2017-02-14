#ifndef DATASET_BASE_H
#define DATASET_BASE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include "graph.h"
#include "similarity_base.h"
#include "similarities/average.h"
#include "similarities/cosine.h"
#include "similarities/correlation.h"
#include "similarities/euclidean.h"
#include "similarities/loglikelihood.h"

using namespace std;

class Dataset_Base //interface for dataset's
{
public:
	Dataset_Base(string base_path, string simFunction);
	virtual ~Dataset_Base(); //let destructor enable for children classes
	int Process(); //pure virtual function for processing dataset
	Graph* GetMatrix();
	Graph* GetRatings();
protected:
	string mPath;
	fstream mFs;
	similarity_base *mSimFunction;
	unordered_map<string,Similarity_t> mSimilarities;
	int mQtdMovies; // must be updated in children classes
	Graph *mRatings, *mSim; // must be updated in children classes

	void Initialize(Similarity_t simType);
	void LoadSimTypes();
	Similarity_t GetSimType(string sim_name);
	virtual int LoadRatings() = 0;
};

#endif