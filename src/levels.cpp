#include <climits>
#include "levels.hpp"
#include "levelName.hpp"

Levels::Levels() {}

Levels::~Levels() {}

bool Levels::init() {
    return true;
}

void Levels::destroy() {}

// set up all static entities
bool Levels::setLevelParam(LevelName curLevel, LevelName preLevel) {
    currentLevel = curLevel;
    switch(curLevel) {
        case LevelName::LEVEL_SELECTION: // FALL THROUGH
        case LevelName::MAIN_MENU: // FALL THROUGH
        default:
            return true;
        case LevelName::VICTORY_PAGE: {
            previousLevel = preLevel;
            EnvironmentPath = (char *) "../data/textures/victoryAssets/v_b.png";
            return true;
        }
        case LevelName::DEFEAT_PAGE: {
            previousLevel = preLevel;
            EnvironmentPath = (char *) "../data/textures/victoryAssets/l_b.png";
            return true;
        }
        case LevelName::TUTORIAL_LEVEL: {
            numRocks = 0;
            numCurrents = 0;
            numHealth = 10;
            curLimits.MAX_BASIC_ENEMIES = 5;
            curLimits.MAX_SHOOTING_ENEMIES = 2;
            curLimits.MAX_SPEED_ENEMIES = 5;
            curLimits.MAX_FRAMES_UNTIL_SPAWN = 60;
            curLimits.MAX_FRAMES_TO_DECREMENT = 3;
            curLimits.DEFAULT_FRAMES_UNTIL_SPEEDUP = 100000;
            curLimits.MIN_FRAMES_UNTIL_SPAWN = 20;
            curLimits.FRAMES_TO_SPEEDUP_BY = 3;
            curLimits.TIME_PER_ABILITY_SPAWN = 10000;
            curLimits.MAX_FRAMES_UNTIL_SHOOT = 100;
            curLimits.MAX_BOSS_ENEMIES = 0;
            curLimits.MAX_BOSS2_ENEMIES = 0;
            curLimits.SPAWNABLE_ABILITIES = {
                    AbilityType::BLINK_SLASH,
                    AbilityType::DROP_BOMB,
                    AbilityType::SHOOT,
                    AbilityType::BOOMERANG,
                    AbilityType::METEOROID
            };
            EnvironmentPath = (char *) "../data/textures/backgrounds/tutorial.png";
            return true;
        }
        case LevelName::LEVEL_ONE: {
            // get max number of rocks
            numRocks = 0;
            // get max number of currents
            numCurrents = 0;
            // get max number of health
            numHealth = 3;
            // get environment Path
            EnvironmentPath = (char *) "../data/textures/backgrounds/background.png";
            // score needed to win
            winningScore = 10000;
            // get enemy numbers
            curLimits.MAX_BASIC_ENEMIES = 5;
            curLimits.MAX_SHOOTING_ENEMIES = 0;
            curLimits.MAX_SPEED_ENEMIES = 0;
            curLimits.MAX_FRAMES_UNTIL_SPAWN = 60;
            curLimits.MAX_FRAMES_TO_DECREMENT = 3;
            curLimits.DEFAULT_FRAMES_UNTIL_SPEEDUP = 100000;
            curLimits.MIN_FRAMES_UNTIL_SPAWN = 20;
            curLimits.FRAMES_TO_SPEEDUP_BY = 3;
            curLimits.TIME_PER_ABILITY_SPAWN = 10000;
            curLimits.MAX_FRAMES_UNTIL_SHOOT = 100;
            curLimits.MAX_BOSS_ENEMIES = 0;
            curLimits.MAX_BOSS2_ENEMIES = 0;
            // get ability types
            curLimits.SPAWNABLE_ABILITIES = {
                    AbilityType::BLINK_SLASH,
                    AbilityType::DROP_BOMB,
                    AbilityType::SHOOT,
                    AbilityType::BOOMERANG,
                    AbilityType::METEOROID
            };
            // get enemy types
            curLimits.SPAWNABLE_ENEMIES = {
                    EnemyType::BASIC
            };
            // TODO: need music entity so we can change music
            return true;
        }
        case LevelName::LEVEL_TWO: {
            // get max number of rocks
            numRocks = 10;
            // get max number of currents
            numCurrents = 3;
            // get max number of health
            numHealth = 3;
            // get environment Path
            EnvironmentPath = (char *) "../data/textures/backgrounds/background.png";
            // score needed to win
            winningScore = 1000;
            // get enemy numbers
            curLimits.MAX_BASIC_ENEMIES = 0;
            curLimits.MAX_SHOOTING_ENEMIES = 0;
            curLimits.MAX_SPEED_ENEMIES = 5;
            curLimits.MAX_FRAMES_UNTIL_SPAWN = 60;
            curLimits.MAX_FRAMES_TO_DECREMENT = 3;
            curLimits.DEFAULT_FRAMES_UNTIL_SPEEDUP = 300;
            curLimits.MIN_FRAMES_UNTIL_SPAWN = 20;
            curLimits.FRAMES_TO_SPEEDUP_BY = 3;
            curLimits.TIME_PER_ABILITY_SPAWN = 10000;
            curLimits.MAX_FRAMES_UNTIL_SHOOT = 100;
            curLimits.MAX_BOSS_ENEMIES = 0;
            curLimits.MAX_BOSS2_ENEMIES = 0;
            // get ability types
            curLimits.SPAWNABLE_ABILITIES = {
                    AbilityType::BLINK_SLASH,
                    AbilityType::DROP_BOMB,
                    AbilityType::SHOOT,
                    AbilityType::BOOMERANG,
                    AbilityType::METEOROID
            };
            // get enemy types
            curLimits.SPAWNABLE_ENEMIES = {
                    EnemyType::SPEED
            };
            // TODO: need music entity so we can change music
            return true;
        }
        case LevelName::LEVEL_THREE: {
            // get max number of rocks
            numRocks = 10;
            // get max number of currents
            numCurrents = 3;
            // get max number of health
            numHealth = 3;
            // get environment Path
            EnvironmentPath = (char *) "../data/textures/backgrounds/background.png";
            // score needed to win
            winningScore = 1000;
            // get enemy types
            // get enemy numbers
            curLimits.MAX_BASIC_ENEMIES = 0;
            curLimits.MAX_SHOOTING_ENEMIES = 5;
            curLimits.MAX_SPEED_ENEMIES = 0;
            curLimits.MAX_FRAMES_UNTIL_SPAWN = 60;
            curLimits.MAX_FRAMES_TO_DECREMENT = 3;
            curLimits.DEFAULT_FRAMES_UNTIL_SPEEDUP = 300;
            curLimits.MIN_FRAMES_UNTIL_SPAWN = 20;
            curLimits.FRAMES_TO_SPEEDUP_BY = 3;
            curLimits.TIME_PER_ABILITY_SPAWN = 10000;
            curLimits.MAX_FRAMES_UNTIL_SHOOT = 100;
            curLimits.MAX_BOSS_ENEMIES = 0;
            curLimits.MAX_BOSS2_ENEMIES = 0;
            // get ability types
            curLimits.SPAWNABLE_ABILITIES = {
                    AbilityType::BLINK_SLASH,
                    AbilityType::DROP_BOMB,
                    AbilityType::SHOOT,
                    AbilityType::BOOMERANG,
                    AbilityType::METEOROID
            };
            // get enemy types
            curLimits.SPAWNABLE_ENEMIES = {
                    EnemyType::SHOOTING
            };
            // TODO: need music entity so we can change music
            return true;
        }
        case LevelName::LEVEL_FOUR: {
            // get max number of rocks
            numRocks = 10;
            // get max number of health
            numHealth = 3;
            // get max number of currents
            numCurrents = 3;
            // get environment Path
            EnvironmentPath = (char *) "../data/textures/backgrounds/background.png";
            // score needed to win
            winningScore = 500;
            // get enemy types
            // get enemy numbers
            curLimits.MAX_BASIC_ENEMIES = 3;
            curLimits.MAX_SHOOTING_ENEMIES = 3;
            curLimits.MAX_SPEED_ENEMIES = 3;
            curLimits.MAX_FRAMES_UNTIL_SPAWN = 60;
            curLimits.MAX_FRAMES_TO_DECREMENT = 3;
            curLimits.DEFAULT_FRAMES_UNTIL_SPEEDUP = 300;
            curLimits.MIN_FRAMES_UNTIL_SPAWN = 20;
            curLimits.FRAMES_TO_SPEEDUP_BY = 3;
            curLimits.TIME_PER_ABILITY_SPAWN = 10000;
            curLimits.MAX_FRAMES_UNTIL_SHOOT = 100;
            curLimits.MAX_BOSS_ENEMIES = 0;
            curLimits.MAX_BOSS2_ENEMIES = 0;
            // get ability types
            curLimits.SPAWNABLE_ABILITIES = {
                    AbilityType::BLINK_SLASH,
                    AbilityType::DROP_BOMB,
                    AbilityType::SHOOT,
                    AbilityType::BOOMERANG,
                    AbilityType::METEOROID
            };
            // get enemy types
            curLimits.SPAWNABLE_ENEMIES = {
                    EnemyType::BASIC,
                    EnemyType::SPEED,
                    EnemyType::SHOOTING
            };
            // TODO: need music entity so we can change music
            return true;
        }
        case LevelName::LEVEL_FIVE: {
            // get max number of rocks
            numRocks = 15;
            // get max number of health
            numHealth = 3;
            // get max number of currents
            numCurrents = 3;
            // get environment Path
            EnvironmentPath = (char *) "../data/textures/backgrounds/background.png";
            // score needed to win
            winningScore = 1000;
            // get enemy numbers
            curLimits.MAX_BASIC_ENEMIES = 0;
            curLimits.MAX_SHOOTING_ENEMIES = 0;
            curLimits.MAX_SPEED_ENEMIES = 0;
            curLimits.MAX_FRAMES_UNTIL_SPAWN = 60;
            curLimits.MAX_FRAMES_TO_DECREMENT = 3;
            curLimits.DEFAULT_FRAMES_UNTIL_SPEEDUP = 300;
            curLimits.MIN_FRAMES_UNTIL_SPAWN = 45;
            curLimits.FRAMES_TO_SPEEDUP_BY = 3;
            curLimits.TIME_PER_ABILITY_SPAWN = 10000;
            curLimits.MAX_FRAMES_UNTIL_SHOOT = 100;
            curLimits.MAX_BOSS_ENEMIES = 1;
            curLimits.MAX_BOSS2_ENEMIES = 0;
            // get ability types
            curLimits.SPAWNABLE_ABILITIES = {
                    AbilityType::BLINK_SLASH,
                    AbilityType::DROP_BOMB,
                    AbilityType::SHOOT,
                    AbilityType::BOOMERANG,
                    AbilityType::METEOROID
            };
            // get enemy types
            curLimits.SPAWNABLE_ENEMIES = {
                    EnemyType::BASIC,
                    EnemyType::SPEED,
                    EnemyType::SHOOTING,
                    EnemyType::BOSS
            };
            // TODO: need music entity so we can change music
            return true;
        }
        case LevelName::LEVEL_SIX: {
            // get max number of rocks
            numRocks = 10;
            // get max number of currents
            numCurrents = 3;
            // get max number of health
            numHealth = 3;
            // get environment Path
            EnvironmentPath = (char *) "../data/textures/backgrounds/background2.png";
            // score needed to win
            winningScore = 2000;
            // get enemy numbers
            curLimits.MAX_BASIC_ENEMIES = 6;
            curLimits.MAX_SHOOTING_ENEMIES = 0;
            curLimits.MAX_SPEED_ENEMIES = 6;
            curLimits.MAX_FRAMES_UNTIL_SPAWN = 60;
            curLimits.MAX_FRAMES_TO_DECREMENT = 3;
            curLimits.DEFAULT_FRAMES_UNTIL_SPEEDUP = 300;
            curLimits.MIN_FRAMES_UNTIL_SPAWN = 45;
            curLimits.FRAMES_TO_SPEEDUP_BY = 3;
            curLimits.TIME_PER_ABILITY_SPAWN = 10000;
            curLimits.MAX_FRAMES_UNTIL_SHOOT = 100;
            curLimits.MAX_BOSS_ENEMIES = 0;
            curLimits.MAX_BOSS2_ENEMIES = 0;
            // get ability types
            curLimits.SPAWNABLE_ABILITIES = {
                    AbilityType::BLINK_SLASH,
                    AbilityType::DROP_BOMB,
                    AbilityType::SHOOT,
                    AbilityType::BOOMERANG,
                    AbilityType::METEOROID
            };
            // get enemy types
            curLimits.SPAWNABLE_ENEMIES = {
                    EnemyType::BASIC,
                    EnemyType::SPEED
            };
            // TODO: need music entity so we can change music
            return true;
        }
        case LevelName::LEVEL_SEVEN: {
            // get max number of rocks
            numRocks = 0;
            // get max number of currents
            numCurrents = 10;
            // get max number of health
            numHealth = 3;
            // get environment Path
            EnvironmentPath = (char *) "../data/textures/backgrounds/background2.png";
            // score needed to win
            winningScore = 2000;
            // get enemy numbers
            curLimits.MAX_BASIC_ENEMIES = 0;
            curLimits.MAX_SHOOTING_ENEMIES = 10;
            curLimits.MAX_SPEED_ENEMIES = 0;
            curLimits.MAX_FRAMES_UNTIL_SPAWN = 60;
            curLimits.MAX_FRAMES_TO_DECREMENT = 3;
            curLimits.DEFAULT_FRAMES_UNTIL_SPEEDUP = 300;
            curLimits.MIN_FRAMES_UNTIL_SPAWN = 20;
            curLimits.FRAMES_TO_SPEEDUP_BY = 3;
            curLimits.TIME_PER_ABILITY_SPAWN = 10000;
            curLimits.MAX_FRAMES_UNTIL_SHOOT = 100;
            curLimits.MAX_BOSS_ENEMIES = 0;
            curLimits.MAX_BOSS2_ENEMIES = 0;
            // get ability types
            curLimits.SPAWNABLE_ABILITIES = {
                    AbilityType::BLINK_SLASH,
                    AbilityType::DROP_BOMB,
                    AbilityType::SHOOT,
                    AbilityType::BOOMERANG,
                    AbilityType::METEOROID
            };
            // get enemy types
            curLimits.SPAWNABLE_ENEMIES = {
                    EnemyType::SHOOTING
            };
            // TODO: need music entity so we can change music
            return true;
        }
        case LevelName::LEVEL_EIGHT: {
            // get max number of rocks
            numRocks = 5;
            // get max number of currents
            numCurrents = 3;
            // get max number of health
            numHealth = 3;
            // get environment Path
            EnvironmentPath = (char *) "../data/textures/backgrounds/background2.png";
            // score needed to win
            winningScore = 1000;
            // get enemy numbers
            curLimits.MAX_BASIC_ENEMIES = 10;
            curLimits.MAX_SHOOTING_ENEMIES = 5;
            curLimits.MAX_SPEED_ENEMIES = 0;
            curLimits.MAX_FRAMES_UNTIL_SPAWN = 50;
            curLimits.MAX_FRAMES_TO_DECREMENT = 3;
            curLimits.DEFAULT_FRAMES_UNTIL_SPEEDUP = 250;
            curLimits.MIN_FRAMES_UNTIL_SPAWN = 20;
            curLimits.FRAMES_TO_SPEEDUP_BY = 3;
            curLimits.TIME_PER_ABILITY_SPAWN = 10000;
            curLimits.MAX_FRAMES_UNTIL_SHOOT = 100;
            curLimits.MAX_BOSS_ENEMIES = 0;
            curLimits.MAX_BOSS2_ENEMIES = 0;
            // get ability types
            curLimits.SPAWNABLE_ABILITIES = {
                    AbilityType::BLINK_SLASH,
                    AbilityType::DROP_BOMB,
                    AbilityType::SHOOT,
                    AbilityType::BOOMERANG,
                    AbilityType::METEOROID
            };
            // get enemy types
            curLimits.SPAWNABLE_ENEMIES = {
                    EnemyType::BASIC,
                    EnemyType::SHOOTING
            };
            // TODO: need music entity so we can change music
            return true;
        }
        case LevelName::LEVEL_NINE: {
            // get max number of rocks
            numRocks = 30;
            // get max number of currents
            numCurrents = 3;
            // get max number of health
            numHealth = 3;
            // get environment Path
            EnvironmentPath = (char *) "../data/textures/backgrounds/background2.png";
            // score needed to win
            winningScore = 2000;
            // get enemy numbers
            curLimits.MAX_BASIC_ENEMIES = 6;
            curLimits.MAX_SHOOTING_ENEMIES = 6;
            curLimits.MAX_SPEED_ENEMIES = 6;
            curLimits.MAX_FRAMES_UNTIL_SPAWN = 45;
            curLimits.MAX_FRAMES_TO_DECREMENT = 3;
            curLimits.DEFAULT_FRAMES_UNTIL_SPEEDUP = 225;
            curLimits.MIN_FRAMES_UNTIL_SPAWN = 20;
            curLimits.FRAMES_TO_SPEEDUP_BY = 3;
            curLimits.TIME_PER_ABILITY_SPAWN = 10000;
            curLimits.MAX_FRAMES_UNTIL_SHOOT = 100;
            curLimits.MAX_BOSS_ENEMIES = 0;
            curLimits.MAX_BOSS2_ENEMIES = 0;
            // get ability types
            curLimits.SPAWNABLE_ABILITIES = {
                    AbilityType::BLINK_SLASH,
                    AbilityType::DROP_BOMB,
                    AbilityType::SHOOT,
                    AbilityType::BOOMERANG,
                    AbilityType::METEOROID
            };
            // get enemy types
            curLimits.SPAWNABLE_ENEMIES = {
                    EnemyType::BASIC,
                    EnemyType::SPEED,
                    EnemyType::SHOOTING
            };
            // TODO: need music entity so we can change music
            return true;
        }
        case LevelName::LEVEL_TEN: {
            // get max number of rocks
            numRocks = 10;
            // get max number of currents
            numCurrents = 3;
            // get max number of health
            numHealth = 3;
            // get environment Path
            EnvironmentPath = (char *) "../data/textures/backgrounds/background2.png";
            // score needed to win
            winningScore = 200000;

            // get enemy numbers
            curLimits.MAX_BASIC_ENEMIES = 0;
            curLimits.MAX_SHOOTING_ENEMIES = 0;
            curLimits.MAX_SPEED_ENEMIES = 0;
            curLimits.MAX_FRAMES_UNTIL_SPAWN = 120;
            curLimits.MAX_FRAMES_TO_DECREMENT = 3;
            curLimits.DEFAULT_FRAMES_UNTIL_SPEEDUP = 225;
            curLimits.MIN_FRAMES_UNTIL_SPAWN = 60;
            curLimits.FRAMES_TO_SPEEDUP_BY = 3;
            curLimits.TIME_PER_ABILITY_SPAWN = 10000;
            curLimits.MAX_FRAMES_UNTIL_SHOOT = 100;
            curLimits.MAX_BOSS_ENEMIES = 0;
            curLimits.MAX_BOSS2_ENEMIES = 1;
            // get ability types
            curLimits.SPAWNABLE_ABILITIES = {
                    AbilityType::BLINK_SLASH,
                    AbilityType::DROP_BOMB,
                    AbilityType::SHOOT,
                    AbilityType::BOOMERANG,
                    AbilityType::METEOROID
            };
            // get enemy types
            curLimits.SPAWNABLE_ENEMIES = {
                    EnemyType::BOSS2
            };
            // TODO: need music entity so we can change music
            return true;
        }
            // survival mode
        case LevelName::SURVIVAL_MODE: {
            // get max number of rocks
            numRocks = 5;
            // get max number of currents
            numCurrents = 3;
            // get max number of health
            numHealth = 3;
            // get environment Path
            EnvironmentPath = (char*) "../data/textures/backgrounds/background2.png";
            //wining score
            winningScore = INT_MAX;
            // get enemy numbers
            curLimits.MAX_BASIC_ENEMIES = 5;
            curLimits.MAX_SHOOTING_ENEMIES = 5;
            curLimits.MAX_SPEED_ENEMIES = 5;
            curLimits.MAX_FRAMES_UNTIL_SPAWN = 120;
            curLimits.MAX_FRAMES_TO_DECREMENT = 3;
            curLimits.DEFAULT_FRAMES_UNTIL_SPEEDUP = 225;
            curLimits.MIN_FRAMES_UNTIL_SPAWN = 60;
            curLimits.FRAMES_TO_SPEEDUP_BY = 3;
            curLimits.TIME_PER_ABILITY_SPAWN = 10000;
            curLimits.MAX_FRAMES_UNTIL_SHOOT = 100;
            curLimits.MAX_BOSS_ENEMIES = 1;
            curLimits.MAX_BOSS2_ENEMIES = 1;
            // get ability types
            curLimits.SPAWNABLE_ABILITIES = {
                    AbilityType::BLINK_SLASH,
                    AbilityType::DROP_BOMB,
                    AbilityType::SHOOT,
                    AbilityType::BOOMERANG,
                    AbilityType::METEOROID
            };
            // get enemy types
            curLimits.SPAWNABLE_ENEMIES = {
                    EnemyType::BASIC,
                    EnemyType::SPEED,
                    EnemyType::SHOOTING,
                    EnemyType::BOSS,
                    EnemyType::BOSS2
            };
            // TODO: need music entity so we can change music
            return true;
        }
    }
}

int Levels::getNumRocks() {
    return numRocks;
}

int Levels::getNumCurrents() {
    return numCurrents;
}

int Levels::getNumHealth() {
    return numHealth;
}

char* Levels::getEnvironmentPath() {
    return EnvironmentPath;
}

SpawnLimits* Levels::getCurLimits() {
    return &curLimits;
}

int Levels::getNumCharges() {
    return numCharges;
}

LevelName Levels::getCurrentLevel() {
    return currentLevel;
}

LevelName Levels::getPreviousLevel() {
    return previousLevel;
}

unsigned long Levels::getWinningScore() {
    return winningScore;
}