#pragma once


#include <AstuECS.h>

class cBall : public astu::EntityComponent
     {
    public:



    cBall()
    {
            //intentionally left empty
    }


    virtual std::shared_ptr<EntityComponent> Clone() override {
        return std::make_shared<cBall>(*this);
    }

};