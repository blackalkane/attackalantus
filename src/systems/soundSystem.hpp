//
// Created by Peter Han on 2019-10-31.
//

#ifndef ATTACKATLANTIS_SOUNDSYSTEM_HPP
#define ATTACKATLANTIS_SOUNDSYSTEM_HPP


#include <SDL.h>
#include <SDL_mixer.h>
#include "system.hpp"
#include "common.hpp"


class SoundSystem: public System
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

    void playHitMusic();

    void playBlinkSlashMusic();

    void playExplosionMusic();

    void playProjectileMusic();

    void playtheguyDeathMusic();

    void playEnemyDeathMusic();

    void playLootMusic();

    void playTheGuyDamageMusic();

    void playMinionDamageMusic();

    void playBossDamageMusic();

    void playGainHealthMusic();

    void playMeteorMusic();

    void playBoomerangMusic();

    void loadAllMusic();



private:
    Mix_Chunk* hitMusic;
    Mix_Chunk* blinkSlashMusic;
    Mix_Chunk* explosionMusic;
    Mix_Chunk* projectileMusic;
    Mix_Chunk* theguyDeathMusic;
    Mix_Chunk* basicEnemyDeathMusic;
    Mix_Chunk* lootMusic;
    Mix_Chunk* theGuyDamageMusic;
    Mix_Chunk* minionDamageMusic;
    Mix_Chunk* bossDamageMusic;
    Mix_Chunk* gainHealthMusic;
    Mix_Chunk* meteorMusic;
    Mix_Chunk* boomerangMusic;



    bool loadHitMusic();
    bool loadBlinkSlashMusic();
    bool loadExplosionMusic();
    bool loadProjectileMusic();
    bool loadtheguyDeathMusic();
    bool loadEnemyDeathMusic();
    bool loadLootMusic();
    bool loadTheGuyDamageMusic();
    bool loadMinionDamageMusic();
    bool loadBossDamageMusic();
    bool loadGainHealthMusic();
    bool loadMeteorMusic();
    bool loadBoomerangMusic();


};


#endif
