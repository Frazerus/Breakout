#pragma once

#include "GameEvent.h"

#include <AstuSuite2D.h>
#include <AstuECS.h>

class cBall : public astu::EntityComponent, 
    private astu2d::CollisionListener,
    private astu::SignalEmitter<GameEvent>
     {
    public:

    float maxSpeed;


    cBall(float maxSpeed):
    maxSpeed(maxSpeed)
    {
            //intentionally left empty
    }


    virtual std::shared_ptr<EntityComponent> Clone() override {
        return std::make_shared<cBall>(*this);
    }

};