from sklearn.cluster import AffinityPropagation
from scipy.sparse import coo_matrix
from numpy import *
import sys

def getMedianValue(simValues):
	# getting median value
	dataSorted = sort(simValues)
	size = len(dataSorted)

	if(size % 2 == 0):
		median = ( (dataSorted[size/2]) + (dataSorted[size/2 - 1]) )/2
	else:
		median = dataSorted[size/2]

	return median

def readSimMatrix(simMatPath):
	i = array([])
	j = array([])
	data = array([])
	counter = 0;
	accum = 0;

	print "[INFO] Reading sim matrix.."
	# with open("Similarities_toy_Sim.txt") as f:
	# with open("Similarities.txt") as f:
	with open(simMatPath) as f:
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
	print "[INFO] Preferences: ", median, " (median of similarities)"

	return i,j,data, median

def readRatings(ratingsPath):
	# dict of users
	# standard => user1 = [
	# 	[movie1, ratingOfMovie1],
	# 	[movie2, ratingOfMovie2],
	# 	.
	# 	..
	# 	[movieN, ratingOfMovieN]
	# ]
	ratings = {}
	print "[INFO] Reading user ratings.."

	with open(ratingsPath) as f:
		content = f.readlines()

	user = ""

	for i in range(0, len(content)):
		line = content[i]
		line = line.strip().split()
		if(i % 2 == 0):
			user = int(line[0])
			ratings[user] = []
		else:
			rat = []
			for j in range(0, len(line), 2):
				rat.append([int(line[j]), float(line[j+1])]) 
			ratings[user] = rat
	
	return ratings

def generateClustersFile(af):
	indices = af.cluster_centers_indices_
	labels = af.labels_
	labels_len = len(labels)

	clusters = {}

	for i in range(0, labels_len):
		# print "user (", i + 1, ") cluster: ", indices[labels[i]]

		if(indices[labels[i]] in clusters):
			c = clusters[indices[labels[i]]]
			c.append(i)
		else:
			c = [i]

		clusters[indices[labels[i]]] = c

	with open("clusters.dat", "w") as file:
		for key in clusters:
			# print key
			file.write(str(key) + "\n")
			users = clusters[key]
			for u in users:
				file.write(str(u) + " " + str(u) + "\n")
				# print " " + str(u)
	return clusters

def accumulateRatings(clusters, totalRatings):
	# list of clusters -> list of movies -> list of ratings
	accumulator = {}
	for cluster, users in clusters.items():
		accumCluster = {}
		# print cluster, users
		for user in users:
			userRatings = totalRatings[user];
			# print user, userRatings
			for rating in userRatings:
				movie = rating[0]
				rat = rating[1]

				if(movie in accumCluster):
					m = accumCluster[movie]
					m.append(rat)
				else:
					m = [rat]
				accumCluster[movie] = m
		accumulator[cluster] = accumCluster

	return accumulator

def generateReprByFrequence(ratingsAccumulated):
	print ratingsAccumulated

	exit(1)

def generateReprByMean(ratingsAccumulated):
	print ratingsAccumulated

	exit(1)

def main(simMatPath, ratingsPath):
	i,j,data, median = readSimMatrix(simMatPath)
	# convert to sparse matrix
	simMatrix = coo_matrix((data,(i, j)))
	# clustering method
	af = AffinityPropagation(damping=0.9, preference=median,affinity='precomputed').fit(simMatrix.toarray())
	# generate clusters.dat
	clusters = generateClustersFile(af)
	# read ratings
	ratings = readRatings(ratingsPath)

	# generate representative clusters
	# accumulate clusters
	ratingsAccumulated = accumulateRatings(clusters, ratings)
	# [TODO] generate repr. clusters by frequence
	generateReprByFrequence(ratingsAccumulated)
	# [TODO] generate repr. clusters by mean
	generateReprByMean(ratingsAccumulated)

	print('Clusters indices: ', af.cluster_centers_indices_)
	print('Clusters labels: ', af.labels_)
	print('Estimated number of clusters: %d' % len(af.cluster_centers_indices_))

if __name__ == '__main__':
	if(len(sys.argv) != 3):
		print "[ERROR] Mssing arguments"
		print "$ python ap.py SIMILARITY_MATRIX_PATH RATINGS_PATH"
		exit(1)
	main(sys.argv[1], sys.argv[2])