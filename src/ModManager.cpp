#include "ModManager.hpp"

using namespace geode::prelude;

ModManager* ModManager::sharedState() {
    static ModManager instance;
    return &instance;
}

ModManager::ModManager() {
    m_dontFadeOnStart = geode::Mod::get()->getSettingValue<bool>("hide");
    m_hideBtns = geode::Mod::get()->getSettingValue<bool>("hideBtns");
    m_ignoreDisabled = geode::Mod::get()->getSettingValue<bool>("ignoreDisabled");
    m_opacity = geode::Mod::get()->getSettingValue<double>("opacity") / 100 * 255;
}

$on_mod(Loaded) {
    auto mm = ModManager::sharedState();
    
    listenForSettingChanges("hide", [mm](bool val) {
        mm->m_dontFadeOnStart = val;
    });
    
    listenForSettingChanges("hideBtns", [mm](bool val) {
        mm->m_hideBtns = val;
    });
    
    listenForSettingChanges("ignoreDisabled", [mm](bool val) {
        mm->m_ignoreDisabled = val;
    });
    
    listenForSettingChanges("opacity", [mm](double val) {
        mm->m_opacity = val / 100 * 255;
    });
}