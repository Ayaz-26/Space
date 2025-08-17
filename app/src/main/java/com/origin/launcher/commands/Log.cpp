#include "Log.h"
#include "com/space/launcher/hooks/HookManager.h"
#include "com/space/launcher/hooks/HookNames.h"
#include <android/log.h>

using namespace com::space::launcher::hooks;

bool Log::enabled = false;

void Log::enable() { enabled = true; info("Logging enabled"); }
void Log::disable() { info("Logging disabled"); enabled = false; }
bool Log::isEnabled() { return enabled; }

void Log::info(const std::string& msg) {
    if (!enabled) return;
    sendToChat("[INFO] " + msg, LogLevel::INFO);
}

void Log::warn(const std::string& msg) {
    if (!enabled) return;
    sendToChat("[WARN] " + msg, LogLevel::WARN);
}

void Log::error(const std::string& msg) {
    if (!enabled) return;
    sendToChat("[ERROR] " + msg, LogLevel::ERROR);
}

void Log::sendToChat(const std::string& msg, LogLevel level) {
    // here you hook into Minecraft’s "SendChatMessage" function
    // for now, just send different colors based on level

    std::string colored = msg;
    switch (level) {
        case LogLevel::INFO:  colored = "§7" + msg; break;  // gray
        case LogLevel::WARN:  colored = "§e" + msg; break;  // yellow
        case LogLevel::ERROR: colored = "§c" + msg; break;  // red
    }

    // Example: find SendChatPacket hook and push
    auto sendChat = HookManager::get<void(*)(const std::string&)>(HookNames::SendChatMessage);
    if (sendChat) {
        sendChat(colored);
    }

    // always also print to logcat for safety
    __android_log_print(ANDROID_LOG_DEBUG, "SpaceLog", "%s", msg.c_str());
}