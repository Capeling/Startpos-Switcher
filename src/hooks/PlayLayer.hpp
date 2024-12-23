#ifndef PLAYLAYER_HPP
#define PLAYLAYER_HPP

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

struct HookPlayLayer : geode::Modify<HookPlayLayer, PlayLayer> {
	struct Fields {
		std::vector<GameObject*> m_startPosObjects = {};
		int m_startPosIdx = 0;
        bool m_canSwitch = true;
	};

	void addObject(GameObject* obj);
    void createObjectsFromSetupFinished();
	void togglePracticeMode(bool practiceMode);

	void updateStartPos(int index);
};

#endif
