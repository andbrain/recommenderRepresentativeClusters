#include "datasets/ml2k.h"

ml2k::ml2k(string path, string sim_function, int based):Dataset_Base(path, sim_function, based)
{
	cout << "Starting ml2k.." << endl;
}

ml2k::~ml2k()
{
	cout << "Finishing ml2k.." << endl;
}

int ml2k::LoadRatings()
{
	cout << "Loading Ratings.." << endl;

	string line;
	vector<string> relation;
	map<string,int> users;
	string userId, movieId, rating;
	int count = 0;

	cout << "Reading first line header..." << endl;
	getline(mFs, line);

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