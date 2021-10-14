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
    
    AddEntity("Ball");
    AddEntity("Paddle");
    PlaceBoundaries();
    


    
}


void MainService::OnShutdown()
{
    // Cleanup
    ASTU_SERVICE(SceneGraph).GetRoot()->DetachAll();
}

void MainService::UpdateLife(int deltalife){
    numLifes += deltalife;
    if(numLifes < 0){
        std::cout <<"Well, you lost. Feels bad man. Would you quit please?" << endl;
        std::cout <<"Nothing is going to happen if you press spacebar again, I swear" << endl;
    }
    else{
        std::cout <<"current hp: " << numLifes << endl;
        std::cout <<"Press Space to keep playing" << endl;
    }

}

void MainService::UpdateNrBlocks(int nr){
    numOfBlocks = nr;
}

void MainService::Win(){
    std::cout <<"EYYYYY YOU WON" << endl;
    std::cout << "Gj, you deserve this ☆⌒(*＾-゜)v"<< endl;
    
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
    
    case GameEvent::Type::BlocksCreated:
        UpdateNrBlocks(signal.intValue);
        break;
    
    case GameEvent::Type::BlockDestroyed:
        if(--numOfBlocks<=0){
            EmitSignal(GameEvent::Type::AllBlocksDestroyed);
        }
        break;

    case GameEvent::Type::AllBlocksDestroyed:
        Win();
        break;  

    }

    return false;
}

void MainService::PlaceBoundaries(){
    AddEntity("VBoundary",-WORLD_HALF_WIDTH-WORLD_WIDTH/2,0);
    AddEntity("VBoundary",WORLD_HALF_WIDTH+WORLD_WIDTH/2,0);
    AddEntity("DBoundary",0,WORLD_HALF_HEIGHT+BOUNDARY_THICKNESS/2);
    AddEntity("HBoundary",0,-WORLD_HALF_HEIGHT-BOUNDARY_THICKNESS/2);
}
