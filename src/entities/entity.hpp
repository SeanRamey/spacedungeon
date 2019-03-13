#ifndef ENTITY_HPP
#define ENTITY_HPP

//#include "sfmlpch.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
<<<<<<< HEAD

class Level; // forward declare to avoid circular dependency

class Entity : public sf::Transformable, public sf::Drawable {

    public:
        Entity(sf::Vector2f position, sf::Vector2u size, sf::Texture* texture, Level* level, unsigned int hitPoints = 100);
        Entity(float x, float y, unsigned int w, unsigned int h, sf::Texture* texture, Level* level, unsigned int hitPoints = 100);
        virtual ~Entity();

        virtual void update(sf::Time frameTime);
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
        void destroy();
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
        
=======
#include "collision-box.hpp"
#include "animation.hpp"

class Level;
class Entity {
    protected:
        sf::Vector2f position;
        sf::Vector2u size;
        sf::Vector2f nextPosition;
        sf::Vector2f velocity;
        float angle;
        Level* level;

        sf::Sprite sprite;

        Animation animation;

        void addEntity(Entity* entiites);
    public:
        CollisionBox collisionBox;

        enum types : int {PLAYER_SHIP, ALIEN_SHIP, TILE};
        types type;

        virtual void update(sf::Time frameTime, sf::RenderWindow* window) = 0;
        virtual void draw(sf::RenderWindow* window);
        // virtual void getNextPosition(sf::Time frameTime) = 0;
        virtual void setVelocity(sf::Vector2f vector);
        virtual void checkCollision(Entity* entity) = 0;
        virtual void setTexture(sf::Texture* texture);
        virtual void applyMovement(sf::Time frameTime);
        virtual sf::Vector2f getVelocity();
        virtual void addVelocity(sf::Vector2f newVelocity);
        virtual float calculateAngleTo(sf::Vector2f position);
        virtual void face(sf::Vector2f position);
        virtual sf::Vector2u getSize();
        void setAnimation(sf::Image image, sf::Vector2u spriteSize, std::vector<int> stateLengths);
        void setState(short state);
        void setDelay(sf::Time delay);

        Level* getLevel();
        sf::Vector2f getPosition();
        Entity(sf::Vector2f position, sf::Vector2f size, Level* level);
        Entity(float x, float y, unsigned int w, unsigned int h, Level* level);
        ~Entity();
>>>>>>> master
        
        //const uint32_t MAX_SPEED; // MAX_SPEED MUST BE LARGER THAN ACCELERATION
        //uint32_t ACCELERATION = 100;
        //float FRICTION = 0.98;

     protected:
        sf::Vector2f velocity;
        sf::FloatRect collisionRect;
        sf::Sprite sprite;
        bool isDead;
        unsigned int hitPoints;
        Level* level;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif
