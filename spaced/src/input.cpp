#include "input.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

namespace Input
{
    unsigned char keyList[sf::Keyboard::KeyCount];
    unsigned char mouseList[sf::Mouse::ButtonCount];
    std::vector<sf::Event> eventList;
    sf::Vector2i mousePosition;
    sf::Vector2f mouseWorldPosition;
    float mouseWheelScrollDelta;

    void updateMousePosition(sf::RenderWindow* window)
    {
        mousePosition = sf::Mouse::getPosition(*window);
        // convert it to world coordinates
        mouseWorldPosition = window->mapPixelToCoords(mousePosition);
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

        case sf::Event::MouseWheelScrolled:
            mouseWheelScrollDelta += event->mouseWheelScroll.delta;
            
        default:
            break;
        }

        eventList.push_back(*event);
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

    std::vector<sf::Event> getEventList() {
        return eventList;
    }
    
    void clearEventList() {
        mouseWheelScrollDelta = 0.0;
        eventList.clear();
    }

}