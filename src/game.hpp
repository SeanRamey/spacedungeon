#ifndef GAME_HPP
#define GAME_HPP

#include "sfmlpch.hpp"

#include "player-ship.hpp"
#include "alien-ship.hpp"
#include "game-state.hpp"

#include <stack>
#include <vector>

class Game
{
    private:
        sf::VideoMode videoMode;
        sf::RenderWindow window;

        std::vector<GameState*> gameStates;
        const unsigned int STATECOUNT = 2;
        int currentState = 0;

		Level* previousLevel = nullptr; // used to store the last level in sequence of gamestates

    public:
        void init();
        void run();
        void update(sf::Time frameTime, sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
        void changeState(int newState=-1, bool carryPlayer = false);
        GameState* getGameState();
        
        Game(sf::VideoMode videoMode);
        ~Game();
    private:
        void processEvents();
};

#endif
