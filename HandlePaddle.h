#pragma once

#include "constants.h"
#include "cPaddle.h"

#include <AstuServices.h>
#include <AstuSuite2D.h>
#include <AstuECS.h>


class HandlePaddle
    :public astu::BaseService
    ,private astu::IteratingEntitySystem
    ,private astu2d::CollisionListener

{
    public:
     HandlePaddle(int updatePriority = astu::Priority::Normal);

    private:
    
	static const astu::EntityFamily FAMILY;

    
	std::shared_ptr<astu::AxisBinding> moveAxis;

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    void HandleBallColl(astu::Entity& Ball, astu::Entity& Paddle);
    
	virtual void ProcessEntity(astu::Entity& entity) override;

    
    virtual bool OnCollision(astu::Entity& entityA, astu::Entity& entityB) override;


};