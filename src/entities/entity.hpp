#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "allpch.hpp"
#include "animation.hpp"
#include "entity-data.hpp"
#include "damageable.hpp"
#include "math-util.hpp"

class Level; // forward declare to avoid circular dependency

class Entity : public sf::Transformable, public sf::Drawable, public Damageable {

	public:
		Entity(sf::Vector2f position, sf::Vector2u size, Level* level);
		Entity(float x, float y, unsigned int w, unsigned int h, Level* level);
		Entity();
		virtual ~Entity();

		virtual void update(sf::Time frameTime);
		Level* getLevel();
		void setAnimation(Animation newAnimation);
		void setTexture(sf::Texture* texture);
		const sf::Texture* getTexture();
		sf::Vector2f getVelocity();
		sf::Vector2f getFrameVelocity();
		void setVelocity(sf::Vector2f vector);
		void accelerate(sf::Vector2f velocity);
		void limitVelocity(const unsigned int MAX_SPEED);
		void face(sf::Vector2f position);
		void setCollisionRect(sf::FloatRect collisionRect);
		sf::FloatRect getCollisionRect();
		sf::Vector2u getSize();
		void restore() override;
		bool windowContains(sf::View view, sf::Sprite sprite) const;
		void setLevel(Level* level);
		bool isMarkedForDeletion();

		enum Type{
			ALIEN_SHIP,
			PLAYER_SHIP,
			BULLET,
			NUM_TYPES
		};
		Type type;


	 protected:
		sf::Vector2f velocity;
		sf::FloatRect collisionRect;
		sf::Vector2f prevPosition;
		sf::Sprite sprite;
		Animation animation;
		bool isDead = false;
		bool isReadyToDelete = false;
		Level* level;
		sf::Time lastFrameTime;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif
