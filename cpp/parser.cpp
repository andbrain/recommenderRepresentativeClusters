#include "parser.h"

Parser::Parser(string ratingsPath, string clusterPath, string reprClusterPath, int n_multi_clusters)
{
	mRatingPath = ratingsPath;
	mClusterPath = clusterPath;
	mReprClusterPath = reprClusterPath;
	mRatings = new Graph();
	mNmultiClusters = n_multi_clusters;
	mRepr = new vector<Representative*>();
}

Parser::~Parser()
{
	delete mRatings;
	//mRepr is deleted after estimator processing
}

void Parser::Process()
{
	ReadRatingsList();
	ReadRepresentatives();
}

void Parser::ReadRatingsList()
{
	mFs.open(mRatingPath.c_str(), ios::in);
	string line;
	vector<string> relation;

	bool isUser = true;
	int indexUser;
	string userId, movieId, rating;

	// Statistics of Test File
	int statUsers=0, statRatings=0, ratingUserCounter; 
	int statMinRatings=INT_MAX, statMaxRatings=INT_MIN;
	double statMediaRatings;
	while(getline(mFs, line))
	{
		relation = Split(line, ' ');
		
		if(isUser)
		{
			indexUser = atoi(relation[0].c_str());
			mRatings->AddVertex(indexUser);

			statUsers++;
		}
		else
		{
			ratingUserCounter = 0;

			for (std::vector<string>::iterator i = relation.begin(); i != relation.end(); ++i)
			{
				movieId = (*i);
				++i;
				rating = (*i);
				mRatings->AddEdge(indexUser, atoi(movieId.c_str()),  stod(rating));

				ratingUserCounter++;
				statRatings++;
			}
			
			if(ratingUserCounter < statMinRatings)
				statMinRatings = ratingUserCounter;
			if(ratingUserCounter > statMaxRatings)
				statMaxRatings = ratingUserCounter;
		}

		isUser = !isUser;
	}

	cout << endl;
	cout << "******* Information about Test File *******" << endl;
	cout << "[INFO] File: " << mRatingPath << endl;
	cout << "[INFO] Users: " << to_string(statUsers) << endl;
	cout << "[INFO] Ratings: " << to_string(statRatings) << endl;
	cout << "[INFO] Average of Ratings per users: " << to_string((double)statRatings/statUsers) << endl;
	cout << "[INFO] Min. of Ratings per users: " << to_string(statMinRatings) << endl;
	cout << "[INFO] Max. of Ratings perusers: " << to_string(statMaxRatings) << endl;
	cout << "*******************************************" << endl;
	cout << endl;

	mFs.close();
}

// void Parser::ReadClusters()
// {

	//TODO:: read all files with clusters generated after kmeans random seeds
	
	// Representative *repr = new Representative();

	// delete repr;

	// mFs.open(mClusterPath.c_str(), ios::in);
	// string line;
	// vector<string> relation;
	// string clusterId, userIndex, userId;

	// while(getline(mFs, line))
	// {
	// 	relation = Split(line, ' ');

	// 	clusterId = relation[0];

	// 	for (int i = 1; i < relation.size(); ++i)
	// 	{
	// 		userIndex = relation[i];
	// 		mUsers[atoi(userIndex.c_str())] = atoi(clusterId.c_str());
	// 	}
	// }

	// mFs.close();
// }

void Parser::ReadRepresentatives()
{

	//TODO:: read all files with clusters generated after kmeans random seeds

	// mFs.open(mReprClusterPath.c_str(), ios::in);
	// string line;
	// vector<string> relation;
	// string clusterId, movieId, reprRating;
	// int movieIndex;
	// while(getline(mFs, line))
	// {
	// 	relation = Split(line, ' ');

	// 	if(relation.size() == 1)
	// 		clusterId = relation[0];
	// 	else
	// 	{
	// 		movieId = relation[0];
	// 		movieIndex = atoi(movieId.c_str());
	// 		reprRating = relation[1];
	// 		map<int,map<int,double>>::iterator it = mMovieReprCluster.find(movieIndex);

	// 		if(it == mMovieReprCluster.end())
	// 		{
	// 			map<int,double> clusterRating;
	// 			clusterRating[atoi(clusterId.c_str())] = stod(reprRating);
	// 			mMovieReprCluster[movieIndex] = clusterRating;
	// 		}
	// 		else
	// 		{
	// 			map<int,double> clusterRating = it->second;
	// 			clusterRating[atoi(clusterId.c_str())] = stod(reprRating);
	// 			it->second = clusterRating;
	// 		}
	// 	}
	// }

	// mFs.close();
}

Graph* Parser::GetRatings()
{
	return mRatings;
}

vector<Representative*>* Parser::GetRepresentatives()
{
	return mRepr;
}