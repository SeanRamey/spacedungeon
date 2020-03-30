#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include "allpch.hpp"

class Animation : public sf::Drawable {

	public:
	Animation(sf::Texture* sourceTexture, unsigned int cellsPerSecond, sf::Vector2u cellSize, bool isRepeating = true);
	Animation();
	~Animation();
	void update(sf::Time frameTime);
	void restart();
	void pause();
	void unpause();
	bool isFinished();
	bool isRepeating();
	bool isPaused();
	void setTexture(sf::Texture* texture);
	void setCellsPerSecond(unsigned int cellsPerSecond);
	void setCellSize(sf::Vector2u cellSize);
	void setCellSize(unsigned int w, unsigned int h);
	sf::Vector2u getNumCells();
	sf::Vector2u getNumCells(sf::Vector2u cellSize);
	void setRepeat(bool repeat);
	sf::IntRect getCurrentCellRect();
	sf::Vector2u getCellSize();
	const sf::Texture* getTexture();

	private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setNumCells(sf::Vector2u cellSize);

	private:
	sf::Sprite sprite;
	sf::Vector2u numCells;
	sf::Vector2u cellSize;
	sf::Time timePerCell = sf::Time::Zero;
	sf::Time timeBeforeNextCell = sf::Time::Zero;
	bool repeating = true;
	bool finished = false;
	bool paused = false;
	unsigned int currentCell = 0;

};
#endif
