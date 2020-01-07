#include "castleTop.hpp"

bool CastleTop::init()
{
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
    float scaleX = 1.05, scaleY = 1;

    preloadTexture();

    drawComp.physics.scale = {scaleX, scaleY};
    switch(wallNum){
        default:
        case 1:
            drawComp.setStaticTexture(castleTopTexture1);
            break;
        case 2:
            drawComp.setStaticTexture(castleTopTexture2);
            break;
        case 3:
            drawComp.setStaticTexture(castleTopTexture3);
            break;
        case 4:
            drawComp.setStaticTexture(castleTopTexture4);
            break;
    }
    drawComp.init();
    positionComp.setPosition({100.f, 100.f});
    Texture *texture = drawComp.texture;
    // TODO FIX HACK
    positionComp.setWidth((texture->width) * scaleX);
    positionComp.setHeight((texture->height) * scaleY);
    type = EntityType::ENVIRONMENT;
    return true;
}

void CastleTop::destroy()
{
    drawComp.destroy();
}

DrawComponent *CastleTop::getDrawComponent() {
    return &drawComp;
}

PositionComponent *CastleTop::getPositionComponent() {
    return &positionComp;
}

void CastleTop::preloadTexture() {
    std::string wallPath1 = "../data/textures/environment/environment_objects/wall1.png";
    castleTopTexture1 = setTexture(wallPath1);

    std::string wallPath2 = "../data/textures/environment/environment_objects/wall2.png";
    castleTopTexture2 = setTexture(wallPath2);

    std::string wallPath3 = "../data/textures/environment/environment_objects/wall3.png";
    castleTopTexture3 = setTexture(wallPath3);

    std::string wallPath4 = "../data/textures/environment/environment_objects/wall4.png";
    castleTopTexture4 = setTexture(wallPath4);
}

void CastleTop::setWallNum(int num) {
    wallNum = num;
}

