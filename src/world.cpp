// Header
#include "world.hpp"
#include "global.hpp"
#include "levelName.hpp"

// stlib
#include <cassert>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <entities/waterCurrent.hpp>
#include <entities/boomerangIcon.hpp>
#include <entities/castle.hpp>
#include <entities/particle.hpp>
#include <entities/rainDrop.hpp>
#include <entities/pork.hpp>
#include <entities/meteoroid.hpp>
#include <entities/meteoroidIcon.hpp>
#include <entities/firePet.hpp>
#include <entities/castleTop.hpp>

vec2 velocity;

namespace {
    void glfw_err_cb(int error, const char *desc) {
        fprintf(stderr, "%d: %s", error, desc);
    }
} // namespace

World::World() {
    // Seeding rng with random device
    m_rng = std::default_random_engine(std::random_device()());
}

World::~World() {
}

// World initialization
bool World::init(vec2 screen, Levels *levelsObj) {
    //-------------------------------------------------------------------------
    // GLFW / OGL Initialization
    // Core Opengl 3.

    glfwSetErrorCallback(glfw_err_cb);
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, 0);
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    m_window = glfwCreateWindow((int) screen.x, (int) screen.y, "Attackalantus", nullptr, nullptr);
    glfwSetWindowPos(m_window, (mode->width / 2) - (int) (screen.x / 2), (mode->height / 2) - (int) (screen.y / 2));
    if (m_window == nullptr)
        return false;

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // vsync

    // Load OpenGL function pointers
    gl3w_init();

    // Setting callbacks to member functions (that's why the redirect is needed)
    // Input is handled using GLFW, for more info see
    // http://www.glfw.org/docs/latest/input_guide.html
    glfwSetWindowUserPointer(m_window, this);
    auto key_redirect = [](GLFWwindow *wnd, int _0, int _1, int _2, int _3) {
        ((World *) glfwGetWindowUserPointer(wnd))->on_key(wnd, _0, _1, _2, _3);
    };
    auto cursor_pos_redirect = [](GLFWwindow *wnd, double _0, double _1) {
        ((World *) glfwGetWindowUserPointer(wnd))->on_mouse_move(wnd, _0, _1);
    };
    auto mouse_button_redirect = [](GLFWwindow *wnd, int _0, int _1, int _2) {
        ((World *) glfwGetWindowUserPointer(wnd))->on_mouse_button(wnd, _0, _1, _2);
    };
    glfwSetKeyCallback(m_window, key_redirect);
    glfwSetCursorPosCallback(m_window, cursor_pos_redirect);
    glfwSetMouseButtonCallback(m_window, mouse_button_redirect);


    // Create a frame buffer
    m_frame_buffer = 0;
    glGenFramebuffers(1, &m_frame_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer);

    // For some high DPI displays (ex. Retina Display on Macbooks)
    // https://stackoverflow.com/questions/36672935/why-retina-screen-coordinate-value-is-twice-the-value-of-pixel-value
    int fb_width, fb_height;
    glfwGetFramebufferSize(m_window, &fb_width, &fb_height);
    m_screen_scale = static_cast<float>(fb_width) / screen.x;


    // Initialize the screen texture
    m_screen_tex.create_from_screen(m_window);

    /////////////////////////////////////////////////////////////////////////////////////
    // self declare world init
    /////////////////////////////////////////////////////////////////////////////////////

    // set new world var
    TheGuy::newWorld = true;
    ShootingEnemy::newWorld = true;
    SpeedEnemy::newWorld = true;
    BasicEnemy::newWorld = true;
    BossEnemy::newWorld = true;
    BossEnemy2::newWorld = true;
    Projectile::newWorld = true;
    BoomerangProjectile::newWorldBoomerang = true;
    EnemyProjectile::newWorld = true;
    BossProjectile::newWorld = true;
    AbilityContainer::newWorld = true;
    Bomb::newWorld = true;
    BombExplosion::newWorld = true;
    WaterCurrent::newWorld = true;
    Particle::newWorld = true;
    RainDrop::newWorld = true;
    Pork::newWorld = true;
    Meteoroid::newWorld = true;
    FireLittleParticle::newWorld = true;
    FirePet::newWorld = true;
    rocks.clear();
    castles.clear();
    currents.clear();
    projectiles.clear();
    enemyProjectiles.clear();
    bossProjectiles.clear();
    enemies.clear();
    healthBars.clear();
    charges.clear();

    // meta data init
    int w, h;
    glfwGetFramebufferSize(m_window, &w, &h);
    currentFrame = 0;
    curLevel = levelsObj->getCurrentLevel();
    nextLevel = LevelName::NO_LEVEL;
    isInPauseAera = false;
    isPause = false;
    winningAnimationFlag = false;
    winningDeleteCounter = 0;
    defeatDeleteFlag = false;
    defeatDeleteCounter = 0;

    srand(time(NULL));
    mousePos = {0.f, 0.f};

    // system init
    moveSystem = syss->getMoveSystem();
    simpleAiSystem = syss->getSimpleAISystem();
    shootingAiSystem = syss->getShootingAISystem();
    bossAiSystem = syss->getBossAISystem();
    bossAiSystem2 = syss->getBossAISystem2();
    missileSystem = syss->getMissileSystem();
    icePickSystem = syss->getIcePickSystem();
    float velocity = 1.5f;
    simpleAiSystem->setVelocity(velocity);
    shootingAiSystem->setVelocity(velocity);
    bossAiSystem->setVelocity(velocity);
    bossAiSystem2->setVelocity(velocity);
    missileSystem->setVelocity(velocity * 3);
    icePickSystem->setVelocity(velocity * 3);
    controlSystem = syss->getControlSystem();
    musicSystem = syss->getMusicSystem();
    musicSystem->openAudio();
    musicSystem->loadBackgroundMusic();
    musicSystem->playBackgroundMusic();
    soundSystem = syss->getSoundSystem();
    soundSystem->openAudio();
    soundSystem->loadAllMusic();
    drawSystem = syss->getDrawSystem();
    collisionSystem = syss->getCollisionSystem();
    abilitySystem = syss->getAbilitySystem();
    spawnSystem = syss->getSpawnSystem();
    spawnSystem->initAbilityContainer();
    scoreSystem = syss->getScoreSystem();
    scoreSystem->setWindow(m_window);
    deleteSystem = syss->getDeleteSystem();
    particleEffectSystem = syss->getParticleEffectSystem();
    petRouteSystem = syss->getPetRouteSystem();
    petRouteSystem->setVelocity(velocity * 4);
    scoreSystem->resetScore();

    // entities init
    theGuy.setMaxHealth(levelsObj->getNumHealth());
    theGuy.init();
    environment.setTexturePath(levelsObj->getEnvironmentPath());
    environment.init();
    curLevelInGame.setLevelTexture(getCurrentLevelTexture(curLevel));
    curLevelInGame.init();
    curLevelInGame.getPositionComponent()->setPosition(setCurrentLevelPos(curLevel));
    curLevelInGame.getDrawComponent()->setScale(setCurrentLevelScale(curLevel));
    numRocks = levelsObj->getNumRocks();
    numCurrents = levelsObj->getNumCurrents();
    winningScore = levelsObj->getWinningScore();

    std::string pausePath = "../data/textures/menuText/exit_highlight.png";
    pauseButton.setMenuTexture(pausePath);
    pauseButton.init();
    pauseButton.getPositionComponent()->setPosition({120, 30});
    pauseButton.getDrawComponent()->setScale({0.3, 0.3});
    pausePos = pauseButton.getPositionComponent()->getPosition();

    drawSystem->addEntity((Drawable *) &environment);
    drawSystem->addEntity((Drawable *) &curLevelInGame);
    drawSystem->addEntity((Drawable *) &pauseButton);

    basicEnemyShouldBeKilled = levelsObj->getCurLimits()->MAX_BASIC_ENEMIES;
    speedEnemyShouldBeKilled = levelsObj->getCurLimits()->MAX_SPEED_ENEMIES;
    shootEnemyShouldBeKilled = levelsObj->getCurLimits()->MAX_SHOOTING_ENEMIES;
    bossLifeShouldBeKilled = levelsObj->getCurLimits()->MAX_BOSS_ENEMIES * 8;
    boss2LifeShouldBeKilled = levelsObj->getCurLimits()->MAX_BOSS2_ENEMIES * 8;
    getEnemyTexturePoses(basicEnemyShouldBeKilled, speedEnemyShouldBeKilled, shootEnemyShouldBeKilled,
                         bossLifeShouldBeKilled, boss2LifeShouldBeKilled);
    createEnemyCounterTexture();
    createRocks(numRocks, levelsObj->getCurrentLevel());

    drawSystem->addEntity((Drawable *) &theGuy);

    int numHealth = theGuy.getHealthComponent()->getHealth();
    vec2 theGuyInitPos = theGuy.getPositionComponent()->getPosition();
    for (int i = 0; i < numHealth; i++) {
        HealthBar *healthBar = new HealthBar();
        healthBar->init();
        healthBar->getPositionComponent()->setPosition({theGuyInitPos.x - 15 * i, theGuyInitPos.y - 15});
        //healthBar->getPositionComponent()->setPosition({1100.f + (i * 35), 25.f});
        healthBars.push_back(healthBar);
        drawSystem->addEntity((Drawable *) healthBar);
    }

    // draw the ability icons
    int numCharges = theGuy.getAbilityComponent()->getNumCharges();

    AbilityType type = theGuy.getAbilityComponent()->getAbilityType();
    for (int i = 0; i < numCharges; i++) {
        switch (type) {
            case AbilityType::BLINK_SLASH : {
                Slash *slash = new Slash();
                slash->init();
                slash->getPositionComponent()->setPosition({1100.f + (i * 35), 30.f});
                charges.push_back(slash);
                drawSystem->addEntity((Drawable *) slash);
                break;
            }
            case AbilityType::DROP_BOMB : {
                Bomb *bomb = new Bomb();
                bomb->init();
                bomb->getPositionComponent()->setPosition({1100.f + (i * 35), 30.f});
                charges.push_back(bomb);
                drawSystem->addEntity((Drawable *) bomb);
                break;
            }
            default: {
            }
        }
    }
    prevType = type;

    collisionSystem->addEntity((Collides *) &theGuy);
    controlSystem->addEntity((Entity *) &theGuy);
    moveSystem->addEntity(&theGuy);
    abilitySystem->addEntity(&theGuy);

    createCastleTops(levelsObj->getCurrentLevel());
    drawSystem->setProjection(w, h, m_screen_scale);

    // add system to systems
    systems.push_back(drawSystem);
    systems.push_back(controlSystem);
    systems.push_back(moveSystem);
    systems.push_back(collisionSystem);
    systems.push_back(simpleAiSystem);
    systems.push_back(shootingAiSystem);
    systems.push_back(bossAiSystem);
    systems.push_back(bossAiSystem2);
    systems.push_back(abilitySystem);
    systems.push_back(spawnSystem);
    systems.push_back(scoreSystem);
    systems.push_back(soundSystem);
    systems.push_back(missileSystem);
    systems.push_back(icePickSystem);

    return true;
}

