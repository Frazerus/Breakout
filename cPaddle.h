#pragma once

#include <AstuECS.h>

using namespace astu;

class cPaddle : public astu::EntityComponent {
    public: 

        float height;

        float speed;

        Vector2f position;

        

        cPaddle(float speed, float height, Vector2f position)
            :speed(speed)
            ,height(height)
            ,position(position)
            {

            }

            virtual std::shared_ptr<EntityComponent> Clone() override {
		// Create copy using copy-constructor.
		return std::make_shared<cPaddle>(*this);
            }
};