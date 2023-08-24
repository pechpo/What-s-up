// src/main.cpp

#include "server.h"
#include <boost/asio.hpp>

int main() {
    boost::asio::io_context io_context;
    Server server(io_context, "127.0.0.1", 8080);
    server.start();
    io_context.run();
    return 0;
}


