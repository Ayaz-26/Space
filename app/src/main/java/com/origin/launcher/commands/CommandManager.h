#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>

namespace com {
namespace space {
namespace launcher {
namespace commands {

class CommandManager {
public:
    using CommandFn = std::function<void(const std::vector<std::string>& args)>;

    // Register a command (ex: ".log")
    static void registerCommand(const std::string& name, CommandFn fn, const std::string& help = "");

    // Execute from string (ex: ".log on")
    static void execute(const std::string& line);

    // List all commands (for help menu)
    static std::vector<std::string> listCommands();

private:
    static std::unordered_map<std::string, CommandFn>& getRegistry();
    static std::unordered_map<std::string, std::string>& getHelp();
};

} // namespace commands
} // namespace launcher
} // namespace space
} // namespace com