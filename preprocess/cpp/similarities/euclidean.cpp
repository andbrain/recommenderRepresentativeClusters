#include "similarities/euclidean.h"

euclidean::euclidean():similarity_base()
{
	cout << "Starting euclidean.." << endl;
}

euclidean::~euclidean()
{
	cout << "Finishing euclidean.." << endl;
}

int euclidean::Process()
{
	GenerateSimUserMatrix();
	return 0;
}

int euclidean::GenerateSimUserMatrix()
{
	cout << "Accumulate Average Ratings.." << endl;
	
	int qtd_datapoints = mRatings->size();
	int actual_dp = 0;
	cout << "Total of data points: " << qtd_datapoints << endl;
	vector<double> cik; //set 'c' of ratings in both movie 'i' and 'k'
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
				result = 1 / (double)(1 + sqrt(sum));
				// result = log2(result);
				mSim->set(i, j, result);
				mSim->set(j, i, result);
			}
		}
	}

	cout << endl;

	return 0;
}

double euclidean::setCik(int fIndex, int sIndex)
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
		return acum; //it needs some adjust to be regularized
	else if(qtd_common >= 5)
		return acum;

	return INT_MIN;
}