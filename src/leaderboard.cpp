#include "leaderboard.hpp"
#include "global.hpp"
#include <time.h>
#include <chrono>

// Much code from https://learnopengl.com/In-Practice/Text-Rendering

namespace {
    void glfw_err_cb(int error, const char *desc) {
        fprintf(stderr, "%d: %s", error, desc);
    }
}

Leaderboard::Leaderboard() {
    leaderboard_is_over = false;
    nextLevel = LevelName::MAIN_MENU;
}

Leaderboard::~Leaderboard() = default;

bool Leaderboard::init(vec2 screen) {
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
        ((Leaderboard *) glfwGetWindowUserPointer(wnd))->on_key(wnd, _0, _1, _2, _3);
    };
    auto cursor_pos_redirect = [](GLFWwindow *wnd, double _0, double _1) {
        ((Leaderboard *) glfwGetWindowUserPointer(wnd))->on_mouse_move(wnd, _0, _1);
    };
    auto mouse_button_redirect = [](GLFWwindow *wnd, int _0, int _1, int _2) {
        ((Leaderboard *) glfwGetWindowUserPointer(wnd))->on_mouse_button(wnd, _0, _1, _2);
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

    // TODO CHANGE SO IT DOESN'T RESTART SONG
    musicSystem = syss->getMusicSystem();
    musicSystem->openAudio();
    musicSystem->loadBackgroundMusic();
    musicSystem->playBackgroundMusic();

    scoreSystem = syss->getScoreSystem();

    drawSystem = syss->getDrawSystem();

    background.init();
    drawSystem->setProjection(w, h, m_screen_scale);
    drawSystem->addEntity(&background);

    DefaultTexture *l = new DefaultTexture();
    std::string spritePath = "../data/textures/victoryAssets/leaderboard.png";
    l->setLevelTexture(spritePath);
    l->init();
    l->getPositionComponent()->setPosition({width / 2,60});
    l->getDrawComponent()->setScale({0.8, 0.8});
    drawSystem->addEntity((Drawable *) l);

    float offset = 50.f;
    for (int i = 0; i < 2; i++) {
        DefaultTexture *l = new DefaultTexture();
        std::string spritePath = "../data/textures/victoryAssets/" + std::to_string(i + 2) + "l.png";
        l->setLevelTexture(spritePath);
        l->init();
        l->getPositionComponent()->setPosition({width / 2, 600 + offset * i});
        l->getDrawComponent()->setScale({0.5, 0.5});
        drawSystem->addEntity((Drawable *) l);
    }

    if (!loadGlyphs()) {
        leaderboard_is_over = true;
        return false;
    }

    renderHighScores();

    return true;
}

void Leaderboard::destroy() {
    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glDeleteFramebuffers(1, &m_frame_buffer);
    glfwDestroyWindow(m_window);

    // Free glyphs from draw system
    std::vector<Entity*> *entities = drawSystem->getEntityListPointer();
    auto it = entities->begin();
    while (it != entities->end()) {
        Entity* entt = *it;
        if (entt->type == EntityType::GLYPH) {
            auto* glyph = dynamic_cast<Glyph*>(entt);
            glyph->destroy();
            delete glyph;
            it = entities->erase(it);
        } else {
            it++;
        }
    }
}

bool Leaderboard::update(float ms) {
    return true;
}

void Leaderboard::draw() {
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

bool Leaderboard::is_over() const {
    return glfwWindowShouldClose(m_window) || leaderboard_is_over;
}

void Leaderboard::on_key(GLFWwindow *, int key, int, int action, int mod) {
    if (action == GLFW_RELEASE && key == GLFW_KEY_ESCAPE) {
        leaderboard_is_over = true;
    }
}

void Leaderboard::on_mouse_move(GLFWwindow *, double xpos, double ypos) {
    float constantPos = width / 2;
    float offset = 20.f;
    if (xpos > constantPos - offset * 3 && xpos < constantPos + offset * 3 && ypos > 600 - offset &&
        ypos < 600 + offset) {
        onHover = 1;
    } else if (xpos > constantPos - offset * 4 && xpos < constantPos + offset * 4 && ypos > 650 - offset &&
               ypos < 650 + offset) {
        onHover = 2;
    } else {
        onHover = 0;
    }
}

void Leaderboard::on_mouse_button(GLFWwindow *, int button, int action, int mod) {
    if (onHover == 1) {
        leaderboard_is_over = true;
    } else if (onHover == 2) {
        leaderboard_is_over = true;
        nextLevel = LevelName::SURVIVAL_MODE;
    } else {
        // do nothing
    }
}

LevelName Leaderboard::get_next_level() {
    return nextLevel;
}

void Leaderboard::renderText(std::string text, vec2 position, float scale, vec3 colour) {
    // todo test
    float x = position.x, y = position.y;

    // Iterate through all characters
    std::string::const_iterator it;
    for (it = text.begin(); it != text.end(); it++) {
        Character character = characters[*it];

        GLfloat xpos = x + character.bearing.x * scale;
        // Use H's bearing because it touches the ceiling of character height
        GLfloat ypos = y + (this->characters['X'].bearing.y - character.bearing.y) * scale;

        GLfloat w = character.size.x * scale;
        GLfloat h = character.size.y * scale;

        // Add character to the draw system
        auto texture = new Texture();
        texture->width = w;
        texture->height = h;
        texture->id = character.textureId;

        auto glyph = new Glyph(texture, character.bearing, character.offsetToNext);
        glyph->init();
        glyph->getPositionComponent()->setPosition({xpos, ypos});

        drawSystem->addEntity(glyph);

        // Now advance cursors for next glyph
        x += (character.offsetToNext >> 6) * scale; // Bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
    }
}

bool Leaderboard::loadGlyphs() {
    if (FT_Init_FreeType(&ft)) {
        perror("Could not initialize freetype.");
        return false;
    }

    // todo investigate different fonts
    if (FT_New_Face(ft, "../data/textures/fonts/ka1.ttf", 0, &face)) {
        perror("Could not load font.");
        return false;
    }

    FT_Set_Pixel_Sizes(face, 0, 30);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Set OpenGL options
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Load ASCII
    for (GLubyte c = 0; c < 255; c++) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        GLuint textureId;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        vec2 size = {static_cast<float>(face->glyph->bitmap.width), static_cast<float>(face->glyph->bitmap.rows)};
        vec2 bearing = {static_cast<float>(face->glyph->bitmap_left), static_cast<float>(face->glyph->bitmap_top)};
        unsigned int offset = face->glyph->advance.x;

        struct Character character = {
                textureId,
                size,
                bearing,
                offset
        };

        characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0); // reset

    return true;
}

void Leaderboard::renderHighScores() {
    std::list<ScoreRecord> *records = scoreSystem->getHighScores();

    float scoreX = width / 16;
    float nameX = scoreX + width / 3;
    float dateX = (3 * width) / 4;
    float currY = height / 6;

    float offsetToNextRecord = 45.f;

    for (const auto& record : *records) {
        std::string score = std::to_string(record.score);
        renderText(score, {scoreX, currY}, 1.f);

        renderText(record.name, {nameX, currY}, 1.f);

        renderText(record.date, {dateX, currY}, 1.f);

        currY += offsetToNextRecord;
    }
}

bool Leaderboard::shouldClose() {
    return glfwWindowShouldClose(m_window);
}