// Releases all the associated resources
void World::destroy() {
    glDeleteFramebuffers(1, &m_frame_buffer);
    musicSystem->destroy();
    for (HealthBar *h: healthBars) {
        free(h);
        h = nullptr;
    }
    for (Rock *r: rocks) {
        free(r);
        r = nullptr;
    }
    for (WaterCurrent *w: currents) {
        free(w);
        w = nullptr;
    }
    for (Enemy *e: enemies) {
        free(e);
    }
    for (Projectile *p: projectiles) {
        free(p);
    }
    for (EnemyProjectile *ep: enemyProjectiles) {
        free(ep);
    }
    for (BossProjectile *ep: bossProjectiles) {
        free(ep);
    }
//    for(Entity* charge: charges) {
//        free(charge);
//    }
    healthBars.clear();
    rocks.clear();
    castles.clear();
    enemies.clear();
    projectiles.clear();
    enemyProjectiles.clear();
    bossProjectiles.clear();
    charges.clear();
    currents.clear();
    glfwDestroyWindow(m_window);
}

// Update our game world
bool World::update(float elapsed_ms) {
    int w, h;
    glfwGetFramebufferSize(m_window, &w, &h);
    vec2 screen = {(float) w / m_screen_scale, (float) h / m_screen_scale};

    /////////////////////////////////////////////////////////////////////////////////
    // self update code
    ////////////////////////////////////////////////////////////////////////////////
    moveSystem->setBoundary((int) screen.x, (int) screen.y);
    int currHealth = theGuy.getHealthComponent()->getHealth();

    if (isPause) {
        nextLevel = LevelName::LEVEL_SELECTION;
        glfwSetWindowShouldClose(m_window, 1);
    }

    if (checkIfWin()) {
        // just win
        if (!winningAnimationFlag) {
            scoreSystem->resetScore();
            nextLevel = LevelName::VICTORY_PAGE;
            //std::unordered_set<Collides *> toBeKilled;
            for (Entity *enemy: drawSystem->getEntityList()) {
                //if (enemy->type != EntityType::ENVIRONMENT && enemy->type != EntityType::THEGUY)
                if (enemy->type == EntityType::ENEMY) {
                    //toBeKilled.emplace(enemy);
                    syss->removeEntityFromSystems(enemy);
                    syss->getDrawSystem()->addEntity(enemy);
                    syss->getDeleteSystem()->addEntity(enemy);
                    winningDeleteCounter++;
                }
            }
            syss->getDeleteSystem()->setWinningDeleteCounter(winningDeleteCounter);
            winningAnimationFlag = true;
        }
        // start death animation
        if (winningAnimationFlag) {
            inGameConditionUpdate(elapsed_ms, screen);
            if (syss->getDeleteSystem()->getWinningDeleteCounter() <= 0) {
                winningAnimationFlag = false;
                glfwSetWindowShouldClose(m_window, 1);
            }
        }
    } else if (checkIfLose(currHealth)) {
        if (!defeatDeleteFlag) {
            // Check to see if we should go to leaderboard
            // and save high score when we were playing survival mode
            if (curLevel == LevelName::SURVIVAL_MODE) {
                nextLevel = LevelName::LEADERBOARD;
                if (scoreSystem->isHighScore()) {
                    scoreSystem->saveCurrentScore();
                    auto highScore = scoreSystem->getSavedScore();
                    // TODO think about how to allow name input
                    scoreSystem->addScoreRecord(highScore, "Anonymous");
                }
            } else { // playing regular level
                nextLevel = LevelName::DEFEAT_PAGE;
            }

            scoreSystem->resetScore();

            for (Entity *enemy: drawSystem->getEntityList()) {
                if (enemy->type == EntityType::THEGUY) {
                    syss->removeEntityFromSystems(enemy);
                    syss->getDrawSystem()->addEntity(enemy);
                    syss->getDeleteSystem()->addEntity(enemy);
                    defeatDeleteCounter++;
                }
            }
            syss->getDeleteSystem()->setDefeatDeleteCounter(defeatDeleteCounter);
            defeatDeleteFlag = true;
        }

        if (defeatDeleteFlag) {
            inGameConditionUpdate(elapsed_ms, screen);
            if (syss->getDeleteSystem()->getDefeatDeleteCounter() <= 0) {
                defeatDeleteFlag = false;
                glfwSetWindowShouldClose(m_window, 1);
            }
        }
    }
        // in game
    else {
        return inGameUpdate(elapsed_ms, screen);
    }

    return true;
}

