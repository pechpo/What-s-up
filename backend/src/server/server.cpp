//
// Created by zixin on 23-8-23.
//
// src/server/server.cpp

#include "server.h"
#include <boost/bind.hpp>

Server::Server(boost::asio::io_context& io_context, const std::string& address, unsigned short port)
        : io_context_(io_context),
          acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(address), port)) {
}

Server::~Server() {
    stop();
}

void Server::start() {
    accept();
}

void Server::stop() {
    acceptor_.close();
    for (auto connection : connections_) {
        delete connection;
    }
    connections_.clear();
}

void Server::accept() {
    Connection* new_connection = new Connection(io_context_);
    new_connection->set_message_handler(boost::bind(&Server::handle_message, this, new_connection, _1));
    acceptor_.async_accept(new_connection->socket(),
                           boost::bind(&Server::handle_accept, this, new_connection, boost::asio::placeholders::error));
}

void Server::handle_accept(Connection* connection, const boost::system::error_code& error) {
    if (!error) {
        connections_.insert(connection);
        connection->start();
        accept(); // 继续接受下一个连接
    } else {
        delete connection;
    }
}

void Server::handle_message(Connection* connection, const std::string& message) {
    // 处理来自客户端的消息
    for (auto conn : connections_) {
        if (conn != connection) {
            conn->send(message); // 转发消息给其他客户端
        }
    }
}
