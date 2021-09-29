#pragma once

#include "constants.h"
#include "cBlock.h"
#include "GameEvent.h"

#include <AstuServices.h>
#include <AstuSuite2D.h>
#include <AstuECS.h>


class HandleBlock
    :public astu::BaseService
    ,private astu::EntityListener
    ,private astu::OneFamilyEntitySystem
    ,private astu2d::CollisionListener
    ,private astu::SignalEmitter<GameEvent>

{
    public:
     HandleBlock();

    private:

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    
    static const astu:: EntityFamily FAMILY;

    void DestroyBlock(astu::Entity &entity);

    virtual bool OnCollision(astu::Entity& entityA, astu::Entity& entityB) override;

};