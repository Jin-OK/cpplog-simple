/**
 * @file simplelog.hpp
 * @brief Simple logging library with colored output
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

#ifndef SIMPLELOG_HPP
#define SIMPLELOG_HPP

#include <string>
#include <memory>
#include <iostream>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

#if defined(_WIN32)
    #if defined(SIMPLELOG_EXPORTS)
        #define SIMPLELOG_API __declspec(dllexport)
    #else
        #define SIMPLELOG_API __declspec(dllimport)
    #endif
#else
    #define SIMPLELOG_API __attribute__((visibility("default")))
#endif   

// Define macros for logging with different log levels API
#define LOG_ERROR(...) LOG().log(LogLevel::ERR, __VA_ARGS__, "\nat (FILE:", __FILE__, " - LINE:", __LINE__, ")")
#define LOG_WARN(...)  LOG().log(LogLevel::WARN, __VA_ARGS__, "\nat (FILE:", __FILE__, " - LINE:", __LINE__, ")")
#define LOG_INFO(...)  LOG().log(LogLevel::INFO, __VA_ARGS__)



enum class LogLevel { ERR, WARN, INFO };

class SIMPLELOG_API Logger {
public:
    Logger();
    ~Logger();
    
    template<typename... Args>
    void log(LogLevel level, Args&&... args) {
        logImpl(level, formatMessage(std::forward<Args>(args)...));
    }

private:
    class SIMPLELOG_API Impl; // Ensure Impl has DLL interface
    std::unique_ptr<Impl> pImpl;
    
    template<typename... Args>
    std::string formatMessage(Args&&... args) {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        return oss.str();
    }
    
    void logImpl(LogLevel level, const std::string& message);
};

SIMPLELOG_API Logger& LOG();

#endif  