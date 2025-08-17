#pragma once
#include <string>
#include <vector>
#include "CommandManager.h"

namespace com {
namespace space {
namespace launcher {
namespace commands {

enum class LogLevel {
    INFO,
    WARN,
    ERROR
};

class LogCommand {
public:
    static void registerCmd();

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

} // namespace commands
} // namespace launcher
} // namespace space
} // namespace com