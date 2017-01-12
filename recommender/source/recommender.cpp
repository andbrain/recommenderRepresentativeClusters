#include <iostream>
#include "graph.h"
#include "parser.h"

using namespace std;

string ratingsPath, clusterPath, reprClusterPath;

void GetDatasetName(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	GetDatasetName(argc, argv);

	Parser p(ratingsPath, clusterPath, reprClusterPath);
	p.Process();

	return 0;
}

void GetDatasetName(int argc, char *argv[])
{
	if(argc == 4)
	{
		ratingsPath = argv[1];
		clusterPath = argv[2];
		reprClusterPath = argv[3];
	}
	else
	{
		cout << "[Error] Missing parameters!" << endl;
		cout << "[INFO] ./clustering DATASET_NAME DATASET_PATH" << endl;
		exit(1);
	}
}