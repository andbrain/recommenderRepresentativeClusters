#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <unordered_map>
#include "types.h"
#include "graph.h"
#include "dataset_base.h"
// #include "datasets/ml10m100k.h"
#include "datasets/ml2k.h"
#include "datasets/ml100k.h"

using namespace std;

class Parser
{
public:
	Parser(string dataset_name, string dataset_path);
	~Parser();
	void Process();
	Graph* GetSimMatrix();
	Graph* GetRatings();
private:
	
	unordered_map<string,Dataset_t> mDatasets;
	Dataset_t mDatasetType;
	string mDataSetPath;
	Dataset_Base *mDatasetBase;
	Graph *mSimMatrix, *mRatings;

	// Methods
	void LoadDataSetTypes();
	void GetDataSetType(string dataset_name);

};

#endif