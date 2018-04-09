#include "parser.h"

Parser::Parser(string ratingsPath, string clusterPrefix, string reprPrefix, int n_multi_clusters)
{
	mRatingPath = ratingsPath;
	mClusterPrefix = clusterPrefix;
	mReprPrefix = reprPrefix;
	mRatings = new Graph();
	mRepr = new vector<Representative*>();
	mNmultiClusters = n_multi_clusters;
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

void Parser::ReadRepresentatives()
{

}

Graph* Parser::GetRatings()
{
	return mRatings;
}

vector<Representative*>* Parser::GetRepresentatives()
{
	return mRepr;
}