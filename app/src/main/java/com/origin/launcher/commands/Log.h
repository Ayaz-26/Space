#pragma once
#include <string>

namespace com {
namespace space {
namespace launcher {
namespace hooks {

enum class LogLevel {
    INFO,
    WARN,
    ERROR
};

class Log {
public:
    static void enable();
    static void disable();
    static bool isEnabled();

    static void info(const std::string& msg);
    static void warn(const std::string& msg);
    static void error(const std::string& msg);

private:
    static bool enabled;

    static void sendToChat(const std::string& msg, LogLevel level);
};

} // namespace hooks
} // namespace launcher
} // namespace space
} // namespace com