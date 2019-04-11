#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "level.hpp"
#include "input.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

void beClever(std::vector<std::string>& progArguments);
void sayHi(std::vector<std::string>& progArguments);
void editMap(std::vector<std::string>& progArguments);
void loadMap(std::string map, std::string images);
void runeditor(Level& level, sf::RenderWindow& window);
void processEvents(sf::RenderWindow& window);

int main(int argCount, const char* args[]) {

    // container for passed in arguments
    std::vector<std::string> progArguments;

    // put all the passed int arguments into a container
    for(int i = 0; i < argCount; ++i) {
        std::string arg = args[i];
        progArguments.push_back(arg);
    }

    // error and exit if no command given
    if(argCount < 2) {
        std::cout << "ERROR: You have to give me a command or file to edit, dummy!\n";
        return 0;
    }

    // Create a map of commands and the functions that they execute
    // For some reason, you HAVE to use a typedef for the function pointer
    // And you HAVE to use std::make_pair to insert elements to the map
    typedef void (*myfunc)(std::vector<std::string>& progArgs);
    std::unordered_map<std::string, myfunc> commandMap;
    commandMap.insert(std::make_pair("clever", beClever));
    commandMap.insert(std::make_pair("sayhi", sayHi));

    // Get the given command
    std::string command = progArguments.at(1);


    // Lookup the command in the command map
    // if it wasn't found, try to edit a map
    // if more than one argument was passed, error out because
    // it can only edit one map at a time
    // if it was found, run the associated function
    auto search = commandMap.find(command);
    if (search != commandMap.end()) {
        search->second(progArguments);
    } else if(argCount == 2) {
        editMap(progArguments);
    } else if(argCount > 2) {
        std::cout << "ERROR: I can only edit one map at a time y'know...\n";
    } else {
        std::cout << "ERROR: That wasn't a recognized command!\n";
    }

    std::cout << "Thanks for using spaced! :)\n";

    return 0;
}

void sayHi(std::vector<std::string>& progArguments) {
    std::cout << "Hi.\n";
}

void beClever(std::vector<std::string>& progArguments) {
    // start printing a clever sentence ;)
    std::cout << "My name is " << progArguments.at(0) << " and I say "; // first arg is always the name of the program

    if(progArguments.size() > 2) {
        for(int i = 2; i < progArguments.size(); ++i) {
            std::cout << progArguments.at(i);
            if(i + 2 < progArguments.size()) {
                std::cout << ", ";
            } else if(i + 1 < progArguments.size()) {
                std::cout << " and ";
            }
        }
    } else { // say nothing because no extra words were passed in 
        std::cout << "nothing";
    }

    // finish the sentence
    std::cout << ".\n";
}

void editMap(std::vector<std::string>& progArguments) {
    sf::RenderWindow window;
    window.create(sf::VideoMode(640,480), "spaced: " + progArguments.at(1));
    Level level(progArguments.at(1), "tileset.png", "");
    runeditor(level, window);
}

void runeditor(Level& level, sf::RenderWindow& window)
{
    // Start the game loop
    sf::Clock loopTimer;
    sf::Time secondsTime = sf::Time::Zero;
    sf::Time unprocessedTime = sf::Time::Zero;
    const sf::Time FRAME_TIME = sf::microseconds(16666);// 60 FPS
    unsigned int framesPerSecond = 0;
    unsigned int updatesPerSecond = 0;

    window.setVerticalSyncEnabled(true);
    while (window.isOpen())
    {
        unprocessedTime = loopTimer.getElapsedTime() + unprocessedTime;
        secondsTime = secondsTime + loopTimer.getElapsedTime();
        loopTimer.restart();

        while(unprocessedTime >= FRAME_TIME)
        {
            unprocessedTime = unprocessedTime - FRAME_TIME;

            processEvents(window);

            level.update(FRAME_TIME, window);
            ++updatesPerSecond;
        }

        // Clear screen
        window.clear(sf::Color::Black);

        // Draw graphics to buffer
        level.draw(window);

        // Display buffer
        window.display();

        ++framesPerSecond;

        // Check if 1 second has passed
        if( secondsTime.asSeconds() >= 1)
        {
            //printf("FPS: %u, UpdatesPerSecond: %u\n", framesPerSecond, updatesPerSecond);
            secondsTime = sf::Time::Zero;
            updatesPerSecond = 0;
            framesPerSecond = 0;
        }
    }
}

void processEvents(sf::RenderWindow& window)
{
    Input::clearEventList();
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::EventType::Closed)
        {
            window.close();
        }
        else if(event.type == sf::Event::EventType::MouseMoved)
        {
            Input::updateMousePosition(&window);
        }

        Input::handleEvent(&event);
    }
}