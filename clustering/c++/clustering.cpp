#include <iostream>
#include <fstream>
#include <algorithm>
#include "include/mat.h"
#include "include/ap.h"
#include "include/graph.h"

using namespace std;

string sim_matrix_path;
string ratings_path;
int iteration, data_points;
double dampingFactor;

void getDatasetName(int argc, char *argv[]);
void readSimilarities(const char* dfn, mat *S);
void readRatings(const char* dfn, Graph *R);

int main(int argc, char *argv[])
{
	getDatasetName(argc, argv);
	mat *S = new mat(data_points);
	readSimilarities(sim_matrix_path.c_str(), S);
	// S->debug();
	Graph *R = new Graph();
	readRatings(ratings_path.c_str(), R);
	// R->Show();

	AP *ap = new AP(iteration, dampingFactor, data_points);
	ap->SetSimMatrix(S);
	ap->SetRatings(R);
	ap->Process();
	
	delete ap;
	delete S;
	delete R;

	return 0;
}

void getDatasetName(int argc, char *argv[])
{
	if(argc == 6)
	{
		sim_matrix_path = argv[1];
		ratings_path = argv[2];
		data_points = atoi(argv[3]);
		iteration = atoi(argv[4]);
		dampingFactor = stod(argv[5]);
	}
	else if(argc == 4)
	{
		sim_matrix_path = argv[1];
		ratings_path = argv[2];
		data_points = atoi(argv[3]);
		iteration = 100;
		dampingFactor = 0.9;	
	}
	else
	{
		cout << "[Error] Missing parameters!" << endl;
		cout << "[INFO] ap.out <SIM_MATRIX_PATH> <RATINGS_MATRIX_PATH> <QTD_DATA_POINTS> [ <ITERATIONS=100> <DAMPING_FACTOR=0.9> ]" << endl;
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