bool World::inGameUpdate(float elapsed_ms, vec2 screen) {
    updateHealthAndAbilityTexture();
    // delete the previous frame death entity first
    deleteSystem->update(0);

    controlSystem->setPos(theGuy.getPositionComponent()->getPosition());
    simpleAiSystem->setDestPoint(theGuy.getPositionComponent()->getPosition());
    shootingAiSystem->setDestPoint(theGuy.getPositionComponent()->getPosition());
    bossAiSystem->setDestPoint(theGuy.getPositionComponent()->getPosition());
    bossAiSystem2->setDestPoint(theGuy.getPositionComponent()->getPosition());
    missileSystem->setDestPoint(theGuy.getPositionComponent()->getPosition());
    petRouteSystem->setCenterPoint(theGuy.getPositionComponent()->getPosition());
    icePickSystem->setDestPoint(theGuy.getPositionComponent()->getPosition());
    controlSystem->setMousePos(mousePos);
    simpleAiSystem->update(0);
    shootingAiSystem->update(0);
    bossAiSystem->update(elapsed_ms);
    bossAiSystem2->update(elapsed_ms);
    missileSystem->update(elapsed_ms);
    icePickSystem->update(elapsed_ms);
    abilitySystem->setMousePos(mousePos);
    abilitySystem->update(0);
    moveSystem->update(0);
    collisionSystem->update(0);
    spawnSystem->update(elapsed_ms);
    scoreSystem->update(0);
    particleEffectSystem->update(0);
    petRouteSystem->update(0);

    updateEnemyCounter();
    // Decrement invincibility
    theGuy.collideAgainDecrement();
    updateProjectilesAndEnemyProjectiles(screen);
    return true;
}

bool World::inGameConditionUpdate(float elapsed_ms, vec2 screen) {
    updateHealthAndAbilityTexture();
    // delete the previous frame death entity first
    deleteSystem->update(0);

    controlSystem->setPos(theGuy.getPositionComponent()->getPosition());
    simpleAiSystem->setDestPoint(theGuy.getPositionComponent()->getPosition());
    shootingAiSystem->setDestPoint(theGuy.getPositionComponent()->getPosition());
    bossAiSystem->setDestPoint(theGuy.getPositionComponent()->getPosition());
    bossAiSystem2->setDestPoint(theGuy.getPositionComponent()->getPosition());
    missileSystem->setDestPoint(theGuy.getPositionComponent()->getPosition());
    icePickSystem->setDestPoint(theGuy.getPositionComponent()->getPosition());
    controlSystem->setMousePos(mousePos);
    simpleAiSystem->update(0);
    shootingAiSystem->update(0);
    bossAiSystem->update(elapsed_ms);
    bossAiSystem2->update(elapsed_ms);
    missileSystem->update(elapsed_ms);
    icePickSystem->update(elapsed_ms);
    abilitySystem->setMousePos(mousePos);
    abilitySystem->update(0);
    moveSystem->update(0);
    collisionSystem->update(0);
    //spawnSystem->update(elapsed_ms);
    scoreSystem->update(0);

    updateEnemyCounter();
    // Decrement invincibility
    theGuy.collideAgainDecrement();
    updateProjectilesAndEnemyProjectiles(screen);
    return true;
}

