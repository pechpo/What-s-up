//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_CLUSTERING_H
#define WHAT_S_UP_CLUSTERING_H
#pragma once
#include <vector>
#include <unordered_map>
#include <QtTypes>

class KMeans {
public:
    KMeans(int k); // k is the number of clusters

    // Run K-means clustering
    std::vector<std::vector<std::pair<quint32, std::vector<double>>>> run(const std::unordered_map<quint32, std::vector<int>>& users);

private:
    int k_; // Number of clusters

    // Map tags to random real numbers and convert them to feature vectors
    std::unordered_map<quint32, std::vector<double>> mapTagsToFeatures(const std::unordered_map<quint32, std::vector<int>>& users);

    // Calculate the Euclidean distance between two vectors
    double distance(const std::vector<double>& a, const std::vector<double>& b);

    // Randomly select K initial centroids from the data
    std::vector<std::vector<double>> initializeCentroids(const std::unordered_map<quint32, std::vector<double>>& data);
};

#endif //WHAT_S_UP_CLUSTERING_H
