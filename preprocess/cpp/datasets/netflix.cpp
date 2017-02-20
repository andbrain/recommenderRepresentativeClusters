#include "datasets/netflix.h"

netflix::netflix(string path, string sim_function):Dataset_Base(path, sim_function)
{
	cout << "Starting Netflix prize..(#tip: Netflix folder path)" << endl;
}

netflix::~netflix()
{
	cout << "Finishing netflix prize.." << endl;
}

int netflix::LoadRatings()
{
	cout << "Loading Ratings.." << endl;



	//TODO:: read all files from folder - maybe try to do it in dataset+base class
	
	// vector<string> files;
	// Folder *folder = new Folder(path);
	// files = folder->GetFiles();
















	// string line;
	// vector<string> relation;
	// map<string,int> users, movies;
	// string userId, movieId, rating;

	// int count = 0;

	// cout << "Reading header.." << endl;
	// getline(mFs, line);

	// cout << "Reading ratings..." << endl;
	// while(getline(mFs, line))
	// {

	// 	relation = Split(line, ' ');

	// 	userId = relation[0];
	// 	movieId = relation[1];
	// 	rating = relation[2];

	// 	int indexUser, indexMovie;

	// 	map<string,int>::iterator itUser = users.find(userId);
	// 	if(itUser == users.end())
	// 	{
	// 		indexUser = users.size();
	// 		users.insert(make_pair(userId, indexUser));
	// 	}
	// 	else indexUser = itUser->second;

	// 	mQtdMovies++;
	// 	mRatings->AddVertex(indexUser, userId);
	// 	mRatings->AddEdge(indexUser, atoi(movieId.c_str()), stod(rating));
	// 	count++;
	// }


	// cout << "Finishing file..." << endl;
	// cout << "Users: " << mRatings->Size() << endl;
	// cout << "Nro of Ratings: " << count << endl;

	return 0;
}