from sklearn.cluster import AffinityPropagation
from scipy.sparse import coo_matrix
from numpy import *
import sys

def readDataset():
	i = array([])
	j = array([])
	data = array([])

	print "[INFO] Constructing matrix.."
	# with open("Similarities_toy_Sim.txt") as f:
	# with open("Similarities.txt") as f:
	with open("ml100k/Similarities.txt") as f:
		content = f.readlines()

	# content = [line.strip().split() for line in content]
	for line in content:
		line = line.strip()
		line = line.split()
		i = append(i, int(line[0]) - 1)
		j = append(j, int(line[1]) - 1)
		data = append(data, float(line[2]))

	return i,j,data

def main():
	i,j,data = readDataset()
	
	# print i,j,data
	simMatrix = coo_matrix((data,(i, j)))

	# print type(simMatrix), sys.getsizeof(simMatrix)
	# print simMatrix.toarray()
	print simMatrix

	# af = AffinityPropagation(damping=0.9, preferences=0.014035).fit(simMatrix)
	# af = AffinityPropagation(damping=0.9, preference=0.014035, affinity='precomputed').fit(simMatrix.todense())

	# af = AffinityPropagation(damping=0.9, preference=0.014035, affinity='precomputed').fit(simMatrix.toarray())
	af = AffinityPropagation(damping=0.9, preference=0.014035,affinity='precomputed').fit(simMatrix.toarray())
	cluster_centers_indices = af.cluster_centers_indices_
	labels = af.labels_

	n_clusters_ = len(cluster_centers_indices)

	print('Clusters indices: ', af.cluster_centers_indices_)
	# print('Clusters centers: ', af.cluster_centers_.toarray())
	print('Clusters labels: ', af.labels_)
	print('Estimated number of clusters: %d' % n_clusters_)

if __name__ == '__main__':
	main()