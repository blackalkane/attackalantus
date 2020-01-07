#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "gcomponent.hpp"
#include <common.hpp>

class PositionComponent: public GComponent
{
	public:
		PositionComponent();
		~PositionComponent();

		bool init();

		void destroy();

        float getPosX();

        float getPosY();

        void setPosX(float posX);

        void setPosY(float posY);

		vec2 getPosition();

        float getPrePosX();

        float getPrePosY();

        void setPrePosX(float preX);

        void setPrePosY(float preY);

        vec2 getPrePosition();

        void setPrePosition(vec2 prePos);

		vec2 getSize();

        void setPosition(vec2 pos);

        void resetPosition();

        void resetPosX();

        void resetPosY();

        void setWidth(float w);

        void setHeight(float h);

        void setPositionOffset(float xo, float yo);

        float getWidth();

        float getHeight();

        vec2 getPositionOffset();

        void setRotation(float radians);

        float getRotation();

        float getMouseX();

        float getMouseY();

        void setMouseX(float posX);

        void setMouseY(float posY);

        void updateRotation();

	private:
        // TOP LEFT OF ENTITY
		float posx;
        float posy;

        vec2 positionOffset;

        // previous position
        float prePosx;
        float prePosy;

        float width;
        float height;

        float mousex;
        float mousey;
        float rotation;
};

#endif