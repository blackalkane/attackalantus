#include "positionComponent.hpp"
#include "common.hpp"
#include <math.h>

PositionComponent::PositionComponent(){

}

PositionComponent::~PositionComponent(){

}

bool PositionComponent::init(){
    posx = 0;
    posy = 0;
    prePosx = 0;
    prePosy = 0;
    width = 0;
    height = 0;
    rotation = 0;

    positionOffset = {0.f, 0.f};

    return true;
}

void PositionComponent::destroy(){

}

float PositionComponent::getPosX()
{
    return posx;
}

float PositionComponent::getPosY()
{
    return posy;
}

void PositionComponent::setPosX(float posX)
{
    prePosx = posx;
    posx = posX;
    updateRotation();
}

void PositionComponent::setPosY(float posY)
{
    prePosy = posy;
    posy = posY;
    updateRotation();
}

vec2 PositionComponent::getPosition() {
    return {posx, posy};
}

void PositionComponent::setPosition(vec2 pos) {
    prePosx = posx;
    prePosy = posy;
    posx = pos.x;
    posy = pos.y;
    updateRotation();
}



vec2 PositionComponent::getSize() {
    return { width, height };
}

void PositionComponent::setHeight(float h) {
    height = h;
}

float PositionComponent::getWidth() {
    return width;
}

float PositionComponent::getHeight() {
    return height;
}

void PositionComponent::setWidth(float w) {
    width = w;
}

void PositionComponent::setRotation(float radians)
{
    rotation = radians;
}

float PositionComponent::getRotation()
{
    return rotation;
}

float PositionComponent::getMouseX()
{
    return mousex;
}

float PositionComponent::getMouseY()
{
    return mousey;
}

void PositionComponent::setMouseX(float posX)
{
    mousex = posX;
    updateRotation();
}

void PositionComponent::setMouseY(float posY)
{
    mousey = posY;
    updateRotation();
}

void PositionComponent::updateRotation()
{
    float deltaX = getMouseX() - getPosX();
    float deltaY = getMouseY() - getPosY();
    setRotation(atan2(deltaY, deltaX));
}

void PositionComponent::setPrePosX(float preX) {
    prePosx = preX;
}

void PositionComponent::setPrePosY(float preY) {
    prePosy = preY;
}

void PositionComponent::setPrePosition(vec2 prePos) {
    prePosx = prePos.x;
    prePosy = prePos.y;
}

float PositionComponent::getPrePosX() {
    return prePosx;
}

float PositionComponent::getPrePosY() {
    return prePosy;
}

vec2 PositionComponent::getPrePosition() {
    return {prePosx, prePosy};
}

void PositionComponent::setPositionOffset(float xo, float yo) {
    positionOffset = {xo, yo};
}

vec2 PositionComponent::getPositionOffset() {
    return positionOffset;
}

void PositionComponent::resetPosition() {
    posx = prePosx;
    posy = prePosy;
    updateRotation();
}

void PositionComponent::resetPosX() {
    posx = prePosx;
    updateRotation();
}

void PositionComponent::resetPosY() {
    posy = prePosy;
    updateRotation();
}




