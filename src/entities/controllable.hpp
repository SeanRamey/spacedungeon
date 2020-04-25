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

		void addKeyboardAction(sf::Keyboard::Key key, std::shared_ptr<Command> command);
		void addMouseAction(sf::Mouse::Button button, std::shared_ptr<Command> command);
		void removeKeyboardAction(sf::Keyboard::Key key);
		void removeMouseAction(sf::Mouse::Button button);
		void replaceKeyboardAction(sf::Keyboard::Key key, std::shared_ptr<Command> command);
		void replaceMouseAction(sf::Mouse::Button button, std::shared_ptr<Command> command);

	private:
		std::map<sf::Keyboard::Key, std::shared_ptr<Command>> keyboardActionMap;
		std::map<sf::Mouse::Button, std::shared_ptr<Command>> mouseActionMap;
};

#endif
