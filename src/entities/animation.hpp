#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include "allpch.hpp"
// #include <SFML/Graphics.hpp>
// #include <SFML/System.hpp>
//#include <vector>

class Animation {
    private:
        sf::Vector2u numCells;
        sf::Vector2u cellSize;
        sf::Texture* sourceTexture;
        sf::Time timePerCell;
        sf::Time timeBeforeNextCell;
        bool repeating;
        bool finished;
        bool paused;
        unsigned int currentCell;

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
        sf::IntRect getCurrentCellRect();
        sf::Texture* getTexture();
    
};
#endif