// Render our game world
// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/
void World::draw() {
    // Clearing error buffer
    gl_flush_errors();

    // Getting size of window
    int w, h;
    glfwGetFramebufferSize(m_window, &w, &h);

    /////////////////////////////////////
    // First render to the custom framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Clearing backbuffer
    glViewport(0, 0, w, h);
    glDepthRange(-1, 10);
    const float clear_color[3] = {0.3f, 0.3f, 0.8f};
    glClearColor(clear_color[0], clear_color[1], clear_color[2], 1.0);
    glClearDepth(1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawSystem->update(0);

    // Presenting
    glfwSwapBuffers(m_window);
}

// Should the game be over ?
bool World::is_over() const {
    return glfwWindowShouldClose(m_window);
}

// On key callback
void World::on_key(GLFWwindow *, int key, int, int action, int mod) {
    controlSystem->setKeyEffect(key, action);
}

void World::on_mouse_move(GLFWwindow *, double xpos, double ypos) {
    theGuy.getPositionComponent()->setMouseX((float) xpos);
    theGuy.getPositionComponent()->setMouseY((float) ypos);
    mousePos = {(float) xpos, (float) ypos};
    float deltaX = xpos - theGuy.getPositionComponent()->getPosX();
    float deltaY = ypos - theGuy.getPositionComponent()->getPosY();
    theGuy.getPositionComponent()->setRotation(atan2(deltaY, deltaX));

    float pauseOffset = 10.f;
    isInPauseAera = xpos > pausePos.x - pauseOffset && xpos < pausePos.x + pauseOffset &&
                    ypos > pausePos.y - pauseOffset && ypos < pausePos.y + pauseOffset;
}

void World::on_mouse_button(GLFWwindow *, int button, int action, int mods) {
    controlSystem->setMouseButtonEffect(button, action);

    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
        if (isInPauseAera) {
            isPause = true;
        }
    }
}

void World::createRocks(int numRock, LevelName level) {
    float w_width2 = 40;
    float w_gate_height = 82;
    float w_gate_width = 35;
    float w_castle_height = 110;
    float wall_width = 7;
    if (level >= LevelName::LEVEL_ONE && level <= LevelName::LEVEL_FIVE) {
        // left
        Castle *left = new Castle();
        left->init();
        left->getPositionComponent()->setPosition({static_cast<float>(333), 334});
        left->getPositionComponent()->setWidth(wall_width);
        left->getPositionComponent()->setHeight(176);
        castles.push_back(left);
        collisionSystem->addEntity((Collides *) left);
        // top
        Castle *top = new Castle();
        top->init();
        top->getPositionComponent()->setPosition({static_cast<float>(610), 243});
        top->getPositionComponent()->setWidth(540);
        top->getPositionComponent()->setHeight(wall_width);
        castles.push_back(top);
        collisionSystem->addEntity((Collides *) top);
        //right
        Castle *right = new Castle();
        right->init();
        right->getPositionComponent()->setPosition({static_cast<float>(882), 334});
        right->getPositionComponent()->setWidth(wall_width);
        right->getPositionComponent()->setHeight(176);
        castles.push_back(right);
        collisionSystem->addEntity((Collides *) right);
        // middle vertical left
        Castle *vetleft = new Castle();
        vetleft->init();
        vetleft->getPositionComponent()->setPosition({static_cast<float>(495), 430});
        vetleft->getPositionComponent()->setWidth(wall_width);
        vetleft->getPositionComponent()->setHeight(170);
        castles.push_back(vetleft);
        collisionSystem->addEntity((Collides *) vetleft);
        // middle vertical right
        Castle *vetright = new Castle();
        vetright->init();
        vetright->getPositionComponent()->setPosition({static_cast<float>(710), 430});
        vetright->getPositionComponent()->setWidth(wall_width);
        vetright->getPositionComponent()->setHeight(170);
        collisionSystem->addEntity((Collides *) vetright);
        // middle vertical right
        castles.push_back(vetright);
        // middle bottom left
        Castle *botleft = new Castle();
        botleft->init();
        botleft->getPositionComponent()->setPosition({static_cast<float>(540), 475});
        botleft->getPositionComponent()->setWidth(62);
        botleft->getPositionComponent()->setHeight(w_castle_height);
        castles.push_back(botleft);
        collisionSystem->addEntity((Collides *) botleft);
        // middle bottom right
        Castle *botright = new Castle();
        botright->init();
        botright->getPositionComponent()->setPosition({static_cast<float>(665), 475});
        botright->getPositionComponent()->setWidth(65);
        botright->getPositionComponent()->setHeight(w_castle_height);
        castles.push_back(botright);
        collisionSystem->addEntity((Collides *) botright);
        // left gate left
        Castle *lleft = new Castle();
        lleft->init();
        lleft->getPositionComponent()->setPosition({static_cast<float>(370), 380});
        lleft->getPositionComponent()->setWidth(w_gate_width);
        lleft->getPositionComponent()->setHeight(w_gate_height);
        castles.push_back(lleft);
        collisionSystem->addEntity((Collides *) lleft);
        // left gate right
        Castle *lright = new Castle();
        lright->init();
        lright->getPositionComponent()->setPosition({static_cast<float>(450), 380});
        lright->getPositionComponent()->setWidth(w_gate_width);
        lright->getPositionComponent()->setHeight(w_gate_height);
        castles.push_back(lright);
        collisionSystem->addEntity((Collides *) lright);
        // right gate left
        Castle *rleft = new Castle();
        rleft->init();
        rleft->getPositionComponent()->setPosition({static_cast<float>(750), 380});
        rleft->getPositionComponent()->setWidth(w_gate_width);
        rleft->getPositionComponent()->setHeight(w_gate_height);
        castles.push_back(rleft);
        collisionSystem->addEntity((Collides *) rleft);
        // right gate right
        Castle *rright = new Castle();
        rright->init();
        rright->getPositionComponent()->setPosition({static_cast<float>(845), 380});
        rright->getPositionComponent()->setWidth(w_gate_width);
        rright->getPositionComponent()->setHeight(w_gate_height);
        castles.push_back(rright);
        collisionSystem->addEntity((Collides *) rright);

        for (int i = 1; i < 4; i++) {
            Rock *rock = new Rock();
            rock->init();
            rock->getPositionComponent()->setPosition({static_cast<float>(300 * i), 700});
            rocks.push_back(rock);
            drawSystem->addEntity((Drawable *) rock);
            collisionSystem->addEntity((Collides *) rock);
        }

        for (int i = 1; i < 4; i++) {
            Rock *rock = new Rock();
            rock->init();
            rock->getPositionComponent()->setPosition({static_cast<float>(300 * i), 100});
            rocks.push_back(rock);
            drawSystem->addEntity((Drawable *) rock);
            collisionSystem->addEntity((Collides *) rock);
        }

        for (int i = 1; i < 7; i++) {
            WaterCurrent *current = new WaterCurrent();
            current->init();
            current->getPositionComponent()->setPosition({70 + static_cast<float>(155 * i), 630});
            currents.push_back(current);
            drawSystem->addEntity((Drawable *) current);
            collisionSystem->addEntity((Collides *) current);
        }

        for (int i = 1; i < 7; i++) {
            WaterCurrent *current = new WaterCurrent();
            current->init();
            current->getPositionComponent()->setPosition({70 + static_cast<float>(155 * i), 170});
            currents.push_back(current);
            drawSystem->addEntity((Drawable *) current);
            collisionSystem->addEntity((Collides *) current);
        }


    } else {
        //left
        Castle *left = new Castle();
        left->init();
        left->getPositionComponent()->setPosition({static_cast<float>(245), 100});
        left->getPositionComponent()->setWidth(wall_width);
        left->getPositionComponent()->setHeight(250);
        castles.push_back(left);
        collisionSystem->addEntity((Collides *) left);
        //bottom left
        Castle *botleft = new Castle();
        botleft->init();
        botleft->getPositionComponent()->setPosition({static_cast<float>(270), 250});
        botleft->getPositionComponent()->setWidth(w_width2);
        botleft->getPositionComponent()->setHeight(50);
        castles.push_back(botleft);
        collisionSystem->addEntity((Collides *) botleft);
        //bottom right
        Castle *botright = new Castle();
        botright->init();
        botright->getPositionComponent()->setPosition({static_cast<float>(370), 250});
        botright->getPositionComponent()->setWidth(w_width2);
        botright->getPositionComponent()->setHeight(50);
        castles.push_back(botright);
        collisionSystem->addEntity((Collides *) botright);
        // vertical right
        Castle *vetright = new Castle();
        vetright->init();
        vetright->getPositionComponent()->setPosition({static_cast<float>(389), 180});
        vetright->getPositionComponent()->setWidth(wall_width + 1);
        vetright->getPositionComponent()->setHeight(90);
        castles.push_back(vetright);
        collisionSystem->addEntity((Collides *) vetright);
        // right side
        Castle *rightside = new Castle();
        rightside->init();
        rightside->getPositionComponent()->setPosition({static_cast<float>(458), 150});
        rightside->getPositionComponent()->setWidth(125);
        rightside->getPositionComponent()->setHeight(60);
        castles.push_back(rightside);
        collisionSystem->addEntity((Collides *) rightside);
        //right
        Castle *right = new Castle();
        right->init();
        right->getPositionComponent()->setPosition({static_cast<float>(516), 65});
        right->getPositionComponent()->setWidth(wall_width);
        right->getPositionComponent()->setHeight(140);
        castles.push_back(right);
        collisionSystem->addEntity((Collides *) right);


        for (int i = 1; i < 4; i++) {
            Rock *rock = new Rock();
            rock->init();
            rock->getPositionComponent()->setPosition({static_cast<float>(300 * i), 500});
            rocks.push_back(rock);
            drawSystem->addEntity((Drawable *) rock);
            collisionSystem->addEntity((Collides *) rock);
        }
        for (int i = 0; i < 5; i++) {
            Rock *rock = new Rock();
            rock->init();
            rock->getPositionComponent()->setPosition({150 + static_cast<float>(300 * i), 700});
            rocks.push_back(rock);
            drawSystem->addEntity((Drawable *) rock);
            collisionSystem->addEntity((Collides *) rock);
        }

        for (int i = 1; i < 4; i++) {
            Rock *rock = new Rock();
            rock->init();
            rock->getPositionComponent()->setPosition({450 + static_cast<float>(300 * i), 300});
            rocks.push_back(rock);
            drawSystem->addEntity((Drawable *) rock);
            collisionSystem->addEntity((Collides *) rock);
        }

        for (int i = 1; i < 3; i++) {
            Rock *rock = new Rock();
            rock->init();
            rock->getPositionComponent()->setPosition({300 + static_cast<float>(300 * i), 100});
            rocks.push_back(rock);
            drawSystem->addEntity((Drawable *) rock);
            collisionSystem->addEntity((Collides *) rock);
        }

        for (int i = 0; i < 2; i++) {
            WaterCurrent *current = new WaterCurrent();
            current->init();
            current->getPositionComponent()->setPosition({450 + static_cast<float>(300 * i), 500});
            currents.push_back(current);
            drawSystem->addEntity((Drawable *) current);
            collisionSystem->addEntity((Collides *) current);
        }

        for (int i = 0; i < 3; i++) {
            WaterCurrent *current = new WaterCurrent();
            current->init();
            current->getPositionComponent()->setPosition({300 + static_cast<float>(300 * i), 700});
            currents.push_back(current);
            drawSystem->addEntity((Drawable *) current);
            collisionSystem->addEntity((Collides *) current);
        }
    }
}

