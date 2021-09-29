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


const astu::EntityFamily HandleBall::FAMILY = EntityFamily::Create<cBall, CPose, CBody>();

HandleBall::HandleBall(int updatePriority)
    :BaseService("Ball HandlerService")
    ,IteratingEntitySystem(FAMILY, updatePriority)
{

}

void HandleBall::OnStartup() {
    SpawnBall();
}

void HandleBall::OnShutdown() {

}

void HandleBall::SpawnBall(){
    auto entity = make_shared<Entity>();
    entity->AddComponent(make_shared<cBall>(BALL_MAXIMUM_SPEED));

    entity->AddComponent(make_shared<CPose>(0.0f,100.0f));

    entity->AddComponent(make_shared<CScene>(PolylineBuilder()
        .Color(BALL_COLOR)
        .VertexBuffer(ShapeGenerator().GenCircleVb(BALL_SIZE))
        .Build())

    );

    entity->AddComponent(CBodyBuilder()
        .Type(CBody::Type::Dynamic)
        .LinearDamping(0)
        .AngularDamping(0)
        .Build()
        );
    entity->AddComponent(CCircleColliderBuilder()
        .Radius(BALL_SIZE)
        .Friction(0)
		.Restitution(1)
        .CategoryBits(BALL_CATEGORY)
        .Build()
    );
    ASTU_SERVICE(EntityService).AddEntity(entity);
}

    void HandleBall::ProcessEntity(Entity &entity){
    auto& body = entity.GetComponent<CBody>();
    body.SetLinearVelocity(0,-25);

}

void HandleBall::ChangeDirection(Entity &ball, Entity &collided){
    //change the balls velocity depending on where the ball hit the other object
    auto bpos = ball.GetComponent<CPose>().transform.GetTranslation();
    auto cpos = collided.GetComponent<CPose>().transform.GetTranslation();

    Vector2f diff = bpos - cpos;
    std::cout<< diff.x << " " << diff.y;
}

bool HandleBall::OnCollision(Entity &entityA, Entity &entityB){
    if(entityA.HasComponent<cBall>()){
        ChangeDirection(entityA, entityB);
    }
    if(entityB.HasComponent<cBall>()){
        ChangeDirection(entityB,entityA);
    }
    return false;
    //change Current movement:
    //if thing is dynamic: change ball velocity accordingly
    //
}

//TODO: CREATE COLLISION STUFF BECAUSE CURRENTLY ITS NOT WORKING

