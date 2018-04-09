#ifndef REPRESENTATIVE_H
#define REPRESENTATIVE_H

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "util.h"

using namespace std;

class Representative
{
public:
	Representative(string clusterPath, string representativePath);
	~Representative();
	void Process();
	
private:
	string mClusterPath, mReprPath;
	map<int,int> mUsers; //<user, cluster>
	map<int,map<int,double>> mMovieReprCluster; //<movie, <cluster,rating>>
	fstream mFs;

	void ReadClusters();
	void ReadRepresentatives();
};

#endif