void World::createCastleTops(LevelName level) {
    if (level >= LevelName::LEVEL_ONE && level <= LevelName::LEVEL_FIVE) {
        CastleTop *castleTop = new CastleTop();
        castleTop->setWallNum(1);
        castleTop->init();
        castleTop->getPositionComponent()->setPosition({605.5, 469});
        castleTops.push_back(castleTop);
        drawSystem->addEntity((Drawable *) castleTop);
        CastleTop *castleTop2 = new CastleTop();
        castleTop2->setWallNum(2);
        castleTop2->init();
        castleTop2->getPositionComponent()->setPosition({801, 374});
        castleTops.push_back(castleTop2);
        drawSystem->addEntity((Drawable *) castleTop2);
        CastleTop *castleTop3 = new CastleTop();
        castleTop3->setWallNum(3);
        castleTop3->init();
        castleTop3->getPositionComponent()->setPosition({410, 374});
        castleTops.push_back(castleTop3);
        drawSystem->addEntity((Drawable *) castleTop3);
    } else {
        CastleTop *castleTop = new CastleTop();
        castleTop->setWallNum(4);
        castleTop->init();
        castleTop->getPositionComponent()->setPosition({320, 253.5});
        castleTops.push_back(castleTop);
        drawSystem->addEntity((Drawable *) castleTop);
    }
}

/**
 * Generates a valid (x, y) position for an enemy to spawn which will not collide with anything.
 * @return a 2d vector representing a spawn position
 */
vec2 World::getValidSpawnPosition() {
    vec2 candidate = {(float) (rand() % width), (float) (rand() % height)};
    float boundary_offset = 100;
    if (candidate.x < boundary_offset ||
        (width - candidate.x) < boundary_offset // check distance to borders
        || candidate.y < boundary_offset || (height - candidate.y) < boundary_offset
        // check that point is not too close to player
        || collisionSystem->isTooClose(candidate, theGuy.getPositionComponent()->getPosition(),
                                       MIN_DISTANCE_TO_PLAYER)) {
        //if any are true, invalid point, try again
        return getValidSpawnPosition();
    } else return candidate;
}

