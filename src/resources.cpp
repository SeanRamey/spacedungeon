#include "stdpch.hpp"

#include "log.hpp"
#include "resources.hpp"

#define PLAYER_SHIP_FILE "data/graphics/new-playership-idle.png"
#define ALIEN_SHIP_FILE "data/graphics/alien-ship.png"
#define BULLET_FILE "data/graphics/new-bullet.png"
#define BIG_BULLET_FILE "data/graphics/big-bullet_test.png"
#define SHRAPNEL_FILE "data/graphics/shrapnel.png"
#define HEALTH_BAR_FILE "data/graphics/healthBar.png"
#define BUTTON_FILE "data/graphics/button.png"

#define SND_PLAYER_SHOOT_FILE "data/sounds/shoot.wav"
#define SND_HIT "data/sounds/hit.wav"
#define MUSIC_1

namespace Resources {

    std::map<TEXTURE_ID, sf::Texture*> textureMap;
    std::map<SOUND_ID, sf::SoundBuffer*> soundBufferMap;
    std::map<SOUND_ID, sf::Sound*> soundMap;
    sf::RenderWindow* window;
    
    std::string textureFiles[] = {
        PLAYER_SHIP_FILE,
        ALIEN_SHIP_FILE,
        BULLET_FILE,
        BIG_BULLET_FILE,
        SHRAPNEL_FILE,
        HEALTH_BAR_FILE,
		BUTTON_FILE,
    };

    std::string soundFiles[] = {
        SND_PLAYER_SHOOT_FILE,
        SND_HIT
    };

    void load() {

        for(int i = 0; i < NUM_TEXTURES; i++) {
            sf::Texture *texture = new sf::Texture();
            textureMap[(TEXTURE_ID)i] = nullptr; // make sure each texture pointer is initialized to null
            if(!texture->loadFromFile(textureFiles[i])) {
                //std::printf("Unable to load texture\n");
                Log::error("Unable to load texture: " + textureFiles[i]);
                std::exit(-1);
            } else {
                textureMap[(TEXTURE_ID)i] = texture;
            }
        }

        for(int i = 0; i < NUM_SOUNDS; i++) {
            sf::SoundBuffer *buffer = new sf::SoundBuffer();
            sf::Sound *sound = new sf::Sound();
            soundBufferMap[(SOUND_ID)i] = nullptr; // make sure each texture pointer is initialized to null
            if(!buffer->loadFromFile(soundFiles[i])) {
                //std::printf("Unable to load texture\n");
                Log::error("Unable to load sound: " + soundFiles[i]);
                std::exit(-1);
            } else {
                soundBufferMap[(SOUND_ID)i] = buffer;
                sound->setBuffer(*buffer);
                soundMap[(SOUND_ID)i] = sound;
            }
        }
    }

    void playSound(SOUND_ID id) {
        if(soundMap[id] != nullptr) {
            soundMap[id]->play();
        }
    }

    sf::Sound* getSound(SOUND_ID id) {
        if(soundMap[id] == nullptr) {
            return nullptr;
        }
        return soundMap[id];
    }

    sf::Texture* getTexture(TEXTURE_ID id) {
        if(textureMap[id] == nullptr) {
            return nullptr;
        }
        return textureMap[id];
    }

    sf::SoundBuffer* getSoundBuffer(SOUND_ID id) {
        if(soundBufferMap[id] == nullptr) {
            return nullptr;
        }
        return soundBufferMap[id];
    }

}
