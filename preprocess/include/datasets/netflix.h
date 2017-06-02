#ifndef NETFLIX_H
#define NETFLIX_H

#include <iostream>
#include <string>
#include "dataset_base.h"
#include "util.h"
#include "graph.h"

using namespace std;

class netflix: public Dataset_Base
{
public:
	netflix(string path, string sim_function, int based);
	~netflix();
protected:
	int LoadRatings();
};


#endif