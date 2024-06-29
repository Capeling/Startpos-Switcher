#include <Geode/modify/PlayLayer.hpp>
#include <Geode/Geode.hpp>

struct HookPlayLayer : geode::Modify<HookPlayLayer, PlayLayer> {
	struct Fields {
		std::vector<StartPosObject*> m_startPosObjects = {};
		int m_StartPosIdx = 0;
	};

	void addObject(GameObject* obj);
    void createObjectsFromSetupFinished();

	void updateStartPos(int index);
};
