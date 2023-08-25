//
// Created by zixin on 23-8-23.
//
// src/media/media.cpp
#include "media.h"
#include <iostream>

void MediaHandler::startCall(const std::string& from_user, const std::string& to_user) {
    // 创建通话会话
    // 这可能涉及设置音频和视频编解码器、建立网络连接等
    std::cout << "Starting call from " << from_user << " to " << to_user << "\n";

    // 可以添加代码来启动音频和视频流
    // ...
}

void MediaHandler::endCall(const std::string& from_user, const std::string& to_user) {
    // 结束通话会话
    // 这可能涉及断开网络连接、释放资源等
    std::cout << "Ending call from " << from_user << " to " << to_user << "\n";

    // 可以添加代码来停止音频和视频流
    // ...
}

// 可能需要更多的方法来处理通话事件，例如暂停/恢复、静音等...

//如何在即时通讯软件中实现音视频通话这部分完全不会喵

