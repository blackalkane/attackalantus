#include "musicSystem.hpp"

#include <iostream>

bool MusicSystem::init()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "Failed to initialize SDL Audio");
        return false;
    }
    return true;
}

void MusicSystem::destroy() {
//    if (backgroundMusic != nullptr)
//        Mix_FreeMusic(backgroundMusic);
    Mix_CloseAudio();
    System::destroy();
}

//bool MusicSystem::removeEntity(Entity* object_ptr){
//    // Pass
//    return true;
//}

void MusicSystem::update(float elapsedMs) {
    // Pass
}

bool MusicSystem::openAudio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        fprintf(stderr, "Failed to open audio device");
        return false;
    }
}

bool MusicSystem::loadBackgroundMusic() {
    backgroundMusic = Mix_LoadMUS(audio_path("background.wav"));

    if (backgroundMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("background.wav"));
        return false;
    }
    return true;
};

void MusicSystem::playBackgroundMusic() {
    Mix_PlayMusic(backgroundMusic, -1);
};

bool MusicSystem::loadVictoryMusic(){
    victoryMusic = Mix_LoadMUS(audio_path("victory.wav"));

    if (victoryMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("victory.wav"));
        return false;
    }
    return true;
}

void MusicSystem::playVictoryMusic(){
    Mix_PlayMusic(victoryMusic, 1);
}

bool MusicSystem::loadDefeatMusic(){
    defeatMusic = Mix_LoadMUS(audio_path("loss.wav"));

    if (defeatMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("loss.wav"));
        return false;
    }
    return true;
}

void MusicSystem::playDefeatMusic(){
    Mix_PlayMusic(defeatMusic, 1);
}
