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

void Dataset_Base::CreateTrainFile(double percTrain)
{
	// trainX - matrix of rating user(line) x movies(column)
	// testX - matrix of rating user(line) x movies(column)
	
	int qtdU = mRatings->Size();
	int uTrain = ceil(qtdU*percTrain);
	int uTest = qtdU - uTrain;

	cout << "[Total of Users]: " << qtdU << endl;
	cout << "[Users for train]: " << uTrain << endl;
	cout << "[Users for test]: " << uTest << endl;

	/////////////////////////
	// Creating Train File //
	/////////////////////////
	string trainFile = "trainX.txt"; //features - ratings of user
	fstream fsTrain(trainFile, ios::out);

	Vertex *v;
	Edge::iterator itMovie;
	G::iterator itEnd = mRatings->begin();
	advance(itEnd, uTrain);

	for (G::iterator it = mRatings->begin(); it != itEnd; ++it)
	{
		v = it->second;

		for (int i = 0; i < mQtdMovies; ++i)
		{
			itMovie = it->second->find(i);

			if(itMovie != it->second->end())
			{
				fsTrain << itMovie->second << " ";
			}
			else
			{
				fsTrain << 0 << " ";
			}

		}
		fsTrain << endl;		
	}

	fsTrain.close();

	cout << "Train file created: " << trainFile << endl;


	/////////////////////////
	// Creating Test File //
	/////////////////////////
	string testFile = "testX.txt"; //features - ratings of user
	fstream fsTest(testFile, ios::out);

	G::iterator it = mRatings->begin();
	advance(it, uTrain);

	for (; it != mRatings->end(); ++it)
	{
		v = it->second;

		for (int i = 0; i < mQtdMovies; ++i)
		{
			itMovie = it->second->find(i);

			if(itMovie != it->second->end())
			{
				fsTest << itMovie->second << " ";
			}
			else
			{
				fsTest << 0 << " ";
			}

		}
		fsTest << endl;		
	}

	fsTest.close();

	cout << "Test file created: " << testFile << endl;
}

int Dataset_Base::Process()
{
	LoadRatings();
	//similarity function
	mSimFunction->SetMatrix(mRatings, mSim);
	mSimFunction->SetElementsSize(mQtdMovies);
	mSimFunction->Process();
	mSim = mSimFunction->GetMatrix();
	// CreateTrainFile(0.7); //train 70% test 30%

	return 0;
}