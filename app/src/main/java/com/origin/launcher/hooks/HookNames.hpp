#pragma once
namespace HookNames {
    // Movement / input
    static constexpr const char* MovePlayerPacket       = "MovePlayerPacket";
    static constexpr const char* PlayerAuthInputPacket  = "PlayerAuthInputPacket";

    // Combat / entity
    static constexpr const char* AddEntityPacket        = "AddEntityPacket";
    static constexpr const char* SetHealthPacket        = "SetHealthPacket";
    static constexpr const char* MobEffectPacket        = "MobEffectPacket";

    // World / blocks / chunks
    static constexpr const char* UpdateBlockPacket      = "UpdateBlockPacket";
    static constexpr const char* LevelChunkPacket       = "LevelChunkPacket";

    // Inventory / transactions
    static constexpr const char* InventoryTransaction   = "InventoryTransactionPacket";

    // Connection control
    static constexpr const char* DisconnectPacket       = "DisconnectPacket";

    // (Optional) low‑priority cosmetics
    static constexpr const char* PlaySoundPacket        = "PlaySoundPacket";
}