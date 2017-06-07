#include "similarity_base.h"

similarity_base::similarity_base()
{
}

similarity_base::~similarity_base()
{

}

void similarity_base::SetMatrix(mat *ratings, mat *sim)
{
	mRatings = ratings;
	mSim = sim;
}

mat* similarity_base::GetMatrix()
{
	return mSim;
}


int similarity_base::SetPreferencesMedian(vector<double> *tmpS)
{
	////////////////////////////////////
	//Assign median value for Sim Matrix
	////////////////////////////////////
	

	//TODO: see if is correct checking the median value
	// sort(tmpS->begin(),tmpS->end());
	// double median = 0;
	// int N = mSim->Size();
	// int size = N*(N-1)/2;

	// if(size%2==0) 
	// 	median = (tmpS->at(size/2)+tmpS->at(size/2-1)/2);
	// else 
	// 	median = tmpS->at(size/2);

	// for(G::iterator it = mSim->begin(); it != mSim->end(); ++it)
	// {
	// 	mSim->AddEdge(it->first, it->first, median);
	// }

	return 0;
}