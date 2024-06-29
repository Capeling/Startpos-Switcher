#include "UILayer.hpp"
#include "Geode/loader/Log.hpp"
#include "PlayLayer.hpp"

using namespace geode::prelude;

bool HookUILayer::init(GJBaseGameLayer* baseGame) {
    if(!UILayer::init(baseGame))
        return false;

    if(auto playLayer = typeinfo_cast<PlayLayer*>(baseGame)) {
        auto director = CCDirector::sharedDirector();
        auto winSize = director->getWinSize();

        m_fields->m_switcherMenu = CCMenu::create();
        m_fields->m_switcherMenu->setPosition(ccp(winSize.width / 2, director->getScreenBottom() + 17.f));
        m_fields->m_switcherMenu->setID("startpos-switcher-menu"_spr);

        m_fields->m_switcherLabel = CCLabelBMFont::create("0/0", "bigFont.fnt");
        m_fields->m_switcherLabel->setID("startpos-switcher-label"_spr);
        m_fields->m_switcherLabel->setScale(0.6);

        auto nextSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
        auto prevSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
        nextSpr->setScale(0.6);
        prevSpr->setScale(0.6);
        nextSpr->setFlipX(true);

        m_fields->m_nextSwitcherBtn = CCMenuItemExt::createSpriteExtra(nextSpr, [this](CCObject* sender){
            auto playLayer = static_cast<HookPlayLayer*>(PlayLayer::get());
            playLayer->updateStartPos(playLayer->m_fields->m_startPosIdx + 1);
        });
        m_fields->m_nextSwitcherBtn->setID("startpos-switcher-next-btn"_spr);

        m_fields->m_prevSwitcherBtn = CCMenuItemExt::createSpriteExtra(prevSpr, [this](CCObject* sender){
            auto playLayer = static_cast<HookPlayLayer*>(PlayLayer::get());
            playLayer->updateStartPos(playLayer->m_fields->m_startPosIdx - 1);
        });
        m_fields->m_prevSwitcherBtn->setID("startpos-switcher-prev-btn"_spr);

        m_fields->m_switcherMenu->addChild(m_fields->m_prevSwitcherBtn);
        m_fields->m_switcherMenu->addChild(m_fields->m_switcherLabel);
        m_fields->m_switcherMenu->addChild(m_fields->m_nextSwitcherBtn);
        m_fields->m_switcherMenu->setLayout(AxisLayout::create()->setAutoScale(false)->setGap(10));

        if(Mod::get()->getSettingValue<bool>("hideBtns")) {
            m_fields->m_prevSwitcherBtn->setVisible(false);
            m_fields->m_nextSwitcherBtn->setVisible(false);
        }

        this->addChild(m_fields->m_switcherMenu);
    }

    return true;
}

void HookUILayer::updateUI() {
    auto playLayer = static_cast<HookPlayLayer*>(PlayLayer::get());

        if(playLayer->m_fields->m_startPosObjects.empty()) {
            m_fields->m_switcherMenu->setVisible(false);
            return;
        } else {
            m_fields->m_switcherMenu->setVisible(true);
        }

    m_fields->m_switcherLabel->setString(fmt::format("{}/{}", playLayer->m_fields->m_startPosIdx, playLayer->m_fields->m_startPosObjects.size()).c_str());
    m_fields->m_switcherLabel->limitLabelWidth(40, 0.6f, 0);

    auto setting = Mod::get()->getSettingValue<double>("opacity");
    auto opacity = setting / 100 * 255;

    m_fields->m_switcherMenu->stopActionByTag(69);
    if(m_fields->m_firstUpdate && Mod::get()->getSettingValue<bool>("hide")) {
        m_fields->m_switcherMenu->setOpacity(opacity);
        m_fields->m_firstUpdate = false;
    } else {
        auto action = CCSequence::create(CCEaseInOut::create(CCFadeTo::create(0.3f, 255), 2), CCDelayTime::create(0.5), CCEaseInOut::create(CCFadeTo::create(0.5f, opacity), 2), nullptr);
        action->setTag(69);
        m_fields->m_switcherMenu->runAction(action);
    }

}

void HookUILayer::keyDown(cocos2d::enumKeyCodes p0) {
    UILayer::keyDown(p0);
    auto playLayer = static_cast<HookPlayLayer*>(PlayLayer::get());

    if(playLayer && !playLayer->m_fields->m_startPosObjects.empty()) {
        if(p0 == enumKeyCodes::KEY_Q) {
            playLayer->updateStartPos(playLayer->m_fields->m_startPosIdx - 1);
            return;
        }

        if(p0 == enumKeyCodes::KEY_E) {
            playLayer->updateStartPos(playLayer->m_fields->m_startPosIdx + 1);
            return;
        }
    }
}