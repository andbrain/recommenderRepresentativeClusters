#ifndef SYNCER_H
#define SYNCER_H

#include <iostream>
#include <vector>
#include "representative.h"
#include "graph.h"

using namespace std;

class syncer
{
public:
	syncer(Graph* ratings, string clusterPrefix, string reprPrefix);
	~syncer();
	void Process(int nMulti);
	vector<int> GetUsers();
	vector<int> GetUserItems(int userIndex);
	double GetEstimRating(int userId, int itemId);
	void SetMode(int mode);
private:
	Graph *mRatings; // user ratings
	string mClusterPrefix, mReprPrefix;
	vector<Representative*> *mRepr;
	vector<int> mUsers;
	int mMode; // [0 => average, 1 => median]

	vector<double> GetListOfRatings(int userId, int itemId);
};

#endif