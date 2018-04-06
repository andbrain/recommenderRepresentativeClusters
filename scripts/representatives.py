from numpy import *
import sys
import operator

def retrieveClusters(clustersPath):
	clusters = {}
	print "[INFO] Reading clusters.."

	with open(clustersPath) as f:
		content = f.readlines()
	f.close()

	user = ""

	for i in range(0, len(content)):
		line = content[i]
		line = line.strip().split()
		clusterId = int(line[0])
		c = []
		for j in range(1,len(line)):
			c.append(int(line[j]))
		clusters[clusterId] = c
	return clusters

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
	f.close()
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

def representativeByFreq(ratings):
	values = {}

	for rating in ratings:
		if(rating in values):
			values[rating] += 1
		else:
			values[rating] = 1
	sortedRatings = sorted(values.items(), key=operator.itemgetter(1), reverse=True)
	
	# TODO:: Check if it returns 0 when 1st != 2nd element, and if the 2nd > 1(freq)
	if(len(sortedRatings) <= 1):
		return sortedRatings[0][0]
	if(sortedRatings[0][1] != sortedRatings[1][1]):
		return sortedRatings[0][0]
	else:
		return 0

def generateReprByFrequence(ratingsAccumulated):
	with open("recFreq.dat", "w") as file:
		for cluster, movies in ratingsAccumulated.items():
			file.write(str(cluster) + "\n")

			for movie,ratings in movies.items():				
				result = representativeByFreq(ratings)
				if(result != 0):
					file.write(str(movie) + " " + str(int(result)) + "\n")
		file.close()


def representativeByMean(ratings):
	# p as median element
	p = 3
	vHigh = []
	vLow = []

	for rating in ratings:
		if(rating < p):
			vLow.append(rating)
		elif(rating > p):
			vHigh.append(rating)

	if(len(vLow) == len(vHigh)):
		return 0
	elif(len(vLow) > len(vHigh)):
		mean = vLow
	else:
		mean = vHigh

	acc = 0
	for res in mean:
		acc += res

	return acc/len(mean)

def generateReprByMean(ratingsAccumulated):
	with open("recMean.dat", "w") as file:
		for cluster, movies in ratingsAccumulated.items():
			file.write(str(cluster) + "\n")

			for movie,ratings in movies.items():				
				result = representativeByMean(ratings)
				if(result != 0):
					file.write(str(movie) + " " + str(round(result,2)) + "\n")
		file.close()

def representativeByAverage(ratings):
	# p as median element
	average = 0.0

	for rating in ratings:
		average+=rating
	
	return average/size(ratings)

def generateReprByAverage(ratingsAccumulated):
	with open("recAverage.dat", "w") as file:
		for cluster, movies in ratingsAccumulated.items():
			file.write(str(cluster) + "\n")

			for movie,ratings in movies.items():				
				result = representativeByAverage(ratings)
				if(result != 0):
					file.write(str(movie) + " " + str(round(result,2)) + "\n")
		file.close()

def main(clustersPath, ratingsPath):
	
	print "[INFO] Retrieving of clusters.."	

	# read clusters
	clusters = retrieveClusters(clustersPath)

	# read ratings
	ratings = readRatings(ratingsPath)

	### generate representative clusters ###

	# accumulate clusters
	ratingsAccumulated = accumulateRatings(clusters, ratings)

	# generate repr. clusters by frequence
	print "[INFO] Created representative cluster by frequence.."	
	generateReprByFrequence(ratingsAccumulated)
	
	# generate repr. clusters by mean
	print "[INFO] Created representative cluster by mean of more frequents.."	
	generateReprByMean(ratingsAccumulated)
	
	# generate repr. clusters by average
	print "[INFO] Created representative cluster by mean.."	
	generateReprByAverage(ratingsAccumulated)

	print "[INFO] Representative .. ok!"	
if __name__ == '__main__':
	if(len(sys.argv) != 3):
		print "[ERROR] Missing arguments"
		print "$ python ap.py <CLUSTERS_PATH> <RATINGS_PATH>"
		exit(1)
	main(sys.argv[1], sys.argv[2])