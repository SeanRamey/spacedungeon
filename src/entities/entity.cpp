#include "stdpch.hpp"
#include "level.hpp"
#include "entity.hpp"
#include "math-util.hpp"
#include "log.hpp"
#include "level.hpp"
#include "entity-data.hpp"

Entity::Entity(sf::Vector2f position, sf::Vector2u size, Level* level)
: Damageable(EntityData::DefaultEntity::HITPOINTS, EntityData::DefaultEntity::HITPOINTS)
, velocity(0,0)
, collisionRect(position.x, position.y, size.x, size.y)
, prevPosition(position)
, level(level) {
	setOrigin(sf::Vector2f(size.x/2, size.y/2));
	setPosition(position);
}

Entity::Entity(float x, float y, unsigned int w, unsigned int h, Level* level)
: Damageable(EntityData::DefaultEntity::HITPOINTS, EntityData::DefaultEntity::HITPOINTS)
, velocity(0,0)
, collisionRect(x,y,w,h)
, prevPosition(x,y)
, level(level) {
	setOrigin(sf::Vector2f(w/2, h/2));
	setPosition(x,y);
}

Entity::Entity()
: Damageable(EntityData::DefaultEntity::HITPOINTS, EntityData::DefaultEntity::HITPOINTS)
{
}

Entity::~Entity() {

}

void Entity::update(sf::Time frameTime) {
	lastFrameTime = frameTime;
	prevPosition = getPosition();
	move(velocity * frameTime.asSeconds());
	sf::Vector2f position(getPosition());
	collisionRect.left = position.x;
	collisionRect.top = position.y;
	//animation.setPosition(position); // don't need this because the transform is passed along in the draw function.
	animation.update(frameTime);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform.combine(getTransform()); // will apply all transformations on the entity to the sprite when it is drawn
	target.draw(animation, states);
}

void Entity::face(sf::Vector2f position){
	setRotation(Math::calculateAngleFromTo(getPosition(), position) - 90); // minus 90 degrees because SFML assumes a different direction is 0
}

void Entity::setVelocity(sf::Vector2f newVelocity) {
	velocity = newVelocity;
}

void Entity::accelerate(sf::Vector2f newVelocity) {
	velocity += newVelocity;
}

void Entity::limitVelocity(const unsigned int MAX_SPEED) {

	// Let m be the allowed maximum speed and v=(v₁,v₂) be the current velocity.
	// Calculate |v|² = v₁² + v₂² and check if |v²| > m². If so set
	// v₁ ← m/|v| · v₁
	// v₂ ← m/|v| · v₂
	float velocityMagnitude = sqrtf(powf(velocity.x, 2) + powf(velocity.y, 2));
	if(powf(velocityMagnitude, 2) > powf((float)MAX_SPEED, 2)) {
		velocity.x = MAX_SPEED / velocityMagnitude * velocity.x;
		velocity.y = MAX_SPEED / velocityMagnitude * velocity.y;
	}
}

sf::Vector2f Entity::getVelocity() {
	return velocity;
}

sf::Vector2f Entity::getFrameVelocity() {
	return velocity * lastFrameTime.asSeconds();
}

sf::Vector2u Entity::getSize() {
	sf::IntRect rect = sprite.getTextureRect();
	return sf::Vector2u(rect.width, rect.height);
}

Level* Entity::getLevel() {
	return level;
}

void Entity::setCollisionRect(sf::FloatRect collisionRect) {
	this->collisionRect = collisionRect;
}

sf::FloatRect Entity::getCollisionRect() {
	return collisionRect;
}

void Entity::setAnimation(Animation newAnimation){
	animation = newAnimation;
}

void Entity::setTexture(sf::Texture* texture) {
	animation.setTexture(texture);
}

const sf::Texture* Entity::getTexture() {
	return animation.getTexture();
}

void Entity::restore(){
	this->isDead = false;

	Hitpoints newHp(EntityData::DefaultEntity::HITPOINTS, EntityData::DefaultEntity::HITPOINTS);
	switch(type) {
		case ALIEN_SHIP:	newHp.setMax(EntityData::AlienShip::HITPOINTS); newHp.set(EntityData::AlienShip::HITPOINTS); break;
		case PLAYER_SHIP:	newHp.setMax(EntityData::PlayerShip::HITPOINTS); newHp.set(EntityData::PlayerShip::HITPOINTS); break;
		case BULLET:	newHp.setMax(EntityData::Bullet::HITPOINTS); newHp.set(EntityData::Bullet::HITPOINTS); break;
		default:	break;
	}
	this->hitpoints = newHp;
}

void Entity::setLevel(Level* level){
	this->level = level;
}

bool Entity::isMarkedForDeletion() {
	return isReadyToDelete;
}
