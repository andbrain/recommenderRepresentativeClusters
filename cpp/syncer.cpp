#include "syncer.h"

syncer::syncer(Graph* ratings, string clusterPrefix, string reprPrefix)
{
	mClusterPrefix = clusterPrefix;
	mReprPrefix = reprPrefix;
	mRepr = new vector<Representative*>();
	mRatings = ratings;
	for(G::iterator it = ratings->begin(); it != ratings->end(); ++it)
		mUsers.push_back(it->first);
}

syncer::~syncer()
{
	for (int i = 0; i < mRepr->size(); ++i)
		delete mRepr->at(i);
	delete mRepr;
	cout << "[Finishing syncer..]" << endl;
}

void syncer::Process(int nMulti)
{
	cout << "Cluster prefix: " << mClusterPrefix << endl;
	cout << "Representative prefix: " << mReprPrefix << endl;
	string tempPath;

	for (int i = 0; i < nMulti; ++i)
	{
		tempPath = to_string(i+1) + ".dat";
		Representative *repr = new Representative(mClusterPrefix + tempPath, mReprPrefix + tempPath);
		repr->Process();
		mRepr->push_back(repr);
	}
}

void syncer::SetMode(int mode)
{
	mMode = mode;
}

vector<int> syncer::GetUserItems(int userIndex)
{
	vector<int> result;

	Vertex *v = mRatings->at(userIndex);

	for(Edge::iterator it = v->begin(); it != v->end(); ++it)
		result.push_back(it->first);

	return result;
}

vector<int> syncer::GetUsers()
{
	return mUsers;
}

double syncer::GetEstimRating(int userId, int itemId)
{
	double estimRating = 0;
	vector<double> ratings = GetListOfRatings(userId, itemId);

	if(mMode == 0)
	{
		// cout << "[MODE] Average of ratings for each cluster generated with random seeds" << endl;
		double acc = 0;
		for (int i = 0; i < ratings.size(); ++i)
		{
			acc += ratings.at(i);
		}

		estimRating = acc/ratings.size();
	}
	else
	{
		// cout << "[MODE] Median of ratings for each cluster generated with random seeds" << endl;
	}

	return estimRating; 
}

vector<double> syncer::GetListOfRatings(int userId, int itemId)
{
	double rating;
	vector<double> ratings;

	for (int i = 0; i < mRepr->size(); ++i)
	{
		rating = mRepr->at(i)->GetRating(userId, itemId);
		ratings.push_back(rating);
	}

	return ratings;
}