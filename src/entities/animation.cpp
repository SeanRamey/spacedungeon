#include "stdpch.hpp"

#include "animation.hpp"
#include "math.h"
//#include <iostream>



Animation::Animation(sf::Texture* sourceTexture, unsigned int cellsPerSecond, sf::Vector2u cellSize, bool repeating)
: numCells(0,0)
, cellSize(cellSize)
, sourceTexture(sourceTexture)
, repeating(repeating)
, finished(false)
, paused(false)
, currentCell(0)
{
	timePerCell = sf::seconds(1.0/cellsPerSecond);
	timeBeforeNextCell = timePerCell;
	numCells.x = sourceTexture->getSize().x / cellSize.x;
	numCells.y = sourceTexture->getSize().y / cellSize.y;
}

Animation::Animation()
: numCells(0,0)
, cellSize(0,0)
, sourceTexture(nullptr)
, timePerCell(sf::Time::Zero)
, timeBeforeNextCell(sf::Time::Zero)
, repeating(false)
, finished(true)
, paused(true)
, currentCell(0) {

}

Animation::~Animation() {

}

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

sf::Texture* Animation::getTexture() {
	return sourceTexture;
}

void Animation::restart() {
	currentCell = 0;
	timeBeforeNextCell = timePerCell;
	finished = false;
}

void Animation::pause() {
	paused = true;
}

void Animation::unpause() {
	paused = false;
}

bool Animation::isFinished() {
	return finished;
}

bool Animation::isRepeating() {
	return repeating;
}

bool Animation::isPaused() {
	return paused;
}
