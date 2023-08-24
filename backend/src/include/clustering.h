//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_CLUSTERING_H
#define WHAT_S_UP_CLUSTERING_H
#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class KMeans {
public:
    KMeans(int k); // k是聚类数量

    // 运行K-means聚类
    std::vector<std::vector<std::pair<std::string, std::vector<double>>>> run(const std::unordered_map<std::string, std::vector<std::string>>& users);

private:
    int k_; // 聚类数量

    // 将用户标签转换为数值向量
    std::unordered_map<std::string, std::vector<double>> convertToFeatures(const std::unordered_map<std::string, std::vector<std::string>>& users);

    // 计算两个向量之间的欧几里得距离
    double distance(const std::vector<double>& a, const std::vector<double>& b);

    // 从数据中随机选择K个初始中心
    std::vector<std::vector<double>> initializeCentroids(const std::unordered_map<std::string, std::vector<double>>& data);
};

#endif //WHAT_S_UP_CLUSTERING_H
