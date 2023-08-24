//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_CONNECTION_H
#define WHAT_S_UP_CONNECTION_H
#pragma once
#include <boost/asio.hpp>
#include <functional>
#include <string>
#include <queue>

class Connection {
public:
    Connection(boost::asio::io_context& io_context);
    ~Connection();

    void start(); // 开始读取
    void stop();  // 停止连接
    void send(const std::string& message); // 发送消息

    // 设置消息处理回调
    void set_message_handler(std::function<void(const std::string&)> handler);

    boost::asio::ip::tcp::socket& socket(); // 获取socket引用

private:
    void readHeader(); // 读取消息头
    void readBody();   // 读取消息体
    void write();      // 异步写入消息
    void handle_read(const boost::system::error_code& error);
    void handle_write(const boost::system::error_code& error);

    boost::asio::ip::tcp::socket socket_;
    enum { header_length = 4 };
    enum { max_body_length = 512 };
    char read_data_[header_length + max_body_length];
    char write_data_[header_length + max_body_length];
    size_t body_length_;
    std::function<void(const std::string&)> message_handler_; // 消息处理回调
    std::queue<std::string> write_messages_; // 待发送的消息队列
};

#endif //WHAT_S_UP_CONNECTION_H
