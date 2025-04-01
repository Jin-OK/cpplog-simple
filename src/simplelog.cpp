/**
 * @file simplelog.cpp
 * @brief Implementation of simple logging library
 * @author Jin-OK
 * @date 2025/04/04
 * 
 * @license MIT License (http://opensource.org/licenses/MIT)
 * 
 * Copyright (c) 2025 Jin-OK
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "simplelog.hpp"
#include <iostream>
#include <sstream>
#include <mutex>
#include <chrono>
#include <iomanip>
#if defined(_WIN32)
#include <windows.h>
#endif

class Logger::Impl {
private:
    std::mutex log_mutex;
    
    static constexpr const char* RED_BG = "\033[41m";
    static constexpr const char* GREEN_BG = "\033[42m";
    static constexpr const char* YELLOW_BG = "\033[43m";
    static constexpr const char* RESET = "\033[0m";
    
    // Get current time in the format [YYYY-MM-DD HH:MM:SS.mmm]
    std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;
        auto timer = std::chrono::system_clock::to_time_t(now);

        std::tm bt = {};
        #if defined(_WIN32)
            localtime_s(&bt, &timer);
        #else
            localtime_r(&timer, &bt);
        #endif

        std::ostringstream oss;
        oss << std::put_time(&bt, "[%Y-%m-%d %H:%M:%S.");
        oss << std::setfill('0') << std::setw(3) << ms.count() << "]";
        return oss.str();
    }

    // Format the message with variable arguments
    const char* getLevelColor(LogLevel level) {
        switch (level) {
            case LogLevel::ERR: return RED_BG;
            case LogLevel::WARN:  return YELLOW_BG;
            case LogLevel::INFO:  return GREEN_BG;
            default:              return RESET;
        }
    }

    // Get the level string representation
    std::string getLevelString(LogLevel level) {
        switch (level) {
            case LogLevel::ERR: return "[ERROR]";
            case LogLevel::WARN:  return "[WARN] ";
            case LogLevel::INFO:  return "[INFO] ";
            default:              return "[UNKNOWN]";
        }
    }

public:
    Impl() {
        #if defined(_WIN32)
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            DWORD dwMode = 0;
            if (GetConsoleMode(hOut, &dwMode)) {
                dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(hOut, dwMode);
            }
        }
        #endif
    }
    
    // Log the message with the specified log level
    void log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(log_mutex);
        std::cout << "\033[1m" << getCurrentTime() << " "
                << getLevelColor(level) << getLevelString(level) << RESET
                << "\033[0m ==> " << message << std::endl;
    }
};

Logger::Logger() : pImpl(std::make_unique<Impl>()) {}
Logger::~Logger() = default;

void Logger::logImpl(LogLevel level, const std::string& message) {
    pImpl->log(level, message);
}

SIMPLELOG_API Logger& LOG() {
    static Logger instance;
    return instance;
}