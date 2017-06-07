#include "similarity_base.h"

similarity_base::similarity_base()
{
}

similarity_base::~similarity_base()
{

}

void similarity_base::SetMatrix(mat *ratings)
{
	mRatings = ratings;
	mSim = new mat(mRatings->size());
}

mat* similarity_base::GetMatrix()
{
	return mSim;
}