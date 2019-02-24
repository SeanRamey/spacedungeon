#ifndef SPECIAL_BULLET_HPP
#define SPECIAL_BULLET_HPP
#include "bullet.hpp"
#include "entity.hpp"
#include "tile.hpp"
#include "special-bullet-split.hpp"

class SpecialBullet : public Bullet {
    public:
        SpecialBullet(sf::Vector2f position, sf::Vector2u size, unsigned int speed, unsigned int damage, Level* level);
        ~SpecialBullet();
        void onDeath();
        void update(sf::Time frameTime, sf::RenderWindow* window);

    private:
        void checkCollision(Entity* entity);

        short numSplits;
        std::vector<SpecialBulletShrapnel> splitoffs;
};

#endif
