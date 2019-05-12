#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "UI-element.hpp"
class Game;
class GameState{
    public:
        virtual void update(sf::Time frameTime, sf::RenderWindow& window) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;
        virtual void clear() = 0;
        virtual void init()  = 0;
        sf::View getView();
        GameState(Game* game);
        ~GameState();

    protected:
        sf::View view;
        Game* game;
};
#endif