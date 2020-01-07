#include <entities/defaultTexture.hpp>
#include <ctime>
#include "winLose.hpp"
#include "global.hpp"
#include "levelName.hpp"

namespace {
    void glfw_err_cb(int error, const char *desc) {
        fprintf(stderr, "%d: %s", error, desc);
    }
}

WinLose::WinLose() {
    // Seeding rng with random device
    m_rng = std::default_random_engine(std::random_device()());
}

WinLose::~WinLose() {}

bool WinLose::init(vec2 screen, Levels *levelObj) {
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

    glfwSetWindowUserPointer(m_window, this);
    auto key_redirect = [](GLFWwindow *wnd, int _0, int _1, int _2, int _3) {
        ((WinLose *) glfwGetWindowUserPointer(wnd))->on_key(wnd, _0, _1, _2, _3);
    };
    auto cursor_pos_redirect = [](GLFWwindow *wnd, double _0, double _1) {
        ((WinLose *) glfwGetWindowUserPointer(wnd))->on_mouse_move(wnd, _0, _1);
    };
    auto mouse_button_redirect = [](GLFWwindow *wnd, int _0, int _1, int _2) {
        ((WinLose *) glfwGetWindowUserPointer(wnd))->on_mouse_button(wnd, _0, _1, _2);
    };
    glfwSetKeyCallback(m_window, key_redirect);
    glfwSetCursorPosCallback(m_window, cursor_pos_redirect);
    glfwSetMouseButtonCallback(m_window, mouse_button_redirect);

    m_frame_buffer = 0;
    glGenFramebuffers(1, &m_frame_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer);

    int fb_width, fb_height;
    glfwGetFramebufferSize(m_window, &fb_width, &fb_height);
    m_screen_scale = static_cast<float>(fb_width) / screen.x;

    m_screen_tex.create_from_screen(m_window);

    int w, h;
    glfwGetFramebufferSize(m_window, &w, &h);
    currentFrame = 0;

    srand(time(NULL));

    curLevel = levelObj->getCurrentLevel();
    preLevel = levelObj->getPreviousLevel();

    musicSystem = syss->getMusicSystem();
    musicSystem->openAudio();
    musicSystem->loadBackgroundMusic();
    musicSystem->loadVictoryMusic();
    musicSystem->loadDefeatMusic();

    drawSystem = syss->getDrawSystem();
    deleteSystem = syss->getDeleteSystem();

    environment.setTexturePath(levelObj->getEnvironmentPath());
    environment.init();
    drawSystem->addEntity((Drawable *) &environment);

    float offset = 50.f;
    if (curLevel == LevelName::VICTORY_PAGE) {
        musicSystem->playVictoryMusic();
        for (int i = 0; i < 3; i++) {
            DefaultTexture *l = new DefaultTexture();
            std::string spritePath = "../data/textures/victoryAssets/" + std::to_string(i + 1) + "l.png";
            l->setLevelTexture(spritePath);
            l->init();
            l->getPositionComponent()->setPosition({width / 2, 600 + offset * i});
            l->getDrawComponent()->setScale({0.5, 0.5});
            levels.push_back(l);
            drawSystem->addEntity((Drawable *) l);
        }
    } else if (curLevel == LevelName::DEFEAT_PAGE) {
        musicSystem->playDefeatMusic();
        for (int i = 0; i < 2; i++) {
            DefaultTexture *l = new DefaultTexture();
            std::string spritePath = "../data/textures/victoryAssets/" + std::to_string(i + 2) + "l.png";
            l->setLevelTexture(spritePath);
            l->init();
            l->getPositionComponent()->setPosition({width / 2, 600 + offset * i});
            l->getDrawComponent()->setScale({0.5, 0.5});
            levels.push_back(l);
            drawSystem->addEntity((Drawable *) l);
        }
    }

    drawSystem->setProjection(w, h, m_screen_scale);
    pageOver = false;

    return true;
}

void WinLose::destroy() {
    glDeleteFramebuffers(1, &m_frame_buffer);
    glfwDestroyWindow(m_window);
}

