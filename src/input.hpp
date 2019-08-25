#ifndef INPUT_H
#define INPUT_H

#include "sfmlpch.hpp"
// #include <SFML/System.hpp>
// #include <SFML/Window.hpp>
// #include <SFML/Graphics.hpp>

namespace Input
{
	extern sf::Vector2i mousePosition;
	void handleEvent(const sf::Event* const event);
	bool checkKey(sf::Keyboard::Key key);
	bool checkMouse(sf::Mouse::Button mouseKey);
	void updateMousePosition(sf::RenderWindow* window);
}

#endif
