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
    listenForSettingChanges("hide", [](bool val) {
        ModManager::sharedState()->m_dontFadeOnStart = val;
    });
    
    listenForSettingChanges("hideBtns", [](bool val) {
        ModManager::sharedState()->m_hideBtns = val;
    });
    
    listenForSettingChanges("ignoreDisabled", [](bool val) {
        ModManager::sharedState()->m_ignoreDisabled = val;
    });
    
    listenForSettingChanges("opacity", [](double val) {
        ModManager::sharedState()->m_opacity = val / 100 * 255;
    });
}