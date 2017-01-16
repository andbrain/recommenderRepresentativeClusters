#include "datasets/ml100k.h"

ml100k::ml100k(string path):Dataset_Base(path)
{
	cout << "Starting ml100k.." << endl;
}

ml100k::~ml100k()
{
	cout << "Finishing ml100k.." << endl;
}

int ml100k::LoadRatings()
{
	cout << "Loading Ratings.." << endl;

	string line;
	vector<string> relation;
	map<string,int> users, movies;
	string userId, movieId, rating;

	int count = 0;

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

		mQtdMovies++;
		mRatings->AddVertex(indexUser, userId);
		mRatings->AddEdge(indexUser, atoi(movieId.c_str()), stod(rating));
		count++;
	}

	cout << "Movies: " << mQtdMovies << endl;
	cout << "Users: " << mRatings->Size() << endl;
	cout << "Nro of Ratings: " << count << endl;

	return 0;
}

// int ml100k::AccumulateRatings()
// {
// 	cout << "Accumulate Average Ratings.." << endl;

// 	G::iterator itX = mRatings->begin();
// 	G::iterator itY;
// 	Vertex *listaAdjX, *listaAdjY;
// 	Edge::iterator itListX, found;
// 	double rx, ry, rating;

// 	int nro_users = mRatings->Size();
// 	int actual_user = 0;
// 	cout << "Total of users: " << nro_users << endl;

// 	//Store up average rating				
// 	for(; itX != mRatings->end(); ++itX)
// 	{
// 		actual_user++;

// 		cout << actual_user << " ";
		
// 		if(actual_user % 30 == 0)
// 			cout << endl;

// 		//Loop over users
// 		itY = itX;
		
// 		//get next user
// 		itY++;

// 		mCounter->AddVertex(itX->first, itX->second->GetId());			

// 		for(; itY != mRatings->end(); ++itY)
// 		{
			
// 			listaAdjX = itX->second;
// 			itListX = listaAdjX->begin();

// 			if(!mCounter->HasVertex(itY->first))
// 				mCounter->AddVertex(itY->first, itY->second->GetId());

// 			listaAdjY = itY->second;

// 			//TODO:: check if listAdjX is smaller than listAdjY
// 			for(itListX; itListX != listaAdjX->end(); ++itListX)
// 			{
// 				rx = 0;
// 				ry = 0;
				
// 				//check if userX rate same movies of userY
// 				found = listaAdjY->find(itListX->first);

// 				if(found != listaAdjY->end())
// 				{
// 					rx = itListX->second;
// 					ry = found->second;

// 					// cout << "\t\t Rx: " << rx << " Ry: " << ry << endl;
// 					rating = mCounter->GetEdge(itX->first, itY->first);
// 					mCounter->AddEdge(itX->first, itY->first, rating);
// 					mCounter->AddEdge(itY->first, itX->first, rating);

// 					rating += (rx+ry)/2;

// 					mCounter->SetEdge(itX->first, itY->first, rating);
// 					mCounter->SetEdge(itY->first, itX->first, rating);
// 				}
// 			}
// 		}
		
// 	}
// 	cout << endl;

// 	return 0;
// }

// int ml100k::GenerateSimUserMatrix()
// {
// 	cout << "Generate Sim User Matrix..." << endl;
// 	int nroMovies =	mMovies.Size();

// 	G::iterator itX = mCounter->begin();
// 	Edge::iterator itListX;
// 	Vertex *listaAdjX;
// 	double result;
// 	vector<double> tmpS;

// 	for(itX; itX != mCounter->end(); ++itX)
// 	{
// 		mSim->AddVertex(itX->first, itX->second->GetId());
		
// 		listaAdjX = itX->second;
// 		itListX = listaAdjX->begin();

// 		for(itListX; itListX != listaAdjX->end(); ++itListX)
// 		{
// 			result = 0;

// 			if(!mSim->HasVertex(itListX->first))
// 			{
// 				mSim->AddVertex(itListX->first, mCounter->at(itListX->first)->GetId());
// 			}

// 			result = itListX->second / (nroMovies * MAX_RATING);
// 			result = log2(result);
// 			mSim->AddEdge(itX->first, itListX->first, result);
// 			mSim->AddEdge(itListX->first, itX->first, result);

// 			//store each similarity
// 			tmpS.push_back(result);
// 		}
// 	}

// 	mSim->PrintForAP();
// 	SetPreferencesMedian(&tmpS);	
// }