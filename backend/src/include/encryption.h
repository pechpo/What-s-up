//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_ENCRYPTION_H
#define WHAT_S_UP_ENCRYPTION_H
// include/utils/encryption.h
#pragma once

#include <string>

class Encryption {
public:
    static const size_t SALT_SIZE = 16; // 常量定义

    std::string hashPassword(const std::string& password);
    std::string encryptData(const std::string& data);
    std::string decryptData(const std::string& encryptedData);

    // 其他可能的成员函数声明
};

#endif //WHAT_S_UP_ENCRYPTION_H
