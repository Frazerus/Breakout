#pragma once


#include <AstuECS.h>

class cDeath : public astu::EntityComponent
     {
    public:



    cDeath()
    {
            //intentionally left empty
    }


    virtual std::shared_ptr<EntityComponent> Clone() override {
        return std::make_shared<cDeath>(*this);
    }

};