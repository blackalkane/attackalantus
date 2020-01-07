#pragma once

// internal
#include "common.hpp"
#include "levels.hpp"
#include "entities/environment.hpp"
#include "levelName.hpp"

// stlib
#include <vector>
#include <random>

#define SDL_MAIN_HANDLED

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
#include <entities/abilityType.hpp>
#include <entities/healthBar.hpp>
#include <entities/bomb.hpp>
#include <entities/slash.hpp>
#include <entities/gun.hpp>
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
#include <systems/soundSystem.hpp>
#include <entities/bossEnemy.hpp>
#include <entities/bossEnemy2.hpp>
#include <systems/bossAISystem.hpp>
#include <systems/missileSystem.hpp>
#include <systems/system.hpp>
#include <systems/drawSystem.hpp>
#include <systems/controlSystem.hpp>
#include <entities/defaultTexture.hpp>
#include <entities/bombExplosion.hpp>
#include <entities/waterCurrent.hpp>
#include <entities/castle.hpp>
#include <systems/petRouteSystem.hpp>
#include <systems/particleEffectSystem.hpp>

extern vec2 velocity;
extern float direction;

// Container for all our entities and game logic. Individual rendering / update is 
// deferred to the relative update() methods
class TutorialLevel {
public:
    TutorialLevel();

    ~TutorialLevel();

    // Creates a window, sets up events and begins the game
    bool init(vec2 screen, Levels* levelsObj);

    // Releases all associated resources
    void destroy();

    // Steps the game ahead by ms milliseconds
    bool update(float ms);

    bool inGameUpdate(float elapsed_ms, vec2 screen);

    bool inGameConditionUpdate(float elapsed_ms, vec2 screen);

    // Renders our scene
    void draw();

    // Should the game be over ?
    bool is_over() const;

    Enemy *createEnemy(EnemyType type);

    std::vector<Projectile *> *getProjectiles();

    std::vector<EnemyProjectile *> *getEnemyProjectiles();

    // !!! INPUT CALLBACK FUNCTIONS
    void on_key(GLFWwindow *, int key, int, int action, int mod);

    void on_mouse_move(GLFWwindow *, double xpos, double ypos);

    void on_mouse_button(GLFWwindow *, int button, int action, int mod);

    TheGuy *getTheGuy();

    AbilityContainer *createAbilityContainer(AbilityType ability);

    LevelName getNextLevel();

    LevelName getCurrentLevel();

    unsigned long getWinningScore();

    static char* getCurrentLevelTexture(LevelName ln);

    static vec2 setCurrentLevelScale(LevelName ln);

    static vec2 setCurrentLevelPos(LevelName ln);

    static char* getEnemyTexture(EnemyType et);

    void getEnemyTexturePoses(int basic, int speed, int shooting, int bossLife);

    static char* getEnemyCounter(int numEnemy);

    void createEnemyCounterTexture();

    void updateHealthAndAbilityTexture();

    void updateEnemyCounter();

    void updateProjectilesAndEnemyProjectiles(vec2 screen);

    bool checkIfWin();

    bool checkIfLose(int curHealth);

    // Window handle
    GLFWwindow *m_window;
private:
    float m_screen_scale; // Screen to pixel coordinates scale factor
    Environment environment;

    // Screen texture
    // The draw loop first renders to this texture, then it is used for the water shader
    GLuint m_frame_buffer;
    Texture m_screen_tex;

    // C++ rng
    std::default_random_engine m_rng;
    std::uniform_real_distribution<float> m_dist; // default 0..1

    // important meta data field
    int numRocks;
    int basicEnemyShouldBeKilled;
    vec2 basicEnemyTexturePos;
    int speedEnemyShouldBeKilled;
    vec2 speedEnemyTexturePos;
    int shootEnemyShouldBeKilled;
    vec2 shootEnemyTexturePos;
    int bossLifeShouldBeKilled;
    vec2 bossLifeTexturePos;
    int numCurrents;
    unsigned long winningScore;
    vec2 mousePos;
    int currentFrame;
    static const int DELETEFRAME = 100;
    bool winningAnimationFlag;
    int winningDeleteCounter;
    bool defeatDeleteFlag;
    int defeatDeleteCounter;

    // list of entities
    TheGuy theGuy;
    std::vector<Enemy *> enemies;
    std::vector<Rock *> rocks;
    std::vector<Castle *> castles;
    std::vector<WaterCurrent *> currents;
    std::vector<Projectile *> projectiles;
    std::vector<EnemyProjectile *> enemyProjectiles;
    std::vector<HealthBar *> healthBars;
    std::vector<Entity *> charges;
    AbilityType prevType;
    DefaultTexture curLevelInGame;
    DefaultTexture basicEnemyTexture;
    DefaultTexture basicEnemyX;
    DefaultTexture basicEnemyCounter;
    DefaultTexture speedEnemyTexture;
    DefaultTexture speedEnemyX;
    DefaultTexture speedEnemyCounter;
    DefaultTexture shootEnemyTexture;
    DefaultTexture shootEnemyX;
    DefaultTexture shootEnemyCounter;
    DefaultTexture bossLifeTexture;
    DefaultTexture bossLifeHeart;
    DefaultTexture bossLifeX;
    DefaultTexture bossLifeCounter;
    MenuItems pauseButton;
    vec2 pausePos;
    bool isInPauseAera;
    bool isInBasicArea;
    bool isInSpeedArea;
    bool isInShootingArea;
    bool isPause;
    bool isBasic;
    bool isSpeed;
    bool isShooting;

    // list of systems
    std::vector<System *> systems;
    DrawSystem* drawSystem;
    MoveSystem* moveSystem;
    MusicSystem* musicSystem;
    CollisionSystem* collisionSystem;
    SimpleAISystem* simpleAiSystem;
    ShootingAISystem* shootingAiSystem;
    BossAISystem* bossAiSystem;
    MissileSystem* missileSystem;
    ControlSystem* controlSystem;
    AbilitySystem* abilitySystem;
    SpawnSystem* spawnSystem;
    DeleteSystem* deleteSystem;
    ScoreSystem* scoreSystem;
    SoundSystem* soundSystem;
    ParticleEffectSystem* particleEffectSystem;
    PetRouteSystem* petRouteSystem;

    // curLevel
    LevelName curLevel;
    LevelName nextLevel;

    void createRocks(int numRocks, LevelName level);
    
    vec2 getValidSpawnPosition();

    void removeEntityFromSystems(Entity *toBeRemoved);
};
