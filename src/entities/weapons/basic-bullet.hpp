#ifndef BASIC_BULLET_HPP
#define BASIC_BULLET_HPP
#include "bullet.hpp"
#include "entity.hpp"

class BasicBullet : public Bullet {

    public:
        BasicBullet(sf::Vector2f position, sf::Vector2f targetPosition, Entity* owner, Level* level);
        ~BasicBullet();
        void update(sf::Time frameTime);

    private:
        int offset;
        const unsigned int SPEED = 1000;
        const sf::Vector2u SIZE = sf::Vector2u(8,16);
        const unsigned int DAMAGE = 1;

};
#endif
