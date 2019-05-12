#ifndef GAME_HPP
#define GAME_HPP

//#include "sfmlpch.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "player-ship.hpp"
#include "alien-ship.hpp"
#include "game-state.hpp"

class Game
{
    private:
        sf::VideoMode videoMode;
        sf::RenderWindow window;

        std::vector<GameState*> gameStates;
        const unsigned int STATECOUNT = 2;
        int currentState = 0;

    public:

        void update(sf::Time frameTime, sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
        void updateState(int newState=-1, bool carryPlayer = false);
        GameState* getGameState();
        
        Game(sf::VideoMode videoMode);
        ~Game();
        void run();
    private:
        void processEvents();
};

#endif