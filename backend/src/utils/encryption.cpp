//
// Created by zixin on 23-8-23.
//
// src/utils/encryption.cpp
//#include "encryption.h"
//#include <openssl/sha.h>
//#include <sstream>
//#include <iomanip>
//
//std::string Encryption::hashPassword(const std::string& password) {
//    // 使用SHA-256对密码进行散列
//    unsigned char hash[SHA256_DIGEST_LENGTH];
//    SHA256_CTX sha256;
//    SHA256_Init(&sha256);
//    SHA256_Update(&sha256, password.c_str(), password.size());
//    SHA256_Final(hash, &sha256);
//
//    // 将散列值转换为十六进制字符串
//    std::ostringstream ss;
//    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
//        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
//    }
//
//    return ss.str(); // 返回十六进制散列字符串
//}
//
//std::string Encryption::encryptData(const std::string& data) {
//    // 在此处实现数据加密逻辑，例如使用AES加密
//    // ...
//}
//
//std::string Encryption::decryptData(const std::string& encryptedData) {
//    // 在此处实现数据解密逻辑，例如使用AES解密
//    // ...
//}
//
//// 可能需要更多的方法来处理不同的加密和解密需求...