#ifndef ATTACKATLANTIS_GLYPH_H
#define ATTACKATLANTIS_GLYPH_H

#include "drawable.hpp"

class Glyph: public Drawable
{
public:
    Glyph(Texture* texture, vec2 bearing, GLuint offsetToNext);

    bool init() override;

    void destroy() override;

    PositionComponent* getPositionComponent() override;

    DrawComponent* getDrawComponent() override;

    void setTexture(Texture *t);

    void preloadTexture() override;

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    Texture* texture{};

    // ID handle of the glyph texture
    vec2 bearing{};  // Offset from baseline to left/top of glyph
    GLuint offsetToNext;    // Horizontal offset to advance to next glyph
};

#endif