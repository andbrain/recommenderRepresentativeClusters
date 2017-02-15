from sklearn.cluster import AffinityPropagation
from scipy.sparse import coo_matrix
from numpy import *
import sys

def getMedianValue(simValues):
	# getting median value
	dataSorted = sort(simValues)
	size = len(dataSorted)
	print "Tamanho: ", size

	if(size % 2 == 0):
		median = ( (dataSorted[size/2]) + (dataSorted[size/2 - 1]) )/2
	else:
		median = dataSorted[size/2]

	return median

def readSimMatrix():
	i = array([])
	j = array([])
	data = array([])
	counter = 0;
	accum = 0;

	print "[INFO] Reading sim matrix.."
	# with open("Similarities_toy_Sim.txt") as f:
	# with open("Similarities.txt") as f:
	with open("similarities.dat") as f:
		content = f.readlines()

	# content = [line.strip().split() for line in content]
	for line in content:
		line = line.strip()
		line = line.split()
		i = append(i, int(line[0]) - 1)
		j = append(j, int(line[1]) - 1)
		value = float(line[2])
		data = append(data, value)
		accum += value;
		counter += 1
	
	median = getMedianValue(data)
	print "Preferences: ", median, " (median of similarities)"

	return i,j,data, median

def main():
	i,j,data, median = readSimMatrix()

	simMatrix = coo_matrix((data,(i, j)))

	# af = AffinityPropagation(damping=0.9, preferences=0.014035).fit(simMatrix)
	# af = AffinityPropagation(damping=0.9, preference=0.014035, affinity='precomputed').fit(simMatrix.todense())
	# af = AffinityPropagation(damping=0.9, preference=0.014035, affinity='precomputed').fit(simMatrix.toarray())
	af = AffinityPropagation(damping=0.9, preference=median,affinity='precomputed').fit(simMatrix.toarray())

	print('Clusters indices: ', af.cluster_centers_indices_)
	print('Clusters labels: ', af.labels_)
	print('Estimated number of clusters: %d' % len(af.cluster_centers_indices_))

if __name__ == '__main__':
	main()