#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "include/mat.h"
#include "include/ap.h"
#include "include/sparse_ap.h"
#include "include/graph.h"

using namespace std;

string sim_matrix_path;
string ratings_path;
int pref_type;
int data_points, maxit, convit;
double damping;

void getDatasetName(int argc, char *argv[]);
void readSimilarities(const char* dfn, mat *S);
void readRatings(const char* dfn, Graph *R);

int main(int argc, char *argv[])
{
	getDatasetName(argc, argv);
	mat *S = new mat(data_points);
	readSimilarities(sim_matrix_path.c_str(), S);
	// S->debug();
	// Graph *R = new Graph();
	// readRatings(ratings_path.c_str(), R);
	// R->Show();

	// AP *ap = new AP(maxit, dampingFactor, data_points);
	// ap->SetSimMatrix(S);
	// ap->SetRatings(R);
	// ap->Process();
  	
  	// Delete S inside the method
  	vector<int> examplar = affinityPropagation(S, pref_type, damping, maxit, convit);
	
	for (size_t i = 0; i < examplar.size(); ++i)
		printf("%d ", examplar[i]);

	// delete R;
	return 0;
}

void getDatasetName(int argc, char *argv[])
{
	if(argc == 8)
	{
		sim_matrix_path = argv[1];
		ratings_path = argv[2];
		data_points = atoi(argv[3]);
		pref_type = atoi(argv[4]);
		damping = stod(argv[5]);
		maxit = atoi(argv[6]);
		convit = atoi(argv[7]);
	}
	else if(argc == 4)
	{
		sim_matrix_path = argv[1];
		ratings_path = argv[2];
		data_points = atoi(argv[3]);
		pref_type = 1;
		damping = 0.9;	
		maxit = 1000;
		convit = 50;
	}
	else
	{
		cout << "[Error] Missing parameters!" << endl;
		cout << "[INFO] ap.out <SIM_MATRIX_PATH> <RATINGS_MATRIX_PATH> <QTD_DATA_POINTS> [ <PREF_TYPE=1> <DAMPING=0.9> <MAXIT=1000> <CONVIT=50> ]" << endl;
		cout << "[PARAMS]:" << endl;
		cout << "SIM_MATRIX_PATH -> Similarities file path" << endl;
		cout << "RATINGS_MATRIX_PATH -> Ratings file path" << endl;
		cout << "QTD_DATA_POINTS -> Number of data points in similarity matrix" << endl;
		cout << "PREF_TYPE -> AP Preferences:" << endl;
		cout << "\t1: use median of similarities as preference" << endl;
		cout << "\t2: use minimum of similarities as preference" << endl;
		cout << "\t3: use min - (max - min) of similarities as preference" << endl;
		cout << "MAXIT -> The maximum number of iterations." << endl;
		cout << "DAMPING -> The damping factor. (0.5 <= damping < 1.0)" << endl;
		cout << "CONVIT -> Specify how many iterations this algorithm stops when examplars did not change for." << endl;

		exit(1);
	}
}

void readSimilarities(const char* dfn, mat *S) {
		
	int j, k;
	double val;
	vector<double> tmpS;
	
	ifstream myfile(dfn);
	//compute preferences for all data points 
	while(myfile >> j >> k >> val) {
		j--;
		k--;
		S->set(j,k,val);
		S->set(k,j,val);
		tmpS.push_back(S->get(j,k)); 
	}
	myfile.close();
	
	//sort data points
	sort(tmpS.begin(), tmpS.end());
	int size = tmpS.size();

	//get median data point value
	double median;		
	if(size%2==0) 
		median = (tmpS[size/2]+tmpS[size/2-1])/2;
	else 
		median = tmpS[size/2];

	cout << "Median: " << median << endl; 

	//set the main diagonal to median value
	for(int i=0; i<data_points; i++)
	{
		S->set(i,i,median);
	}
}

void readRatings(const char* dfn, Graph *R)
{
	int i, j;
	double rat, aux;
	string line;
	
	ifstream myfile(dfn);
	//compute all ratings 
	while(myfile >> i) {
		if(!R->HasVertex(i))
			R->AddVertex(i);
		do
		{
			myfile >> j >> rat;
			R->AddEdge(i,j,rat);
		}while(myfile.peek() != '\n' && myfile.peek() != EOF);
	}
	myfile.close();
}