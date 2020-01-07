#include "environment.hpp"

#include <iostream>

/*
bool Environment::init() {
    m_dead_time = -1;

    if (!environment_texture.is_valid())
    {
        if (!environment_texture.load_from_file("../data/textures/background.png"))
        {
            fprintf(stderr, "Failed to load background texture!");
            return false;
        }else{

        }
    }else{
        printf("gg");
    }
    // Since we are not going to apply transformation to this screen geometry
    // The coordinates are set to fill the standard openGL window [-1, -1 .. 1, 1]
    // Make the size slightly larger then the screen to crop the boundary.
    static const GLfloat screen_vertex_buffer_data[] = {
            -1.05f, -1.05f, 0.0f,
            1.05f, -1.05f, 0.0f,
            -1.05f,  1.05f, 0.0f,
            -1.05f,  1.05f, 0.0f,
            1.05f, -1.05f, 0.0f,
            1.05f,  1.05f, 0.0f,
    };

    // Clearing errors
    gl_flush_errors();

    // Vertex Buffer creation
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screen_vertex_buffer_data), screen_vertex_buffer_data, GL_STATIC_DRAW);

    if (gl_has_errors())
        return false;

    // Loading shaders
    if (!effect.load_from_file(shader_path("world.vs.glsl"), shader_path("world.fs.glsl")))
        return false;

    return true;
}*/

bool Environment::init()
{
    drawComponent.fragmentShaderPath = shader_path("world.fs.glsl");
    drawComponent.vertexShaderPath = shader_path("world.vs.glsl");
    //drawComponent.PNGPath = "../data/textures/background.png";
    drawComponent.vdepth = 1.0;
    if (backgroundPath.empty()) {
        return false;
    }
    preloadTexture();
    drawComponent.setStaticTexture(environment_texture);
    drawComponent.init();

    max_x = width;
    max_y = height;
    type = EntityType::ENVIRONMENT;


    // Load shared texture
    /*if (!environment_texture.is_valid())
    {
        if (!environment_texture.load_from_file("../data/textures/background.png"))
        {
            fprintf(stderr, "Failed to load background texture!");
            return false;
        }else{

        }
    }else{
        printf("gg");
    }

    // The positionComp corresponds to the center of the texture
    float wr = environment_texture.width * 0.5f;
    float hr = environment_texture.height * 0.5f;

    TexturedVertex vertices[4];
    vertices[0].positionComp = { -wr, +hr, -0.02f };
    vertices[0].texcoord = { 0.f, 1.f };
    vertices[1].positionComp = { +wr, +hr, -0.02f };
    vertices[1].texcoord = { 1.f, 1.f };
    vertices[2].positionComp = { +wr, -hr, -0.02f };
    vertices[2].texcoord = { 1.f, 0.f };
    vertices[3].positionComp = { -wr, -hr, -0.02f };
    vertices[3].texcoord = { 0.f, 0.f };

    // Counterclockwise as it's the default opengl front winding direction
    uint16_t indices[] = { 0, 3, 1, 1, 3, 2 };

    // Clearing errors
    gl_flush_errors();

    // Vertex Buffer creation
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexturedVertex) * 4, vertices, GL_STATIC_DRAW);

    // Index Buffer creation
    glGenBuffers(1, &mesh.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 6, indices, GL_STATIC_DRAW);

    // Vertex Array (Container for Vertex + Index buffer)
    glGenVertexArrays(1, &mesh.vao);
    if (gl_has_errors())
        return false;

    // Loading shaders
    if (!effect.load_from_file(shader_path("world.vs.glsl"), shader_path("world.fs.glsl")))
        return false;

    motion.radians = 0.f;
    motion.speed = 200.f;

    // Setting initial values, scale is negative to make it face the opposite way
    // 1.0 would be as big as the original texture.
    physics.scale = { -0.4f, 0.4f };

    */
    return true;
}

// Releases all graphics resources
void Environment::destroy() {
    drawComponent.destroy();
}


/*
void Environment::draw(const mat3& projection) {
    // Enabling alpha channel for textures
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    // Setting shaders
    glUseProgram(effect.program);

    // Set screen_texture sampling to texture unit 0
    // Set clock
    GLuint screen_text_uloc = glGetUniformLocation(effect.program, "screen_texture");
    GLuint time_uloc = glGetUniformLocation(effect.program, "time");
    GLuint dead_timer_uloc = glGetUniformLocation(effect.program, "dead_timer");
    glUniform1i(screen_text_uloc, 0);
    glUniform1f(time_uloc, (float)(glfwGetTime() * 10.0f));
    glUniform1f(dead_timer_uloc, (m_dead_time > 0) ? (float)((glfwGetTime() - m_dead_time) * 10.0f) : -1);

    // Draw the screen texture on the quad geometry
    // Setting vertices
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, environment_texture.id);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

    // Bind to attribute 0 (in_position) as in the vertex shader
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles
    glDisableVertexAttribArray(0);
}*/

/*void Environment::draw(const mat3& projection)
{
    // Transformation code, see Rendering and Transformation in the template specification for more info
    // Incrementally updates transformation matrix, thus ORDER IS IMPORTANT
    transform.begin();
    transform.translate(motion.positionComp);
    transform.rotate(motion.radians);
    transform.scale(physics.scale);
    transform.end();

    // Setting shaders
    glUseProgram(effect.program);

    // Enabling alpha channel for textures
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    // Getting uniform locations for glUniform* calls
    GLint transform_uloc = glGetUniformLocation(effect.program, "transform");
    GLint color_uloc = glGetUniformLocation(effect.program, "fcolor");
    GLint projection_uloc = glGetUniformLocation(effect.program, "projection");

    // Setting vertices and indices
    glBindVertexArray(mesh.vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);

    // Input data location as in the vertex buffer
    GLint in_position_loc = glGetAttribLocation(effect.program, "in_position");
    GLint in_texcoord_loc = glGetAttribLocation(effect.program, "in_texcoord");
    glEnableVertexAttribArray(in_position_loc);
    glEnableVertexAttribArray(in_texcoord_loc);
    glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)0);
    glVertexAttribPointer(in_texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)sizeof(vec3));

    // Enabling and binding texture to slot 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, environment_texture.id);

    // Setting uniform values to the currently bound program
    glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float*)&transform.out);
    float color[] = { 1.f, 1.f, 1.f };
    glUniform3fv(color_uloc, 1, color);
    glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float*)&projection);

    // Drawing!
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}*/

DrawComponent *Environment::getDrawComponent() {
    return &drawComponent;
}

PositionComponent *Environment::getPositionComponent() {
    return &positionComponent;
}

bool Environment::handleCollision(Collides *collidedWith) {
    // TODO
    return false;
}

void Environment::preloadTexture() {
    environment_texture = setTexture(backgroundPath);
}

void Environment::setTexturePath(char *path) {
    backgroundPath = path;

}

