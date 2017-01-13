#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include "graph.h"
#include "util.h"

using namespace std;

class Parser
{
public:
	Parser(string ratingsPath, string clusterPath, string reprClusterPath);
	~Parser();
	void Process();

	/* data */
private:
	string mRatingPath, mClusterPath, mReprClusterPath;
	Graph *mRatings; // user ratings
	map<int,int> mUsers; //<user, cluster>
	map<int,map<int,double>> mMovieReprCluster; //<movie, <cluster,rating>>
	fstream mFs;

	void ReadRatingsList();
	void ReadClusters();
	void ReadRepresentatives();
	void Estimation();
};

#endif