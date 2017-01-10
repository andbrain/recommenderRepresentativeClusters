#include "datasets/ml10m100k.h"

ml10m100k::ml10m100k(string path):Dataset_Base(path)
{
	cout << "Starting ml10m100k.." << endl;
	Initialize();	
}

ml10m100k::~ml10m100k()
{
	delete mRatings;
	delete mSim;
	delete mCounter;
	cout << "Finishing ml10m100k.." << endl;
}

void ml10m100k::Initialize()
{
	string basePath = mPath + "/" + RATING_FILE;

	mFs.open(basePath.c_str(), ios::in);

	if(!mFs.is_open())
	{
		cout << "[ERROR] Cannot open file: " << basePath << endl;
		exit(1);
	}

	mRatings = new Hash();
	mSim = new Hash();
	mCounter = new Hash();
}

int ml10m100k::Process()
{
	LoadRatings();
	AccumulateRatings();
	GenerateSimUserMatrix();

	return 0;
}

int ml10m100k::LoadRatings()
{
	cout << "Loading Ratings.." << endl;

	string line;
	vector<string> relation;
	string userId, movieId, rating;

	int count = 0;
	while(getline(mFs, line))
	{
		relation = Split(line, ':');

		userId = relation[0];
		movieId = relation[2];
		rating = relation[4];

		mMovies.AddVertice(movieId);

		mRatings->AddVertice(userId);
		mRatings->AddAresta(userId, movieId, stod(rating));
	}

	cout << "Movies: " << mMovies.NumeroVertices() << endl;
	// mRatings->Imprime();

	return 0;
}

int ml10m100k::AccumulateRatings()
{
	cout << "Accumulate Average Ratings.." << endl;

	unordered_map<string,unordered_map<string,double>* >::iterator itX = mRatings->begin();
	unordered_map<string,unordered_map<string,double>* >::iterator itY;
	unordered_map<string,double> *listaAdjX, *listaAdjY;
	unordered_map<string,double>::iterator itListX, found;
	double rx, ry, rating;

	int nro_users = mRatings->NumeroVertices();
	int actual_user = 0;
	cout << "Total of users: " << nro_users << endl;

	//Store up average rating				
	for(itX; itX != mRatings->end(); ++itX)
	{
		actual_user++;
		cout << "( " << actual_user << "/" << nro_users << " )" << endl;
		
		//Loop over users
		itY = itX;
		
		//get next user
		itY++;

		for(itY; itY != mRatings->end(); ++itY)
		{
			
			listaAdjX = itX->second;
			itListX = listaAdjX->begin();

			mCounter->AddVertice(itX->first);
			mCounter->AddVertice(itY->first);

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
					rating = mCounter->GetAresta(itX->first, itY->first);
					mCounter->AddAresta(itX->first, itY->first, rating);
					mCounter->AddAresta(itY->first, itX->first, rating);

					rating += (rx+ry)/2;

					mCounter->SetAresta(itX->first, itY->first, rating);
					mCounter->SetAresta(itY->first, itX->first, rating);
				}
			}
		}
		
	}

	// mCounter->Imprime();
	return 0;
}

int ml10m100k::GenerateSimUserMatrix()
{
	cout << "Generate Sim User Matrix..." << endl;
	int nroMovies =	mMovies.NumeroVertices();

	unordered_map<string,unordered_map<string,double>* >::iterator itX = mCounter->begin();
	unordered_map<string,double>::iterator itListX;
	unordered_map<string,double> *listaAdjX;
	double result;

	for(itX; itX != mCounter->end(); ++itX)
	{
		//Similarity 1 for same user
		mSim->AddVertice(itX->first);
		mSim->AddAresta(itX->first, itX->first, 1);
		
		listaAdjX = itX->second;
		itListX = listaAdjX->begin();

		for(itListX; itListX != listaAdjX->end(); ++itListX)
		{
			result = 0;
			mSim->AddVertice(itListX->first);
			result = itListX->second / (nroMovies * MAX_RATING);
			mSim->AddAresta(itX->first, itListX->first, result);
			mSim->AddAresta(itListX->first, itX->first, result);
		}
	}

	mSim->PrintForAP();
}

Hash* ml10m100k::GetMatrix()
{
	return mSim->Copiar();
}