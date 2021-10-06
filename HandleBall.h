#pragma once

#include "constants.h"
#include "cBall.h"

#include <AstuServices.h>
#include <AstuSuite2D.h>
#include <AstuECS.h>


class HandleBall
    :public astu::BaseService
    ,private astu2d::CollisionListener

{
    public:
     HandleBall(int updatePriority = astu::Priority::Normal);

    private:

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    void SpawnBall();
    
    static const astu:: EntityFamily FAMILY;
};