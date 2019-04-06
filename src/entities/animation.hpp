#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
class Animation {
    private:
        short currentFrame;
        short currentState;
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
        Animation();
        ~Animation();
    
};
#endif
