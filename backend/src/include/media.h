//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_MEDIA_H
#define WHAT_S_UP_MEDIA_H
// include/media/media.h
#pragma once

#include <string>

class MediaHandler {
public:
    void startCall(const std::string& from_user, const std::string& to_user);
    void endCall(const std::string& from_user, const std::string& to_user);

    // 其他可能的成员函数声明
};

#endif //WHAT_S_UP_MEDIA_H
