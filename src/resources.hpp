#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <SFML/Graphics.hpp>

namespace Resources {
    extern sf::RenderWindow* window;
    enum ID : int {
        PLAYER_SHIP,
        ALIEN_SHIP,
        BULLET,
        NUM_RESOURCES
    };

    void load();
    sf::Texture* get(ID id);
}

#endif