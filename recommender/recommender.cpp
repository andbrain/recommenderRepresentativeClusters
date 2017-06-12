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

	vector<double> results(4), parcResult;
	for(int i=0; i<repetitions; ++i)
	{
		parcResult = est.Process(i+1);
		for (int j = 0; j < parcResult.size(); ++j)
			results[j] += parcResult[j];
	}
	cout << endl;
	cout << "**********************" << endl;
	cout << "**********************" << endl;
	cout << "   Mean of Results" << endl;
	cout << "**********************" << endl;
	cout << "**********************" << endl;
	cout << "RMSE: " << results[0]/repetitions << endl;
	cout << "MAE: " << results[1]/repetitions << endl;
	cout << "Error: " << results[2]/repetitions << endl;
	cout << "Square Error: " << results[3]/repetitions << endl;

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