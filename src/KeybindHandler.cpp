#include <geode.custom-keybinds/include/Keybinds.hpp>

using namespace keybinds;

$execute {
    BindManager::get()->registerBindable({
        "switch-next"_spr,
        "Next Startpos",
        "Goes to the next Startpos",
        {
            Keybind::create(cocos2d::KEY_E),
            ControllerBind::create(cocos2d::CONTROLLER_Right)
        },
        "Startpos Switcher",
        false
    });

    BindManager::get()->registerBindable({
        "switch-previous"_spr,
        "Previous Startpos",
        "Goes to the Previous Startpos",
                {
            Keybind::create(cocos2d::KEY_Q),
            ControllerBind::create(cocos2d::CONTROLLER_Left)
        },
        "Startpos Switcher",
        false
    });
}