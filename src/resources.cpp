#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>

#include "log.hpp"
#include "resources.hpp"

#define PLAYER_SHIP_FILE "data/graphics/player-ship.png"
#define ALIEN_SHIP_FILE "data/graphics/alien-ship.png"
#define BULLET_FILE "data/graphics/bullet.png"
#define BIG_BULLET_FILE "data/graphics/big-bullet.png"

namespace Resources {

    static std::unordered_map<ID, sf::Texture*> textureMap;
    sf::RenderWindow* window;
    
    static std::string fileList[] = {
        PLAYER_SHIP_FILE,
        ALIEN_SHIP_FILE,
        BULLET_FILE,
        BIG_BULLET_FILE
    };

    void load() {

        for(int i = 0; i < NUM_RESOURCES; i++) {
            sf::Texture *texture = new sf::Texture();
            textureMap[(ID)i] = nullptr; // make sure each texture pointer is initialized to null
            if(!texture->loadFromFile(fileList[i])) {
                //std::printf("Unable to load texture\n");
                Log::error("Unable to load texture: " + fileList[i]);
                std::exit(-1);
            } else {
                textureMap[(ID)i] = texture;
            }
        }
    }

    sf::Texture* get(ID id) {
        if(textureMap[id] == nullptr) {
            return nullptr;
        }
        return textureMap[id];
    }

}