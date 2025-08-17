#include "LogCommand.h"
#include "com/space/launcher/hooks/HookManager.h"
#include "com/space/launcher/hooks/HookNames.h"
#include <android/log.h>

using namespace com::space::launcher::commands;
using namespace com::space::launcher::hooks;

bool LogCommand::enabled = false;

void LogCommand::registerCmd() {
    CommandManager::registerCommand(".log",
        [](const std::vector<std::string>& args) {
            if (args.empty()) {
                warn("Usage: .log on/off");
                return;
            }
            if (args[0] == "on") enable();
            else if (args[0] == "off") disable();
            else warn("Usage: .log on/off");
        },
        "Enable/disable logging"
    );
}

void LogCommand::enable() {
    enabled = true;
    info("Logging enabled");
}

void LogCommand::disable() {
    info("Logging disabled");
    enabled = false;
}

bool LogCommand::isEnabled() { return enabled; }

void LogCommand::info(const std::string& msg) {
    if (!enabled) return;
    sendToChat("[INFO] " + msg, LogLevel::INFO);
}
void LogCommand::warn(const std::string& msg) {
    if (!enabled) return;
    sendToChat("[WARN] " + msg, LogLevel::WARN);
}
void LogCommand::error(const std::string& msg) {
    if (!enabled) return;
    sendToChat("[ERROR] " + msg, LogLevel::ERROR);
}

void LogCommand::sendToChat(const std::string& msg, LogLevel level) {
    std::string colored = msg;
    switch (level) {
        case LogLevel::INFO:  colored = "§7" + msg; break;  // gray
        case LogLevel::WARN:  colored = "§e" + msg; break;  // yellow
        case LogLevel::ERROR: colored = "§c" + msg; break;  // red
    }

    // call Minecraft's SendChat hook if available
    auto sendChat = HookManager::get<void(*)(const std::string&)>(HookNames::SendChatMessage);
    if (sendChat) sendChat(colored);

    // also logcat for debugging
    __android_log_print(ANDROID_LOG_DEBUG, "SpaceLog", "%s", msg.c_str());
}