#include <float.h>
#include <math.h>
#include "kmeans.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/**
 * Assigns each point in the dataset to a cluster based on the distance from that cluster.
 *
 * The return value indicates how many points were assigned to a _different_ cluster
 * in this assignment process: this indicates how close the algorithm is to completion.
 * When the return value is zero, no points changed cluster so the clustering is complete.
 *
 * @param dataset set of all points with current cluster assignments
 * @param num_points number of points in the dataset
 * @param centroids array that holds the current centroids
 * @param num_clusters number of clusters - hence size of the centroids array
 * @return the number of points for which the cluster assignment was changed
 */
int assign_clusters(struct point* dataset, int num_points, struct point *centroids, int num_clusters)
{
#ifdef DEBUG
    printf("\nStarting assignment phase:\n");
#endif
    int cluster_changes = 0;
							dummyMethod1();
#pragma omp parallel for schedule(runtime)
    for (int n = 0; n < num_points; ++n) {
#ifdef DEBUG_OMP
        char msg[50];
        sprintf(msg, "Point %d", n);
        omp_debug(msg);
#endif
        double min_distance = DBL_MAX; // init the min distance to a big number
        int closest_cluster = -1;
        for (int k = 0; k < num_clusters; ++k) {
            // calc the distance passing pointers to points since the distance does not modify them
            double distance_from_centroid = euclidean_distance(&dataset[n], &centroids[k]);
            if (distance_from_centroid < min_distance) {
                min_distance = distance_from_centroid;
                closest_cluster = k;
            }
        }
        // if the point was not already in the closest cluster, move it there and count changes
        if (dataset[n].cluster != closest_cluster) {
            dataset[n].cluster = closest_cluster;
            cluster_changes++;
#ifdef TRACE
            debug_assignment(&dataset[n], closest_cluster, &centroids[closest_cluster], min_distance);
#endif
        }
    }
							dummyMethod2();
    return cluster_changes;
}

/**
 * Calculates new centroids for the clusters of the given dataset by finding the
 * mean x and y coordinates of the current members of the cluster for each cluster.
 *
 * The centroids are set in the array passed in, which is expected to be pre-allocated
 * and contain the previous centroids: these are overwritten by the new values.
 *
 * @param dataset set of all points with current cluster assigments
 * @param num_points number of points in the dataset
 * @param centroids array to hold the centroids - already allocated
 * @param num_clusters number of clusters - hence size of the centroids array
 */
void calculate_centroids(struct point* dataset, int num_points, struct point *centroids, int num_clusters)
{
    double sum_of_x_per_cluster[num_clusters];
    double sum_of_y_per_cluster[num_clusters];
    int num_points_in_cluster[num_clusters];
							dummyMethod1();
#pragma omp parallel for schedule(runtime)
    for (int k = 0; k < num_clusters; ++k) {
        sum_of_x_per_cluster[k] = 0.0;
        sum_of_y_per_cluster[k] = 0.0;
        num_points_in_cluster[k] = 0;
    }
							dummyMethod2();

    // loop over all points in the database and sum up
    // the x coords of clusters to which each belongs
    // FAIL: Note pramgma omp for schedule(runtime) here with anything but static scheduling will result in
    //       every point being assigned to the same cluster
    //       this is because of a data race on num_points_in_cluster[k]
//#pragma omp parallel for schedule(static,1) //schedule(runtime)
							dummyMethod3();
    for (int n = 0; n < num_points; ++n) {
        // use pointer to struct to avoid creating unnecessary copy in memory
        struct point *p = &dataset[n];
        int k = p->cluster;
        sum_of_x_per_cluster[k] += p->x;
        sum_of_y_per_cluster[k] += p->y;
        // count the points in the cluster to get a mean later
        num_points_in_cluster[k]++;
    }
							dummyMethod4();

    // the new centroids are at the mean x and y coords of the clusters
							dummyMethod1();
#pragma omp parallel for schedule(runtime)
    for (int k = 0; k < num_clusters; ++k) {
        struct point new_centroid;
        // mean x, mean y => new centroid
        new_centroid.x = sum_of_x_per_cluster[k] / num_points_in_cluster[k];
        new_centroid.y = sum_of_y_per_cluster[k] / num_points_in_cluster[k];
        centroids[k] = new_centroid;
    }
							dummyMethod2();
}
int dummyMethod1(){
    return 0;
}
int dummyMethod2(){
    return 0;
}
int dummyMethod3(){
    return 0;
}
int dummyMethod4(){
    return 0;
}