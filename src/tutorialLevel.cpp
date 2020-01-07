// Header
#include "tutorialLevel.hpp"
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
#include <json.hpp>
#include <entities/rainDrop.hpp>
#include <entities/pork.hpp>
#include <entities/meteoroid.hpp>
#include <entities/firePet.hpp>
#include <entities/meteoroidIcon.hpp>

vec2 tvelocity;

namespace {
    void glfw_err_cb(int error, const char *desc) {
        fprintf(stderr, "%d: %s", error, desc);
    }
} // namespace

TutorialLevel::TutorialLevel() {
    // Seeding rng with random device
    m_rng = std::default_random_engine(std::random_device()());
}

TutorialLevel::~TutorialLevel() {
}

// World initialization
bool TutorialLevel::init(vec2 screen, Levels *levelsObj) {
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
        ((TutorialLevel *) glfwGetWindowUserPointer(wnd))->on_key(wnd, _0, _1, _2, _3);
    };
    auto cursor_pos_redirect = [](GLFWwindow *wnd, double _0, double _1) {
        ((TutorialLevel *) glfwGetWindowUserPointer(wnd))->on_mouse_move(wnd, _0, _1);
    };
    auto mouse_button_redirect = [](GLFWwindow *wnd, int _0, int _1, int _2) {
        ((TutorialLevel *) glfwGetWindowUserPointer(wnd))->on_mouse_button(wnd, _0, _1, _2);
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
    isInBasicArea = false;
    isInSpeedArea = false;
    isInShootingArea = false;
    isPause = false;
    isBasic = false;
    isSpeed = false;
    isShooting = false;

    srand(time(NULL));
    mousePos = {0.f, 0.f};

    // system init
    moveSystem = syss->getMoveSystem();
    simpleAiSystem = syss->getSimpleAISystem();
    shootingAiSystem = syss->getShootingAISystem();
    bossAiSystem = syss->getBossAISystem();
    missileSystem = syss->getMissileSystem();
    float velocity = 1.5f;
    simpleAiSystem->setVelocity(velocity);
    shootingAiSystem->setVelocity(velocity);
    bossAiSystem->setVelocity(velocity);
    missileSystem->setVelocity(velocity * 3);
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

    // entities init
    theGuy.setMaxHealth(levelsObj->getNumHealth());
    theGuy.init();
    environment.setTexturePath(levelsObj->getEnvironmentPath());
    environment.init();
    curLevelInGame.setLevelTexture((char *) "../data/textures/levels/0s.png");
    curLevelInGame.init();
    curLevelInGame.getPositionComponent()->setPosition(setCurrentLevelPos(curLevel));
    curLevelInGame.getDrawComponent()->setScale(setCurrentLevelScale(curLevel));

    std::string pausePath = "../data/textures/menuText/exit_highlight.png";
    pauseButton.setMenuTexture(pausePath);
    pauseButton.init();
    pauseButton.getPositionComponent()->setPosition({120, 30});
    pauseButton.getDrawComponent()->setScale({0.3, 0.3});
    pausePos = pauseButton.getPositionComponent()->getPosition();

    basicEnemyTexture.setLevelTexture(getEnemyTexture(EnemyType::BASIC));
    basicEnemyTexture.init();
    basicEnemyTexturePos = {200,30};
    basicEnemyTexture.getPositionComponent()->setPosition(basicEnemyTexturePos);
    basicEnemyTexture.getDrawComponent()->setScale({2, 2});

    speedEnemyTexture.setLevelTexture(getEnemyTexture(EnemyType::SPEED));
    speedEnemyTexture.init();
    speedEnemyTexturePos = {300,30};
    speedEnemyTexture.getPositionComponent()->setPosition(speedEnemyTexturePos);
    speedEnemyTexture.getDrawComponent()->setScale({2, 2});

    shootEnemyTexture.setLevelTexture(getEnemyTexture(EnemyType::SHOOTING));
    shootEnemyTexture.init();
    shootEnemyTexturePos = {400,30};
    shootEnemyTexture.getPositionComponent()->setPosition(shootEnemyTexturePos);
    shootEnemyTexture.getDrawComponent()->setScale({2, 2});

    drawSystem->addEntity((Drawable *) &environment);
    drawSystem->addEntity((Drawable *) &curLevelInGame);
    drawSystem->addEntity((Drawable *) &pauseButton);
    drawSystem->addEntity((Drawable *) &basicEnemyTexture);
    drawSystem->addEntity((Drawable *) &speedEnemyTexture);
    drawSystem->addEntity((Drawable *) &shootEnemyTexture);

    drawSystem->addEntity((Drawable *) &theGuy);

    int numHealth = theGuy.getHealthComponent()->getHealth();
    vec2 theGuyInitPos = theGuy.getPositionComponent()->getPosition();
    for (int i = 0; i < numHealth; i++) {
        HealthBar *healthBar = new HealthBar();
        healthBar->init();
        healthBar->getPositionComponent()->setPosition({theGuyInitPos.x - 15 * i, theGuyInitPos.y - 15});
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
    drawSystem->setProjection(w, h, m_screen_scale);

    // add system to systems
    systems.push_back(drawSystem);
    systems.push_back(controlSystem);
    systems.push_back(moveSystem);
    systems.push_back(collisionSystem);
    systems.push_back(simpleAiSystem);
    systems.push_back(shootingAiSystem);
    systems.push_back(bossAiSystem);
    systems.push_back(abilitySystem);
    systems.push_back(spawnSystem);
    systems.push_back(scoreSystem);
    systems.push_back(soundSystem);
    systems.push_back(missileSystem);

    return true;
}

// Releases all the associated resources
void TutorialLevel::destroy() {
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
    healthBars.clear();
    rocks.clear();
    castles.clear();
    enemies.clear();
    projectiles.clear();
    enemyProjectiles.clear();
    charges.clear();
    currents.clear();
    glfwDestroyWindow(m_window);
}

// Update our game world
bool TutorialLevel::update(float elapsed_ms) {
    int w, h;
    glfwGetFramebufferSize(m_window, &w, &h);
    vec2 screen = {(float) w / m_screen_scale, (float) h / m_screen_scale};

    /////////////////////////////////////////////////////////////////////////////////
    // self update code
    ////////////////////////////////////////////////////////////////////////////////
    moveSystem->setBoundary((int) screen.x, (int) screen.y);

    if (isPause) {
        nextLevel = LevelName::MAIN_MENU;
        glfwSetWindowShouldClose(m_window, 1);
    }
    if (isBasic) {
        spawnSystem->spawnEnemy(EnemyType::BASIC);
        isBasic = false;
    }
    if (isSpeed) {
        spawnSystem->spawnEnemy(EnemyType::SPEED);
        isSpeed = false;
    }
    if (isShooting) {
        spawnSystem->spawnEnemy(EnemyType::SHOOTING);
        isShooting = false;
    }
    return inGameUpdate(elapsed_ms, screen);
}

bool TutorialLevel::inGameUpdate(float elapsed_ms, vec2 screen) {
    if (theGuy.getHealthComponent()->getHealth() <= 1) {
        theGuy.getHealthComponent()->setHealth(10);
    }
    updateHealthAndAbilityTexture();
    // delete the previous frame death entity first
    deleteSystem->update(0);

    controlSystem->setPos(theGuy.getPositionComponent()->getPosition());
    simpleAiSystem->setDestPoint(theGuy.getPositionComponent()->getPosition());
    shootingAiSystem->setDestPoint(theGuy.getPositionComponent()->getPosition());
    bossAiSystem->setDestPoint(theGuy.getPositionComponent()->getPosition());
    missileSystem->setDestPoint(theGuy.getPositionComponent()->getPosition());
    petRouteSystem->setCenterPoint(theGuy.getPositionComponent()->getPosition());
    controlSystem->setMousePos(mousePos);
    simpleAiSystem->update(0);
    shootingAiSystem->update(0);
    bossAiSystem->update(elapsed_ms);
    missileSystem->update(elapsed_ms);
    abilitySystem->setMousePos(mousePos);
    abilitySystem->update(0);
    moveSystem->update(0);
    collisionSystem->update(0);
    spawnSystem->update(elapsed_ms);
    scoreSystem->update(0);
    particleEffectSystem->update(0);
    petRouteSystem->update(0);
    // Decrement invincibility
    theGuy.collideAgainDecrement();
    updateProjectilesAndEnemyProjectiles(screen);
    return true;
}

// Render our game world
// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/
void TutorialLevel::draw() {
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
bool TutorialLevel::is_over() const {
    return glfwWindowShouldClose(m_window);
}

// On key callback
void TutorialLevel::on_key(GLFWwindow *, int key, int, int action, int mod) {
    controlSystem->setKeyEffect(key, action);
}

void TutorialLevel::on_mouse_move(GLFWwindow *, double xpos, double ypos) {
    theGuy.getPositionComponent()->setMouseX((float) xpos);
    theGuy.getPositionComponent()->setMouseY((float) ypos);
    mousePos = {(float) xpos, (float) ypos};
    float deltaX = xpos - theGuy.getPositionComponent()->getPosX();
    float deltaY = ypos - theGuy.getPositionComponent()->getPosY();
    theGuy.getPositionComponent()->setRotation(atan2(deltaY, deltaX));

    float pauseOffset = 20.f;
    isInPauseAera = xpos > pausePos.x - pauseOffset && xpos < pausePos.x + pauseOffset &&
                    ypos > pausePos.y - pauseOffset && ypos < pausePos.y + pauseOffset;
    isInBasicArea = xpos > basicEnemyTexturePos.x - pauseOffset && xpos < basicEnemyTexturePos.x + pauseOffset &&
                    ypos > basicEnemyTexturePos.y - pauseOffset && ypos < basicEnemyTexturePos.y + pauseOffset;
    isInSpeedArea = xpos > speedEnemyTexturePos.x - pauseOffset && xpos < speedEnemyTexturePos.x + pauseOffset &&
                    ypos > speedEnemyTexturePos.y - pauseOffset && ypos < speedEnemyTexturePos.y + pauseOffset;
    isInShootingArea = xpos > shootEnemyTexturePos.x - pauseOffset && xpos < shootEnemyTexturePos.x + pauseOffset &&
                       ypos > shootEnemyTexturePos.y - pauseOffset && ypos < shootEnemyTexturePos.y + pauseOffset;
}

void TutorialLevel::on_mouse_button(GLFWwindow *, int button, int action, int mods) {
    controlSystem->setMouseButtonEffect(button, action);

    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
        if (isInPauseAera) {
            isPause = true;
        }
        if (isInBasicArea) {
            isBasic = true;
        }
        if (isInSpeedArea) {
            isSpeed = true;
        }
        if (isInShootingArea) {
            isShooting = true;
        }
    }
}

std::vector<Projectile *> *TutorialLevel::getProjectiles() {
    return &projectiles;
}

std::vector<EnemyProjectile *> *TutorialLevel::getEnemyProjectiles() {
    return &enemyProjectiles;
}

TheGuy *TutorialLevel::getTheGuy() {
    return &theGuy;
}

void TutorialLevel::removeEntityFromSystems(Entity *toBeRemoved) {
    for (System *system : systems) {
        system->removeEntity(toBeRemoved);
    }
}

vec2 TutorialLevel::setCurrentLevelScale(LevelName ln) {
    return {0.5, 0.5};
}

vec2 TutorialLevel::setCurrentLevelPos(LevelName ln) {
    return {30, 30};
}

char *TutorialLevel::getEnemyTexture(EnemyType et) {
    switch (et) {
        case EnemyType::BASIC :
            return (char *) "../data/textures/characters/enemies/pig/pig_idle_00.png";
        case EnemyType::SPEED :
            return (char *) "../data/textures/characters/enemies/Golem/Golem_idle_00.png";
        case EnemyType::SHOOTING :
            return (char *) "../data/textures/characters/enemies/devil/devil_idle_00.png";
        case EnemyType::BOSS :
            return (char *) "../data/textures/characters/yasuo/Idle/Character_01_Idle1.png";
        default:
            return NULL;
    }
}

void TutorialLevel::updateHealthAndAbilityTexture() {
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

void TutorialLevel::updateProjectilesAndEnemyProjectiles(vec2 screen) {
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
}

LevelName TutorialLevel::getNextLevel() {
    return nextLevel;
}
