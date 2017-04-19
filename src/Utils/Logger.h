//
// Created by wojciech on 15.04.17.
//

#ifndef GLPRESS_LOGGER_H
#define GLPRESS_LOGGER_H

#include <string>
#include <iostream>
#include <chrono>

class Logger {
private:
    static std::string timePointToString(std::chrono::system_clock::time_point point) {
        time_t time = std::chrono::system_clock::to_time_t(point);
        std::string res = std::ctime(&time);
        res.resize(res.size() - 1);
        return res;
    }

public:
    static void info(std::string message) {
        std::cout << "[INFO][" + timePointToString(std::chrono::system_clock::now()) + "] " << message << std::endl;
    }
};


#endif //GLPRESS_LOGGER_H
