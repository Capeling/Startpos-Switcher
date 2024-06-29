#include "Geode/modify/PauseLayer.hpp"
#include "hooks/PlayLayer.hpp"
#include "hooks/UILayer.hpp"

using namespace geode::prelude;

struct HookPauseLayer : geode::Modify<HookPauseLayer, PauseLayer> {
	void keyDown(cocos2d::enumKeyCodes p0) {
		PauseLayer::keyDown(p0);
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
};