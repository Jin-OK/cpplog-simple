#include "simplelog.hpp"

int main()
{
    // First, through macro calls (recommended)
    LOG_INFO("Application started");
    LOG_WARN("Low memory detected: ", 1024, "MB available");
    LOG_ERROR("Failed to open file: ", "config.txt", " with error code: ", 2);

    // The second is called by invoking a static class
    LOG().log(LogLevel::INFO, "This is a test message with multiple arguments: ", 42, " and ", 3.14);
    LOG().log(LogLevel::WARN, "This is a warning message with a string: ", "Warning!");
    LOG().log(LogLevel::ERR, "Failed to open file: ", "data.txt", " with error code: ", 5);

    return 0;
}