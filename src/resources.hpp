#ifndef RESOURCES_HPP
#define RESOURCES_HPP

namespace Resources {
    extern sf::RenderWindow* window;
    enum ID : int {
        PLAYERSHIP,
        ALIENSHIP,
        BULLET,
        SPECIALBULLET,
        NUM_RESOURCES
    };

    void load();
    sf::Texture* get(ID id);
}

#endif