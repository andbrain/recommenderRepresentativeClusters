#include "datasets/ml2k.h"

ml2k::ml2k(string path):Dataset_Base(path)
{
	cout << "Starting ml2k.." << endl;
	Initialize();	
}

ml2k::~ml2k()
{
	delete mRatings;
	delete mSim;
	delete mCounter;
	mFs.close();
	cout << "Finishing ml2k.." << endl;
}

void ml2k::Initialize()
{
	// mRatingFile="rating10.dat";
	// string basePath = mPath + "/" + mRatingFile;
	string basePath = mPath;

	cout << "Initializing dataset from [" << basePath << "]" << endl;
	mFs.open(basePath.c_str(), ios::in);

	if(!mFs.is_open())
	{
		cout << "[ERROR] Cannot open file: " << basePath << endl;
		exit(1);
	}

	mRatings = new Graph();
	mSim = new Graph();
	mCounter = new Graph();
}

int ml2k::Process()
{
	LoadRatings();
	AccumulateRatings();
	GenerateSimUserMatrix();

	return 0;
}

int ml2k::LoadRatings()
{
	cout << "Loading Ratings.." << endl;

	string line;
	vector<string> relation;
	map<string,int> users, movies;
	string userId, movieId, rating;

	int count = 0;

	cout << "Reading first line header..." << endl;
	getline(mFs, line);

	cout << "Reading ratings..." << endl;

	while(getline(mFs, line))
	{
		relation = Split(line, '\t');

		userId = relation[0];
		movieId = relation[1];
		rating = relation[2];

		int indexUser, indexMovie;

		map<string,int>::iterator itUser = users.find(userId);
		if(itUser == users.end())
		{
			indexUser = users.size();
			users.insert(make_pair(userId, indexUser));
		}
		else indexUser = itUser->second;

		// map<string,int>::iterator itMovie = movies.find(movieId);
		// if(itMovie == movies.end())
		// {
		// 	indexMovie = movies.size();
		// 	movies.insert(make_pair(movieId, movies.size()));
		// }
		// else indexMovie = itMovie->second;
		
		// mMovies.AddVertex(indexMovie, movieId);
		mMovies.AddVertex(atoi(movieId.c_str()), movieId);
		mRatings->AddVertex(indexUser, userId);
		// mRatings->AddEdge(indexUser, indexMovie, stod(rating));
		mRatings->AddEdge(indexUser, atoi(movieId.c_str()), stod(rating));
		count++;
	}

	cout << "Movies: " << mMovies.Size() << endl;
	cout << "Users: " << mRatings->Size() << endl;
	cout << "Nro of Ratings: " << count << endl;
	// mRatings->Show();

	return 0;
}

int ml2k::AccumulateRatings()
{
	cout << "Accumulate Average Ratings.." << endl;

	G::iterator itX = mRatings->begin();
	G::iterator itY;
	Vertex *listaAdjX, *listaAdjY;
	Edge::iterator itListX, found;
	double rx, ry, rating;

	int nro_users = mRatings->Size();
	int actual_user = 0;
	cout << "Total of users: " << nro_users << endl;

	//Store up average rating				
	for(; itX != mRatings->end(); ++itX)
	{
		actual_user++;
		
		cout << actual_user << " ";
		
		if(actual_user % 30 == 0)
			cout << endl;

		//Loop over users
		itY = itX;
		
		//get next user
		itY++;

		mCounter->AddVertex(itX->first, itX->second->GetId());			

		for(; itY != mRatings->end(); ++itY)
		{
			
			listaAdjX = itX->second;
			itListX = listaAdjX->begin();

			if(!mCounter->HasVertex(itY->first))
				mCounter->AddVertex(itY->first, itY->second->GetId());

			listaAdjY = itY->second;

			//TODO:: check if listAdjX is smaller than listAdjY
			for(itListX; itListX != listaAdjX->end(); ++itListX)
			{
				rx = 0;
				ry = 0;
				
				//check if userX rate same movies of userY
				found = listaAdjY->find(itListX->first);

				if(found != listaAdjY->end())
				{
					rx = itListX->second;
					ry = found->second;

					// cout << "\t\t Rx: " << rx << " Ry: " << ry << endl;
					rating = mCounter->GetEdge(itX->first, itY->first);
					mCounter->AddEdge(itX->first, itY->first, rating);
					mCounter->AddEdge(itY->first, itX->first, rating);

					rating += (rx+ry)/2;

					mCounter->SetEdge(itX->first, itY->first, rating);
					mCounter->SetEdge(itY->first, itX->first, rating);
				}
			}
		}
		
	}
	cout << endl;

	return 0;
}

int ml2k::GenerateSimUserMatrix()
{
	cout << "Generate Sim User Matrix..." << endl;
	int nroMovies =	mMovies.Size();

	G::iterator itX = mCounter->begin();
	Edge::iterator itListX;
	Vertex *listaAdjX;
	double result;
	vector<double> tmpS;

	for(itX; itX != mCounter->end(); ++itX)
	{
		mSim->AddVertex(itX->first, itX->second->GetId());
		
		listaAdjX = itX->second;
		itListX = listaAdjX->begin();

		for(itListX; itListX != listaAdjX->end(); ++itListX)
		{
			result = 0;

			if(!mSim->HasVertex(itListX->first))
			{
				mSim->AddVertex(itListX->first, mCounter->at(itListX->first)->GetId());
			}

			result = itListX->second / (nroMovies * MAX_RATING);
			result = log2(result);
			mSim->AddEdge(itX->first, itListX->first, result);
			mSim->AddEdge(itListX->first, itX->first, result);

			//store each similarity
			tmpS.push_back(result);
		}
	}

	CreateTrainFile(0.7); //train 70% test 30%
	mSim->PrintForAP();
	SetPreferencesMedian(&tmpS);	
}

int ml2k::SetPreferencesMedian(vector<double> *tmpS)
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

Graph* ml2k::GetMatrix()
{
	return mSim->Clone();
}

Graph* ml2k::GetRatings()
{
	return mRatings->Clone();
}

void ml2k::CreateTrainFile(double percTrain)
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

		for (int i = 0; i < mMovies.Size(); ++i)
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

		for (int i = 0; i < mMovies.Size(); ++i)
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