std::vector<Projectile *> *World::getProjectiles() {
    return &projectiles;
}

std::vector<EnemyProjectile *> *World::getEnemyProjectiles() {
    return &enemyProjectiles;
}

std::vector<BossProjectile *> *World::getBossProjectiles() {
    return &bossProjectiles;
}

TheGuy *World::getTheGuy() {
    return &theGuy;
}

void World::removeEntityFromSystems(Entity *toBeRemoved) {
    for (System *system : systems) {
        system->removeEntity(toBeRemoved);
    }
}

LevelName World::getNextLevel() {
    return nextLevel;
}

LevelName World::getCurrentLevel() {
    return curLevel;
}

unsigned long World::getWinningScore() {
    return winningScore;
}

char *World::getCurrentLevelTexture(LevelName ln) {
    switch (ln) {
        case LevelName::LEVEL_ONE :
            return (char *) "../data/textures/levels/1s.png";
        case LevelName::LEVEL_TWO :
            return (char *) "../data/textures/levels/2s.png";
        case LevelName::LEVEL_THREE :
            return (char *) "../data/textures/levels/3s.png";
        case LevelName::LEVEL_FOUR :
            return (char *) "../data/textures/levels/4s.png";
        case LevelName::LEVEL_FIVE :
            return (char *) "../data/textures/levels/5s.png";
        case LevelName::LEVEL_SIX :
            return (char *) "../data/textures/levels/6s.png";
        case LevelName::LEVEL_SEVEN :
            return (char *) "../data/textures/levels/7s.png";
        case LevelName::LEVEL_EIGHT :
            return (char *) "../data/textures/levels/8s.png";
        case LevelName::LEVEL_NINE :
            return (char *) "../data/textures/levels/9s.png";
        case LevelName::LEVEL_TEN :
            return (char *) "../data/textures/levels/10s.png";
        case LevelName::SURVIVAL_MODE :
            return (char *) "../data/textures/levels/infinity.png";
        default:
            return NULL;
    }
}

vec2 World::setCurrentLevelScale(LevelName ln) {
    switch (ln) {
        case LevelName::SURVIVAL_MODE :
            return {0.2, 0.2};
        default:
            return {0.5, 0.5};
    }
}

vec2 World::setCurrentLevelPos(LevelName ln) {
    switch (ln) {
        case LevelName::SURVIVAL_MODE :
            return {40, 30};
        default:
            return {30, 30};
    }
}

char *World::getEnemyTexture(EnemyType et) {
    switch (et) {
        case EnemyType::BASIC :
            return (char *) "../data/textures/characters/enemies/pig/pig_idle_00.png";
        case EnemyType::SPEED :
            return (char *) "../data/textures/characters/enemies/Golem/Golem_idle_00.png";
        case EnemyType::SHOOTING :
            return (char *) "../data/textures/characters/enemies/devil/devil_idle_00.png";
        case EnemyType::BOSS :
            return (char *) "../data/textures/characters/yasuo/Idle/Character_01_Idle1.png";
        case EnemyType::BOSS2 :
            return (char *) "../data/textures/characters/Boss2/Idle/Idle_01.png";
        default:
            return NULL;
    }
}

void World::getEnemyTexturePoses(int basic, int speed, int shooting, int bossLife, int boss2Life) {
    basicEnemyTexturePos = {0, 0};
    speedEnemyTexturePos = {0, 0};
    shootEnemyTexturePos = {0, 0};
    bossLifeTexturePos = {0, 0};
    boss2LifeTexturePos = {0, 0};
    std::vector<vec2> tempPoses;
    tempPoses.push_back({1100, 100});
    tempPoses.push_back({1100, 130});
    tempPoses.push_back({1100, 160});
    tempPoses.push_back({1100, 190});
    tempPoses.push_back({1100, 220});
    tempPoses.push_back({1100, 250});
    tempPoses.push_back({1100, 280});
    tempPoses.push_back({1100, 310});
    std::vector<vec2 *> enemyPoses;
    if (basic > 0) enemyPoses.push_back(&basicEnemyTexturePos);
    if (speed > 0) enemyPoses.push_back(&speedEnemyTexturePos);
    if (shooting > 0) enemyPoses.push_back(&shootEnemyTexturePos);
    if (bossLife > 0) enemyPoses.push_back(&bossLifeTexturePos);
    if (boss2Life > 0) enemyPoses.push_back(&boss2LifeTexturePos);

    for (int i = 0; i < enemyPoses.size(); i++) {
        *enemyPoses[i] = tempPoses[i];
    }
}

char *World::getEnemyCounter(int numEnemy) {
    switch (numEnemy) {
        case 1 :
            return (char *) "../data/textures/levels/1s.png";
        case 2 :
            return (char *) "../data/textures/levels/2s.png";
        case 3 :
            return (char *) "../data/textures/levels/3s.png";
        case 4 :
            return (char *) "../data/textures/levels/4s.png";
        case 5 :
            return (char *) "../data/textures/levels/5s.png";
        case 6 :
            return (char *) "../data/textures/levels/6s.png";
        case 7 :
            return (char *) "../data/textures/levels/7s.png";
        case 8 :
            return (char *) "../data/textures/levels/8s.png";
        case 9 :
            return (char *) "../data/textures/levels/9s.png";
        case 10 :
            return (char *) "../data/textures/levels/10s.png";
        default:
            return (char *) "../data/textures/levels/0s.png";
    }
}

