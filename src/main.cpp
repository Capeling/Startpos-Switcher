#include "Geode/modify/PauseLayer.hpp"
#include "hooks/PlayLayer.hpp"
#include "hooks/UILayer.hpp"

using namespace geode::prelude;

#ifndef GEODE_IS_ANDROID
struct HookPauseLayer : geode::Modify<HookPauseLayer, PauseLayer> {
	void keyDown(cocos2d::enumKeyCodes p0) {
		PauseLayer::keyDown(p0);
		auto playLayer = static_cast<HookPlayLayer*>(PlayLayer::get());

		if(playLayer && !playLayer->m_fields->m_startPosObjects.empty()) {
			if(p0 == enumKeyCodes::KEY_Q || p0 == enumKeyCodes::CONTROLLER_Left) {
				playLayer->updateStartPos(playLayer->m_fields->m_startPosIdx - 1);
				return;
			}

			if(p0 == enumKeyCodes::KEY_E || p0 == enumKeyCodes::CONTROLLER_Right) {
				playLayer->updateStartPos(playLayer->m_fields->m_startPosIdx + 1);
				return;
			}
		}
	}
};
#endif