#include "velocityComponent.hpp"
#include "common.hpp"

VelocityComponent::VelocityComponent(){

}

VelocityComponent::~VelocityComponent(){

}

bool VelocityComponent::init(){
    velocityx = 0;
    velocityy = 0;

    return true;
}

void VelocityComponent::destroy(){

}

float VelocityComponent::getVX()
{
    return velocityx;
}

float VelocityComponent::getVY()
{
    return velocityy;
}

void VelocityComponent::setVX(float VX)
{
    velocityx = VX;
}

void VelocityComponent::setVY(float VY)
{
    velocityy = VY;
}

vec2 VelocityComponent::getVelocity()
{
    return {velocityx, velocityy};
}

void VelocityComponent::setVelocity(vec2 velocity)
{
    velocityx = velocity.x;
    velocityy = velocity.y;
}