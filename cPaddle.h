#pragma once

#include <AstuECS.h>

using namespace astu;

class cPaddle : public astu::EntityComponent {
    public: 
        float currVel;

        bool control;

        float controlMult = 1;


        cPaddle()
            {

            }

            virtual std::shared_ptr<EntityComponent> Clone() override {
		// Create copy using copy-constructor.
		return std::make_shared<cPaddle>(*this);
            }
};