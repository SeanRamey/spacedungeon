#ifndef GAME_HPP
#define GAME_HPP

#include "allpch.hpp"

#include "player-ship.hpp"
#include "alien-ship.hpp"
#include "game-state.hpp"

class Game
{
    private:
        sf::VideoMode videoMode;
        sf::RenderWindow window;
        std::stack<std::shared_ptr<GameState>> gameStates;
        PlayerShip* player = nullptr;

    public:
        void init();
        void run();
        void update(sf::Time frameTime);
        void draw(sf::RenderWindow& window);
        void changeState(std::shared_ptr<GameState> state);
        void pushState(std::shared_ptr<GameState> state);
        void popState();
        std::shared_ptr<GameState> getGameState();
        PlayerShip* getPlayer();
        
        Game(sf::VideoMode videoMode);
        ~Game();
    private:
        void processEvents();
};

#endif
