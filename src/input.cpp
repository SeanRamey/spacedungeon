#include "input.hpp"
// #include <SFML/Graphics.hpp>
// #include <SFML/System.hpp>

namespace Input
{
    static unsigned char keyList[sf::Keyboard::KeyCount];
    static unsigned char mouseList[sf::Mouse::ButtonCount];
    sf::Vector2i mousePosition;

    void updateMousePosition(sf::RenderWindow* window)
    {
        mousePosition = sf::Mouse::getPosition(*window);
    }

    void handleEvent(const sf::Event* const event)
    {
        switch(event->type)
        {
        case sf::Event::KeyPressed:
            if(event->key.code == -1){
                break;
            }
            keyList[event->key.code] = 1; // set to true
            break;
        case sf::Event::KeyReleased:
            if(event->key.code == -1){
                break;
            }
            keyList[event->key.code] = 0; // set to false
            break;
        case sf::Event::MouseButtonPressed:
            if(event->mouseButton.button == -1){
                break;
            }
            mouseList[event->mouseButton.button] = 1;
            break;
        case sf::Event::MouseButtonReleased:
            if(event->mouseButton.button == -1){
                break;
            }
            mouseList[event->mouseButton.button] = 0;
            break;
        default:
            break;
        }
    }

    bool checkKey(sf::Keyboard::Key key)
    {
        if(key == -1)
        {
            return false;
        }

        return keyList[key];
    }

    bool checkMouse(sf::Mouse::Button mouseKey)
    {
        if(mouseKey == -1)
        {
            return false;
        }

        return mouseList[mouseKey];
    }

}