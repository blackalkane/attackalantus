#include "glyph.hpp"

Glyph::Glyph(Texture *texture, vec2 bearing, GLuint offsetToNext) {
    this->texture = texture;
    this->bearing = bearing;
    this->offsetToNext = offsetToNext;
    this->type = EntityType::GLYPH;
}

bool Glyph::init() {
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
    float scaleX = 1.f, scaleY = 1.f;
    drawComp.physics.scale = {scaleX, scaleY};
    drawComp.setStaticTexture(texture);
    drawComp.init();
    positionComp.init();

    positionComp.setWidth(texture->width * scaleX);
    positionComp.setHeight(texture->height * scaleY);

    return true;
}

void Glyph::destroy() {
    drawComp.destroy();
    positionComp.destroy();
}

PositionComponent *Glyph::getPositionComponent() {
    return &positionComp;
}

DrawComponent *Glyph::getDrawComponent() {
    return &drawComp;
}

void Glyph::setTexture(Texture *t) {
    // TODO
    texture = t;
}

void Glyph::preloadTexture() {

}




