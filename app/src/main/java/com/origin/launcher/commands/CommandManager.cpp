#include "CommandManager.h"
#include <sstream>
#include <android/log.h>

#define CMDLOG(...) __android_log_print(ANDROID_LOG_DEBUG, "SpaceCmd", __VA_ARGS__)

namespace com {
namespace space {
namespace launcher {
namespace commands {

std::unordered_map<std::string, CommandManager::CommandFn>& CommandManager::getRegistry() {
    static std::unordered_map<std::string, CommandFn> registry;
    return registry;
}

std::unordered_map<std::string, std::string>& CommandManager::getHelp() {
    static std::unordered_map<std::string, std::string> help;
    return help;
}

void CommandManager::registerCommand(const std::string& name, CommandFn fn, const std::string& help) {
    getRegistry()[name] = fn;
    getHelp()[name] = help;
    CMDLOG("Registered command: %s", name.c_str());
}

void CommandManager::execute(const std::string& line) {
    if (line.empty()) return;

    std::istringstream iss(line);
    std::string name;
    iss >> name; // first word is command

    std::vector<std::string> args;
    std::string arg;
    while (iss >> arg) args.push_back(arg);

    auto& reg = getRegistry();
    auto it = reg.find(name);
    if (it != reg.end()) {
        it->second(args);
    } else {
        CMDLOG("Unknown command: %s", name.c_str());
    }
}

std::vector<std::string> CommandManager::listCommands() {
    std::vector<std::string> cmds;
    for (auto& kv : getRegistry()) cmds.push_back(kv.first + " - " + getHelp()[kv.first]);
    return cmds;
}

} // namespace commands
} // namespace launcher
} // namespace space
} // namespace com