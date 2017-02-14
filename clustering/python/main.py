from sklearn.cluster import AffinityPropagation
from sklearn import metrics
from sklearn.datasets.samples_generator import make_blobs
from scipy.sparse import coo_matrix

import sys

centers = [
	[1, 1],
	[-1, -1],
	[1, -1]
]

# centers = [
# 	[5, 3, 0],
# 	[5, 1, 2],
# 	[1, 0, 5]
# ]
# 


X, labels_true = make_blobs(n_samples=300, centers=centers, cluster_std=0.5,random_state=0)

print type(X), sys.getsizeof(X)

X = coo_matrix(X)

print type(X), sys.getsizeof(X)

af = AffinityPropagation(preference=-50).fit(X)
cluster_centers_indices = af.cluster_centers_indices_
labels = af.labels_

n_clusters_ = len(cluster_centers_indices)

print('Estimated number of clusters: %d' % n_clusters_)
print("Homogeneity: %0.3f" % metrics.homogeneity_score(labels_true, labels))
print("Completeness: %0.3f" % metrics.completeness_score(labels_true, labels))
print("V-measure: %0.3f" % metrics.v_measure_score(labels_true, labels))
print("Adjusted Rand Index: %0.3f"
      % metrics.adjusted_rand_score(labels_true, labels))
print("Adjusted Mutual Information: %0.3f"
      % metrics.adjusted_mutual_info_score(labels_true, labels))
# print("Silhouette Coefficient: %0.3f"
      # % metrics.silhouette_score(X, labels, metric='sqeuclidean'))
