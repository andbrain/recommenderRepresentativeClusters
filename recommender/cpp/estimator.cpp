#include "estimator.h"

Estimator::Estimator()
{
	cout << "[Starting estimator..]" << endl;
	srand(time(NULL));
}

Estimator::~Estimator()
{
	cout << "[Finishing estimator..]" << endl;
}

void Estimator::SetRatings(Graph *g)
{
	mRatings = g;
}

void Estimator::SetUsers(map<int,int> *users)
{
	mUsers = users;
}

void Estimator::SetItemClusters(map<int,map<int,double>> *movieClusters)
{
	mMovieReprCluster = movieClusters;
}

void Estimator::Process()
{
	vector<int> randomUsers = RandomTestData(1.0);
	// int nTest = randomUsers.size();
	int nTest = 0;
	double estimRating, realRating, diff, RMSE, MAE, error = 0, squareError = 0;
	int uCluster;

	for (std::vector<int>::iterator i = randomUsers.begin(); i != randomUsers.end(); ++i)
	{
		vector<int> randomItems = RandomItems(*i,0.2);

		// cout << "User " << *i << endl;
		for (std::vector<int>::iterator it = randomItems.begin(); it != randomItems.end(); ++it)
		{
			// cout << "\t[Selected Item] " << *it << endl;
			uCluster = mUsers->at(*i);
			// cout << "\t\tItem: " << *it << endl;
			// cout << "\t\tUser cluster: " << uCluster << endl;

			map<int,map<int,double>>::iterator itFound = mMovieReprCluster->find(*it);

			if(itFound == mMovieReprCluster->end())
				estimRating = 0;
			else
			{
				Edge::iterator itEdge = mMovieReprCluster->at(*it).find(uCluster);

				if(itEdge == mMovieReprCluster->at(*it).end())
					estimRating = 0;
				else
					estimRating = mMovieReprCluster->at(*it).at(uCluster);	
			}

			// cout << "\t\tEstimated rating per cluster: " << estimRating << endl;
			realRating = mRatings->at(*i)->at(*it); 
			// cout << "\t\tReal rating: " << realRating << endl;
			diff = realRating - estimRating;

			error += (diff < 0)? diff*(-1): diff;
			squareError += pow(diff, 2);
			nTest++;
		}
		// cout << endl;
	}

	cout << "Error: " << error << endl;
	cout << "Square Error: " << squareError << endl;
	//Root Mean Square Error for system
	RMSE = squareError/nTest;
	RMSE = sqrt(RMSE);

	MAE = error/nTest;
	cout << "MAE: " << MAE << endl;
	cout << "RMSE: " << RMSE << endl;
}

vector<int> Estimator::RandomTestData(double perc)
{
	vector<int> result, aux;

	for(map<int,int>::iterator it = mUsers->begin(); it != mUsers->end(); ++it)
	{
		aux.push_back(it->first);
	}

	int rUser;
	int totalSize = aux.size() * perc;
	while(totalSize > 0)
	{
		rUser = rand() % (totalSize); // random number between 0 - size of users remaining
		result.push_back(aux[rUser]);
		aux.erase(aux.begin() + rUser);
		totalSize--;
	}

	return result;
}

vector<int> Estimator::RandomItems(int userIndex, double perc)
{
	vector<int> result, aux;

	Vertex *v = mRatings->at(userIndex);

	for(Edge::iterator it = v->begin(); it != v->end(); ++it)
	{
		aux.push_back(it->first);
	}

	int rItem;
	int totalSize = ceil(aux.size() * perc);

	while(totalSize > 0)
	{
		rItem = rand() % (aux.size()); // random number between 0 - size of users remaining
		result.push_back(aux[rItem]);
		aux.erase(aux.begin() + rItem);
		totalSize--;
	}

	return result;
}