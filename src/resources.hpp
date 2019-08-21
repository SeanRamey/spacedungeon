#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "sfmlpch.hpp"

namespace Resources {
    extern sf::RenderWindow* window;
    enum TEXTURE_ID : int {
        PLAYER_SHIP,
        ALIEN_SHIP,
        BULLET,
        SPECIALBULLET,
        SHRAPNEL,
        HEALTH_BAR,
		BUTTON,
        NUM_TEXTURES
    };

    enum SOUND_ID : int {
        SND_PLAYER_SHOOT,
        SND_HIT,
        NUM_SOUNDS
    };

    void load();
    void playSound(SOUND_ID id);
    sf::Sound* getSound(SOUND_ID id);
    sf::Texture* getTexture(TEXTURE_ID id);
    sf::SoundBuffer* getSoundBuffer(SOUND_ID id);
}

#endif
