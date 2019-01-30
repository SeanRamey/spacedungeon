#ifndef RESOURCES_HPP
#define RESOURCES_HPP

namespace Resources {
    extern sf::RenderWindow* window;
    enum ID : int {
        PlayerShip,
        AlienShip,
        Bullet,
        NUM_RESOURCES
    };

    void load();
    sf::Texture* get(ID id);
}

#endif