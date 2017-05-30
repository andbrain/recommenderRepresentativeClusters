#include <iostream>
#include <fstream>
#include <algorithm>
#include "include/mat.h"
#include "include/ap.h"

using namespace std;

string sim_matrix_path;
string ratings_path;
int iteration, elements;
double dampingFactor;

void getDatasetName(int argc, char *argv[]);
void readSimilarities(const char* dfn, mat *S);

int main(int argc, char *argv[])
{
	getDatasetName(argc, argv);
	mat *S = new mat(elements, elements);

	readSimilarities(sim_matrix_path.c_str(), S);

	S->debug();

	AP *ap = new AP(iteration, dampingFactor, elements);
	ap->SetSimMatrix(S);
	// ap->SetRatings(ratings);
	ap->Process();
	
	delete ap;
	delete S;

	return 0;
}

void getDatasetName(int argc, char *argv[])
{
	if(argc == 5)
	{
		sim_matrix_path = argv[1];
		iteration = atoi(argv[2]);
		dampingFactor = stod(argv[3]);
		elements = atoi(argv[4]);
	}
	else
	{
		cout << "[Error] Missing parameters!" << endl;
		cout << "[INFO] ./ap.out SIM_MATRIX_PATH ITERATIONS DAMPING_FACTOR ELEMENTS" << endl;
		exit(1);
	}
}

void readSimilarities(const char* dfn, mat *S) {
		
	int j, k, old=-1;
	double val;
	vector<double> tmpS;
	
	ifstream myfile(dfn);
	while(myfile >> j >> k >> val) {
		j--;
		k--;
		
		S->set(j,k,val);
		S->set(k,j,val);
		tmpS.push_back(S->get(j,k)); 
	}
	myfile.close();
	
	//compute preferences for all data points 
	sort(tmpS.begin(), tmpS.end());
	int size = tmpS.size();

	double median;		
	if(size%2==0) 
		median = (tmpS[size/2]+tmpS[size/2-1])/2;
	else 
		median = tmpS[size/2];

	cout << "Median: " << median << endl; 

	for(int i=0; i<elements; i++)
	{
		S->set(i,i,median);
	}
}
