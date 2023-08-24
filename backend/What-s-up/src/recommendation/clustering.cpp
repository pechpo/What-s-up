//
// Created by zixin on 23-8-23.
//
// src/recommendation/clustering.cpp
#include "clustering.h"
#include <cmath>
#include <random>
#include <algorithm>

KMeans::KMeans(int k) : k_(k) {
}

std::unordered_map<std::string, std::vector<double>> KMeans::convertToFeatures(const std::unordered_map<std::string, std::vector<std::string>>& users) {
    // 将用户标签转换为数值向量
    // 在这个例子中，我们可以简单地使用标签的哈希值
    std::unordered_map<std::string, std::vector<double>> features;
    for (const auto& [userId, tags] : users) {
        std::vector<double> featureVector;
        for (const auto& tag : tags) {
            featureVector.push_back(std::hash<std::string>{}(tag));
        }
        features[userId] = featureVector;
    }
    return features;
}

double KMeans::distance(const std::vector<double>& a, const std::vector<double>& b) {
    // 计算两个向量之间的欧几里得距离
    double sum = 0.0;
    for (size_t i = 0; i < a.size() && i < b.size(); ++i) {
        double diff = a[i] - b[i];
        sum += diff * diff;
    }
    return std::sqrt(sum);
}

std::vector<std::vector<double>> KMeans::initializeCentroids(const std::unordered_map<std::string, std::vector<double>>& data) {
    // 从数据中随机选择K个初始中心
    std::vector<std::vector<double>> centroids;
    std::vector<std::vector<double>> values;
    for (const auto& item : data) {
        values.push_back(item.second);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(values.begin(), values.end(), g);
    centroids.assign(values.begin(), values.begin() + k_);
    return centroids;
}

std::vector<std::vector<std::pair<std::string, std::vector<double>>>> KMeans::run(const std::unordered_map<std::string, std::vector<std::string>>& users) {
    // 转换用户标签为特征向量
    auto data = convertToFeatures(users);

    // 随机选择初始中心
    auto centroids = initializeCentroids(data);

    std::vector<std::vector<std::pair<std::string, std::vector<double>>>> clusters;
    bool converged = false;

    while (!converged) {
        // 1. 分配每个数据点到最近的中心
        clusters.clear();
        clusters.resize(k_);
        for (const auto& [userId, feature] : data) {
            int nearestCluster = 0;
            double minDistance = std::numeric_limits<double>::max();
            for (int i = 0; i < k_; ++i) {
                double d = distance(feature, centroids[i]);
                if (d < minDistance) {
                    minDistance = d;
                    nearestCluster = i;
                }
            }
            clusters[nearestCluster].emplace_back(userId, feature);
        }

        // 2. 重新计算中心
        converged = true; // 假设已收敛
        for (int i = 0; i < k_; ++i) {
            std::vector<double> newCentroid(data.begin()->second.size(), 0.0);
            for (const auto& [userId, feature] : clusters[i]) {
                for (size_t j = 0; j < feature.size(); ++j) {
                    newCentroid[j] += feature[j];
                }
            }
            for (double& value : newCentroid) {
                value /= clusters[i].size();
            }

            // 检查是否收敛
            if (distance(newCentroid, centroids[i]) > 1e-5) {
                converged = false;
            }

            centroids[i] = newCentroid;
        }
    }

    return clusters;
}

//你的`clustering.h`和`clustering.cpp`文件看起来已经很完整了。K-means聚类算法的实现也是正确的。以下是我对代码的一些评估和可能的优化建议：
//
//1. **特征转换**：在`convertToFeatures`函数中，你使用了标签的哈希值作为特征。这种方法虽然简单，但可能不是最佳选择，因为哈希冲突可能导致不同的标签具有相同的哈希值。在实际应用中，你可能需要更复杂的特征工程来表示用户的兴趣和偏好。
//
//2. **数据维度一致性**：你的代码假设所有用户的特征向量具有相同的维度。如果有些用户有更多或更少的标签，可能会导致问题。你可能需要确保所有特征向量具有相同的长度，或者在计算距离时处理长度不一致的情况。
//
//3. **空集群的处理**：K-means算法有时可能会导致空集群（即某个集群中没有任何数据点）。你的代码没有处理这种情况。虽然在许多情况下这可能不是问题，但在某些数据分布下可能会导致问题。一种常见的解决方案是将空集群的中心重新初始化为数据集中的一个随机点。
//
//4. **效率**：K-means算法的运行时间可能会变得非常慢，特别是当数据集很大或维度很高时。你可能需要考虑一些优化，例如使用更有效的数据结构或并行化计算。
