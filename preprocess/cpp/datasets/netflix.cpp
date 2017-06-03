#include "datasets/netflix.h"

netflix::netflix(string path, string sim_function, int based):Dataset_Base(path, sim_function, based)
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
	
	string lineId;
	int id;
	map<string,int> *dataPoint = new map<string,int>();
	map<string,int> *secDataPoint = new map<string,int>();
	
	//statistics
	vector<int> *acumRatings = new vector<int>(5,0);
	int qtdRatings = 0;

	for(int i=0; i < mFiles.size(); ++i)
	// for(int i=0; i < 2; ++i)
	{
		cout << "Reading: " << mFiles[i] << " --> (" << i + 1 <<  "/"<< mFiles.size() << ")" << endl;
		mFs.open(mFiles[i].c_str(), ios::in);

		if(!mFs.is_open())
		{
			cout << "[ERROR] Cannot open file: " << mFiles[i] << endl;
			exit(1);
		}

		getline(mFs,lineId);
		id = atoi(lineId.substr(0, lineId.size() - 1).c_str());
		LoadFile(id, dataPoint, secDataPoint, acumRatings, &qtdRatings);
		mFs.close();
	}

	cout << "Finished reading of dataset..." << endl;
	cout << "*** Statistics Information ***" << endl;

	if(!mBased)
	{
		cout << "Users: " << dataPoint->size() << endl;
		cout << "Movies: " << secDataPoint->size() << endl;
	}
	else
	{
		cout << "Movies: " << dataPoint->size() << endl;
		cout << "Users: " << secDataPoint->size() << endl;
	}

	cout << "Number of Ratings: " << qtdRatings << endl;
	// show % per type of rating
	for(int i=0; i < acumRatings->size(); ++i)
		cout << "\t[" << i + 1 << "] => " << acumRatings->at(i) << " (" << fixed << setprecision(2) << ((double)acumRatings->at(i)/qtdRatings)*100 << "\%)" << endl;

	// show dataset sparsity
	int totalMatrix = dataPoint->size() * secDataPoint->size();
	int totalGaps = totalMatrix - qtdRatings;
	cout << "Dataset sparsity: " << fixed << setprecision(2) << ((double)totalGaps/totalMatrix)*100 << "\%" << endl;

	return 0;
}

int netflix::LoadFile(int movieId, map<string,int> *dataPoint,map<string,int> *secDataPoint,vector<int> *acumRatings,int *qtdRatings)
{

	string line;
	vector<string> relation;
	string userId, rating;
	string basedId, secondaryId;
	
	while(getline(mFs, line))
	{
		relation = Split(line, ',');

		userId = relation[0];
		rating = relation[1];

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
		map<string,int>::iterator itDataPoint = dataPoint->find(basedId);
		if(itDataPoint == dataPoint->end())
		{
			indexDataPoint = dataPoint->size();
			dataPoint->insert(make_pair(basedId, indexDataPoint));
		}
		else indexDataPoint = itDataPoint->second;
		mRatings->AddVertex(indexDataPoint, basedId);
		mRatings->AddEdge(indexDataPoint, atoi(secondaryId.c_str()), stod(rating));
		
		// Add secondary data point
		int indexsecDataPoint;
		itDataPoint = secDataPoint->find(secondaryId);
		if(itDataPoint == secDataPoint->end())
		{
			indexsecDataPoint = secDataPoint->size();
			secDataPoint->insert(make_pair(secondaryId, indexsecDataPoint));
		}
		else indexsecDataPoint = itDataPoint->second;

		//acumulate for statistics
		acumRatings->at(atoi(rating.c_str()) - 1) += 1;
		*qtdRatings += 1;		
	}

	return 0;
}