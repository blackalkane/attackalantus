#include <ctime>
#include "mainMenu.hpp"
#include "global.hpp"

namespace {
    void glfw_err_cb(int error, const char *desc) {
        fprintf(stderr, "%d: %s", error, desc);
    }
}

MainMenu::MainMenu() {
    // Seeding rng with random device
    m_rng = std::default_random_engine(std::random_device()());
}

MainMenu::~MainMenu() {}

bool MainMenu::init(vec2 screen) {
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
        ((MainMenu *) glfwGetWindowUserPointer(wnd))->on_key(wnd, _0, _1, _2, _3);
    };
    auto cursor_pos_redirect = [](GLFWwindow *wnd, double _0, double _1) {
        ((MainMenu *) glfwGetWindowUserPointer(wnd))->on_mouse_move(wnd, _0, _1);
    };
    auto mouse_button_redirect = [](GLFWwindow *wnd, int _0, int _1, int _2) {
        ((MainMenu *) glfwGetWindowUserPointer(wnd))->on_mouse_button(wnd, _0, _1, _2);
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

    menu_over = false;
    is_new_game = false;
    is_survival_mode = false;
    is_exit = false;
    is_tutorial = false;

    musicSystem = syss->getMusicSystem();
    musicSystem->openAudio();
    musicSystem->loadBackgroundMusic();
    musicSystem->playBackgroundMusic();

    drawSystem = syss->getDrawSystem();
    deleteSystem = syss->getDeleteSystem();

    m_menu.init();

    std::string newGamePath = "../data/textures/menuText/newgame.png";
    newGameButton.setMenuTexture(newGamePath);
    newGameButton.init();
    newGameButton.getPositionComponent()->setPosition({600, 300});
    newGamePos = newGameButton.getPositionComponent()->getPosition();

    std::string survivalPath = "../data/textures/menuText/survival.png";
    survivalModeButton.setMenuTexture(survivalPath);
    survivalModeButton.init();
    survivalModeButton.getPositionComponent()->setPosition({600, 400});
    survivalModePos = survivalModeButton.getPositionComponent()->getPosition();

    std::string tutorialPath = "../data/textures/menuText/tutorialword.png";
    tutorialLevelButton.setMenuTexture(tutorialPath);
    tutorialLevelButton.init();
    tutorialLevelButton.getPositionComponent()->setPosition({600,500});
    tutorialPos = tutorialLevelButton.getPositionComponent()->getPosition();

    std::string exitPath = "../data/textures/menuText/exit.png";
    exitButton.setMenuTexture(exitPath);
    exitButton.init();
    exitButton.getPositionComponent()->setPosition({600, 600});
    exitPos = exitButton.getPositionComponent()->getPosition();

    std::string arrowPath = "../data/textures/levels/arrow.png";
    arrow.setMenuTexture(arrowPath);
    arrow.init();
    arrow.getDrawComponent()->setScale({0.1, 0.1});
    arrow.getPositionComponent()->setPosition({-50, -50});

    drawSystem->addEntity(&m_menu);
    drawSystem->addEntity(&newGameButton);
    drawSystem->addEntity(&survivalModeButton);
    drawSystem->addEntity(&tutorialLevelButton);
    drawSystem->addEntity(&exitButton);
    drawSystem->addEntity(&arrow);

    drawSystem->setProjection(w, h, m_screen_scale);

    return true;
}

void MainMenu::destroy() {
    glDeleteFramebuffers(1, &m_frame_buffer);
    glfwDestroyWindow(m_window);
}

bool MainMenu::update(float elapsed_ms) {
    int w, h;
    glfwGetFramebufferSize(m_window, &w, &h);
    vec2 screen = {(float) w / m_screen_scale, (float) h / m_screen_scale};

    if (currentFrame++ >= DELETEFRAME) {
        currentFrame = 0;
        deleteSystem->update(0);
    }

    return true;
}

void MainMenu::draw() {
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

    drawSystem->update(0);

    glfwSwapBuffers(m_window);
}

bool MainMenu::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void MainMenu::on_key(GLFWwindow *, int key, int, int action, int mod) {
    if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_ENTER:
                menu_over = true;
                break;
        }
    }
}

void MainMenu::on_mouse_move(GLFWwindow *, double xpos, double ypos) {
    float newGame_offset = 200.f;
    float survivalMode_offset_2 = 300.f;
    float tutorialMode_offset = 200.f;
    float exit_offset = 50.f;
    float y_offset = 25.f;
    if (xpos > newGamePos.x - newGame_offset && xpos < newGamePos.x + newGame_offset &&
        ypos > newGamePos.y - y_offset && ypos < newGamePos.y + y_offset) {
        is_new_game = true;
        is_survival_mode = false;
        is_tutorial = false;
        is_exit = false;
        nextLevel = LevelName::LEVEL_SELECTION;
        arrow.getPositionComponent()->setPosition({400, 300});
    } else if (xpos > survivalModePos.x - survivalMode_offset_2 && xpos < survivalModePos.x + survivalMode_offset_2 &&
               ypos > survivalModePos.y - y_offset && ypos < survivalModePos.y + y_offset) {
        is_new_game = false;
        is_survival_mode = true;
        is_tutorial = false;
        is_exit = false;
        arrow.getPositionComponent()->setPosition({300,400});
    } else if (xpos > tutorialPos.x-tutorialMode_offset && xpos < tutorialPos.x+tutorialMode_offset &&
               ypos > tutorialPos.y-y_offset && ypos < tutorialPos.y+y_offset) {
        is_new_game = false;
        is_survival_mode = false;
        is_tutorial = true;
        is_exit = false;
        arrow.getPositionComponent()->setPosition({400,500});
    } else if (xpos > exitPos.x-exit_offset && xpos < exitPos.x+exit_offset &&
               ypos > exitPos.y-y_offset && ypos < exitPos.y+y_offset) {
        is_new_game = false;
        is_survival_mode = false;
        is_tutorial = false;
        is_exit = true;
        arrow.getPositionComponent()->setPosition({500, 600});
    } else {
        is_new_game = false;
        is_survival_mode = false;
        is_tutorial = false;
        is_exit = false;
        arrow.getPositionComponent()->setPosition({-50, -50});
    }
}

void MainMenu::on_mouse_button(GLFWwindow *, int button, int action, int mod) {
    if (action ==  GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
        if (is_new_game || is_survival_mode || is_exit || is_tutorial) {
            menu_over = true;
        }
    }
}

bool MainMenu::check_menu_over() {
    return menu_over;
}

int MainMenu::checkMode() {
    if (is_new_game) return 0;
    if (is_survival_mode) return 1;
    if (is_tutorial) return 2;
    else return -1;
}

bool MainMenu::checkIfExit() {
    return is_exit;
}

LevelName MainMenu::getNextLevel() {
    return nextLevel;
}
