#ifndef AP_H
#define AP_H

#include <iostream>
#include <unordered_map>
#include <map>
#include <cmath>
#include "graph.h"

using namespace std;

class AP
{
public:
	AP(int iterations, double lambda);
	~AP();
	void SetSimMatrix(Graph* graph);
	void Process();
private:
	Graph *mS, *mR, *mA, *mE; 
	int mIter;
	double mLambda;
	void AffinityPropagation();
	void PrintCluster();
	void OutputClusters(map<int,vector<int>> *clusters);
	void UpdateResponsability();
	void UpdateAvailability();
	void CreateTrainFile(int *users, int size, map<int,vector<int>> *clusters, double percTrain);
};

#endif