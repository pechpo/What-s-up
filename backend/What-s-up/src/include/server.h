//
// Created by zixin on 23-8-23.
//

#ifndef WHAT_S_UP_SERVER_H
#define WHAT_S_UP_SERVER_H
#pragma once
#include "connection.h"
#include <boost/asio.hpp>
#include <set>

class Server {
public:
    Server(boost::asio::io_context& io_context, const std::string& address, unsigned short port);
    ~Server();

    void start(); // 开始监听
    void stop();  // 停止服务器

private:
    void accept(); // 异步接受连接
    void handle_accept(Connection* connection, const boost::system::error_code& error);
    void handle_message(Connection* connection, const std::string& message);

    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::set<Connection*> connections_; // 连接集合
};

#endif //WHAT_S_UP_SERVER_H
