#ifndef MUSICSYSTEM_H
#define MUSICSYSTEM_H
#include "common.hpp"
#include "system.hpp"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>

class MusicSystem: public System
{
public:
    // SDL init
    bool init() override;

    // Releases all associated resources
    void destroy() override;

    // bool removeEntity(Entity* entity)override;

    void update(float elapsedMs) override;

    // Open audio
    bool openAudio();

    // Load background music
    bool loadBackgroundMusic();

    bool loadVictoryMusic();

    bool loadDefeatMusic();

    // Play background music
    void playBackgroundMusic();

    void playVictoryMusic();

    void playDefeatMusic();

private:
    Mix_Music* backgroundMusic;
    Mix_Music* victoryMusic;
    Mix_Music* defeatMusic;
};

#endif