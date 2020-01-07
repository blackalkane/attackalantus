#ifndef CASTLETOP_H
#define CASTLETOP_H

#include "drawable.hpp"

class CastleTop: public Drawable
{
public:

	bool init() override ;

	void destroy() override;

    DrawComponent* getDrawComponent() override;

    PositionComponent* getPositionComponent() override;

    void preloadTexture() override;

    void setWallNum(int num);

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    Texture* castleTopTexture1;
    Texture* castleTopTexture2;
    Texture* castleTopTexture3;
    Texture* castleTopTexture4;
    int wallNum;
};

#endif
