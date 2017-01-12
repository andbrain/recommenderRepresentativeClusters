#include <iostream>

#include "include/parser.h"
#include "include/graph.h"
#include "include/ap.h"

using namespace std;

string dataset_name;
string dataset_path;

void GetDatasetName(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	GetDatasetName(argc, argv);
	
	Parser *p = new Parser(dataset_name, dataset_path);
	p->Process();

	Graph *graph = p->GetSimMatrix();
	Graph *ratings = p->GetRatings();

	ratings->Show();
	
	AP *ap = new AP(50, 0.5);
	ap->SetSimMatrix(graph);
	ap->SetRatings(ratings);
	ap->Process();

	delete ap;
	delete p;
	return 0;
}

void GetDatasetName(int argc, char *argv[])
{
	if(argc == 3)
	{
		dataset_name = argv[1];
		dataset_path = argv[2];
	}
	else
	{
		cout << "[Error] Missing parameters!" << endl;
		cout << "[INFO] ./clustering DATASET_NAME DATASET_PATH" << endl;
		exit(1);
	}
}
