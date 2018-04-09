#ifndef SYNCER_H
#define SYNCER_H

#include <iostream>
#include <vector>
#include "representative.h"

using namespace std;

class syncer
{
public:
	syncer(string clusterPrefix, string reprPrefix);
	~syncer();
	void Process(int nMulti);	
private:
	string mClusterPrefix, mReprPrefix;
	vector<Representative*> *mRepr;
};

#endif