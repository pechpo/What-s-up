//
// Created by 李嘉政 on 2023/8/30.
//

#ifndef BACKEND_LOG_H
#define BACKEND_LOG_H

#endif //BACKEND_LOG_H

#include <iostream>
#include <fstream>

class Log {
public:
    static Log *get_instance() {
        static Log instance;
        return &instance;
    }

    void log(const std::string &msg) {
        std::ofstream fout("log.txt", std::ios::app);
        fout << msg << std::endl;
        fout.close();
    }

    void log(const char *msg) {
        std::ofstream fout("log.txt", std::ios::app);
        fout << msg << std::endl;
        fout.close();
    }

    void log(const int &msg) {
        std::ofstream fout("log.txt", std::ios::app);
        fout << msg << std::endl;
        fout.close();
    }

    void log(const double &msg) {
        std::ofstream fout("log.txt", std::ios::app);
        fout << msg << std::endl;
        fout.close();
    }

    void log(const bool &msg) {
        std::ofstream fout("log.txt", std::ios::app);
        fout << msg << std::endl;
        fout.close();
    }

    void log(const char &msg) {
        std::ofstream fout("log.txt", std::ios::app);
        fout << msg << std::endl;
        fout.close();
    }

    void log(const unsigned char &msg) {
        std::ofstream fout("log.txt", std::ios::app);
        fout << msg << std::endl;
        fout.close();
    }

    void log(const long &msg) {
        std::ofstream fout("log.txt", std::ios::app);
        fout << msg << std::endl;
        fout.close();
    }

    void log(const unsigned long &msg) {
        std::ofstream fout("log.txt", std::ios::app);
        fout << msg << std::endl;
        fout.close();
    }

private:
    Log() = default;
    ~Log() = default;

};
