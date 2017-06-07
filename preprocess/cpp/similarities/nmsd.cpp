#include "similarities/nmsd.h"

nmsd::nmsd():similarity_base()
{
	cout << "Starting negative mean-square difference sim. function.." << endl;
}

nmsd::~nmsd()
{
	cout << "Finishing nmsd sim. function.." << endl;
}

int nmsd::Process()
{
	GenerateSimUserMatrix();
	
	return 0;
}

int nmsd::GenerateSimUserMatrix()
{
	cout << "Generating Similarity Sparse Matrix.." << endl;
	
	int qtd_datapoints = mRatings->size();
	int actual_dp = 0;
	cout << "Total of data points: " << qtd_datapoints << endl;
	int i,j;
	double sum, result;

	for(i = 0; i < qtd_datapoints; ++i)
	{
		cout << i + 1 << " ";
		if( (i+1) % 30 == 0)
			cout << endl;

		for (j = i + 1; j < qtd_datapoints; ++j)
		{
			if(mRatings->size(i) <= mRatings->size(j))
				sum = setCik(i, j);
			else
				sum = setCik(j, i);

			if(sum != INT_MIN)
			{
				result = sum;
				mSim->set(i, j, result);
				mSim->set(j, i, result);
			}
		}
	}

	cout << endl;

	return 0;
}

double nmsd::setCik(int fIndex, int sIndex)
{
	double acum = 0;
	int qtd_common = 0;
	map<int, double>::iterator itLine = mRatings->getLine(fIndex)->begin();

	for (; itLine != mRatings->getLine(fIndex)->end(); ++itLine)
	{
		if(mRatings->get(sIndex, itLine->first) != 0)
		{
			qtd_common++;
			acum += pow(mRatings->get(fIndex, itLine->first) - mRatings->get(sIndex, itLine->first), 2);
		}
	}

	//TODO:: return correct value for each limit
	if(qtd_common > 0 && qtd_common < 5)
		return -( (double)(acum + 2*2*(5 - qtd_common))/5 );
	else if(qtd_common >= 5)
		return -(acum / qtd_common);

	return INT_MIN;
}