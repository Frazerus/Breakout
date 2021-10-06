#pragma once
// Local includes
#include "MainService.h"
#include "cBall.h"
#include "cBlock.h"
#include "cPaddle.h"
#include "constants.h"

// AST-Utilities includes
#include <AstuSuite2D.h>

using namespace astu::suite2d;
using namespace astu2d;
using namespace astu;
using namespace std;

#define SPEED   1.0f

    const EntityFamily MainService::FAMILY = EntityFamily::Create<cBall, CPose>();


MainService::MainService(int updatePriority)
    : BaseService("Main Service")
{
    // Intentionally left empty.
}

void MainService::OnStartup()
{

    GetCamera().ShowFitting(WORLD_WIDTH,WORLD_HEIGHT);

    numLifes = 3;
    AddEntity("Ball",Vector2f(0,10));
    AddEntity("Block",Vector2f(0,-50));


    
}


void MainService::OnShutdown()
{
    // Cleanup
    ASTU_SERVICE(SceneGraph).GetRoot()->DetachAll();
}

void MainService::UpdateLife(int deltalife){
    numLifes += deltalife;
    std::cout <<"current hp: " << numLifes;
    if(numLifes < 0){
        
    }

}

Vector2f MainService::GetCenter()
{
    auto& winSrv = ASTU_SERVICE(WindowService);
    return Vector2f((float) winSrv.GetWidth() / 2, (float) winSrv.GetHeight() / 2);
}

bool MainService::OnSignal(const GameEvent &signal){
    switch(signal.type){

    case GameEvent::Type::BallOut:
        UpdateLife(-1);  
        break;  
         
        
    }

    return false;
}
