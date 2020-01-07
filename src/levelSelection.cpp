#include <ctime>
#include "levelSelection.hpp"
#include "global.hpp"

namespace {
    void glfw_err_cb(int error, const char *desc) {
        fprintf(stderr, "%d: %s", error, desc);
    }
}

LevelSelection::LevelSelection() {
    // Seeding rng with random device
    m_rng = std::default_random_engine(std::random_device()());
}

LevelSelection::~LevelSelection() {}

bool LevelSelection::init(vec2 screen) {
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
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    m_window = glfwCreateWindow((int) screen.x, (int) screen.y, "Attackalantus", nullptr, nullptr);
    glfwSetWindowPos(m_window, (mode->width/2)-(int)(screen.x/2), (mode->height/2)-(int)(screen.y/2));
    if (m_window == nullptr)
        return false;

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // vsync

    // Load OpenGL function pointers
    gl3w_init();

    glfwSetWindowUserPointer(m_window, this);
    auto key_redirect = [](GLFWwindow *wnd, int _0, int _1, int _2, int _3) {
        ((LevelSelection *) glfwGetWindowUserPointer(wnd))->on_key(wnd, _0, _1, _2, _3);
    };
    auto cursor_pos_redirect = [](GLFWwindow *wnd, double _0, double _1) {
        ((LevelSelection *) glfwGetWindowUserPointer(wnd))->on_mouse_move(wnd, _0, _1);
    };
    auto mouse_button_redirect = [](GLFWwindow *wnd, int _0, int _1, int _2) {
        ((LevelSelection *) glfwGetWindowUserPointer(wnd))->on_mouse_button(wnd, _0, _1, _2);
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

    level_selection_over = false;

    musicSystem = syss->getMusicSystem();
    musicSystem->openAudio();
    musicSystem->loadBackgroundMusic();
    musicSystem->playBackgroundMusic();

    drawSystem = syss->getDrawSystem();
    deleteSystem = syss->getDeleteSystem();

    background.init();
    drawSystem->addEntity(&background);

    float offset = 200.f;
    for (int i = 0; i < 10; i++) {
        DefaultTexture* l = new DefaultTexture();
        char* spritePath = new char[256];
        sprintf(spritePath, "%s%d%s", "../data/textures/levels/", i + 1, "l.png");
        l->setLevelTexture((char*) spritePath);
        l->init();
        l->getPositionComponent()->setPosition({i < 5 ? (float)(i + 1) * offset : offset + (float)(i - 5) * offset, i < 5 ? offset : 500.f});
        levels.push_back(l);
        drawSystem->addEntity((Drawable *) l);
    }
    DefaultTexture* l = new DefaultTexture();
    l->setLevelTexture((char*) "../data/textures/levels/15l.png");
    l->init();
    l->getPositionComponent()->setPosition({600.f, 700.f});
    l->getDrawComponent()->setScale({0.5, 0.5});
    levels.push_back(l);

    std::string levelArrowPath = "../data/textures/levels/arrow2.png";
    levelArrow.setMenuTexture(levelArrowPath);
    levelArrow.init();
    levelArrow.getDrawComponent()->setScale({2,2});
    levelArrow.getPositionComponent()->setPosition({-50,-50});

    drawSystem->addEntity((Drawable *) l);
    drawSystem->addEntity((Drawable *)&levelArrow);
    drawSystem->setProjection(w, h, m_screen_scale);

    return true;
}

void LevelSelection::destroy() {
    for (DefaultTexture* level: levels) {
        free(level);
        level = nullptr;
    }
    levels.clear();
    glDeleteFramebuffers(1, &m_frame_buffer);
    glfwDestroyWindow(m_window);
}

bool LevelSelection::update(float elapsed_ms) {
    return true;
}

void LevelSelection::draw() {
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

bool LevelSelection::is_over() const {
    return glfwWindowShouldClose(m_window);
}

void LevelSelection::on_key(GLFWwindow *, int key, int, int action, int mod) {
    if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_RIGHT_SHIFT:
                set_chosen_level(LevelName::SURVIVAL_MODE);
                level_selection_over = true;
                break;
        }
    }
}

/*
 * Hardcoded this since haven't figure out how the scale works with mouse position...
 */
