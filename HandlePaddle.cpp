#pragma once

#include "HandlePaddle.h"
#include "cPaddle.h"
#include "cBall.h"
#include "cBound.h"
#include "constants.h"

#include <AstuSuite2D.h>
#include <AstuECS.h>



using namespace astu::suite2d;
using namespace astu2d;
using namespace astu;
using namespace std;

const EntityFamily HandlePaddle::FAMILY = EntityFamily::Create<cPaddle>();

HandlePaddle::HandlePaddle(int updatePriority)
    :BaseService("Paddle HandlerService")
	,IteratingEntitySystem(FAMILY, updatePriority)    
{

}

void HandlePaddle::OnStartup() {
    
    auto& imps = ASTU_SERVICE(InputMappingService);
    moveAxis = imps.BindAxis("Move");
}
void HandlePaddle::OnShutdown() {
    auto& imps = ASTU_SERVICE(InputMappingService);
    imps.RemoveAxisBinding(moveAxis);
    moveAxis = nullptr;
}

void HandlePaddle::ProcessEntity(Entity &entity){

    auto& pos = entity.GetComponent<CPose>();
    auto& pad = entity.GetComponent<cPaddle>();

    if( pad.currVel > 0 && moveAxis->GetValue() > 0 
    ||  pad.currVel < 0 && moveAxis->GetValue() < 0){
        pad.currVel += PADDLE_ACC*moveAxis->GetValue();
    }
    else{
        pad.currVel += PADDLE_ACC*moveAxis->GetValue()* pad.controlMult;
    }
    


    //constrain the currVel between negative and positive max speed
    pad.currVel = pad.currVel < -MAX_PADDLE_VEL? -MAX_PADDLE_VEL : pad.currVel;
    pad.currVel = pad.currVel > MAX_PADDLE_VEL? MAX_PADDLE_VEL : pad.currVel;

    if(pad.controlMult <= MAX_NOT_CONTROL_MULT){
        pad.controlMult*= CONTROL_UP_MULT;
    }
    else{
        pad.controlMult = 1;
    }

    //move the paddle
    float currX = pos.transform.GetTranslationX();

    //if the paddle hits the wall, calc the vel into the opposite direction and set the acc multiplier  to the lower value
    if(currX + pad.currVel > WORLD_PADDLE_WIDTH){
        float antiX = pad.currVel -(WORLD_PADDLE_WIDTH - currX);
        currX -= antiX;
        pad.currVel = -pad.currVel;
        pad.controlMult = MIN_NOT_CONTROL_MULT;
    }
    else if(currX + pad.currVel < -WORLD_PADDLE_WIDTH){
        float antiX = pad.currVel -(-WORLD_PADDLE_WIDTH - currX);
        currX -= antiX;
        pad.currVel = -pad.currVel;
        pad.controlMult = MIN_NOT_CONTROL_MULT;
    }
    else {
        currX += pad.currVel;
    }

    pos.transform.SetTranslationX(currX);

    //slow down the paddle over time and stop it if it becomes too slow
    pad.currVel*=PADDLE_DAMPENING;
    if(pad.currVel < MIN_PADDLE_VEL && pad.currVel > 0) {
        pad.currVel = 0;
    }
    if(pad.currVel > -MIN_PADDLE_VEL && pad.currVel < 0){
        pad.currVel = 0;
    }

    


}

void HandlePaddle::HandleBallColl(astu::Entity& Ball, astu::Entity& Paddle){
    auto& ballB = Ball.GetComponent<CBody>();
    auto& pad = Paddle.GetComponent<cPaddle>();

    Vector2f lvel = ballB.GetLinearVelocity();
    lvel.x += pad.currVel * PADDLE_HIT_MULTIPLIER;
    ballB.SetLinearVelocity(lvel);


}




bool HandlePaddle::OnCollision(astu::Entity& entityA, astu::Entity& entityB){
    if(entityA.HasComponent<cBall>()&& entityB.HasComponent<cPaddle>()){
        HandleBallColl(entityA, entityB);
    }
    if(entityB.HasComponent<cBall>()&& entityA.HasComponent<cPaddle>()){
        HandleBallColl(entityB, entityA);
    }
  
    return 0;
}


