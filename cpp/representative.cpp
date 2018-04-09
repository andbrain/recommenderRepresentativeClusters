#include "representative.h"

Representative::Representative(string clusterPath, string representativePath)
{
	cout << "Representative created.." << endl;
	mClusterPath = clusterPath;
	mReprPath = representativePath;
}

Representative::~Representative()
{
	cout << "Representative released.." << endl;
}

void Representative::Process()
{
	
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

// void Parser::ReadRepresentatives()
// {

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
// }