void World::createEnemyCounterTexture() {
    if (curLevel != LevelName::SURVIVAL_MODE) {
        if (basicEnemyShouldBeKilled > 0) {
            basicEnemyTexture.setLevelTexture(getEnemyTexture(EnemyType::BASIC));
            basicEnemyTexture.init();
            basicEnemyTexture.getPositionComponent()->setPosition(basicEnemyTexturePos);
            basicEnemyTexture.getDrawComponent()->setScale({2, 2});

            drawSystem->addEntity((Drawable *) &basicEnemyTexture);

            basicEnemyX.setLevelTexture((char *) "../data/textures/characters/X.png");
            basicEnemyX.init();
            basicEnemyX.getPositionComponent()->setPosition({1140, basicEnemyTexturePos.y + 5});
            basicEnemyX.getDrawComponent()->setScale({0.4, 0.4});

            drawSystem->addEntity((Drawable *) &basicEnemyX);

            basicEnemyCounter.setLevelTexture(getEnemyCounter(basicEnemyShouldBeKilled));
            basicEnemyCounter.init();
            basicEnemyCounter.getPositionComponent()->setPosition({1160, basicEnemyTexturePos.y + 5});
            basicEnemyCounter.getDrawComponent()->setScale({0.4, 0.4});

            drawSystem->addEntity((Drawable *) &basicEnemyCounter);
        }

        if (speedEnemyShouldBeKilled > 0) {
            speedEnemyTexture.setLevelTexture(getEnemyTexture(EnemyType::SPEED));
            speedEnemyTexture.init();
            speedEnemyTexture.getPositionComponent()->setPosition(speedEnemyTexturePos);
            speedEnemyTexture.getDrawComponent()->setScale({2, 2});

            drawSystem->addEntity((Drawable *) &speedEnemyTexture);

            speedEnemyX.setLevelTexture((char *) "../data/textures/characters/X.png");
            speedEnemyX.init();
            speedEnemyX.getPositionComponent()->setPosition({1140, speedEnemyTexturePos.y + 5});
            speedEnemyX.getDrawComponent()->setScale({0.4, 0.4});

            drawSystem->addEntity((Drawable *) &speedEnemyX);

            speedEnemyCounter.setLevelTexture(getEnemyCounter(speedEnemyShouldBeKilled));
            speedEnemyCounter.init();
            speedEnemyCounter.getPositionComponent()->setPosition({1160, speedEnemyTexturePos.y + 5});
            speedEnemyCounter.getDrawComponent()->setScale({0.4, 0.4});

            drawSystem->addEntity((Drawable *) &speedEnemyCounter);
        }

        if (shootEnemyShouldBeKilled > 0) {
            shootEnemyTexture.setLevelTexture(getEnemyTexture(EnemyType::SHOOTING));
            shootEnemyTexture.init();
            shootEnemyTexture.getPositionComponent()->setPosition(shootEnemyTexturePos);
            shootEnemyTexture.getDrawComponent()->setScale({2, 2});

            drawSystem->addEntity((Drawable *) &shootEnemyTexture);

            shootEnemyX.setLevelTexture((char *) "../data/textures/characters/X.png");
            shootEnemyX.init();
            shootEnemyX.getPositionComponent()->setPosition({1140, shootEnemyTexturePos.y + 5});
            shootEnemyX.getDrawComponent()->setScale({0.4, 0.4});

            drawSystem->addEntity((Drawable *) &shootEnemyX);

            shootEnemyCounter.setLevelTexture(getEnemyCounter(shootEnemyShouldBeKilled));
            shootEnemyCounter.init();
            shootEnemyCounter.getPositionComponent()->setPosition({1160, shootEnemyTexturePos.y + 5});
            shootEnemyCounter.getDrawComponent()->setScale({0.4, 0.4});

            drawSystem->addEntity((Drawable *) &shootEnemyCounter);
        }

        if (bossLifeShouldBeKilled > 0) {
            bossLifeTexture.setLevelTexture(getEnemyTexture(EnemyType::BOSS));
            bossLifeTexture.init();
            bossLifeTexture.getPositionComponent()->setPosition(bossLifeTexturePos);
            bossLifeTexture.getDrawComponent()->setScale({1.5, 1.5});

            drawSystem->addEntity((Drawable *) &bossLifeTexture);

            bossLifeHeart.setLevelTexture((char *) "../data/textures/others/Hearts/PNG/basic/heart.png");
            bossLifeHeart.init();
            bossLifeHeart.getPositionComponent()->setPosition({1120, bossLifeTexturePos.y + 5});
            bossLifeHeart.getDrawComponent()->setScale({2, 2});

            drawSystem->addEntity((Drawable *) &bossLifeHeart);

            bossLifeX.setLevelTexture((char *) "../data/textures/characters/X.png");
            bossLifeX.init();
            bossLifeX.getPositionComponent()->setPosition({1140, bossLifeTexturePos.y + 5});
            bossLifeX.getDrawComponent()->setScale({0.4, 0.4});

            drawSystem->addEntity((Drawable *) &bossLifeX);


            bossLifeCounter.setLevelTexture(getEnemyCounter(bossLifeShouldBeKilled));
            bossLifeCounter.init();
            bossLifeCounter.getPositionComponent()->setPosition({1160, bossLifeTexturePos.y + 5});
            bossLifeCounter.getDrawComponent()->setScale({0.4, 0.4});

            drawSystem->addEntity((Drawable *) &bossLifeCounter);
        }

        if (boss2LifeShouldBeKilled > 0) {
            boss2LifeTexture.setLevelTexture(getEnemyTexture(EnemyType::BOSS2));
            boss2LifeTexture.init();
            boss2LifeTexture.getPositionComponent()->setPosition(boss2LifeTexturePos);
            boss2LifeTexture.getDrawComponent()->setScale({1.5, 1.5});

            drawSystem->addEntity((Drawable *) &boss2LifeTexture);

            boss2LifeHeart.setLevelTexture((char *) "../data/textures/others/Hearts/PNG/basic/heart.png");
            boss2LifeHeart.init();
            boss2LifeHeart.getPositionComponent()->setPosition({1120, boss2LifeTexturePos.y + 5});
            boss2LifeHeart.getDrawComponent()->setScale({2, 2});

            drawSystem->addEntity((Drawable *) &boss2LifeHeart);

            boss2LifeX.setLevelTexture((char *) "../data/textures/characters/X.png");
            boss2LifeX.init();
            boss2LifeX.getPositionComponent()->setPosition({1140, boss2LifeTexturePos.y + 5});
            boss2LifeX.getDrawComponent()->setScale({0.4, 0.4});

            drawSystem->addEntity((Drawable *) &boss2LifeX);


            boss2LifeCounter.setLevelTexture(getEnemyCounter(boss2LifeShouldBeKilled));
            boss2LifeCounter.init();
            boss2LifeCounter.getPositionComponent()->setPosition({1160, boss2LifeTexturePos.y + 5});
            boss2LifeCounter.getDrawComponent()->setScale({0.4, 0.4});

            drawSystem->addEntity((Drawable *) &boss2LifeCounter);
        }
    }
}

