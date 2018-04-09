#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include "graph.h"
#include "util.h"
#include "representative.h"

using namespace std;

class Parser
{
public:
	Parser(string ratingsPath, string clusterPrefix, string reprPrefix, int n_multi_clusters);
	~Parser();
	void Process();

	Graph* GetRatings();
	vector<Representative*>* GetRepresentatives();

private:
	string mRatingPath, mClusterPrefix, mReprPrefix;
	int mNmultiClusters;
	Graph *mRatings; // user ratings
	fstream mFs;
	vector<Representative*> *mRepr;

	void ReadRatingsList();
	void ReadRepresentatives();
};

#endif