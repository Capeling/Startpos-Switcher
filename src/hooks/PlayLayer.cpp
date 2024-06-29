#include "PlayLayer.hpp"
#include "Geode/binding/PlayLayer.hpp"
#include "Geode/loader/Log.hpp"
#include "UILayer.hpp"

using namespace geode::prelude;

void HookPlayLayer::addObject(GameObject* obj) {
    if(auto startPosObj = typeinfo_cast<StartPosObject*>(obj)) {
        m_fields->m_startPosObjects.push_back(startPosObj);
    }

    PlayLayer::addObject(obj);
}

void HookPlayLayer::updateStartPos(int idx) {

    std::sort(m_fields->m_startPosObjects.begin(), m_fields->m_startPosObjects.end(), [](auto* a, auto* b) { return a->getPositionX() < b->getPositionX(); });

    if(idx < 0) idx = m_fields->m_startPosObjects.size();
    if(idx > m_fields->m_startPosObjects.size()) idx = 0;

    if(idx == 0) {
        m_isTestMode = false;
        updateTestModeLabel();
    } else {
        m_isTestMode = true;
        updateTestModeLabel();
    }

    m_currentCheckpoint = nullptr;
    m_fields->m_startPosIdx = idx;

    auto object = idx > 0 ? m_fields->m_startPosObjects[idx - 1] : nullptr;
    setStartPosObject(object);

    if(m_isPracticeMode)
        resetLevelFromStart();

    resetLevel();
    startMusic();

    static_cast<HookUILayer*>(m_uiLayer)->updateUI();
}

void HookPlayLayer::createObjectsFromSetupFinished() {
    PlayLayer::createObjectsFromSetupFinished();

    if(this->m_startPosObject) {
        auto currentIdx = find(m_fields->m_startPosObjects.begin(), m_fields->m_startPosObjects.end(), this->m_startPosObject) - m_fields->m_startPosObjects.begin();
        log::info("currentIdx: {}", currentIdx);
        m_fields->m_startPosIdx = currentIdx + 1;
    }

    static_cast<HookUILayer*>(m_uiLayer)->updateUI();
}