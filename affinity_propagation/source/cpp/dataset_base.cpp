#include "dataset_base.h"

Dataset_Base::Dataset_Base(string base_path)
{
	mPath = base_path;
	Initialize();	
}

Dataset_Base::~Dataset_Base()
{
	delete mRatings;
	delete mSim;
	mFs.close();
}

void Dataset_Base::Initialize()
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
}

Graph* Dataset_Base::GetMatrix()
{
	return mSim->Clone();
}

Graph* Dataset_Base::GetRatings()
{
	return mRatings->Clone();
}

int Dataset_Base::SetPreferencesMedian(vector<double> *tmpS)
{
	////////////////////////////////////
	//Assign median value for Sim Matrix
	////////////////////////////////////
	
	sort(tmpS->begin(),tmpS->end());
	double median = 0;
	int N = mSim->Size();
	int size = N*(N-1)/2;

	if(size%2==0) 
		median = (tmpS->at(size/2)+tmpS->at(size/2-1)/2);
	else 
		median = tmpS->at(size/2);

	for(G::iterator it = mSim->begin(); it != mSim->end(); ++it)
	{
		mSim->AddEdge(it->first, it->first, median);
	}

	return 0;
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
	// AccumulateRatings();
	// GenerateSimUserMatrix();
	
	CreateTrainFile(0.7); //train 70% test 30%

	return 0;
}