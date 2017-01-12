#include "parser.h"

Parser::Parser(string dataset_name, string dataset_path)
{
	cout << "Init parser.." << endl;
	this->LoadDataSetTypes();
	this->GetDataSetType(dataset_name);
	mDataSetPath = dataset_path;
}

Parser::~Parser()
{
	// delete mDatasetBase;
	delete mSimMatrix;
	cout << "Finishing parser.." << endl;
}

void Parser::LoadDataSetTypes()
{
	mDatasets["netflixPrize"] = NETFLIXPRIZE;
	mDatasets["ml10M100K"] = ML10M100K;
	mDatasets["ml2k"] = ML2K;
	mDatasets["ml100k"] = ML100K;
}

void Parser::GetDataSetType(string dataset_name)
{
	unordered_map<string,Dataset_t>::iterator it = mDatasets.find(dataset_name);

	if(it != mDatasets.end())
		mDatasetType = it->second;
	else
	{
		cout << "[ERROR] Dataset not found!" << endl;
		cout << "[INFO] Available datasets:" << endl;
		unordered_map<string, Dataset_t>::iterator itShow = mDatasets.begin();

		for (; itShow != mDatasets.end(); ++itShow)
		{
			cout << "[INFO] " << itShow->first << endl;
		}

		exit(1);
	}
}

void Parser::Process()
{
	cout << "Processing dataset.." << endl;

	switch(mDatasetType)
	{
		case ML10M100K:
			{
				cout << "Movie Lens 10M100K processing.." << endl;
				// mDatasetBase = new ml10m100k(mDataSetPath);
				// mDatasetBase->Process();
				// mSimMatrix = mDatasetBase->GetMatrix();
			}
			break;
		case NETFLIXPRIZE:
			cout << "Netflix prize processing.." << endl;
			break;
		case ML2K:
			{
				cout << "Movie Lens 2K processing.." << endl;
				mDatasetBase = new ml2k(mDataSetPath);
				mDatasetBase->Process();
				mSimMatrix = mDatasetBase->GetMatrix();
				mRatings = mDatasetBase->GetRatings();
			}
			break;
		case ML100K:
			{
				cout << "Movie Lens 100K processing.." << endl;
				mDatasetBase = new ml100k(mDataSetPath);
				mDatasetBase->Process();
				mSimMatrix = mDatasetBase->GetMatrix();
				mRatings = mDatasetBase->GetRatings();
			}
			break;
		default:
			cout << "...No dataset selected" << endl;
			break;
	}

	delete mDatasetBase;
}

Graph* Parser::GetSimMatrix()
{
	return mSimMatrix;
}

Graph* Parser::GetRatings()
{
	return mRatings;
}
