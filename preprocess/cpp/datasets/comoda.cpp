#include "datasets/comoda.h"

comoda::comoda(string path, string sim_function, int based):Dataset_Base(path, sim_function, based)
{
	cout << "Starting comoda..(#tip: it's trying LDOS-CoMoDa.csv)" << endl;
}

comoda::~comoda()
{
	cout << "Finishing comoda.." << endl;
}

int comoda::LoadRatings()
{
	cout << "Loading Ratings.." << endl;

	string line;
	vector<string> relation;
	map<string,int> dataPoint, secDataPoint;
	string userId, movieId, rating;
	string basedId, secondaryId;

	//statistics
	vector<int> acumRatings(5,0);
	int qtdRatings = 0;

	cout << "Reading header.." << endl;
	getline(mFs, line);

	cout << "Reading ratings..." << endl;
	while(getline(mFs, line))
	{

		relation = Split(line, ' ');

		userId = relation[0];
		movieId = relation[1];
		rating = relation[2];

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

		//acumulate for statistics
		acumRatings[atoi(rating.c_str()) - 1]++;
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

	cout << "Nro of Ratings: " << qtdRatings << endl;
	// show % per type of rating
	for(int i=0; i < acumRatings.size(); ++i)
		cout << "\t[" << i + 1 << "] => " << acumRatings[i] << " (" << fixed << setprecision(2) << ((double)acumRatings[i]/qtdRatings)*100 << "\%)" << endl;

	// show dataset sparsity
	int totalMatrix = dataPoint.size() * secDataPoint.size();
	int totalGaps = totalMatrix - qtdRatings;
	cout << "Dataset sparsity: " << fixed << setprecision(2) << ((double)totalGaps/totalMatrix)*100 << "\%" << endl;

	return 0;
}