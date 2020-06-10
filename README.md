# kmeansclustering
k-Means Clustering algorithm implemented in C++. Used as a subroutine for Portfolio Optimisation. Lots of interview questions ask for this algorithm so I have decided to implement this from scratch to improve my understanding of the algorithm. 

k-Means clustering allows us to cluster data. It allows us to group similar datapoints together. It does this by ensuring that the total variance within each group is minimised. This variance is calculated using sum-of-square euclidean distance between each datapoint and the cluster center.

The algorithm implemented within is officially known as the Lloyd's algorithm. 

There are essentially three steps:

1. Initialise the cluster. We randomly select k points which become the "generating points" (or cluster center). We effectively have k clusters now.

2. We assign every data point to a cluster, by measuring how close it is to each cluster center. It will be assigned to the cluster that it is closest to.

3. We then recalculate the center of each cluster and set those to be the new generating points. We recalculate by simply taking the mean of the previous cluster.

4. Repeat steps 2-3.

The k-Means clustering algorithm has two hyperparameters: the number of iterations we want to repeat steps 2-3, and the number of centers.

Many simplifications were made here: we are using only two dimensions and also pre-set the number of clusters. In fact this is one of the shortcomings of the k-Means clustering algorithm - we have to know the number of clusters beforehand. 
The random initialisation can also result in poor clusters. There is actually another algorithm, k-means++ that chooses the intial cluster centers using probabilities that are proportional to the distance from a point that has already been chosen to be the center. 
This means that the initial cluster centers will be as far away from each other as possible, making for good clusters.

k-means also suffers from the curse of dimensionality i.e. data becomes more sparse in high dimensions. It is also quite inefficient - it is a O(n^2) algorithm. But it's simple to explain and intuitive.

The jupyter notebook helps visualise the clustering output.

