#include "ap.h"

AP::AP(int iterations, double lambda)
{
	cout << "Initializing ap.." << endl;
	mIter = iterations;
	mLambda = lambda;
}

AP::~AP()
{
	delete mR;
	// delete mA;
	// delete mE;
	cout << "Finishing ap.." << endl;
}

void AP::SetSimMatrix(Graph* hash)
{
	mS = hash;
}

void AP::SetRatings(Graph* hash)
{
	mRatings = hash;
}

void AP::Process()
{
	cout << "Processing AP.." << endl;
	AffinityPropagation();
}


void AP::AffinityPropagation()
{
	mR = mS->Clone();
	mR->Clear();

	mA = mS->Clone();
	mA->Clear();

	mE = mS->Clone();
	mE->Clear();


	cout << "Start AP iteration: " << endl;
	for(int m=0; m < mIter; m++) {
		cout << "( " << m + 1 << "/" << mIter << " )"<< endl;
		UpdateResponsability();
		UpdateAvailability();
	}

	PrintCluster();
}

//update responsibility
void AP::UpdateResponsability()
{
	int i, k, kk;
	Edge::iterator itAux, cef;

	int c1,c2;

	G::iterator cgf;
	cgf = mS->end();
	c1 = cgf->first;
	double value;
	//loop in vertexes
	for(G::iterator itNode = mS->begin(); itNode != mS->end(); ++itNode)
	{
		i = itNode->first;
		// cout << "i (" << i << "/" << c1 << ")"<< endl;

		cef = itNode->second->end();
		c2 = cef->first;
		//loop in edges
		for(Edge::iterator it = itNode->second->begin(); it != itNode->second->end(); ++it) {
			double max = -1e100;
			k = it->first;

			// cout << "\tk (" << k << "/" << c2 << ")" << endl;

			for(itAux = itNode->second->begin(); itAux != it; ++itAux) {
				kk = itAux->first;
				// cout << "kk1: " << kk << endl;
				
				if( mS->at(i)->at(kk) + mA->at(i)->at(kk) > max )
					max = mS->at(i)->at(kk) + mA->at(i)->at(kk);
			}

			itAux = it;
			itAux++;
			for(itAux; itAux != itNode->second->end(); ++itAux) {
				kk = itAux->first;
				// cout << "kk2: " << kk << endl;
				if ( mS->at(i)->at(kk) + mA->at(i)->at(kk) > max )
					max = mS->at(i)->at(kk) + mA->at(i)->at(kk);
			}
			value = (1 - mLambda)*(mS->at(i)->at(k) - max) + mLambda*mR->at(i)->at(k);
			mR->SetEdge(i,k,value);
		}
	}
}

void AP::UpdateAvailability()
{
	int i, k, ii;
	Edge::iterator itAux, itI, itMin, itMax;
	double value;

	for(G::iterator itNode = mS->begin(); itNode != mS->end(); ++itNode)
	{
		i = itNode->first;

		// cout << "i: " << i << endl;
		for(Edge::iterator it = itNode->second->begin(); it != itNode->second->end(); ++it) 
		{
			double sum = 0.0;
			k = it->first;
			// cout << "k: " << k << endl;

			if(i==k)
			{
				//TODO::check with pacience
				itI = itNode->second->find(i);

				if(itI == itNode->second->end())
					cout << "no index found" << endl;
				//continue if doesn't have i index incollection of edges
				//
				for(itAux = itNode->second->begin(); itAux != itI; ++itAux)
				{
					ii = itAux->first;

					// cout << "(i==k) ii1: " << ii << endl;
					
					sum += max(0.0, mR->at(ii)->at(k));
				}

				itAux = itI;
				itAux++;

				for(; itAux != itNode->second->end(); ++itAux)
				{
					ii = itAux->first;
					
					// cout << "(i==k) ii2: " << ii << endl;
					
					sum += max(0.0, mR->at(ii)->at(k));
				}

				value = (1-mLambda)*sum + mLambda*mA->at(i)->at(k);
				mA->SetEdge(i,k, value);
			}
			else
			{
				int maxik = max(i,k);
				int minik = min(i,k);

				itMin = itNode->second->find(minik);

				if(itMin == itNode->second->end())
				{
					cout << "no MIN index found" << endl;
					continue;
				}
				
				itMax = itNode->second->find(maxik);
				if(itMax == itNode->second->end())
				{
					cout << "no Max index found" << endl;
					continue;
				}

				for (itAux = itNode->second->begin(); itAux != itMin; ++itAux)
				{
					ii = itAux->first;

					// cout << "(i!=k) ii1: " << ii << endl;

					sum += max(0.0, mR->at(ii)->at(k));
				}

				itAux = itMin;
				itAux++;
				for (; itAux != itMax; ++itAux)
				{
					ii = itAux->first;

					// cout << "(i!=k) ii2: " << ii << endl;

					sum += max(0.0, mR->at(ii)->at(k));
				}

				itAux = itMax;
				itAux++;
				for (; itAux != itNode->second->end(); ++itAux)
				{
					ii = itAux->first;
					
					// cout << "(i!=k) ii3: " << ii << endl;

					sum += max(0.0, mR->at(ii)->at(k));
				}
				value = (1-mLambda)*min(0.0, mR->at(k)->at(k) + sum ) + mLambda*mA->at(i)->at(k);
				mA->SetEdge(i,k, value);
			}

		}

	}
}

