#pragma once

#include <AstuECS.h>

class cBlock: public astu::EntityComponent {
    public: 
        cBlock()
        {

        }

        virtual std::shared_ptr<EntityComponent> Clone() override {
		// Create copy using copy-constructor.
		return std::make_shared<cBlock>(*this);
        }
};

