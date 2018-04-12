#include "estimator.h"

Estimator::Estimator()
{
	cout << "[Starting estimator..]" << endl;
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
	vector<int> randomUsers = GetUserData(); //TODO: instead of get random users, return all users
	vector<double> result(5);
	int nTest = 0;
	double estimRating, realRating, diff, RMSE, MAE, error = 0, squareError = 0;
	int uCluster;


	for (std::vector<int>::iterator i = randomUsers.begin(); i != randomUsers.end(); ++i)
	{
		vector<int> randomItems = GetItems(*i); //TODO:: get all items, cause the test file was created randomly

		cout << "User " << *i << endl;
		for (std::vector<int>::iterator it = randomItems.begin(); it != randomItems.end(); ++it)
		{
			uCluster = mUsers->at(*i);
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

			realRating = mRatings->at(*i)->at(*it); 
			diff = realRating - estimRating;
			error += (diff < 0)? diff*(-1): diff;
			squareError += pow(diff, 2);
			
			cout << "\t[Selected Item] " << *it << endl;
			cout << "\t\tUser cluster: " << uCluster << endl;
			cout << "\t\tEstimated rating per cluster: " << estimRating << endl;
			cout << "\t\tReal rating: " << realRating << endl;
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

vector<int> Estimator::GetUserData()
{
	vector<int> result;

	for(map<int,int>::iterator it = mUsers->begin(); it != mUsers->end(); ++it)
		result.push_back(it->first);

	return result;
}

vector<int> Estimator::GetItems(int userIndex)
{
	vector<int> result;

	Vertex *v = mRatings->at(userIndex);

	if(v != NULL)
	{
		for(Edge::iterator it = v->begin(); it != v->end(); ++it)
			result.push_back(it->first);
	}

	return result;
}