void AP::PrintCluster()
{
	map<int,vector<int>> clusters;
	vector<int> center;
	int i,c,idxForI;
	double value, maxSim;
	for (G::iterator it = mS->begin(); it != mS->end(); ++it)
	{
		i = it->first;
		value = mR->at(i)->at(i) + mA->at(i)->at(i);
		mE->SetEdge(i,i,value);
		if(mE->at(i)->at(i) > 0)
			center.push_back(i);
	}

	int N = mS->Size();
	int idx[N] = {0};

	for (G::iterator it = mS->begin(); it != mS->end(); ++it)
	{
		
		idxForI = 0;
		maxSim = -1e100;
		i = it->first;

		for(int j=0; j < center.size(); ++j)
		{
			c = center[j];
			//TODO:: validate c index edge before
			
			if(mS->at(i)->at(c) > maxSim)
			{
				maxSim = mS->at(i)->at(c);
				idxForI = c;
			}
		}

		idx[i] = idxForI;
	}


	//output the assignment
	vector<int> vCluster;
	for(int i=0; i<N; i++) {

		map<int,vector<int>>::iterator itC = clusters.find(idx[i]);

		if(itC != clusters.end())
		{
			itC->second.push_back(i);
		}
		else
		{
			vector<int> vCluster;
			vCluster.push_back(i);
			clusters.insert(make_pair(idx[i], vCluster));
		}

		//since the index of data points starts from zero, I add 1 to let it start from 1
		// cout << i << ": " << idx[i] << endl; 
	}

	

	cout << endl;
	cout << "*****Print clusters****" << endl;	
	map<int, vector<int>>::iterator it = clusters.begin();

	vector<int> vec;
	for (; it != clusters.end(); ++it)
	{
		cout << "Cluster " << it->first << ":";
		cout << "[";
		vec = it->second;

		for (std::vector<int>::iterator i = vec.begin(); i != vec.end(); ++i)
		{
			cout  << " " << (*i);
		}

		cout << " ]" << endl;
	}

	cout << "Total of clusters: " << clusters.size() << endl;
	OutputClusters(&clusters);
	//Output train and test files
	CreateTrainFile(idx, mS->Size(), &clusters, 0.7);

	//Output representative clusters
	CalculateRepresentative(&clusters);
}

void AP::OutputClusters(map<int,vector<int>> *clusters)
{
	/*
		Standard of output

		cluster1
		document1 documentId1
		document2 documentId2
		cluster4
		document3 documentId3
		document4 documentId4
		.
		.
		.
		documentN documentIdN
	 */


	string output = "clusters.txt";
	fstream fs(output, ios::out);
	Vertex *v;
	int aux;
	vector<int> vec;

	for (map<int, vector<int>>::iterator it = clusters->begin(); it!=clusters->end(); ++it)
	{
		vec = it->second;

		fs << it->first << endl;

		for (vector<int>::iterator itDocs = vec.begin(); itDocs!=vec.end(); ++itDocs)
		{
			aux = *(itDocs);
			v = mS->at(aux);
			fs << aux << " " << v->GetId() << endl;
		}
	}

	fs.close();

	cout << "Output file of clusters created: " << output << endl;
}

void AP::CreateTrainFile(int *users, int size, map<int,vector<int>> *clusters, double percTrain)
{
	int qtdU = size;
	int uTrain = ceil(qtdU*percTrain);
	int uTest = qtdU - uTrain;

	// numerize cluster starting from 0
	map<int,int> numCluster;
	int cCluster = 0;
	for(map<int,vector<int>>::iterator it = clusters->begin(); it != clusters->end(); ++it)
	{
		numCluster[it->first] = cCluster;
		cCluster++;
	}

	/////////////////////
	///		trainY	  ///
	/////////////////////
	string output = "trainY.txt";
	fstream fsTrain(output, ios::out);

	for (int i = 0; i < uTrain; ++i)
	{
		// fsTrain << users[i] << endl;
		fsTrain << numCluster[users[i]] << endl;
	}

	fsTrain.close();
	cout << "Output TrainY created: " << output << endl;

	/////////////////////
	///		testY	  ///
	/////////////////////
	output = "testY.txt";
	fstream fsTest(output, ios::out);

	for (int i = uTrain; i < qtdU; ++i)
	{
		// fsTest << users[i] << endl;
		fsTest << numCluster[users[i]] << endl;
	}

	fsTest.close();
	cout << "Output TestY created: " << output << endl;	
}

