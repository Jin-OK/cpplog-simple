#include "simplelog.hpp"

int main() {
    // First use the macro to log messages
    LOG_INFO("Application started");
    LOG_WARN("Low memory detected: ", 1024, "MB available");
    LOG_ERROR("Failed to open file: ", "config.txt", " with error code: ", 2);

    // Second use the class directly to log messages
    LOG().log(LogLevel::INFO, "This is a test message with multiple arguments: ", 42, " and ", 3.14);
    LOG().log(LogLevel::WARN, "This is a warning message with a string: ", "Warning!");
    LOG().log(LogLevel::ERR, "Failed to open file: ", "data.txt", " with error code: ", 5);
    
    return 0;
}