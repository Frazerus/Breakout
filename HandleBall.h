#pragma once

#include "constants.h"
#include "cBall.h"
#include "GameEvent.h"

#include <AstuServices.h>
#include <AstuSuite2D.h>
#include <AstuECS.h>


class HandleBall
    :public astu::BaseService
    ,private astu::IteratingEntitySystem
    ,private astu::SignalEmitter<GameEvent>
    ,private astu::SignalListener<GameEvent>
    ,private astu2d::CollisionListener

{
    public:
     HandleBall(int updatePriority = astu::Priority::Normal);

    private:

    std::shared_ptr<astu::ActionBinding> respawnBallAction;

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;
    
    static const astu:: EntityFamily FAMILY;

    void DestroyBall(astu::Entity& Ball);

    virtual bool OnCollision(astu::Entity& entityA, astu::Entity& entityB) override;

	virtual void ProcessEntity(astu::Entity& entity) override;

    static const astu:: EntityFamily FAMILY;
};