//
// Created by zixin on 23-8-23.
//
// src/recommendation/clustering.cpp

#include "clustering.h"
#include <cmath>
#include <random>
#include <algorithm>
#include <iterator>
#include <limits>
#include <QDebug>

KMeans::KMeans(int k) : k_(k) {}

double KMeans::get(const int &label) {
    if (mapping.count(label)) {
        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        mapping[label] = distribution(generator);
    }
    return mapping[label];
}

std::unordered_map<quint32, std::vector<double>> KMeans::mapTagsToFeatures(const std::unordered_map<quint32, std::vector<int>>& users) {
    std::unordered_map<quint32, std::vector<double>> features;
    for (const auto& [userId, tags] : users) {
        std::vector<double> mapped_tags;
        int id = 0;
        for (const auto& tag : tags) {
            mapped_tags.push_back(tag == 1 ? get(id) : 0.0);
            id++;
        }
        features[userId] = mapped_tags;
    }
    return features;
}

double KMeans::distance(const std::vector<double>& a, const std::vector<double>& b) {
    double dist = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        dist += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sqrt(dist);
}

std::vector<std::vector<double>> KMeans::initializeCentroids(const std::unordered_map<quint32, std::vector<double>>& data) {
    std::vector<std::vector<double>> centroids;
    std::vector<std::pair<quint32, std::vector<double>>> temp_centroids;
    std::sample(data.begin(), data.end(), std::back_inserter(temp_centroids), k_, std::mt19937{std::random_device{}()});
    for (const auto& pair : temp_centroids) {
        centroids.push_back(pair.second);
    }
    return centroids;
}

std::vector<std::vector<std::pair<quint32, std::vector<double>>>> KMeans::run(const std::unordered_map<quint32, std::vector<int>>& users) {
    auto features = mapTagsToFeatures(users);
    auto centroids = initializeCentroids(features);
    std::vector<std::vector<std::pair<quint32, std::vector<double>>>> clusters(k_);

    // Iterative K-means clustering
    for (int iter = 0; iter < 100; ++iter) {
        // Assignment step
        std::vector<std::vector<std::pair<quint32, std::vector<double>>>>(k_).swap(clusters);
        for (const auto& [userId, featureVec] : features) {
            double min_dist = std::numeric_limits<double>::max();
            int cluster_idx = 0;
            for (int i = 0; i < k_; ++i) {
                double dist = distance(featureVec, centroids[i]);
                if (dist < min_dist) {
                    min_dist = dist;
                    cluster_idx = i;
                }
            }
            clusters[cluster_idx].push_back({userId, featureVec});
        }

        // Update step
        for (int i = 0; i < k_; ++i) {
            std::vector<double> new_centroid(features.begin()->second.size(), 0.0);
            for (const auto& [userId, featureVec] : clusters[i]) {
                for (size_t j = 0; j < featureVec.size(); ++j) {
                    new_centroid[j] += featureVec[j];
                }
            }
            for (size_t j = 0; j < new_centroid.size(); ++j) {
                new_centroid[j] /= clusters[i].size();
            }
            centroids[i] = new_centroid;
        }
    }

    return clusters;
}
