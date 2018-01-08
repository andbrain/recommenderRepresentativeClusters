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

vector<double> Estimator::Process(int exp)
{
	vector<int> randomUsers = RandomTestData(1.0);
	// int nTest = randomUsers.size();
	vector<double> result(5);
	int nTest = 0;
	double estimRating, realRating, diff, RMSE, MAE, error = 0, squareError = 0;
	int uCluster;

	for (std::vector<int>::iterator i = randomUsers.begin(); i != randomUsers.end(); ++i)
	{
		vector<int> randomItems = RandomItems(*i,0.2);

		cout << "User " << *i << endl;
		for (std::vector<int>::iterator it = randomItems.begin(); it != randomItems.end(); ++it)
		{

			cout << "\t[Selected Item] " << *it << endl;
			uCluster = mUsers->at(*i);
			// cout << "\t\tItem: " << *it << endl;
			cout << "\t\tUser cluster: " << uCluster << endl;

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
			
			if(estimRating == 0)
				continue;
			
			cout << "\t[Selected Item] " << *it << endl;
			// cout << "\t\tItem: " << *it << endl;
			cout << "\t\tUser cluster: " << uCluster << endl;

			if(estimRating == 0)
				continue;

			cout << "\t[Selected Item] " << *it << endl;
			// cout << "\t\tItem: " << *it << endl;
			cout << "\t\tUser cluster: " << uCluster << endl;
			cout << "\t\tEstimated rating per cluster: " << estimRating << endl;
			realRating = mRatings->at(*i)->at(*it); 
			cout << "\t\tReal rating: " << realRating << endl;
			diff = realRating - estimRating;

			error += (diff < 0)? diff*(-1): diff;
			squareError += pow(diff, 2);
			cout << "\t\tError: " << error << " Square error: " << squareError << endl;
			nTest++;
		}
		cout << endl;
	}

	//Root Mean Square Error for system
	RMSE = squareError/nTest;
	RMSE = sqrt(RMSE);

	MAE = error/nTest;

	cout << "[" << exp << "o. experiment] ";
	cout << "RMSE: " << RMSE;
	cout << " MAE: " << MAE;
	cout << " Error: " << error;
	cout << " Square Error: " << squareError;
	cout << " Predictions: " << nTest;
	cout << endl;

	result[0] = RMSE;
	result[1] = MAE;
	result[2] = error;
	result[3] = squareError;
	result[4] = nTest;

	return result;
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