void World::updateHealthAndAbilityTexture() {
    vec2 theGuyCurrentPos = theGuy.getPositionComponent()->getPosition();
    int currHealth = theGuy.getHealthComponent()->getHealth();
    if (currHealth < healthBars.size()) {
        HealthBar *lostHealth = healthBars.back();
        healthBars.pop_back();
        drawSystem->removeEntity(lostHealth);
        free(lostHealth);
    }
    if (currHealth > healthBars.size()) {
        HealthBar *healthBar = new HealthBar();
        healthBar->init();
        healthBars.push_back(healthBar);
        drawSystem->addEntity((Drawable *) healthBar);
    }
    for (int i = 0; i < healthBars.size(); i++) {
        healthBars[i]->getPositionComponent()->setPosition(
                {theGuyCurrentPos.x - 15 * i, theGuyCurrentPos.y - 15});
    }
    int currCharges = theGuy.getAbilityComponent()->getNumCharges();
    if (currCharges < charges.size()) {
        Entity *lostCharge = charges.back();
        charges.pop_back();
        drawSystem->removeEntity(lostCharge);
    } else if (currCharges > charges.size() || theGuy.getAbilityComponent()->getAbilityType() != prevType) {
        for (Entity *c: charges) {
            drawSystem->removeEntity(c);
        }
        charges.clear();
        AbilityType type = theGuy.getAbilityComponent()->getAbilityType();
        for (int i = 0; i < currCharges; i++) {
            switch (type) {
                case AbilityType::BLINK_SLASH : {
                    Slash *slash = new Slash();
                    slash->init();
                    slash->getPositionComponent()->setPosition({1100.f + (i * 35), 30.f});
                    charges.push_back(slash);
                    drawSystem->addEntity((Drawable *) slash);
                    break;
                }
                case AbilityType::DROP_BOMB : {
                    Bomb *bomb = new Bomb();
                    bomb->init();
                    bomb->getPositionComponent()->setPosition({1100.f + (i * 35), 30.f});
                    charges.push_back(bomb);
                    drawSystem->addEntity((Drawable *) bomb);
                    break;
                }
                case AbilityType::METEOROID : {
                    MeteoroidIcon *meteoroid = new MeteoroidIcon();
                    meteoroid->init();
                    meteoroid->getPositionComponent()->setPosition({1150.f + (i * 35), 30.f});
                    charges.push_back(meteoroid);
                    drawSystem->addEntity((Drawable *) meteoroid);
                    break;
                }
                case AbilityType::SHOOT : {
                    Gun *gun = new Gun();
                    gun->init();
                    gun->getPositionComponent()->setPosition({1100.f, 30.f});
                    charges.push_back(gun);
                    drawSystem->addEntity((Drawable *) gun);
                    break;
                }
                case AbilityType::BOOMERANG: {
                    auto *icon = new BoomerangIcon();
                    icon->init();
                    icon->getPositionComponent()->setPosition({1100.f + (i * 35), 30.f});
                    charges.push_back(icon);
                    drawSystem->addEntity((Drawable *) icon);
                    break;
                }
                default: {
                }
            }
        }
        prevType = type;
    }
}

void World::updateEnemyCounter() {
    for (Collides *toBeKilled: collisionSystem->getToBeKilledForChecking()) {
        switch (toBeKilled->type) {
            case EntityType::ENEMY:
                switch (dynamic_cast<Enemy *>(toBeKilled)->getEnemyType()) {
                    case EnemyType::BASIC : {
                        basicEnemyShouldBeKilled--;
                        basicEnemyCounter.setLevelTexture(getEnemyCounter(basicEnemyShouldBeKilled));
                        break;
                    }
                    case EnemyType::SPEED : {
                        speedEnemyShouldBeKilled--;
                        speedEnemyCounter.setLevelTexture(getEnemyCounter(speedEnemyShouldBeKilled));
                        break;
                    }
                    case EnemyType::SHOOTING : {
                        shootEnemyShouldBeKilled--;
                        shootEnemyCounter.setLevelTexture(getEnemyCounter(shootEnemyShouldBeKilled));
                        break;
                    }
                    default: {
                    }
                }
            default: {
            }
        }
        if (bossAiSystem->getBossTracker() != nullptr) {
            if (bossAiSystem->getBossTracker()->type == EntityType::ENEMY) {
                if (bossAiSystem->getBossTracker()->getHealthComponent()->getHealth() <= bossLifeShouldBeKilled) {
                    bossLifeShouldBeKilled = bossAiSystem->getBossTracker()->getHealthComponent()->getHealth();
                    bossLifeCounter.setLevelTexture(getEnemyCounter(bossLifeShouldBeKilled));
                } else {
                    bossLifeShouldBeKilled = 0;
                }
            }
        }

        if (bossAiSystem2->getBossTracker() != nullptr) {
            if (bossAiSystem2->getBossTracker()->type == EntityType::ENEMY) {
                if (bossAiSystem2->getBossTracker()->getHealthComponent()->getHealth() <= boss2LifeShouldBeKilled) {
                    boss2LifeShouldBeKilled = bossAiSystem2->getBossTracker()->getHealthComponent()->getHealth();
                    boss2LifeCounter.setLevelTexture(getEnemyCounter(boss2LifeShouldBeKilled));
                } else {
                    boss2LifeShouldBeKilled = 0;
                }
            }
        }
    }
}

bool World::checkIfWin() {
    return basicEnemyShouldBeKilled <= 0 && speedEnemyShouldBeKilled <= 0 &&
           shootEnemyShouldBeKilled <= 0 && bossLifeShouldBeKilled <= 0 &&
           boss2LifeShouldBeKilled <= 0;
}

void World::updateProjectilesAndEnemyProjectiles(vec2 screen) {
    for (auto *projectile : projectiles) {
        if (projectile->getPositionComponent()->getPosition().x > screen.x ||
            projectile->getPositionComponent()->getPosition().x < 0.f ||
            projectile->getPositionComponent()->getPosition().y > screen.y ||
            projectile->getPositionComponent()->getPosition().y < 0.f) {
            removeEntityFromSystems(projectile);
        }
    }
    for (auto *projectile : enemyProjectiles) {
        if (projectile->getPositionComponent()->getPosition().x > screen.x ||
            projectile->getPositionComponent()->getPosition().x < 0.f ||
            projectile->getPositionComponent()->getPosition().y > screen.y ||
            projectile->getPositionComponent()->getPosition().y < 0.f) {
            removeEntityFromSystems(projectile);
        }
    }
    for (auto *projectile : bossProjectiles) {
        if (projectile->getPositionComponent()->getPosition().x > screen.x ||
            projectile->getPositionComponent()->getPosition().x < 0.f ||
            projectile->getPositionComponent()->getPosition().y > screen.y ||
            projectile->getPositionComponent()->getPosition().y < 0.f) {
            removeEntityFromSystems(projectile);
        }
    }
}

bool World::checkIfLose(int curHealth) {
    return curHealth <= 0;
}
