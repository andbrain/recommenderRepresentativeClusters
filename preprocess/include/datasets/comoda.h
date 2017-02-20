#ifndef COMODA_H
#define COMODA_H

#include <iostream>
#include <string>
#include "dataset_base.h"
#include "util.h"
#include "graph.h"

using namespace std;

class comoda: public Dataset_Base
{
public:
	comoda(string path, string sim_function);
	~comoda();
protected:
	int LoadRatings();
};


#endif