#include "syncer.h"

syncer::syncer(string clusterPrefix, string reprPrefix)
{
	mClusterPrefix = clusterPrefix;
	mReprPrefix = reprPrefix;
	mRepr = new vector<Representative*>();	
}

syncer::~syncer()
{
	for (int i = 0; i < mRepr->size(); ++i)
		delete mRepr->at(i);
	delete mRepr;
	cout << "[Finishing syncer..]" << endl;
}

void syncer::Process(int nMulti)
{
	cout << "Cluster prefix: " << mClusterPrefix << endl;
	cout << "Representative prefix: " << mReprPrefix << endl;
	string tempPath;

	for (int i = 0; i < nMulti; ++i)
	{
		tempPath = to_string(i+1) + ".dat";
		Representative *repr = new Representative(mClusterPrefix + tempPath, mReprPrefix + tempPath);
		repr->Process();
		mRepr->push_back(repr);
	}
}