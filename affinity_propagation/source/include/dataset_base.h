#ifndef DATASET_BASE_H
#define DATASET_BASE_H

#include <iostream>
#include "graph.h"

using namespace std;

class Dataset_Base //interface for dataset's
{
public:
	Dataset_Base(string base_path) { mPath = base_path; }
	virtual ~Dataset_Base() {}; //let destructor enable for children classes
	virtual int Process() = 0; //pure virtual function for processing dataset
	virtual Graph* GetMatrix() = 0;
	virtual Graph* GetRatings() = 0;
protected:
	string mPath;
};

#endif