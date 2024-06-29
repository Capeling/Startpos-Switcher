#include <Geode/modify/UILayer.hpp>
#include <Geode/Geode.hpp>

struct HookUILayer : geode::Modify<HookUILayer, UILayer> {
	struct Fields {
		CCMenuItemSpriteExtra* m_nextSwitcherBtn = nullptr;
		CCMenuItemSpriteExtra* m_prevSwitcherBtn = nullptr;
		cocos2d::CCLabelBMFont* m_switcherLabel = nullptr;

		cocos2d::CCMenu* m_switcherMenu = nullptr;

		bool m_firstUpdate = true;
	};

	bool init(GJBaseGameLayer* baseGame);

	void keyDown(cocos2d::enumKeyCodes p0);

	void updateUI();
};