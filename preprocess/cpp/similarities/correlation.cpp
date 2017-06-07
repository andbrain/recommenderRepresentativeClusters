#include "similarities/correlation.h"

correlation::correlation():similarity_base()
{
	cout << "Starting correlation.." << endl;
	// mCounter = new Graph();
}

correlation::~correlation()
{
	// delete mCounter;
	cout << "Finishing correlation.." << endl;
}

int correlation::Process()
{
	CalculateMean();
	AccumulateRatings();
	CalculateNorma();
	GenerateSimUserMatrix();
	
	return 0;
}

int correlation::CalculateMean()
{
	// G::iterator itX = mRatings->begin();
	// Vertex *listaAdjX;
	// Edge::iterator itListX;
	// double acc;

	// for(; itX != mRatings->end(); ++itX)
	// {
	// 	listaAdjX = itX->second;
	// 	itListX = listaAdjX->begin();
	// 	acc = 0;

	// 	for(itListX; itListX != listaAdjX->end(); ++itListX)
	// 	{
	// 		acc += itListX->second;
	// 	}
		
	// 	mMean[itX->first] = acc / listaAdjX->Size();
	// }

	return 0;
}

int correlation::CalculateNorma()
{
	// G::iterator itX = mRatings->begin();
	// Vertex *listaAdjX;
	// Edge::iterator itListX;
	// double acc, diff;

	// for(; itX != mRatings->end(); ++itX)
	// {
	// 	listaAdjX = itX->second;
	// 	itListX = listaAdjX->begin();
	// 	acc = 0;

	// 	for(itListX; itListX != listaAdjX->end(); ++itListX)
	// 	{
	// 		diff = itListX->second - mMean[itX->first];
	// 		acc += pow(diff, 2);
	// 	}
		
	// 	mNorma[itX->first] = sqrt(acc);
	// }

	return 0;
}

int correlation::AccumulateRatings()
{
	// cout << "Accumulate Average Ratings.." << endl;

	// G::iterator itX = mRatings->begin();
	// G::iterator itY;
	// Vertex *listaAdjX, *listaAdjY;
	// Edge::iterator itRX, itRY;
	// double rx, ry, rating;

	// int nro_users = mRatings->Size();
	// int actual_user = 0;
	// cout << "Total of data points: " << nro_users << endl;

	// //Store up average rating				
	// for(; itX != mRatings->end(); ++itX)
	// {
	// 	actual_user++;
		
	// 	cout << actual_user << " ";
		
	// 	if(actual_user % 30 == 0)
	// 		cout << endl;

	// 	mCounter->AddVertex(itX->first, itX->second->GetId());			
	// 	//Loop over users
	// 	itY = itX;
		
	// 	//get next user
	// 	itY++;

	// 	for(; itY != mRatings->end(); ++itY)
	// 	{
	// 		//Add vertex if user is not in the hash table
	// 		if(!mCounter->HasVertex(itY->first))
	// 			mCounter->AddVertex(itY->first, itY->second->GetId());
			
	// 		//Get list of ratings
	// 		listaAdjX = itX->second;
	// 		listaAdjY = itY->second;

	// 		//getting elements distincts to check ratings of users
	// 		unordered_map<int,int> elements = GetDistinctElements(listaAdjX, listaAdjY);

	// 		for (unordered_map<int,int>::iterator itEl = elements.begin(); itEl != elements.end(); ++itEl)
	// 		{
	// 			//get rating of user x
	// 			itRX = listaAdjX->find(itEl->first);
	// 			if(itRX != listaAdjX->end()) rx = itRX->second;
	// 			else continue;

	// 			//get rating of user y
	// 			itRY = listaAdjY->find(itEl->first);
	// 			if(itRY != listaAdjY->end()) ry = itRY->second;
	// 			else continue;

	// 			rating = mCounter->GetEdge(itX->first, itY->first);
	// 			mCounter->AddEdge(itX->first, itY->first, rating);

	// 			mCounter->AddEdge(itY->first, itX->first, rating);

	// 			rating += ((double)rx - mMean[itX->first])*((double)ry - mMean[itY->first]);
	// 			mCounter->SetEdge(itX->first, itY->first, rating);
	// 			mCounter->SetEdge(itY->first, itX->first, rating);
	// 		}
	// 	}
		
	// }
	// cout << endl;
	// mCounter->Show();
	
	return 0;
}

int correlation::GenerateSimUserMatrix()
{
	// cout << "Generate Sim Data Points Matrix..." << endl;

	// G::iterator itX = mCounter->begin();
	// Edge::iterator itListX;
	// Vertex *listaAdjX;
	// double result, n1, n2;

	// for(itX; itX != mCounter->end(); ++itX)
	// {
	// 	mSim->AddVertex(itX->first, itX->second->GetId());
		
	// 	listaAdjX = itX->second;
	// 	itListX = listaAdjX->begin();

	// 	for(itListX; itListX != listaAdjX->end(); ++itListX)
	// 	{
	// 		result = 0;

	// 		if(!mSim->HasVertex(itListX->first))
	// 			mSim->AddVertex(itListX->first, mCounter->at(itListX->first)->GetId());
	// 		n1 = mNorma[itX->first];
	// 		n2 = mNorma[itListX->first];

	// 		result = itListX->second / (n1 * n2);
	// 		result = log2(result);
	// 		mSim->AddEdge(itX->first, itListX->first, result);
	// 		mSim->AddEdge(itListX->first, itX->first, result);
	// 	}
	// }
}

// unordered_map<int,int> correlation::GetDistinctElements(Vertex *listX, Vertex *listY)
// {
// 	unordered_map<int,int> m;
	// unordered_map<int,int>::iterator found;
	// Edge::iterator itList;

	// for(itList = listX->begin(); itList != listX->end(); ++itList)
	// {
	// 	m[itList->first] = 0;
	// }

	// for (itList = listY->begin(); itList != listY->end(); ++itList)
	// {
	// 	found = m.find(itList->first);

	// 	if(found == m.end())
	// 		m[itList->first] = 0;
	// }

// 	return m;
// }