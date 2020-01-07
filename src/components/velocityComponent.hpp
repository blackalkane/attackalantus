#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include <common.hpp>
#include "gcomponent.hpp"

class VelocityComponent: public GComponent
{
	public:
		VelocityComponent();
		~VelocityComponent();

		bool init();

		void destroy();

        float getVX();

        float getVY();

        void setVX(float VX);

        void setVY(float VY);

		vec2 getVelocity();

		void setVelocity(vec2 velocity);

	private:
		float velocityx;
        float velocityy;
	
};

#endif