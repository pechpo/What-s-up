//
// Created by zixin on 23-8-23.
//
// src/server/connection.cpp

#include "connection.h"
#include <boost/bind.hpp>
#include <cstring>

Connection::Connection(boost::asio::io_context& io_context)
        : socket_(io_context), body_length_(0) {
}

Connection::~Connection() {
    stop();
}

void Connection::start() {
    readHeader();
}

void Connection::stop() {
    socket_.close();
}

void Connection::send(const std::string& message) {
    bool write_in_progress = !write_messages_.empty();
    write_messages_.push(message);
    if (!write_in_progress) {
        write();
    }
}

void Connection::set_message_handler(std::function<void(const std::string&)> handler) {
    message_handler_ = handler;
}

boost::asio::ip::tcp::socket& Connection::socket() {
    return socket_;
}

void Connection::readHeader() {
    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_data_, header_length),
                            boost::bind(&Connection::readBody, this));
}

void Connection::readBody() {
    body_length_ = std::atoi(read_data_);
    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_data_ + header_length, body_length_),
                            boost::bind(&Connection::handle_read, this, boost::asio::placeholders::error));
}

void Connection::write() {
    std::string message = write_messages_.front();
    write_messages_.pop();
    std::sprintf(write_data_, "%4d", message.size());
    std::memcpy(write_data_ + header_length, message.c_str(), message.size());
    boost::asio::async_write(socket_,
                             boost::asio::buffer(write_data_, header_length + message.size()),
                             boost::bind(&Connection::handle_write, this, boost::asio::placeholders::error));
}

void Connection::handle_read(const boost::system::error_code& error) {
    if (!error) {
        std::string message(read_data_ + header_length, body_length_);
        if (message_handler_) {
            message_handler_(message); // 调用回调处理消息
        }
        readHeader(); // 继续读取下一个消息
    } else {
        stop();
    }
}

void Connection::handle_write(const boost::system::error_code& error) {
    if (!error) {
        if (!write_messages_.empty()) {
            write(); // 继续发送下一个消息
        }
    } else {
        stop();
    }
}
