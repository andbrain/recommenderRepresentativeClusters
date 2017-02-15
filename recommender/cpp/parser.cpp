#include "parser.h"

Parser::Parser(string ratingsPath, string clusterPath, string reprClusterPath)
{
	mRatingPath = ratingsPath;
	mClusterPath = clusterPath;
	mReprClusterPath = reprClusterPath;
	mRatings = new Graph();
}

Parser::~Parser()
{
	delete mRatings;
}

void Parser::Process()
{
	ReadRatingsList();
	ReadClusters();
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

	while(getline(mFs, line))
	{
		relation = Split(line, ' ');
		
		if(isUser)
		{
			indexUser = atoi(relation[0].c_str());
			userId = relation[1];
			mRatings->AddVertex(indexUser, userId);
		}
		else
		{
			for (std::vector<string>::iterator i = relation.begin(); i != relation.end(); ++i)
			{
				movieId = (*i);
				++i;
				rating = (*i);
				mRatings->AddEdge(indexUser, atoi(movieId.c_str()), stod(rating));
			}
		}

		isUser = !isUser;
	}	
	mFs.close();
	// mRatings->Show();
}

void Parser::ReadClusters()
{
	mFs.open(mClusterPath.c_str(), ios::in);
	string line;
	vector<string> relation;
	string clusterId, userIndex, userId;

	while(getline(mFs, line))
	{
		relation = Split(line, ' ');

		if(relation.size() == 1)
			clusterId = relation[0];
		else
		{
			userIndex = relation[0];
			userId = relation[1]; //TODO:: nothing to do, remove someday
			mUsers[atoi(userIndex.c_str())] = atoi(clusterId.c_str());
		}
	}

	mFs.close();
}

void Parser::ReadRepresentatives()
{
	mFs.open(mReprClusterPath.c_str(), ios::in);
	string line;
	vector<string> relation;
	string clusterId, movieId, reprRating;
	int movieIndex;
	while(getline(mFs, line))
	{
		relation = Split(line, ' ');

		if(relation.size() == 1){
			map<int,double> movieRating;
			clusterId = relation[0];
		}
		else
		{
			movieId = relation[0];
			movieIndex = atoi(movieId.c_str());
			reprRating = relation[1];
			map<int,map<int,double>>::iterator it = mMovieReprCluster.find(movieIndex);

			if(it == mMovieReprCluster.end())
			{
				map<int,double> clusterRating;
				clusterRating[atoi(clusterId.c_str())] = stod(reprRating);
				mMovieReprCluster[movieIndex] = clusterRating;
			}
			else
			{
				map<int,double> clusterRating = it->second;
				clusterRating[atoi(clusterId.c_str())] = stod(reprRating);
				it->second = clusterRating;
			}
		}
	}

	mFs.close();
}

Graph* Parser::GetRatings()
{
	return mRatings;
}

map<int,int>* Parser::GetUsers()
{
	return &mUsers;
}

map<int,map<int,double>>* Parser::GetMovieClusters()
{
	return &mMovieReprCluster;
}