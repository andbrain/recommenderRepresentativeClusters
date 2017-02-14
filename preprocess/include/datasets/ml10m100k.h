#ifndef ML10M100K_H
#define ML10M100K_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "dataset_base.h"
#include "util.h"
#include "graph.h"

#define RATING_FILE "ratings4_1.dat"
// #define RATING_FILE "toy.dat"
#define MAX_RATING 5
using namespace std;

class ml10m100k: public Dataset_Base
{
public:
	ml10m100k(string path);
	~ml10m100k();
	int Process();
	Graph* GetMatrix();
private:
	fstream mFs;
	Graph *mRatings, *mSim, *mCounter, mMovies;
	void Initialize();
	int LoadRatings();
	int AccumulateRatings();
	int GenerateSimUserMatrix();
};


#endif