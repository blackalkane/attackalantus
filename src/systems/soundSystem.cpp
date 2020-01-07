//
// Created by Peter Han on 2019-10-31.
//

#include "soundSystem.hpp"

bool SoundSystem::init()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "Failed to initialize SDL Audio");
        return false;
    }
    return true;
}

void SoundSystem::destroy() {
//    if (backgroundMusic != nullptr)
//        Mix_FreeMusic(backgroundMusic);
/*    Mix_FreeChunk(hitMusic);
    Mix_FreeChunk(blinkSlashMusic);
    Mix_FreeChunk(explosionMusic);
    Mix_FreeChunk(projectileMusic);
    Mix_FreeChunk(theguyDeathMusic);
    Mix_FreeChunk(basicEnemyDeathMusic);*/


    Mix_CloseAudio();
    System::destroy();
}

//bool MusicSystem::removeEntity(Entity* object_ptr){
//    // Pass
//    return true;
//}

void SoundSystem::update(float elapsedMs) {
    // Pass
}

bool SoundSystem::openAudio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        fprintf(stderr, "Failed to open audio device");
        return false;
    }
    return true;
};

bool SoundSystem::loadHitMusic() {
    hitMusic = Mix_LoadWAV(audio_path("slash.wav"));


    if (hitMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("slash.wav"));
        return false;
    }
    return true;
};

void SoundSystem::playHitMusic() {
    Mix_PlayChannel(-1, hitMusic, 0);
};

bool SoundSystem::loadBlinkSlashMusic(){
    blinkSlashMusic = Mix_LoadWAV(audio_path("Abyssmal.wav"));


    if (blinkSlashMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("Abyssmal.wav"));
        return false;
    }
    return true;
}

void SoundSystem::playBlinkSlashMusic(){
    Mix_PlayChannel(-1, blinkSlashMusic, 0);
}

bool SoundSystem::loadExplosionMusic(){
    explosionMusic = Mix_LoadWAV(audio_path("explosion.wav"));


    if (explosionMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("explosion.wav"));
        return false;
    }
    return true;
}

void SoundSystem::playExplosionMusic(){
    Mix_PlayChannel(-1, explosionMusic, 0);
}

bool SoundSystem::loadProjectileMusic(){
    projectileMusic = Mix_LoadWAV(audio_path("projectile.wav"));


    if (projectileMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("projectile.wav"));
        return false;
    }
    return true;
}

void SoundSystem::playProjectileMusic(){
    Mix_PlayChannel(-1, projectileMusic, 0);
}

bool SoundSystem::loadtheguyDeathMusic(){
    theguyDeathMusic = Mix_LoadWAV(audio_path("theGuyDie.wav"));


    if (theguyDeathMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("gg.wav"));
        return false;
    }
    return true;
}

void SoundSystem::playtheguyDeathMusic(){
    Mix_PlayChannel(-1, theguyDeathMusic, 0);
}

bool SoundSystem::loadEnemyDeathMusic(){
    basicEnemyDeathMusic = Mix_LoadWAV(audio_path("gg.wav"));


    if (basicEnemyDeathMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("gg.wav"));
        return false;
    }
    return true;
}

void SoundSystem::playEnemyDeathMusic(){
    Mix_PlayChannel(-1, theguyDeathMusic, 0);
}


bool SoundSystem::loadLootMusic(){
    lootMusic = Mix_LoadWAV(audio_path("loot.wav"));


    if (lootMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("loot.wav"));
        return false;
    }
    return true;
}
void SoundSystem::playLootMusic(){
    Mix_PlayChannel(-1, lootMusic, 0);
}

bool SoundSystem::loadTheGuyDamageMusic(){
    theGuyDamageMusic = Mix_LoadWAV(audio_path("theGuyDamage.wav"));


    if (theGuyDamageMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("theGuyDamage.wav"));
        return false;
    }
    return true;
}
void SoundSystem::playTheGuyDamageMusic(){
    Mix_PlayChannel(-1, theGuyDamageMusic, 0);
}

bool SoundSystem::loadMinionDamageMusic(){
    minionDamageMusic = Mix_LoadWAV(audio_path("minionHit.wav"));


    if (minionDamageMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("minionHit.wav"));
        return false;
    }
    return true;
}
void SoundSystem::playMinionDamageMusic(){
    Mix_PlayChannel(-1, minionDamageMusic, 0);
}

bool SoundSystem::loadBossDamageMusic(){
    bossDamageMusic = Mix_LoadWAV(audio_path("bossDamage.wav"));


    if (bossDamageMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("bossDamage.wav"));
        return false;
    }
    return true;
}
void SoundSystem::playBossDamageMusic(){
    Mix_PlayChannel(-1, bossDamageMusic, 0);
}

bool SoundSystem::loadGainHealthMusic(){
    gainHealthMusic = Mix_LoadWAV(audio_path("gainHealth.wav"));


    if (gainHealthMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("bossDamage.wav"));
        return false;
    }
    return true;
}
void SoundSystem::playGainHealthMusic(){
    Mix_PlayChannel(-1, gainHealthMusic, 0);
}

bool SoundSystem::loadMeteorMusic(){
    meteorMusic = Mix_LoadWAV(audio_path("meteor.wav"));


    if (meteorMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("meteor.wav"));
        return false;
    }
    return true;
}
void SoundSystem::playMeteorMusic(){
    Mix_PlayChannel(-1, meteorMusic, 5);
}

bool SoundSystem::loadBoomerangMusic(){
    boomerangMusic = Mix_LoadWAV(audio_path("boomerang.wav"));


    if (boomerangMusic == nullptr)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present \n");
        fprintf(stderr, audio_path("meteor.wav"));
        return false;
    }
    return true;
}
void SoundSystem::playBoomerangMusic(){
    Mix_PlayChannel(-1, boomerangMusic, 5);
}

void SoundSystem::loadAllMusic(){
    loadHitMusic();
    loadBlinkSlashMusic();
    loadExplosionMusic();
    loadProjectileMusic();
    loadEnemyDeathMusic();
    loadtheguyDeathMusic();
    loadLootMusic();
    loadTheGuyDamageMusic();
    loadMinionDamageMusic();
    loadBossDamageMusic();
    loadGainHealthMusic();
    loadMeteorMusic();
    loadBoomerangMusic();
}