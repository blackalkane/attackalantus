#ifndef ATTACKATLANTIS_LEVELSELECTION_HPP
#define ATTACKATLANTIS_LEVELSELECTION_HPP

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
#include <entities/levelSelectionBackground.hpp>
#include <entities/defaultTexture.hpp>

class LevelSelection {
public:
    LevelSelection();

    ~LevelSelection();

    bool init(vec2 screen);

    void destroy();

    bool update(float ms);

    void draw();

    bool is_over() const;

    void on_key(GLFWwindow *, int key, int, int action, int mod);

    void on_mouse_move(GLFWwindow *, double xpos, double ypos);

    void on_mouse_button(GLFWwindow *, int button, int action, int mod);

    bool check_level_selection_over();

    void reset_level_selection_over();

    void set_chosen_level(LevelName l);

    LevelName get_chosen_level();

    GLFWwindow *m_window;
private:
    float m_screen_scale;
    LevelSelectionBackground background;
    std::vector<DefaultTexture*> levels;
    MenuItems levelArrow;

    GLuint m_frame_buffer;
    Texture m_screen_tex;
    int currentFrame;
    static const int DELETEFRAME = 100;

    std::default_random_engine m_rng;
    std::uniform_real_distribution<float> m_dist;

    bool level_selection_over;
    LevelName onHover;
    LevelName chosenLevel;

    DrawSystem* drawSystem;
    MusicSystem* musicSystem;
    DeleteSystem* deleteSystem;
};

#endif //ATTACKATLANTIS_LEVELSELECTION_HPP
