#include "HookManager.hpp"
#include "HookNames.hpp"
using namespace SpaceHooks;

// If you can query your loader for addresses, declare it here.
// Replace with your real API or fill addresses manually.
extern "C" uintptr_t MtGetHookAddress(const char* name); // <-- your loader, if available

// Call this once at startup (e.g., from JNI_OnLoad or your client init).
extern "C" void InitSpaceHooks() {
    // Example: fetch from loader (preferred)
    const char* names[] = {
        HookNames::MovePlayerPacket,
        HookNames::PlayerAuthInputPacket,
        HookNames::AddEntityPacket,
        HookNames::SetHealthPacket,
        HookNames::MobEffectPacket,
        HookNames::UpdateBlockPacket,
        HookNames::LevelChunkPacket,
        HookNames::InventoryTransaction,
        HookNames::DisconnectPacket,
        // HookNames::PlaySoundPacket, // usually not needed
    };

    for (auto* n : names) {
        uintptr_t addr = MtGetHookAddress ? MtGetHookAddress(n) : 0;
        HookManager::registerHook(n, addr);
    }

    HookManager::dump();
}