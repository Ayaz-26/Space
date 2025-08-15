#pragma once
#include <unordered_map>
#include <string>
#include <mutex>
#include <cstdint>
#include "Log.hpp"

namespace SpaceHooks {

class HookManager {
public:
    // Register a hook address by name (string identifier).
    static bool registerHook(const std::string& name, uintptr_t addr) {
        if (addr == 0) {
            HOOKLOGW("registerHook: '%s' got nullptr/0 address", name.c_str());
            return false;
        }
        std::lock_guard<std::mutex> lk(mutex());
        auto& map = registry();
        map[name] = addr;
        HOOKLOGD("registerHook: '%s' -> 0x%llX", name.c_str(), (unsigned long long)addr);
        return true;
    }

    // Check if a hook is known.
    static bool has(const std::string& name) {
        std::lock_guard<std::mutex> lk(mutex());
        return registry().count(name) != 0;
    }

    // Get raw address (or 0 if missing).
    static uintptr_t getAddress(const std::string& name) {
        std::lock_guard<std::mutex> lk(mutex());
        auto it = registry().find(name);
        if (it == registry().end()) return 0;
        return it->second;
    }

    // Get typed function pointer. Returns nullptr if not registered.
    template <typename Fn>
    static Fn get(const std::string& name) {
        uintptr_t addr = getAddress(name);
        if (!addr) {
            HOOKLOGW("get: hook '%s' not registered", name.c_str());
            return nullptr;
        }
        return reinterpret_cast<Fn>(addr);
    }

    // Debug: list all hooks to logcat.
    static void dump() {
        std::lock_guard<std::mutex> lk(mutex());
        HOOKLOGD("---- HookManager dump (%zu entries) ----", registry().size());
        for (auto& kv : registry()) {
            HOOKLOGD("  %s -> 0x%llX", kv.first.c_str(), (unsigned long long)kv.second);
        }
        HOOKLOGD("---- end dump ----");
    }

private:
    static std::unordered_map<std::string, uintptr_t>& registry() {
        static std::unordered_map<std::string, uintptr_t> s;
        return s;
    }
    static std::mutex& mutex() {
        static std::mutex m;
        return m;
    }
};

} // namespace SpaceHooks