#include "mat.h"

mat::mat(int line, int column)
{
	mLine = line;
	mColumn = column;
	mData = new vector<map<int, double> *>(line);

	for(int i = 0; i < line; ++i)
		mData->at(i) = new map<int, double>();
}

mat::~mat()
{
	vector<map<int, double>* >::iterator it = mData->begin();
	for (int i = 0; i < mData->size(); ++i)
	{
		map<int, double>* column = mData->at(i);
		delete column;
	}

	delete mData;
}

void mat::debug()
{
	vector<map<int, double>* >::iterator itLine = mData->begin();

	for(int i =0 ;i < mData->size(); ++i)
	{
		cout << i << endl;

		map<int, double>*column = mData->at(i);
		map<int, double>::iterator itColumn = column->begin();

		for(;itColumn != column->end(); ++itColumn)
		{
			cout << "\t" << itColumn->first << " -> " << itColumn->second << endl;
		}
	}
}

mat* mat::clone(double def_value)
{
	mat *newMat = new mat(mLine, mColumn);

	for(int i = 0; i < mData->size(); ++i)
	{
		map<int, double>*column = mData->at(i);
		map<int, double>::iterator itColumn = column->begin();

		for(;itColumn != column->end(); ++itColumn)
		{
			newMat->set(i, itColumn->first, def_value);
		}
	}

	return newMat;
}