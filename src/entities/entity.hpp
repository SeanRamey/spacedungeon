#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "allpch.hpp"
#include "animation.hpp"
#include "floatline.hpp"
#include "entity-data.hpp"

class Level; // forward declare to avoid circular dependency

class Entity : public sf::Transformable, public sf::Drawable {

    public:
        Entity(sf::Vector2f position, sf::Vector2u size, sf::Texture* texture, Level* level, unsigned int hitPoints = EntityData::DefaultEntity::hitpoints);
        Entity(float x, float y, unsigned int w, unsigned int h, sf::Texture* texture, Level* level, unsigned int hitPoints = EntityData::DefaultEntity::hitpoints);
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
        FloatLine getCollisionLine();
        sf::Vector2u getSize();
        unsigned int getHitpoints();
        void repair(unsigned int hitPoints);
        void damage(unsigned int hitPoints);
        void setHitpoints(unsigned int hitPoints);
        virtual void destroy();
        bool isDestroyed();
        void revive();
        bool windowContains(sf::View view, sf::Sprite sprite) const;
        void setLevel(Level* level);

        enum Type{
            ALIEN_SHIP,
            PLAYER_SHIP,
            BULLET,
            TILE,
            NUM_TYPES
        };
        Type type;
        
        
     protected:
        sf::Vector2f velocity;
        sf::FloatRect collisionRect;
        sf::Vector2f prevPosition;
        sf::Sprite sprite;
        Animation animation;
        bool isDead;
        unsigned int hitPoints;
        Level* level;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif
