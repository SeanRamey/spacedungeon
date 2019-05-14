#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "sfmlpch.hpp"
// #include <SFML/System.hpp>
// #include <SFML/Graphics.hpp>
#include <vector>
#include "animation.hpp"

class Level; // forward declare to avoid circular dependency

class Entity : public sf::Transformable, public sf::Drawable {

    public:
        Entity(sf::Vector2f position, sf::Vector2u size, sf::Texture* texture, Level* level, unsigned int hitPoints = 100);
        Entity(float x, float y, unsigned int w, unsigned int h, sf::Texture* texture, Level* level, unsigned int hitPoints = 100);
        virtual ~Entity();

        virtual void update(sf::Time frameTime);
        Level* getLevel();
        void setAnimation(Animation newAnimation);
        void setTexture(sf::Texture* texture);
        sf::Vector2f getVelocity();
        void setVelocity(sf::Vector2f vector);
        void accelerate(sf::Vector2f velocity);
        void limitVelocity(const unsigned int MAX_SPEED);
        float calculateAngleTo(sf::Vector2f position);
        void face(sf::Vector2f position);
        sf::FloatRect getCollisionRect();
        sf::Vector2u getSize();
        unsigned int getHitpoints();
        void repair(unsigned int hitPoints);
        void damage(unsigned int hitPoints);
        void setHitpoints(unsigned int hitPoints);
        virtual void destroy();
        bool isDestroyed();
        bool windowContains(sf::View view, sf::Sprite sprite) const;

        enum Type{
            ALIEN_SHIP,
            PLAYER_SHIP,
            BULLET,
            TILE,
            NUM_TYPES
        };
        Type type;
        
        
        //const uint32_t MAX_SPEED; // MAX_SPEED MUST BE LARGER THAN ACCELERATION
        //uint32_t ACCELERATION = 100;
        //float FRICTION = 0.98;

     protected:
        sf::Vector2f velocity;
        sf::FloatRect collisionRect;
        sf::Sprite sprite;
        Animation animation;
        bool isDead;
        unsigned int hitPoints;
        Level* level;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif
