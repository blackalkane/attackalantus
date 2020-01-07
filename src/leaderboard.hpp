#ifndef ATTACKATLANTIS_LEADERBOARD_HPP
#define ATTACKATLANTIS_LEADERBOARD_HPP

#include <ft2build.h>
#include FT_FREETYPE_H

#include <entities/levelSelectionBackground.hpp>
#include <entities/defaultTexture.hpp>
#include <entities/menu_items.hpp>
#include <systems/drawSystem.hpp>
#include <systems/deleteSystem.hpp>
#include <systems/musicSystem.hpp>
#include <map>
#include <systems/scoreSystem.hpp>
#include <entities/glyph.hpp>
#include "common.hpp"
#include "levelName.hpp"

class Leaderboard {
public:
    Leaderboard();

    ~Leaderboard();

    bool init(vec2 screen);

    void destroy();

    bool update(float ms);

    void draw();

    bool is_over() const;

    void on_key(GLFWwindow *, int key, int, int action, int mod);

    void on_mouse_move(GLFWwindow *, double xpos, double ypos);

    void on_mouse_button(GLFWwindow *, int button, int action, int mod);

    GLFWwindow *m_window;

    LevelName get_next_level();

    void renderText(std::string text, vec2 position, float scale, vec3 colour = { 1.f, 1.f, 1.f });

    bool shouldClose();

private:
    bool loadGlyphs();

    struct Character {
        GLuint textureId;   // ID handle of the glyph texture
        vec2 size;    // Size of glyph
        vec2 bearing;  // Offset from baseline to left/top of glyph
        GLuint offsetToNext;    // Horizontal offset to advance to next glyph
    };

    FT_Library ft;
    FT_Face face;
    std::map<GLchar, Character> characters;

    float m_screen_scale;
    LevelSelectionBackground background;

    GLuint m_frame_buffer;
    Texture m_screen_tex;

    DrawSystem *drawSystem;
    MusicSystem *musicSystem;
    ScoreSystem *scoreSystem;
    DeleteSystem *deleteSystem;

    bool leaderboard_is_over;
    int onHover;
    void renderHighScores();

    LevelName nextLevel;
};

#endif