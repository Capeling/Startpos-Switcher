#include <Geode/modify/PlayLayer.hpp>
#include <Geode/Geode.hpp>

struct HookPlayLayer : geode::Modify<HookPlayLayer, PlayLayer> {
	struct Fields {
		std::vector<GameObject*> m_startPosObjects = {};
		int m_startPosIdx = 0;
        bool m_canSwitch = true;
	};

	void addObject(GameObject* obj);
    void createObjectsFromSetupFinished();

	void updateStartPos(int index);
};
