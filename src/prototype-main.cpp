#include "sfmlpch.hpp"
// #include <SFML/Graphics.hpp>
// #include <SFML/System.hpp>

#include "input.hpp"
#include "game.hpp"

int main(){

    Game game(sf::VideoMode(1080, 720, 32));
    game.run();

    return 0;
}