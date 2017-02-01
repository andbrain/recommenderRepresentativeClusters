#include "similarities/euclidean.h"

euclidean::euclidean():similarity_base()
{
	cout << "Starting euclidean.." << endl;
	mCounter = new Graph(); 
}

euclidean::~euclidean()
{
	delete mCounter;
	cout << "Finishing euclidean.." << endl;
}

int euclidean::Process()
{
	AccumulateRatings();
	GenerateSimUserMatrix();
	
	return 0;
}

int euclidean::AccumulateRatings()
{
	cout << "Accumulate Average Ratings.." << endl;

	G::iterator itX = mRatings->begin();
	G::iterator itY;
	Vertex *listaAdjX, *listaAdjY, *lHigher, *lSmaller;
	Edge::iterator itRX, itRY;
	double rx, ry, rating;

	int nro_users = mRatings->Size();
	int actual_user = 0;
	cout << "Total of users: " << nro_users << endl;

	//Store up average rating				
	for(; itX != mRatings->end(); ++itX)
	{
		actual_user++;
		
		cout << actual_user << " ";
		
		if(actual_user % 30 == 0)
			cout << endl;

		mCounter->AddVertex(itX->first, itX->second->GetId());			
		//Loop over users
		itY = itX;
		
		//get next user
		itY++;

		for(; itY != mRatings->end(); ++itY)
		{
			//Add vertex if user is not in the hash table
			if(!mCounter->HasVertex(itY->first))
				mCounter->AddVertex(itY->first, itY->second->GetId());

			//Get list of ratings
			listaAdjX = itX->second;
			listaAdjY = itY->second;

			//getting elements distincts to check ratings of users
			unordered_map<int,int> elements = GetDistinctElements(listaAdjX, listaAdjY);

			for (unordered_map<int,int>::iterator itEl = elements.begin(); itEl != elements.end(); ++itEl)
			{
				//get rating of user x
				itRX = listaAdjX->find(itEl->first);
				if(itRX != listaAdjX->end()) rx = itRX->second;
				else rx = 0;

				//get rating of user y
				itRY = listaAdjY->find(itEl->first);
				if(itRY != listaAdjY->end()) ry = itRY->second;
				else ry = 0;

				// cout << "\t\tRx: " << rx << " Ry: " << ry << endl;
				rating = mCounter->GetEdge(itX->first, itY->first);
				mCounter->AddEdge(itX->first, itY->first, rating);

				mCounter->AddEdge(itY->first, itX->first, rating);

				rating += pow(rx-ry, 2);
				mCounter->SetEdge(itX->first, itY->first, rating);
				mCounter->SetEdge(itY->first, itX->first, rating);
			}
			// cout << "\tSum: " << mCounter->GetEdge(itX->first, itY->first) << endl;
		}
		
	}
	cout << endl;
	// mCounter->Show();

	return 0;
}

int euclidean::GenerateSimUserMatrix()
{
	cout << "Generate Sim User Matrix..." << endl;

	G::iterator itX = mCounter->begin();
	Edge::iterator itListX;
	Vertex *listaAdjX;
	double result;
	vector<double> tmpS;

	for(itX; itX != mCounter->end(); ++itX)
	{
		mSim->AddVertex(itX->first, itX->second->GetId());
		
		listaAdjX = itX->second;
		itListX = listaAdjX->begin();

		for(itListX; itListX != listaAdjX->end(); ++itListX)
		{
			result = 0;

			if(!mSim->HasVertex(itListX->first))
				mSim->AddVertex(itListX->first, mCounter->at(itListX->first)->GetId());

			result = 1 / (double)(1 + sqrt(itListX->second));
			// result = log2(result);
			mSim->AddEdge(itX->first, itListX->first, result);
			mSim->AddEdge(itListX->first, itX->first, result);

			//store each similarity
			tmpS.push_back(result);
		}
	}

	mSim->PrintForAP();
	SetPreferencesMedian(&tmpS);	
}

unordered_map<int,int> euclidean::GetDistinctElements(Vertex *listX, Vertex *listY)
{
	unordered_map<int,int> m;
	unordered_map<int,int>::iterator found;
	Edge::iterator itList;

	for(itList = listX->begin(); itList != listX->end(); ++itList)
	{
		// cout << "element add: " << itList->first << endl;
		m[itList->first] = 0;
	}

	for (itList = listY->begin(); itList != listY->end(); ++itList)
	{
		found = m.find(itList->first);

		if(found == m.end())
			m[itList->first] = 0;
	}

	return m;
}