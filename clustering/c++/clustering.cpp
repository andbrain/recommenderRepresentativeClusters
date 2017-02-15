#include <iostream>
#include "include/graph.h"
#include "include/ap.h"

using namespace std;

string sim_matrix_path;
string ratings_path;
int iteration;
double dampingFactor;

void GetDatasetName(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	GetDatasetName(argc, argv);

	// Graph *graph = p->GetSimMatrix();
	// Graph *sim = p->GetSimMatrix();

	// AP *ap = new AP(iteration, dampingFactor);
	// ap->SetSimMatrix(graph);
	// ap->SetRatings(ratings);
	// ap->Process();
	
	// delete ap;
	
	return 0;
}

void GetDatasetName(int argc, char *argv[])
{
	if(argc == 5)
	{
		sim_matrix_path = argv[1];
		ratings_path = argv[2];
		iteration = atoi(argv[3]);
		dampingFactor = stod(argv[4]);
	}
	else
	{
		cout << "[Error] Missing parameters!" << endl;
		cout << "[INFO] ./ap.out SIM_MATRIX_PATH RATINGS_PATH ITERATIONS DAMPING_FACTOR" << endl;
		exit(1);
	}
}
