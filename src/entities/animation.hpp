#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

// TODO: Animation needs a rewrite
class Animation {
    private:
        unsigned int currentFrame;
        unsigned int currentState;
        sf::Time delay;
        sf::Clock timer;

        std::vector<std::vector<sf::Texture>> textures;
        std::vector<int> stateLengths;

    public:
        void init(sf::Image image, sf::Vector2u spriteSize, std::vector<int> stateLengths);
        void update();
        void setState(short state);
        void setDelay(sf::Time delay);
        const sf::Texture* getCurrentTexture();
        Animation(sf::Image image, sf::Vector2u spriteSize, std::vector<int> stateLengths);
        Animation();
        ~Animation();
    
};
#endif
