#ifndef SPECIAL_BULLET_HPP
#define SPECIAL_BULLET_HPP
#include "bullet.hpp"
#include "entity.hpp"
#include "tile.hpp"

class SpecialBullet : public Bullet {
    public:
        SpecialBullet(sf::Vector2f position, sf::Vector2u size, unsigned int speed, unsigned int damage);
        ~SpecialBullet();
        void onDeath();
        void update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities);

    private:
        void checkCollision(Entity* entity);
};

#endif