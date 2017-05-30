#ifndef AP_H
#define AP_H

#include <iostream>
#include <unordered_map>
#include <map>
#include <cmath>
#include <algorithm>

#include <ctime>
#include <sys/time.h>

#include "graph.h"
#include "mat.h"

using namespace std;

struct PairValue
{
	double index;
	int freq;
};
	
class AP
{
public:
	AP(int iterations, double lambda, int elements);
	~AP();
	void SetSimMatrix(mat* graph);
	void SetRatings(Graph* graph);
	void Process();
private:
	mat *mS, *mR, *mA, *mE; 
	Graph *mRatings;
	int mIter, mElements;
	double mLambda;
	void AffinityPropagation();
	void PrintCluster();
	void OutputClusters(map<int,vector<int>> *clusters);
	void UpdateResponsability();
	void UpdateAvailability();
	
	map<int, map<int, vector<double>> > AccumulateRatings(map<int,vector<int>> *clusters);
	void CalculateRepresentative(map<int,vector<int>> *clusters);
	void MakeRepresentativeByFrequency(map<int, map<int, vector<double>>> *accumList);
	void MakeRepresentativeByMean(map<int, map<int, vector<double>>> *accumList, map<int,vector<int>> *clusters);
};

#endif