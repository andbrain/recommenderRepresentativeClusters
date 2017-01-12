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

	Estimation();
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
	mRatings->Show();
}

void Parser::ReadClusters()
{

}

void Parser::ReadRepresentatives()
{

}

void Parser::Estimation()
{

}