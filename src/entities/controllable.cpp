#include "controllable.hpp"
#include "input.hpp"
#include "command.hpp"

///////////////////////////
Controllable::Controllable() {

}

///////////////////////////
Controllable::~Controllable() {

}

///////////////////////////
void Controllable::handleUserInput() {
	for(auto it = keyboardActionMap.begin(); it != keyboardActionMap.end(); ++it) {
		if(Input::checkKey(it->first)) {
			it->second->execute();
		}
	}

	for(auto it = mouseActionMap.begin(); it != mouseActionMap.end(); ++it) {
		if(Input::checkMouse(it->first)) {
			it->second->execute();
		}
	}
}

///////////////////////////
void Controllable::addKeyboardAction(sf::Keyboard::Scancode key, std::shared_ptr<Command> command) {
	keyboardActionMap[key] = command;
}

///////////////////////////
void Controllable::addMouseAction(sf::Mouse::Button button, std::shared_ptr<Command> command) {
	mouseActionMap[button] = command;
}

///////////////////////////
void Controllable::removeKeyboardAction(sf::Keyboard::Scancode key) {
	auto search = keyboardActionMap.find(key);
	if (search != keyboardActionMap.end()) {
		// found key, now remove it
		keyboardActionMap.erase(search);
	}
}

///////////////////////////
void Controllable::removeMouseAction(sf::Mouse::Button button) {
	auto search = mouseActionMap.find(button);
	if (search != mouseActionMap.end()) {
		// found button, now remove it
		mouseActionMap.erase(search);
	}
}

///////////////////////////
void Controllable::replaceKeyboardAction(sf::Keyboard::Scancode key, std::shared_ptr<Command> command) {
	keyboardActionMap.at(key) = command;
}

///////////////////////////
void Controllable::replaceMouseAction(sf::Mouse::Button button, std::shared_ptr<Command> command) {
	mouseActionMap.at(button) = command;
}
