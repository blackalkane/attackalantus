#ifndef ATTACKATLANTIS_MAINMENU_HPP
#define ATTACKATLANTIS_MAINMENU_HPP

#include <vector>
#include <random>
#include <SDL.h>
#include <SDL_mixer.h>
#include "common.hpp"
#include "levelName.hpp"
#include <systems/system.hpp>
#include <systems/drawSystem.hpp>
#include <systems/musicSystem.hpp>
#include <systems/deleteSystem.hpp>
#include <entities/menu.hpp>
#include <entities/menu_items.hpp>

class MainMenu {
public:
    MainMenu();

    ~MainMenu();

    bool init(vec2 screen);

    void destroy();

    bool update(float ms);

    void draw();

    bool shouldClose() const;

    void on_key(GLFWwindow *, int key, int, int action, int mod);

    void on_mouse_move(GLFWwindow *, double xpos, double ypos);

    void on_mouse_button(GLFWwindow *, int button, int action, int mod);

    bool check_menu_over();

    int checkMode();

    bool checkIfExit();

    GLFWwindow *m_window;

    LevelName getNextLevel();

private:
    float m_screen_scale;
    Menu m_menu;
    MenuItems newGameButton;
    vec2 newGamePos;
    MenuItems survivalModeButton;
    vec2 survivalModePos;
    MenuItems tutorialLevelButton;
    vec2 tutorialPos;
    MenuItems exitButton;
    vec2 exitPos;
    MenuItems arrow;

    GLuint m_frame_buffer;
    Texture m_screen_tex;
    int currentFrame;
    static const int DELETEFRAME = 100;

    std::default_random_engine m_rng;
    std::uniform_real_distribution<float> m_dist;

    bool menu_over;
    bool is_new_game;
    bool is_survival_mode;
    bool is_exit;
    LevelName nextLevel;
    bool is_tutorial;

    DrawSystem* drawSystem;
    MusicSystem* musicSystem;
    DeleteSystem* deleteSystem;
};

#endif //ATTACKATLANTIS_MAINMENU_HPP
