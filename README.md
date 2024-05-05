# Kmeans-Clustering
 Implementation of the K-means clustering Algorithm in both Python and C.

# Introduction
  
The K-means algorithm is a popular clustering method for finding a partition of N unlabeled
observations into K distinct clusters, where K is a parameter of the method.

Given a set of N datapoints x1, x2, . . . , xN ∈ Rd
, the goal is to group the data into K ∈ N
clusters, each datapoint is assigned to exactly one cluster and the number of clusters K is such
that 1 < K < N. Each cluster k is represented by it’s centroid which is the mean µk ∈ Rd of the
cluster’s members.

# Algorithm
1. Initialize centroids as first k datapoints: µk = xk, ∀k ∈ K.
2. repeat:
3. Assign every xi to the closest cluster k: argmin<k>d(xi, µk), ∀k 1 ≤ k ≤ K.
4. Update the centroids: µk = 1/|k|* sum(xi : xi∈k ).
5. until convergence: (∆µk < epsilon) OR (iteration_number = iter).

# Requirements
1. 1 < K < N, K ∈ N.
2. 1 < iter < 1000, iter ∈ N.  If iter is not provided, default value is 200.
3. The data points privided in a .txt file.
4.  epsilon = 0.001

# C
compile with the following command:
 `gcc -ansi -Wall -Wextra -Werror -pedantic-errors kmeans.c -o kmeans`
 Running example : `./kmeans 3 100 <input_data.txt`     // k=3, iter=100

 # Python
 Running example:  `kmeans.py 3 100 input_data.txt` .
 רו
 רו
   

