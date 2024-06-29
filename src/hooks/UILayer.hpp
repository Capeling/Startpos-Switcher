#include <Geode/modify/UILayer.hpp>
#include <Geode/Geode.hpp>

using namespace geode::prelude;

struct HookUILayer : Modify<HookUILayer, UILayer> {
	struct Fields {
		CCMenuItemSpriteExtra* m_nextSwitcherBtn = nullptr;
		CCMenuItemSpriteExtra* m_prevSwitcherBtn = nullptr;
		CCLabelBMFont* m_switcherLabel = nullptr;

		CCMenu* m_switcherMenu = nullptr;
	};

	bool init(GJBaseGameLayer* baseGame);

	void keyDown(cocos2d::enumKeyCodes p0);

	void updateUI();
};