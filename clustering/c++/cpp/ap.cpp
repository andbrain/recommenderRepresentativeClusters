#include "ap.h"

AP::AP(int iterations, double lambda, int elements)
{
	cout << "Initializing ap.." << endl;
	mIter = iterations;
	mLambda = lambda;
	mElements = elements;
	cout << "Iterations: " << mIter << endl;
	cout << "Damping factor: " << mLambda << endl;
	cout << "Elements size: " << mElements << endl;
}

AP::~AP()
{
	delete mR;
	delete mA;
	delete mE;
	cout << "Finishing ap.." << endl;
}

void AP::SetSimMatrix(mat* hash)
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
	mR = mS->clone(0);
	mA = mS->clone(0);
	mE = mS->clone(0);

	cout << "Start AP iteration: " << endl;

 	struct timeval begin, end;

 	/*Measuring time elapsed*/
 	gettimeofday(&begin, NULL);

	for(int m=0; m < mIter; m++) {
		cout << "(" << m + 1 << "/" << mIter << ")" << endl;

		UpdateResponsability();
		UpdateAvailability();
	}
	cout << endl;

	gettimeofday(&end, NULL);
	int tmili = (int) (1000 * (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) / 1000);

	cout << "Time Elapsed: " << tmili << " (milis)" << endl;
	cout << "Time Elapsed: " << (float)tmili/1000 << " (s)" << endl;


	PrintCluster();
}

void AP::UpdateResponsability()
{
	for(int i=0; i < mElements; i++) 
	{
		for(int k=0; k < mElements; k++)
		{
			double max = -1e100;
			for(int kk=0; kk<k; kk++)
			{
				if(mS->get(i,kk)+ mA->get(i,kk) > max)
					max = mS->get(i,kk) + mA->get(i,kk);
			}
			for(int kk=k+1; kk< mElements; kk++)
			{
				if(mS->get(i,kk)+ mA->get(i,kk)>max) 
					max = mS->get(i,kk)+mA->get(i,kk);
			}

			double resp = (1-mLambda)*(mS->get(i,k) - max) + mLambda*mR->get(i,k);
			mR->set(i,k,resp);
		}
	}
}

void AP::UpdateAvailability()
{

	for(int i=0; i< mElements; i++)
	{
		for(int k=0; k < mElements; k++)
		{
			if(i==k)
			{
				double sum = 0.0;
				for(int ii=0; ii<i; ii++)
					sum += max(0.0, mR->get(ii,k));
				for(int ii=i+1; ii < mElements; ii++)
					sum += max(0.0, mR->get(ii,k));
				double avail = (1-mLambda)*sum + mLambda*mA->get(i,k);
				mA->set(i,k,avail);
			} 
			else
			{
				double sum = 0.0;
				int maxik = max(i, k);
				int minik = min(i, k);
				for(int ii=0; ii<minik; ii++)
					sum += max(0.0, mR->get(ii,k));
				for(int ii=minik+1; ii<maxik; ii++)
					sum += max(0.0, mR->get(ii,k));
				for(int ii=maxik+1; ii<mElements; ii++)
					sum += max(0.0, mR->get(ii,k));
				
				double avail = (1-mLambda)*min(0.0, mR->get(k,k)+sum) + mLambda*mA->get(i,k);
				mA->set(i,k, avail);
			}
		}
	}
}

