#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "sfmlpch.hpp"
// #include <SFML/Graphics.hpp>

namespace Resources {
    extern sf::RenderWindow* window;
    enum ID : int {
        PLAYER_SHIP,
        ALIEN_SHIP,
        BULLET,
        SPECIALBULLET,
        SHRAPNEL,
        NUM_RESOURCES
    };

    void load();
    sf::Texture* get(ID id);
}

#endif