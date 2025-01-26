#ifndef MODMANAGER_HPP
#define MODMANAGER_HPP

class ModManager {
public:
    static ModManager* sharedState();

    ModManager();

    bool m_dontFadeOnStart = false;
    bool m_hideBtns = false;
    bool m_ignoreDisabled = false;
    float m_opacity = 0.f; 
};
#endif