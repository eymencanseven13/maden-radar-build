#include <pl/Config.hpp>
#include <pl/Mod.hpp>
#include <pl/ModMenu.hpp>
#include <pl/Memory.hpp>
#include <cstring>
struct MadenConfig{int version=1;bool aktif=false;int mesafe=60;int yogunluk=3;bool elmas=true;bool demir=true;bool altin=false;bool redstone=false;bool lapis=false;bool zumrut=false;bool komur=false;bool bakir=false;bool quartz=false;bool ancient_debris=false;bool nether_altin=false;};
static constexpr const char*MOD_ID="madenradar.MadenRadar";
static constexpr const char*MOD_NAME="Maden Radar";
static bool gRadarEnabled=false;
static int gMesafe=60,gYogunluk=3;
class MadenRadarMod{
  ll::mod::NativeMod*mSelf=&ll::mod::NativeMod::current();
  std::optional<pl::config::ConfigFile<MadenConfig>>mConfig;
public:
  bool load(){mConfig.emplace();mConfig->load();if(mConfig)gMesafe=mConfig->value().mesafe;return true;}
  bool enable(){
    return pl::modmenu::ModuleBuilder(MOD_ID,MOD_NAME)
      .modId(mSelf->getId()).description("60 blok icindeki madenleri gosterir.").category("Gorsel").defaultEnabled(false)
      .onToggle([](std::string_view,bool en){gRadarEnabled=en;})
      .config("mesafe","Tarama Mesafesi",pl::modmenu::ConfigType::SliderInt,"60","10","60")
      .config("yogunluk","Partikul Yogunlugu",pl::modmenu::ConfigType::SliderInt,"3","1","5")
      .config("elmas","Elmas (Cyan)",pl::modmenu::ConfigType::Toggle,"true")
      .config("demir","Demir (Bej)",pl::modmenu::ConfigType::Toggle,"true")
      .config("altin","Altin (Sari)",pl::modmenu::ConfigType::Toggle,"false")
      .config("redstone","Redstone (Kirmizi)",pl::modmenu::ConfigType::Toggle,"false")
      .config("lapis","Lapis (Mavi)",pl::modmenu::ConfigType::Toggle,"false")
      .config("zumrut","Zumrut (Yesil)",pl::modmenu::ConfigType::Toggle,"false")
      .config("komur","Komur (Gri)",pl::modmenu::ConfigType::Toggle,"false")
      .config("bakir","Bakir (Turuncu)",pl::modmenu::ConfigType::Toggle,"false")
      .config("quartz","Quartz (Beyaz)",pl::modmenu::ConfigType::Toggle,"false")
      .config("ancient_debris","Ancient Debris (Kahve)",pl::modmenu::ConfigType::Toggle,"false")
      .config("nether_altin","Nether Altin (Sari)",pl::modmenu::ConfigType::Toggle,"false")
      .registerModule();
  }
  bool disable(){pl::modmenu::unregisterModule(MOD_ID);gRadarEnabled=false;if(mConfig)mConfig->save();return true;}
};
PL_REGISTER_MOD(MadenRadarMod);
