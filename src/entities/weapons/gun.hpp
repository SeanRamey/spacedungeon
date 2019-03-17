#ifndef GUN_HPP
#define GUN_HPP
#include "bullet.hpp"
#include "basic-bullet.hpp"
#include "special-bullet.hpp"
#include <vector>

class Gun {

    public:
        enum Type{
            BASIC_GUN,
            BIG_GUN,
            NUM_GUNS
        };

    public:
        Gun(Entity* owner, Type gunType);
        ~Gun();

        void shoot(sf::Vector2f targetPosition);
        void setType(Type gunType);

    private:
        Entity* owner;
        Type gunType;

        // TODO: Clean this out
        std::vector<int> specialBulletStateLengths = {3};
        std::vector<int> basicBulletStateLengths = {4};
};
#endif