void AP::CalculateRepresentative(map<int,vector<int>> *clusters)
{
	map<int, map<int, vector<double>>> accumList = AccumulateRatings(clusters);

	for (map<int, map<int, vector<double>> >::iterator it = accumList.begin(); it != accumList.end(); ++it)
	{
		cout << endl;
		cout << "Cluster (" << it->first << ")" << endl << endl;

		map<int, vector<double>> movieAux = it->second;

		for(map<int, vector<double>>::iterator it2 = movieAux.begin(); it2 != movieAux.end(); ++it2)
		{
			cout << "Item: " << it2->first << endl;

			vector<double> userRatings = it2->second;
			cout << "\tRatings: ";
			for (std::vector<double>::iterator i = userRatings.begin(); i != userRatings.end(); ++i)
			{
				cout << (*i) << " ";
			}
			cout << endl;
		}
	}

	MakeRepresentativeByFrequency(&accumList);
	// MakeRepresentativeByMean(clusters);
}

map<int, map<int, vector<double>> > AP::AccumulateRatings(map<int,vector<int>> *clusters)
{
	map<int, map<int, vector<double>> > accClusterRatings; //<cluster, <movie, vector of ratings> >
	map<int,vector<int>>::iterator it = clusters->begin();
	map<int,vector<double>>::iterator foundMov;
	//run over all clusers
	for(; it != clusters->end(); ++it)
	{
		map<int, vector<double> > accRatings; // <movie, vector of ratings>
		vector<int> users;
		users = it->second;

		Vertex *v;
		//get user ratings
		for (vector<int>::iterator i = users.begin(); i != users.end(); ++i)
		{
			v = mRatings->at((*i));

			//for each movie rated by user
			Edge::iterator itAux;
			for(itAux = v->begin(); itAux!= v->end(); ++itAux)
			{
				vector<double> accVec;
				foundMov = accRatings.find(itAux->first);

				//if found movie, add rating
				if(foundMov != accRatings.end())
				{
					accVec = foundMov->second;
					accVec.push_back(itAux->second);
					foundMov->second = accVec;
				}
				else
				{

					accVec.push_back(itAux->second);
					accRatings[itAux->first] = accVec;
				}
			}
		}

		//add in cluster acc
		accClusterRatings[it->first] = accRatings;
	}


	return accClusterRatings;
}

bool funcDec (PairValue i,PairValue j) { return (i.freq > j.freq); }

void AP::MakeRepresentativeByFrequency(map<int, map<int, vector<double>>> *accumList)
{
	string output = "representativeClustersByFreq.txt";
	fstream fs(output, ios::out);

	
	
	for (map<int, map<int, vector<double>> >::iterator it = accumList->begin(); it != accumList->end(); ++it)
	{
		fs << it->first << endl;
		map<int, vector<double>> movieAux = it->second;

		for(map<int, vector<double>>::iterator it2 = movieAux.begin(); it2 != movieAux.end(); ++it2)
		{
			fs << it2->first << " ";

			// calculate highest frequency of rating
			vector<double> userRatings = it2->second;
			map<double,int> counter;
			map<double,int>::iterator itCounter;

			for (std::vector<double>::iterator i = userRatings.begin(); i != userRatings.end(); ++i)
			{
				itCounter = counter.find((*i));

				if(itCounter == counter.end())
				{
					counter[(*i)] = 1;
				}
				else
				{
					itCounter->second++;
				}
			}

			vector<PairValue> vecMax;

			for (itCounter = counter.begin(); itCounter != counter.end(); ++itCounter)
			{
				PairValue pv;
				pv.index = itCounter->first;
				pv.freq = itCounter->second;
				vecMax.push_back(pv);
			}

			sort(vecMax.begin(), vecMax.end(), funcDec);

			if(vecMax[0].freq == vecMax[1].freq)
				fs << 0;
			else
				fs << vecMax[0].index;
			
			fs << endl;
		}
	}

	fs.close();
}

void AP::MakeRepresentativeByMean(map<int, map<int, vector<double>>> *accumList)
{
	string output = "representativeClustersByMean.txt";
	fstream fs(output, ios::out);

	fs.close();

}