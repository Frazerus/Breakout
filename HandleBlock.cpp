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
    EmitSignal(GameEvent(GameEvent::Type::BlocksCreated,createBlocks()));
}

void HandleBlock::OnShutdown() {

}

int HandleBlock::createBlocks(){
    int count = 0;
    for(float x = -WORLD_HALF_WIDTH+BLOCK_X/2; x <WORLD_HALF_WIDTH; x+=BLOCK_X+BLOCK_ROW_DIST ){
        for(float y = FIRST_ROW_HEIGHT; y < LAST_ROW_HEIGHT; y+= BLOCK_Y+BLOCK_COL_DIST){
            AddEntity("Block",x,y);
            count++;
        }
    }
    return count;
}


void HandleBlock::DestroyBlock(Entity &entity){

    EmitSignal(GameEvent(GameEvent::Type::BlockDestroyed));
    
    GetEntityService().RemoveEntity(entity);

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



