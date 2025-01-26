#include "UILayer.hpp"
#include "PlayLayer.hpp"
#include "../ModManager.hpp"

using namespace geode::prelude;

bool HookUILayer::init(GJBaseGameLayer* baseGame) {
    if(!UILayer::init(baseGame))
        return false;

    if(auto playLayer = typeinfo_cast<PlayLayer*>(baseGame)) {
        auto director = CCDirector::sharedDirector();
        auto winSize = director->getWinSize();
        auto fields = m_fields.self();
        auto mm = ModManager::sharedState();

        fields->m_switcherMenu = CCMenu::create();
        fields->m_switcherMenu->setPosition(ccp(winSize.width / 2, director->getScreenBottom() + 17.f));
        fields->m_switcherMenu->setID("menu"_spr);

        fields->m_switcherLabel = CCLabelBMFont::create("0/0", "bigFont.fnt");
        fields->m_switcherLabel->setID("idx-label"_spr);
        fields->m_switcherLabel->setScale(0.6);

        bool gamepad = PlatformToolbox::isControllerConnected() && false;

        auto nextSpr = CCSprite::createWithSpriteFrameName(gamepad ? "controllerBtn_DPad_Right_001.png" : "GJ_arrow_02_001.png");
        auto prevSpr = CCSprite::createWithSpriteFrameName(gamepad ? "controllerBtn_DPad_Left_001.png" : "GJ_arrow_02_001.png");
        nextSpr->setScale(0.6);
        prevSpr->setScale(0.6);
        nextSpr->setFlipX(true);

        fields->m_nextSwitcherBtn = CCMenuItemExt::createSpriteExtra(nextSpr, [this](CCObject* sender){
            auto playLayer = static_cast<HookPlayLayer*>(PlayLayer::get());
            playLayer->updateStartPos(playLayer->m_fields->m_startPosIdx + 1);
        });
        fields->m_nextSwitcherBtn->setID("next-btn"_spr);

        fields->m_prevSwitcherBtn = CCMenuItemExt::createSpriteExtra(prevSpr, [this](CCObject* sender){
            auto playLayer = static_cast<HookPlayLayer*>(PlayLayer::get());
            playLayer->updateStartPos(playLayer->m_fields->m_startPosIdx - 1);
        });
        fields->m_prevSwitcherBtn->setID("prev-btn"_spr);

        fields->m_switcherMenu->addChild(fields->m_prevSwitcherBtn);
        fields->m_switcherMenu->addChild(fields->m_switcherLabel);
        fields->m_switcherMenu->addChild(fields->m_nextSwitcherBtn);
        fields->m_switcherMenu->setLayout(AxisLayout::create()->setAutoScale(false)->setGap(10));

        if(mm->m_hideBtns) {
            fields->m_prevSwitcherBtn->setVisible(false);
            fields->m_nextSwitcherBtn->setVisible(false);
        }

        this->addChild(fields->m_switcherMenu);
    }

    Loader::get()->queueInMainThread([this] {
        if(!PlayLayer::get()) return;

        this->defineKeybind("switch-next"_spr, [this](bool down) {
            auto playLayer = static_cast<HookPlayLayer*>(PlayLayer::get());
            if(down && !playLayer->m_fields->m_startPosObjects.empty() && playLayer->canPauseGame())
                playLayer->updateStartPos(playLayer->m_fields->m_startPosIdx + 1);

            return ListenerResult::Stop;
        });

        this->defineKeybind("switch-previous"_spr, [this](bool down) {
            auto playLayer = static_cast<HookPlayLayer*>(PlayLayer::get());

            if(down && !playLayer->m_fields->m_startPosObjects.empty() && playLayer->canPauseGame())
                playLayer->updateStartPos(playLayer->m_fields->m_startPosIdx - 1);

            return ListenerResult::Stop;
        });

    });

    return true;
}

void HookUILayer::updateUI() {
    auto playLayer = static_cast<HookPlayLayer*>(PlayLayer::get());
    auto fields = m_fields.self();
    auto mm = ModManager::sharedState();

        if(playLayer->m_fields->m_startPosObjects.empty()) {
            fields->m_switcherMenu->setVisible(false);
            return;
        } else {
            fields->m_switcherMenu->setVisible(true);
        }

    fields->m_switcherLabel->setString(fmt::format("{}/{}", playLayer->m_fields->m_startPosIdx, playLayer->m_fields->m_startPosObjects.size()).c_str());
    fields->m_switcherLabel->limitLabelWidth(40, 0.6f, 0);

    fields->m_switcherMenu->stopActionByTag(69);
    if(fields->m_firstUpdate && mm->m_dontFadeOnStart) {
        fields->m_switcherMenu->setOpacity(mm->m_opacity);
        fields->m_firstUpdate = false;
    } else {
        auto action = CCSequence::create(CCEaseInOut::create(CCFadeTo::create(0.3f, 255), 2), CCDelayTime::create(0.5), CCEaseInOut::create(CCFadeTo::create(0.5f, mm->m_opacity), 2), nullptr);
        action->setTag(69);
        fields->m_switcherMenu->runAction(action);
    }

}

#include <geode.custom-keybinds/include/Keybinds.hpp>
using namespace keybinds;

void HookUILayer::defineKeybind(const char* id, std::function<ListenerResult(bool)> callback) {
	PlayLayer::get()->template addEventListener<InvokeBindFilter>([this, callback](InvokeBindEvent* event) {
		return callback(event->isDown());
	}, id);
}
