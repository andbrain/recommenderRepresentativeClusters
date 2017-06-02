#include "datasets/ml100k.h"

ml100k::ml100k(string path, string sim_function, int based):Dataset_Base(path, sim_function, based)
{
	cout << "Starting ml100k.." << endl;
}

ml100k::~ml100k()
{
	cout << "Finishing ml100k.." << endl;
}

int ml100k::LoadRatings()
{
	cout << "Loading Ratings.." << endl;

	string line;
	vector<string> relation;
	map<string,int> users, movies;
	string userId, movieId, rating;

	int count = 0;

	cout << "Reading ratings..." << endl;
	while(getline(mFs, line))
	{
		relation = Split(line, '\t');

		userId = relation[0];
		movieId = relation[1];
		rating = relation[2];

		int indexUser, indexMovie;

		map<string,int>::iterator itUser = users.find(userId);
		if(itUser == users.end())
		{
			indexUser = users.size();
			users.insert(make_pair(userId, indexUser));
		}
		else indexUser = itUser->second;

		mQtdMovies++;
		mRatings->AddVertex(indexUser, userId);
		mRatings->AddEdge(indexUser, atoi(movieId.c_str()), stod(rating));
		count++;
	}

	// cout << "Movies: " << mQtdMovies << endl;
	cout << "Users: " << mRatings->Size() << endl;
	cout << "Nro of Ratings: " << count << endl;

	return 0;
}