#include <iostream>

#include "include/parser.h"

using namespace std;

string sim_matrix_path;
string ratings_path;

void GetDatasetName(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	GetDatasetName(argc, argv);
	
	return 0;
}

void GetDatasetName(int argc, char *argv[])
{
	if(argc == 3)
	{
		sim_matrix_path = argv[1];
		ratings_path = argv[2];
	}
	else
	{
		cout << "[Error] Missing parameters!" << endl;
		cout << "[INFO] ./clustering.out SIM_MATRIX_PATH RATINGS_PATH" << endl;
		exit(1);
	}
}
