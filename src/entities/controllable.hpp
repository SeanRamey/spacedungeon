#ifndef CONTROLLABLE_HPP
#define CONTROLLABLE_HPP

#include "allpch.hpp"
#include "entity-command.hpp"
#include "command.hpp"

class Controllable {

	public:
		Controllable();
		virtual ~Controllable();
		virtual void handleUserInput();

		void addKeyboardAction(sf::Keyboard::Scancode key, std::shared_ptr<Command> command);
		void addMouseAction(sf::Mouse::Button button, std::shared_ptr<Command> command);
		void removeKeyboardAction(sf::Keyboard::Scancode key);
		void removeMouseAction(sf::Mouse::Button button);
		void replaceKeyboardAction(sf::Keyboard::Scancode key, std::shared_ptr<Command> command);
		void replaceMouseAction(sf::Mouse::Button button, std::shared_ptr<Command> command);

	private:
		std::map<sf::Keyboard::Scancode, std::shared_ptr<Command>> keyboardActionMap;
		std::map<sf::Mouse::Button, std::shared_ptr<Command>> mouseActionMap;
};

#endif
