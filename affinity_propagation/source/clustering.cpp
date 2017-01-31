#include <iostream>

#include "include/parser.h"
#include "include/graph.h"
#include "include/ap.h"

using namespace std;

string dataset_name;
string dataset_path;
string sim_function;
int iteration;
double dampingFactor;

void GetDatasetName(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	GetDatasetName(argc, argv);
	
	Parser *p = new Parser(dataset_name, dataset_path, sim_function);
	p->Process();

	Graph *graph = p->GetSimMatrix();
	Graph *ratings = p->GetRatings();
	AP *ap = new AP(iteration, dampingFactor);
	ap->SetSimMatrix(graph);
	ap->SetRatings(ratings);
	ap->Process();
	
	ratings->Print("ratings.txt");

	delete ap;
	delete p;
	return 0;
}

void GetDatasetName(int argc, char *argv[])
{
	if(argc == 4)
	{
		dataset_name = argv[1];
		dataset_path = argv[2];
		sim_function = argv[3];
		iteration = 10;
		dampingFactor = 0.9;
	}
	else if(argc == 6)
	{
		dataset_name = argv[1];
		dataset_path = argv[2];
		sim_function = argv[3];
		iteration = atoi(argv[4]);
		dampingFactor = stod(argv[5]);
	}
	else
	{
		cout << "[Error] Missing parameters!" << endl;
		cout << "[INFO] ./clustering DATASET_NAME DATASET_PATH SIM_FUNCTION [NUMBER_ITER] [DAMPING_FACTOR]" << endl;
		exit(1);
	}
}
