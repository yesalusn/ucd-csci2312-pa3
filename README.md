# ucd-csci2312-pa3
Programming assignment 3 for an undergraduate object-oriented programming course with C++.

#### Notes
1. ~~From [PA3](https://ucdenver.instructure.com/courses/327553/pages/programming-assignment-3)~~
   1. ~~`Cluster::__id` + generator~~
   2. ~~`Cluster::Centroid` inner class + private member~~
   3. ~~`Cluster::Move`~~
   4. ~~`Cluster::pickPoints`~~
   5. ~~`Cluster` score computing functions~~
   6. ~~`Cluster::operator<<` to include the `Cluster::__id`~~
   7. ~~`KMeams`~~
   8. ~~`Kmeans` score computing function~~
2. From [PA4](https://ucdenver.instructure.com/courses/327552/pages/programming-assignment-4)
   1. Exceptions
     * `DimensionalityMismatchEx`
     * `OutOfBoundsEx`
     * `RemoveFromEmptyEx`
     * `OutOfBoundsEx`
     * `ZeroClustersEx`
   2. `std::vector` for `Point`
   3. `std::forward_list` for `Cluster`
   4. `std::vector` for clusters and initial centroids in `KMeans`
   5. `std::unordered_map` to hash-n-cache the distances
   6. `Cluster::operator>>` to count exceptions from `Point::operator>>` + public getters
   
