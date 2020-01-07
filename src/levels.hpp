#ifndef ATTACKATLANTIS_LEVELS_HPP
#define ATTACKATLANTIS_LEVELS_HPP

#include "common.hpp"
#include "entities/environment.hpp"
#include "levelName.hpp"
#include <vector>
#include <random>

#include <SDL.h>
#include <SDL_mixer.h>
#include <systems/system.hpp>
#include <systems/drawSystem.hpp>
#include <entities/theguy.hpp>
#include <entities/projectile.hpp>

#include <systems/moveSystem.hpp>

#include <entities/menu.hpp>
#include <entities/menu_items.hpp>
#include <entities/enemy.hpp>
#include <entities/healthBar.hpp>
#include <entities/basicEnemy.hpp>
#include <entities/shootingEnemy.hpp>
#include <entities/speedEnemy.hpp>
#include <entities/rock.hpp>
#include <systems/collisionSystem.hpp>
#include <systems/simpleAISystem.hpp>
#include <systems/musicSystem.hpp>
#include <systems/controlSystem.hpp>
#include <systems/abilitySystem.hpp>
#include <systems/spawnSystem.hpp>
#include <systems/deleteSystem.hpp>
#include <systems/scoreSystem.hpp>
#include <systems/shootingAISystem.hpp>
#include <entities/abilityType.hpp>
#include <entities/healthBar.hpp>
#include <entities/enemyProjectile.hpp>

class Levels {
public:
    Levels();

    ~Levels();

    bool init();

    void destroy();

    // setter
    bool setLevelParam(LevelName curLevel, LevelName preLevel);

    // getter
    //TheGuy* getTheGuy();
    int getNumRocks();
    int getNumCurrents();
    int getNumHealth();
    char* getEnvironmentPath();
    SpawnLimits* getCurLimits();
    int getNumCharges();
    LevelName getCurrentLevel();
    LevelName getPreviousLevel();
    unsigned long getWinningScore();

private:
    int numRocks;
    int numCurrents;
    int numHealth;
    char * EnvironmentPath;
    LevelName currentLevel;
    LevelName previousLevel;
    unsigned long winningScore;

    SpawnLimits curLimits;
    int numCharges;
};

#endif