#include "dataset_base.h"

Dataset_Base::Dataset_Base(string base_path, string simFunction)
{
	mPath = base_path;
	LoadSimTypes();
	Similarity_t type = GetSimType(simFunction);
	Initialize(type);	
}

Dataset_Base::~Dataset_Base()
{
	delete mRatings;
	delete mSim;
	delete mSimFunction;
	mFs.close();
}

void Dataset_Base::LoadSimTypes()
{
	mSimilarities["euclidean"] = EUCLIDEAN;
	mSimilarities["cosine"] = COSINE;
	mSimilarities["correlation"] = CORRELATION;
	mSimilarities["loglikelihood"] = LOGLIKELIHOOD;
	mSimilarities["average"] = AVERAGE;
}

Similarity_t Dataset_Base::GetSimType(string sim_name)
{
	unordered_map<string,Similarity_t>::iterator it = mSimilarities.find(sim_name);

	if(it != mSimilarities.end())
		return it->second;
	else
	{
		cout << "[ERROR] Similarity function not found!" << endl;
		cout << "[INFO] Available similarity functions:" << endl;
		unordered_map<string, Similarity_t>::iterator itShow = mSimilarities.begin();

		for (; itShow != mSimilarities.end(); ++itShow)
		{
			cout << "[INFO] " << itShow->first << endl;
		}

		exit(1);
	}
}

void Dataset_Base::Initialize(Similarity_t simType)
{
	string basePath = mPath;

	cout << "Initializing dataset from [" << basePath << "]" << endl;
	mFs.open(basePath.c_str(), ios::in);

	if(!mFs.is_open())
	{
		cout << "[ERROR] Cannot open file: " << basePath << endl;
		exit(1);
	}

	mQtdMovies = 0;
	mRatings = new Graph();
	mSim = new Graph();

	switch(simType){
		case EUCLIDEAN:{
			cout << "Using Euclidean similarity function..." << endl;
			mSimFunction = new euclidean();
			break;
		}
		case COSINE:{
			cout << "Using Cosine similarity function..." << endl;
			mSimFunction = new cosine();
			break;
		}
		case CORRELATION:{
			cout << "Using Correlation similarity function..." << endl;
			mSimFunction = new correlation();
			break;			
		}
		case LOGLIKELIHOOD:{
			cout << "Using Log Likelihood similarity function..." << endl;
			mSimFunction = new loglikelihood();
			break;
		}
		case AVERAGE:{
			cout << "Using Average similarity function..." << endl;
			mSimFunction = new average();
			break;
		}
	}

}

Graph* Dataset_Base::GetMatrix()
{
	return mSim->Clone();
}

Graph* Dataset_Base::GetRatings()
{
	return mRatings->Clone();
}

int Dataset_Base::Process()
{
	cout << "**********Information of dataset**********" << endl;
	LoadRatings();
	cout << "**********End of dataset**********" << endl;

	//similarity function
	mSimFunction->SetMatrix(mRatings, mSim);
	mSimFunction->SetElementsSize(mQtdMovies);
	mSimFunction->Process();
	mSim = mSimFunction->GetMatrix();

	return 0;
}