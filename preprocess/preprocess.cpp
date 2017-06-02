#include <iostream>

#include "include/parser.h"
#include "include/graph.h"

using namespace std;

string dataset_name;
string dataset_path;
string sim_function;
int based=0;

void GetDatasetName(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	GetDatasetName(argc, argv);
	
	Parser *p = new Parser(dataset_name, dataset_path, sim_function, based);
	p->Process();

	Graph *sim = p->GetSimMatrix();
	Graph *ratings = p->GetRatings();
	ratings->PrintPair("ratings.dat");
	int start_at = 1;
	sim->PrintList("similarities.dat", start_at);
		
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
	}
	else if(argc == 5)
	{
		dataset_name = argv[1];
		dataset_path = argv[2];
		sim_function = argv[3];
		based = atoi(argv[4]);
	}
	else
	{
		cout << "[Error] Missing parameters!" << endl;
		cout << "[INFO] preprocess <DATASET_NAME> <DATASET_PATH> <SIM_FUNCTION> [BASED=0]" << endl;
		cout << "*BASED=0 -> User Based" << endl;
		cout << "*BASED=1 -> Item Based" << endl;
		exit(1);
	}
}
