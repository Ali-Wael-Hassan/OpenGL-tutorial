#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

enum class LogLevel {
    Info, Warning, Error
};

class Logger {
public:
    static void Log(LogLevel level, const std::string& message) {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        struct tm timeInfo;
        localtime_s(&timeInfo, &now);

        // start block
        std::cout << "-----------------------------------------------------------" << std::endl;

        // print timestamp
        std::cout << "[" << std::put_time(&timeInfo, "%H:%M:%S") << "]";

        // print level
        switch (level) {
            case LogLevel::Info:    std::cout << " [  INFO  ] | "; break;
            case LogLevel::Warning: std::cout << " [ WARNING ] | "; break;
            case LogLevel::Error:   std::cout << " [  ERROR  ] | "; break;
        }

        // print the message
        std::cout << message << std::endl;
        // end block
        std::cout << "-----------------------------------------------------------" << std::endl;
    }
};

// Macros for usage
#define LOG_INFO(x)    Logger::Log(LogLevel::Info, x)
#define LOG_WARN(x)    Logger::Log(LogLevel::Warning, x)
#define LOG_ERROR(x)   Logger::Log(LogLevel::Error, x)