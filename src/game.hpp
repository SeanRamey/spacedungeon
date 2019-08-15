#ifndef GAME_HPP
#define GAME_HPP

#include "allpch.hpp"

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
        std::stack<std::shared_ptr<GameState>> gameStates;

    public:
        void init();
        void run();
        void update(sf::Time frameTime, sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
        void changeState(std::shared_ptr<GameState> state);
        void pushState(std::shared_ptr<GameState> state);
        void popState();
        std::shared_ptr<GameState> getGameState();
        
        Game(sf::VideoMode videoMode);
        ~Game();
    private:
        void processEvents();
};

#endif
