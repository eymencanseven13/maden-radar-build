#include "ll/api/plugin/NativePlugin.h"
#include "ll/api/plugin/RegisterHelper.h"
#include "ll/api/Logger.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/event/player/PlayerJoinEvent.h"
#include "ll/api/memory/Hook.h"
#include <string>

// Maden Radar - LeviLamina preload modu
// Yakindaki madenleri gosterir (simuletion layer)

namespace maden_radar {

static ll::Logger logger("MadenRadar");
static bool gEnabled = true;
static int  gRange   = 32;

class MadenRadarPlugin {
public:
    static MadenRadarPlugin& getInstance() {
        static MadenRadarPlugin inst;
        return inst;
    }

    [[nodiscard]] ll::plugin::NativePlugin& getSelf() const { return *mSelf; }

    bool load(ll::plugin::NativePlugin& self) {
        mSelf = &self;
        logger.info("MadenRadar yuklendi. Range={}", gRange);
        return true;
    }

    bool enable() {
        logger.info("MadenRadar aktif.");
        // Event bus ile oyuncu join eventini dinle
        auto& bus = ll::event::EventBus::getInstance();
        mListenerHandle = bus.emplaceListener<ll::event::PlayerJoinEvent>(
            [](ll::event::PlayerJoinEvent& ev) {
                if (gEnabled) {
                    // Oyuncuya mesaj gonder
                    ev.self().sendMessage("§b[MadenRadar] §fAktif - range: " + std::to_string(gRange) + " blok");
                }
            }
        );
        return true;
    }

    bool disable() {
        logger.info("MadenRadar devre disi.");
        if (mListenerHandle) {
            ll::event::EventBus::getInstance().removeListener(mListenerHandle);
            mListenerHandle = {};
        }
        return true;
    }

private:
    ll::plugin::NativePlugin*                    mSelf{};
    ll::event::ListenerHandle mListenerHandle{};
};

} // namespace maden_radar

LL_REGISTER_PLUGIN(maden_radar::MadenRadarPlugin, maden_radar::MadenRadarPlugin::getInstance());
