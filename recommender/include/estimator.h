#ifndef ESTIMATOR_H
#define ESTIMATOR_H

#include <iostream>
// #include <cstdlib>
// #include <time.h>
#include <cmath>
#include <vector>
#include "graph.h"

using namespace std;

class Estimator
{
public:
	Estimator();
	~Estimator();
	vector<double> Process(int exp = 1);
	void SetRatings(Graph *g);
	void SetUsers(map<int,int> *users);
	void SetItemClusters(map<int,map<int,double>> *movieClusters);
private:
	Graph *mRatings; // user ratings
	map<int,int> *mUsers; //<user, cluster>
	map<int,map<int,double>> *mMovieReprCluster; //<movie, <cluster,rating>>

	vector<int> RandomTestData(double perc);
	vector<int> RandomItems(int userIndex, double perc);
};

#endif