bool WinLose::update(float elapsed_ms) {
    // TODO: re-add highlighting without creating a new page every time...
//    int w, h;
//    glfwGetFramebufferSize(m_window, &w, &h);
//    vec2 screen = {(float) w / m_screen_scale, (float) h / m_screen_scale};
//
//    if (curLevel == LevelName::VICTORY_PAGE) {
//        switch (onHover) {
//            case 0: {
//                for (int i = 0; i < 3; i++) {
//                    drawSystem->removeEntity(levels[i]);
//                    char *spritePath = new char[256];
//                    sprintf(spritePath, "%s%d%s", "../data/textures/victoryAssets/", i + 1, "l.png");
//                    levels[i]->setLevelTexture(spritePath);
//                    levels[i]->init();
//                    levels[i]->getDrawComponent()->setScale({0.5, 0.5});
//                    drawSystem->addEntity(levels[i]);
//                }
//                break;
//            }
//            case 1: {
//                drawSystem->removeEntity(levels[0]);
//                levels[0]->setLevelTexture((char *) "../data/textures/victoryAssets/1s.png");
//                levels[0]->init();
//                levels[0]->getDrawComponent()->setScale({0.5, 0.5});
//                drawSystem->addEntity(levels[0]);
//                break;
//            }
//            case 2: {
//                drawSystem->removeEntity(levels[1]);
//                //levels[1]->getDrawComponent()->PNGPath = "../data/textures/victoryAssets/2s.png";
//                levels[1]->setLevelTexture((char *) "../data/textures/victoryAssets/2s.png");
//                levels[1]->init();
//                levels[1]->getDrawComponent()->setScale({0.5, 0.5});
//                drawSystem->addEntity(levels[1]);
//                break;
//            }
//            case 3: {
//                drawSystem->removeEntity(levels[2]);
//                //levels[2]->getDrawComponent()->PNGPath = "../data/textures/victoryAssets/3s.png";
//                levels[2]->setLevelTexture((char *) "../data/textures/victoryAssets/3s.png");
//                levels[2]->init();
//                levels[2]->getDrawComponent()->setScale({0.5, 0.5});
//                drawSystem->addEntity(levels[2]);
//                break;
//            }
//        }
//    } else if (curLevel == LevelName::DEFEAT_PAGE) {
//        switch (onHover) {
//            case 0: {
//                for (int i = 0; i < 2; i++) {
//                    drawSystem->removeEntity(levels[i]);
//                    std::string spritePath = "../data/textures/victoryAssets/" + std::to_string(i + 2) + "l.png";
//                    //levels[i]->getDrawComponent()->PNGPath = spritePath;
//                    levels[i]->setLevelTexture(spritePath);
//                    levels[i]->init();
//                    levels[i]->getDrawComponent()->setScale({0.5, 0.5});
//                    drawSystem->addEntity(levels[i]);
//                }
//                break;
//            }
//            case 2: {
//                drawSystem->removeEntity(levels[0]);
//                //levels[0]->getDrawComponent()->PNGPath = "../data/textures/victoryAssets/2s.png";
//                levels[0]->setLevelTexture((char *) "../data/textures/victoryAssets/2s.png");
//                levels[0]->init();
//                levels[0]->getDrawComponent()->setScale({0.5, 0.5});
//                drawSystem->addEntity(levels[0]);
//                break;
//            }
//            case 3: {
//                drawSystem->removeEntity(levels[1]);
//                //levels[1]->getDrawComponent()->PNGPath = "../data/textures/victoryAssets/3s.png";
//                levels[1]->setLevelTexture((char *) "../data/textures/victoryAssets/3s.png");
//                levels[1]->init();
//                levels[1]->getDrawComponent()->setScale({0.5, 0.5});
//                drawSystem->addEntity(levels[1]);
//                break;
//            }
//        }
//    }
//
//
//    if (currentFrame++ >= DELETEFRAME) {
//        currentFrame = 0;
//        deleteSystem->update(0);
//    }

    return true;
}

void WinLose::draw() {
    gl_flush_errors();

    int w, h;
    glfwGetFramebufferSize(m_window, &w, &h);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, w, h);
    glDepthRange(-1, 10);
    const float clear_color[3] = {0.3f, 0.3f, 0.8f};
    glClearColor(clear_color[0], clear_color[1], clear_color[2], 1.0);
    glClearDepth(1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float left = 0.f;                          // *-0.5;
    float top = 0.f;                          // (float)h * -0.5;
    float right = (float) w / m_screen_scale;  // *0.5;
    float bottom = (float) h / m_screen_scale; // *0.5;

    float sx = 2.f / (right - left);
    float sy = 2.f / (top - bottom);
    float tx = -(right + left) / (right - left);
    float ty = -(top + bottom) / (top - bottom);
    mat3 projection_2D{{sx,  0.f, 0.f},
                       {0.f, sy,  0.f},
                       {tx,  ty,  1.f}};
    drawSystem->update(0);

    glfwSwapBuffers(m_window);
}

bool WinLose::is_over() const {
    return glfwWindowShouldClose(m_window);
}

void WinLose::on_key(GLFWwindow *, int key, int, int action, int mod) {
    if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_B:
                nextLevel = LevelName::MAIN_MENU;
                pageOver = true;
                break;
        }
    }
}

void WinLose::on_mouse_move(GLFWwindow *, double xpos, double ypos) {
    float constantPos = width / 2;
    float offset = 20.f;
    if (curLevel == LevelName::VICTORY_PAGE) {
        if (xpos > constantPos - offset * 7 && xpos < constantPos + offset * 7 && ypos > 600 - offset &&
            ypos < 600 + offset) {
            onHover = 1;
        } else if (xpos > constantPos - offset * 3 && xpos < constantPos + offset * 3 && ypos > 650 - offset &&
                   ypos < 650 + offset) {
            onHover = 2;
        } else if (xpos > constantPos - offset * 4 && xpos < constantPos + offset * 4 && ypos > 700 - offset &&
                   ypos < 700 + offset) {
            onHover = 3;
        } else {
            onHover = 0;
        }
    } else if (curLevel == LevelName::DEFEAT_PAGE) {
        if (xpos > constantPos - offset * 3 && xpos < constantPos + offset * 3 && ypos > 600 - offset &&
            ypos < 600 + offset) {
            onHover = 2;
        } else if (xpos > constantPos - offset * 4 && xpos < constantPos + offset * 4 && ypos > 650 - offset &&
                   ypos < 650 + offset) {
            onHover = 3;
        } else {
            onHover = 0;
        }
    }
}

void WinLose::on_mouse_button(GLFWwindow *, int button, int action, int mod) {
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT && onHover != 0) {
        if (onHover == 1) {
            // TODO FIX THIS FOR THE LOVE OF GOD
            nextLevel = (LevelName) ((int) preLevel + 1);
            pageOver = true;
        } else if (onHover == 2) {
            nextLevel = LevelName::MAIN_MENU;
            pageOver = true;
        } else if (onHover == 3) {
            nextLevel = preLevel;
            pageOver = true;
        } else {
            // do nothing
        }
    }
}

bool WinLose::check_win_lose_over() {
    return pageOver;
}

void WinLose::reset_win_lose_over() {
    pageOver = false;
}

LevelName WinLose::get_next_level() {
    return nextLevel;
}