#include <iostream>
#include "graph.h"
#include "parser.h"
#include "estimator.h"

using namespace std;

string ratingsPath, clusterPath, reprClusterPath;
int repetitions;

void GetDatasetName(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	GetDatasetName(argc, argv);

	Parser p(ratingsPath, clusterPath, reprClusterPath);
	p.Process();

	Estimator est;
	est.SetRatings(p.GetRatings());
	est.SetUsers(p.GetUsers());
	est.SetItemClusters(p.GetMovieClusters());

	for(int i=0; i<repetitions; ++i)
	{
		est.Process(i+1);
	}


	return 0;
}

void GetDatasetName(int argc, char *argv[])
{
	if(argc == 4)
	{
		ratingsPath = argv[1];
		clusterPath = argv[2];
		reprClusterPath = argv[3];
		repetitions = 1;
	}
	else if(argc == 5)
	{

		ratingsPath = argv[1];
		clusterPath = argv[2];
		reprClusterPath = argv[3];
		repetitions = atoi(argv[4]);
	}
	else
	{
		cout << "[Error] Missing parameters!" << endl;
		cout << "[INFO] rec <RATINGS_PATH> <CLUSTER_PATH> <REPR_CLUSTERS_PATH>" << endl;
		exit(1);
	}
}