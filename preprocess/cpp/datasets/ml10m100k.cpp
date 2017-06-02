#include "datasets/ml10m100k.h"

ml10m100k::ml10m100k(string path, string sim_function, int based):Dataset_Base(path, sim_function, based)
{
	cout << "Starting ml10m100k.." << endl;
}

ml10m100k::~ml10m100k()
{
	cout << "Finishing ml10m100k.." << endl;
}

int ml10m100k::LoadRatings()
{
	cout << "Loading Ratings.." << endl;

	string line;
	vector<string> relation;
	map<string,int> dataPoint, secDataPoint;
	string userId, movieId, rating;
	string basedId, secondaryId;
	int auxRating;

	//statistics
	vector<int> acumRatings(5,0);
	int qtdRatings = 0;

	cout << "Reading ratings..." << endl;
	while(getline(mFs, line))
	{
		relation = Split(line, ':');

		userId = relation[0];
		movieId = relation[2];
		rating = relation[4];

		if(!mBased)
		{
			basedId = userId;
			secondaryId = movieId;
		}
		else
		{
			basedId = movieId;
			secondaryId = userId;
		}
		
		// Add based data Point
		int indexDataPoint;
		map<string,int>::iterator itDataPoint = dataPoint.find(basedId);
		if(itDataPoint == dataPoint.end())
		{
			indexDataPoint = dataPoint.size();
			dataPoint.insert(make_pair(basedId, indexDataPoint));
		}
		else indexDataPoint = itDataPoint->second;
		mRatings->AddVertex(indexDataPoint, basedId);
		mRatings->AddEdge(indexDataPoint, atoi(secondaryId.c_str()), stod(rating));
		
		// Add secondary data point
		int indexsecDataPoint;
		itDataPoint = secDataPoint.find(secondaryId);
		if(itDataPoint == secDataPoint.end())
		{
			indexsecDataPoint = secDataPoint.size();
			secDataPoint.insert(make_pair(secondaryId, indexsecDataPoint));
		}
		else indexsecDataPoint = itDataPoint->second;
		auxRating = round(stod(rating.c_str()));
		//acumulate for statistics
		acumRatings.at(auxRating - 1) += 1;
		qtdRatings++;		
	}

	cout << "Finished reading of dataset..." << endl;
	cout << "*** Statistics Information ***" << endl;

	if(!mBased)
	{
		cout << "Users: " << dataPoint.size() << endl;
		cout << "Movies: " << secDataPoint.size() << endl;
	}
	else
	{
		cout << "Movies: " << dataPoint.size() << endl;
		cout << "Users: " << secDataPoint.size() << endl;
	}

	cout << "Number of Ratings: " << qtdRatings << endl;
	// show % per type of rating
	for(int i=0; i < acumRatings.size(); ++i)
		cout << "\t[" << i + 1 << "] => " << acumRatings[i] << " (" << fixed << setprecision(2) << ((double)acumRatings[i]/qtdRatings)*100 << "\%)" << endl;

	// show dataset sparsity
	int totalMatrix = dataPoint.size() * secDataPoint.size();
	int totalGaps = totalMatrix - qtdRatings;
	cout << "Dataset sparsity: " << fixed << setprecision(2) << ((double)totalGaps/totalMatrix)*100 << "\%" << endl;

	return 0;
}