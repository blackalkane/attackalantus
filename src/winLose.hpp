#ifndef ATTACKATLANTIS_WINLOSE_HPP
#define ATTACKATLANTIS_WINLOSE_HPP

#include <vector>
#include <random>
#include <SDL.h>
#include <SDL_mixer.h>
#include "common.hpp"
#include <systems/system.hpp>
#include <systems/drawSystem.hpp>
#include <systems/musicSystem.hpp>
#include <systems/deleteSystem.hpp>
#include "levels.hpp"

class WinLose {
public:
    WinLose();

    ~WinLose();

    bool init(vec2 screen, Levels* levelObj);

    void destroy();

    bool update(float ms);

    void draw();

    bool is_over() const;

    void on_key(GLFWwindow *, int key, int, int action, int mod);

    void on_mouse_move(GLFWwindow *, double xpos, double ypos);

    void on_mouse_button(GLFWwindow *, int button, int action, int mod);

    bool check_win_lose_over();

    void reset_win_lose_over();

    LevelName get_next_level();

    GLFWwindow *m_window;
private:
    float m_screen_scale;

    GLuint m_frame_buffer;
    Texture m_screen_tex;
    int currentFrame;
    static const int DELETEFRAME = 100;

    std::default_random_engine m_rng;
    std::uniform_real_distribution<float> m_dist;
    std::vector<DefaultTexture*> levels;

    Environment environment;
    bool pageOver;
    LevelName nextLevel;
    LevelName curLevel;
    LevelName preLevel;
    int onHover;

    DrawSystem* drawSystem;
    MusicSystem* musicSystem;
    DeleteSystem* deleteSystem;
};

#endif //ATTACKATLANTIS_WINLOSE_HPP