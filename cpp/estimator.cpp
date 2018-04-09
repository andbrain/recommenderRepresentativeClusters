#include "estimator.h"

Estimator::Estimator()
{
	cout << "[Starting estimator..]" << endl;
}

Estimator::~Estimator()
{
	delete mSync;
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

void Estimator::SetSyncer(syncer* sync)
{
	mSync = sync;
}

void Estimator::SetItemClusters(map<int,map<int,double>> *movieClusters)
{
	mMovieReprCluster = movieClusters;
}

vector<double> Estimator::Process(int exp)
{
	vector<int> users = mSync->GetUsers();
	vector<double> result(5);
	int predictions = 0;
	double estimRating, realRating, diff, RMSE, MAE, error = 0, squareError = 0;

	for (std::vector<int>::iterator user = users.begin(); user != users.end(); ++user)
	{
		vector<int> items = mSync->GetUserItems(*user);
		// cout << "User " << *user << endl;

		for (std::vector<int>::iterator item = items.begin(); item != items.end(); ++item)
		{
			estimRating = mSync->GetEstimRating(*user, *item);
			
			if(estimRating == 0)
				continue;
			
			realRating = mRatings->at(*user)->at(*item); 
			diff = realRating - estimRating;

			error += (diff < 0)? diff*(-1): diff;
			squareError += pow(diff, 2);
			predictions++;

			// cout << "\t\tEstimated rating: " << estimRating << endl;
			// cout << "\t\tReal rating: " << realRating << endl;
			// cout << "\t\tError: " << error << " Square error: " << squareError << endl;
		}
		// cout << endl;
	}

	//Root Mean Square Error for system
	RMSE = squareError/predictions;
	RMSE = sqrt(RMSE);

	MAE = error/predictions;

	cout << "[" << exp << "o. experiment] ";
	cout << "RMSE: " << RMSE;
	cout << " MAE: " << MAE;
	cout << " Error: " << error;
	cout << " Square Error: " << squareError;
	cout << " Predictions: " << predictions;
	cout << endl;

	result[0] = RMSE;
	result[1] = MAE;
	result[2] = error;
	result[3] = squareError;
	result[4] = predictions;

	return result;
}