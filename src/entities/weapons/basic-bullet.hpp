#ifndef BASIC_BULLET_HPP
#define BASIC_BULLET_HPP
#include "bullet.hpp"

class BasicBullet : public Bullet {
    private:
        int offset;

    public:
        BasicBullet(sf::Vector2f, sf::Vector2u, unsigned int, unsigned int);
        ~BasicBullet();

    protected:
        void checkCollision(Entity* entity);
        void update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities);

};
#endif