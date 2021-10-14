#pragma once

#include "HandleBall.h"
#include "cBall.h"
#include "cDeath.h"
#include "constants.h"

#include <AstuSuite2D.h>
#include <AstuECS.h>



using namespace astu::suite2d;
using namespace astu2d;
using namespace astu;
using namespace std;


const astu::EntityFamily HandleBall::FAMILY = EntityFamily::Create<cBall>();

HandleBall::HandleBall(int updatePriority)
    :BaseService("Ball HandlerService")
    ,IteratingEntitySystem(FAMILY,updatePriority)
{

}

void HandleBall::OnStartup() {
    auto& imps = ASTU_SERVICE(InputMappingService);
    respawnBallAction = imps.BindAction("Respawn");
}

void HandleBall::OnShutdown() {
    auto& imps = ASTU_SERVICE(InputMappingService);
    imps.RemoveActionBinding(respawnBallAction);
    respawnBallAction = nullptr;
}

void HandleBall::DestroyBall(astu::Entity& ball){
    ball.GetComponent<CBody>().SetLinearVelocity(0,0);
    ball.GetComponent<CPose>().transform.SetTranslation(BALL_INIT_POS);
    EmitSignal(GameEvent(GameEvent::Type::BallOut));
}

bool HandleBall::OnCollision(astu::Entity& entityA, astu::Entity& entityB){
    if(entityA.HasComponent<cBall>()&& entityB.HasComponent<cDeath>()){
        DestroyBall(entityA);
    }
     if(entityB.HasComponent<cBall>()&& entityA.HasComponent<cDeath>()){
        DestroyBall(entityB);
    }
    return 0;
}

void HandleBall::ProcessEntity(Entity& entity){
    if(respawnBallAction->IsPressed()){
        auto& body = entity.GetComponent<CBody>();
        if(body.GetLinearVelocity()==Vector2f(0,0)){
           body.SetLinearVelocity(0,BALL_INITSPEED); 
        }
    }
}

