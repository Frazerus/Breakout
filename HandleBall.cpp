#pragma once

#include "HandleBall.h"
#include "cBall.h"
#include "constants.h"

#include <AstuSuite2D.h>
#include <AstuECS.h>



using namespace astu::suite2d;
using namespace astu2d;
using namespace astu;
using namespace std;


HandleBall::HandleBall(int updatePriority)
    :BaseService("Ball HandlerService")
{

}

void HandleBall::OnStartup() {
}

void HandleBall::OnShutdown() {

}