void AP::PrintCluster()
{
	map<int,vector<int>> clusters;
	vector<int> center;
	int N = mElements;

	for(int i=0; i<N; i++) 
	{
		mE->set(i,i, mR->get(i,i) + mA->get(i,i));
		if( mE->get(i,i) > 0)
			center.push_back(i);
	}

	int idx[N] = {0};

	for(int i=0; i<N; i++) {
		int idxForI = 0;
		double maxSim = -1e100;
		for(int j=0; j<center.size(); j++) {
			int c = center[j];
			if (mS->get(i,c)>maxSim) {
				maxSim = mS->get(i,c);
				idxForI = c;
			}
		}
		idx[i] = idxForI;
	}

	vector<int> vCluster;
	for(int i=0; i<N; i++) {

		map<int,vector<int>>::iterator itC = clusters.find(idx[i] + 1);

		if(itC != clusters.end())
		{
			itC->second.push_back(i);
		}
		else
		{
			vector<int> vCluster;
			vCluster.push_back(i);
			clusters.insert(make_pair(idx[i] + 1, vCluster));
		}
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

	int N = mElements;
	string output = "clusters.txt";
	fstream fs(output, ios::out);
	vector<int> vec;

	for (map<int, vector<int>>::iterator it = clusters->begin(); it!=clusters->end(); ++it)
	{
		
	}

	for (map<int, vector<int>>::iterator it = clusters->begin(); it!=clusters->end(); ++it)
	{
		vec = it->second;
		fs << it->first << endl;
		for (vector<int>::iterator itDocs = vec.begin(); itDocs!=vec.end(); ++itDocs)
			fs << *(itDocs) << " " << mS->get(it->first,*(itDocs)) << endl;
	}

	fs.close();
	cout << "Output file of clusters created: " << output << endl;
}

void AP::CalculateRepresentative(map<int,vector<int>> *clusters)
{
	map<int, map<int, vector<double>>> accumList = AccumulateRatings(clusters);

	MakeRepresentativeByFrequency(&accumList);
	MakeRepresentativeByMean(&accumList, clusters);
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

			if(vecMax[0].freq != vecMax[1].freq)
				fs << it2->first << " " << vecMax[0].index << endl;
		}
	}

	fs.close();
	cout << "Output Representative cluster by Frequency created: " << output << endl;

}

void AP::MakeRepresentativeByMean(map<int, map<int, vector<double>>> *accumList, map<int,vector<int>> *clusters)
{
	string output = "representativeClustersByMean.txt";
	fstream fs(output, ios::out);
	int upperBound; //value to validate mean of ratings
	int p = 3; //parameter for delimite what is highest ratings or lowest ratings
	double alpha = 0.6;

	for (map<int, map<int, vector<double>> >::iterator it = accumList->begin(); it != accumList->end(); ++it)
	{
		fs << it->first << endl;
		map<int, vector<double>> movieAux = it->second;

		// get number of users for actual cluster
		vector<int> users = clusters->at(it->first);
		
		upperBound = users.size() * alpha;

		for(map<int, vector<double>>::iterator it2 = movieAux.begin(); it2 != movieAux.end(); ++it2)
		{
			vector<double> userRatings = it2->second;
			// calculate frequency of rating highest than p
			map<double,int> counterHighest;
			// calculate frequency of rating lowest than p
			map<double,int> counterLowest;
			// the most frequency ratings for cluster
			map<double,int> counter;
			map<double,int>::iterator itCounter;

			for (std::vector<double>::iterator i = userRatings.begin(); i != userRatings.end(); ++i)
			{
				if(*i > p)
				{
					itCounter = counterHighest.find((*i));

					if(itCounter == counterHighest.end())
						counterHighest[(*i)] = 1;
					else
						itCounter->second++;
				}
				else if(*i < p)
				{
					itCounter = counterLowest.find((*i));

					if(itCounter == counterLowest.end())
						counterLowest[(*i)] = 1;
					else
						itCounter->second++;
				}
			}

			if(counterHighest.size() == counterLowest.size())
				continue;
			else if( counterHighest.size() > counterLowest.size() )
				counter = counterHighest;
			else
				counter = counterLowest;

			double reprValue = 0;
			int elements = 0;

			for (itCounter = counter.begin(); itCounter != counter.end(); ++itCounter)
			{
				reprValue += itCounter->first * itCounter->second;
				elements += itCounter->second;
			}

			reprValue = reprValue / elements;

			if(elements >= upperBound)
				fs << it2->first << " " << reprValue << endl;
		}
	}

	fs.close();
	cout << "Output Representative cluster by Mean created: " << output << endl;
}