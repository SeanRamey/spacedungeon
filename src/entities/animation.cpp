#include "stdpch.hpp"

#include "animation.hpp"
#include <cmath>
#include <cassert>


///////////////////////////
Animation::Animation(sf::Texture* sourceTexture, unsigned int cellsPerSecond, sf::Vector2u cellSize, bool repeating)
: repeating(repeating)
{
	setCellsPerSecond(cellsPerSecond);
	setTexture(sourceTexture);
	setCellSize(cellSize);
	setNumCells(cellSize);
}

///////////////////////////
Animation::Animation() {

}

///////////////////////////
Animation::~Animation() {

}

///////////////////////////
void Animation::update(sf::Time frameTime) {
	if(!paused) {
		if(finished) {
			if(repeating) {
				restart();
			}
		} else {
			if(timeBeforeNextCell <= sf::Time::Zero) {
				// Make sure to not go past the number of cells
				if(currentCell + 1 < numCells.x * numCells.y) {
					++currentCell;
					sprite.setTextureRect(getCurrentCellRect());
				} else {
					finished = true;
				}
				timeBeforeNextCell += timePerCell; // += to make sure extra time carries over
			} else {
				timeBeforeNextCell -= frameTime;
			}
		}
	}
}

///////////////////////////
void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}

///////////////////////////
void Animation::setTexture(sf::Texture* texture) {
	sprite.setTexture(*texture);
}

///////////////////////////
sf::IntRect Animation::getCurrentCellRect() {
	sf::IntRect textureRect;

	// get x,y coordinates of current cell
	unsigned int cellX;
	unsigned int cellY;
	cellX = currentCell % numCells.x;
	if(currentCell - cellX > 0) {
		cellY = (currentCell - cellX) / numCells.x;
	} else {
		cellY = 0;
	}

	textureRect.left = cellX * cellSize.x;
	textureRect.top = cellY * cellSize.y;
	textureRect.width = cellSize.x;
	textureRect.height = cellSize.y;

	return textureRect;

}

///////////////////////////
sf::Vector2u Animation::getCellSize() {
	return cellSize;
}

///////////////////////////
const sf::Texture* Animation::getTexture() {
	return sprite.getTexture();
}

///////////////////////////
void Animation::restart() {
	currentCell = 0;
	timeBeforeNextCell = timePerCell;
	finished = false;
}

///////////////////////////
void Animation::pause() {
	paused = true;
}

///////////////////////////
void Animation::unpause() {
	paused = false;
}

///////////////////////////
bool Animation::isFinished() {
	return finished;
}

///////////////////////////
bool Animation::isRepeating() {
	return repeating;
}

///////////////////////////
bool Animation::isPaused() {
	return paused;
}

///////////////////////////
void Animation::setCellsPerSecond(unsigned int cellsPerSecond) {
	timePerCell = sf::seconds(1.0f/cellsPerSecond);
	timeBeforeNextCell = timePerCell;
}

///////////////////////////
void Animation::setCellSize(sf::Vector2u cellSize) {
	setCellSize(cellSize.x, cellSize.y);
}

///////////////////////////
void Animation::setCellSize(unsigned int w, unsigned int h) {
	cellSize.x = w;
	cellSize.y = h;
	setNumCells(cellSize);
	sprite.setTextureRect(getCurrentCellRect());
}

///////////////////////////
void Animation::setRepeat(bool repeat) {
	repeating = repeat;
}

sf::Vector2u Animation::getNumCells() {
	return this->numCells;
}

sf::Vector2u Animation::getNumCells(sf::Vector2u cellSize) {
	assert(cellSize.x != 0);
	assert(cellSize.y != 0);
	sf::Vector2u numCells;
	numCells.x = sprite.getTexture()->getSize().x / cellSize.x;
	numCells.y = sprite.getTexture()->getSize().y / cellSize.y;
	return numCells;
}

void Animation::setNumCells(sf::Vector2u cellSize) {
	assert(cellSize.x != 0);
	assert(cellSize.y != 0);
	numCells.x = sprite.getTexture()->getSize().x / cellSize.x;
	numCells.y = sprite.getTexture()->getSize().y / cellSize.y;
}
