#pragma once

#include "HandleBlock.h"
#include "cBlock.h"
#include "cBall.h"
#include "constants.h"

#include <AstuSuite2D.h>
#include <AstuECS.h>



using namespace astu::suite2d;
using namespace astu2d;
using namespace astu;
using namespace std;


const astu::EntityFamily HandleBlock::FAMILY = EntityFamily::Create<cBlock, CPose>();

HandleBlock::HandleBlock()
    :BaseService("Block HandlerService")
    ,OneFamilyEntitySystem(FAMILY)
    ,EntityListener(FAMILY)
{

}

void HandleBlock::OnStartup() {
}

void HandleBlock::OnShutdown() {

}

void HandleBlock::DestroyBlock(Entity &entity){
    GetEntityService().RemoveEntity(entity);

    EmitSignal(GameEvent(GameEvent::Type::BlockDestroyed));

}

bool HandleBlock::OnCollision(Entity& entityA, Entity& entityB){
    if(entityA.HasComponent<cBall>()){
        if(entityB.HasComponent<cBlock>()){
            DestroyBlock(entityB);
        }
    }

    if(entityA.HasComponent<cBlock>()){
        if(entityB.HasComponent<cBall>()){
            DestroyBlock(entityA);
        }
    }
    return false;
}