void LevelSelection::on_mouse_move(GLFWwindow *, double xpos, double ypos) {
    float offset = 50.f;
    float constantPos = 200.f;
    float row2Pos = 500.f;
    // printf("%f, %f\n", xpos, ypos);
    if (xpos > constantPos - offset && xpos < constantPos + offset && ypos > constantPos - offset && ypos < constantPos + offset) {
        onHover = LevelName::LEVEL_ONE;
        levelArrow.getPositionComponent()->setPosition({constantPos-30,constantPos-100});
    }
    else if (xpos > constantPos * 2 - offset && xpos < constantPos * 2 + offset && ypos > constantPos - offset && ypos < constantPos + offset) {
        onHover = LevelName::LEVEL_TWO;
        levelArrow.getPositionComponent()->setPosition({constantPos * 2 - 30, constantPos - 100});
    }
    else if (xpos > constantPos * 3 - offset && xpos < constantPos * 3 + offset && ypos > constantPos - offset && ypos < constantPos + offset) {
        onHover = LevelName::LEVEL_THREE;
        levelArrow.getPositionComponent()->setPosition({constantPos * 3 - 30, constantPos - 100});
    }
    else if (xpos > constantPos * 4 - offset && xpos < constantPos * 4 + offset && ypos > constantPos - offset && ypos < constantPos + offset) {
        onHover = LevelName::LEVEL_FOUR;
        levelArrow.getPositionComponent()->setPosition({constantPos * 4 - 30, constantPos - 100});
    }
    else if (xpos > constantPos * 5 - offset && xpos < constantPos * 5 + offset && ypos > constantPos - offset && ypos < constantPos + offset) {
        onHover = LevelName::LEVEL_FIVE;
        levelArrow.getPositionComponent()->setPosition({constantPos * 5 - 30, constantPos - 100});
    }
    else if (xpos > constantPos * 1 - offset && xpos < constantPos * 1 + offset && ypos > row2Pos - offset && ypos < row2Pos + offset) {
        onHover = LevelName::LEVEL_SIX;
        levelArrow.getPositionComponent()->setPosition({constantPos - 30, row2Pos - 100});
    }
    else if (xpos > constantPos * 2 - offset && xpos < constantPos * 2 + offset && ypos > row2Pos - offset && ypos < row2Pos + offset) {
        onHover = LevelName::LEVEL_SEVEN;
        levelArrow.getPositionComponent()->setPosition({constantPos * 2 - 30, row2Pos - 100});
    }
    else if (xpos > constantPos * 3 - offset && xpos < constantPos * 3 + offset && ypos > row2Pos - offset && ypos < row2Pos + offset) {
        onHover = LevelName::LEVEL_EIGHT;
        levelArrow.getPositionComponent()->setPosition({constantPos * 3 - 30, row2Pos - 100});
    }
    else if (xpos > constantPos * 4 - offset && xpos < constantPos * 4 + offset && ypos > row2Pos - offset && ypos < row2Pos + offset) {
        onHover = LevelName::LEVEL_NINE;
        levelArrow.getPositionComponent()->setPosition({constantPos * 4 - 30, row2Pos - 100});
    }
    else if (xpos > constantPos * 5 - offset && xpos < constantPos * 5 + offset && ypos > row2Pos - offset && ypos < row2Pos + offset) {
        onHover = LevelName::LEVEL_TEN;
        levelArrow.getPositionComponent()->setPosition({constantPos * 5 - 30, row2Pos - 100});
    }
    else if (xpos > 600 - offset * 5 && xpos < 600 + offset * 5 && ypos > 700 - offset && ypos < 700 + offset) {
        onHover = LevelName::MAIN_MENU;
        levelArrow.getPositionComponent()->setPosition({600, 650});
    }
    else {
        onHover = LevelName::LEVEL_SELECTION;
        levelArrow.getPositionComponent()->setPosition({-50,-50});
    }
}

void LevelSelection::on_mouse_button(GLFWwindow *, int button, int action, int mod) {
    if (action ==  GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT && onHover != LevelName::LEVEL_SELECTION) {
        set_chosen_level(onHover);
        level_selection_over = true;
    }
}

bool LevelSelection::check_level_selection_over() {
    return level_selection_over;
}

void LevelSelection::reset_level_selection_over() {
    level_selection_over = false;
}

void LevelSelection::set_chosen_level(LevelName level) {
    chosenLevel = level;
}

LevelName LevelSelection::get_chosen_level() {
    return chosenLevel;
}
