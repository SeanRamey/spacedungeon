#ifndef GUN_HPP
#define GUN_HPP
#include "stdpch.hpp"

#include "bullet.hpp"
#include "basic-bullet.hpp"
#include "special-bullet.hpp"
//#include <vector>

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
};
#endif