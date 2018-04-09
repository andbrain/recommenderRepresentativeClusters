#ifndef REPRESENTATIVE_H
#define REPRESENTATIV_H

#include <iostream>
#include <map>
#include <fstream>

using namespace std;

class Representative
{
public:
	Representative();
	~Representative();
	
private:
	map<int,int> mUsers; //<user, cluster>
	map<int,map<int,double>> mMovieReprCluster; //<movie, <cluster,rating>>
	fstream mFs;
};

#endif