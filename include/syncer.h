#ifndef SYNCER_H
#define SYNCER_H

#include <iostream>
#include <vector>
#include "representative.h"

using namespace std;

class syncer
{
public:
	syncer();
	~syncer();
	
private:
	vector<Representative*> *mRepr;
};

#endif