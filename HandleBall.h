#pragma once

#include "constants.h"
#include "cBall.h"

#include <AstuServices.h>
#include <AstuSuite2D.h>
#include <AstuECS.h>


class HandleBall
    :public astu::BaseService
    ,private astu::IteratingEntitySystem
    ,private astu2d::CollisionListener

{
    public:
     HandleBall(int updatePriority = astu::Priority::Normal);

    private:

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    void SpawnBall();

    void ChangeDirection(astu::Entity &ball, astu::Entity &collided);
    
    static const astu:: EntityFamily FAMILY;


    virtual void ProcessEntity(astu::Entity& entity) override;

    
    virtual bool OnCollision(astu::Entity& entityA, astu::Entity& entityB) override;
};