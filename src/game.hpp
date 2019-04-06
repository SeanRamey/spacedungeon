#ifndef GAME_HPP
#define GAME_HPP

//#include "sfmlpch.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "player-ship.hpp"
#include "alien-ship.hpp"

class Game
{
    private:
    sf::VideoMode videoMode;
    sf::RenderWindow window;

    public:
    Game(sf::VideoMode videoMode);
    ~Game();
    void run();
    private:
    void processEvents();
};

#endif