#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include "graph.h"
#include "util.h"
#include "syncer.h"

using namespace std;

class Parser
{
public:
	Parser(string ratingsPath, string clusterPrefix, string reprPrefix, int n_multi_clusters);
	~Parser();
	void Process(string clusterPrefix, string reprPrefix);

	Graph* GetRatings();
	syncer* GetSyncer();

private:
	string mRatingPath;
	int mNmultiClusters;
	Graph *mRatings; // user ratings
	fstream mFs;
	syncer *mSync;
	void ReadRatingsList();
	void ReadRepresentatives(string clusterPrefix, string reprPrefix);
};

#endif