#ifndef AP_H
#define AP_H

#include <iostream>
#include <unordered_map>
#include <map>
#include <cmath>
#include <algorithm>
#include "graph.h"

using namespace std;

struct PairValue
{
	double index;
	int freq;
};
	
class AP
{
public:
	AP(int iterations, double lambda);
	~AP();
	void SetSimMatrix(Graph* graph);
	void SetRatings(Graph* graph);
	void Process();
private:
	Graph *mS, *mR, *mA, *mE, *mRatings; 
	int mIter;
	double mLambda;
	void AffinityPropagation();
	void PrintCluster();
	void OutputClusters(map<int,vector<int>> *clusters);
	void UpdateResponsability();
	void UpdateAvailability();
	
	void CreateTrainFile(int *users, int size, map<int,vector<int>> *clusters, double percTrain);
	
	map<int, map<int, vector<double>> > AccumulateRatings(map<int,vector<int>> *clusters);
	void CalculateRepresentative(map<int,vector<int>> *clusters);
	void MakeRepresentativeByFrequency(map<int, map<int, vector<double>>> *accumList);
	void MakeRepresentativeByMean(map<int, map<int, vector<double>>> *accumList);
};

#endif