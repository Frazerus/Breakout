/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "EntityPrototypeService.h"
#include "Constants.h"
#include "cBall.h"
#include "cBlock.h"
#include "cPaddle.h"
#include "cDeath.h"
#include "cBound.h"


// AST-Utilities includes
#include <AstuSuite2D.h>

using namespace astu2d;
using namespace astu;
using namespace std;


EntityPrototypeService::EntityPrototypeService(bool debug)
	: BaseService("Entity Prototype Service")
	, debug(debug)
{
	// Intentionally left empty.    
}

void EntityPrototypeService::OnStartup()
{
	// Create and register entity prototypes.
	auto &entityFactory = ASTU_SERVICE(EntityFactoryService);

	// Register boundary entity prototypes.
	entityFactory.RegisterPrototype("HBoundary", CreateBoundary(WORLD_WIDTH, BOUNDARY_THICKNESS, false));
	entityFactory.RegisterPrototype("VBoundary", CreateBoundary(WORLD_WIDTH, WORLD_HEIGHT, false));
    entityFactory.RegisterPrototype("DBoundary", CreateBoundary(WORLD_WIDTH,BOUNDARY_THICKNESS, true));

	// Register entity prototypes.
	entityFactory.RegisterPrototype("Ball", createBall());
	entityFactory.RegisterPrototype("Block", createBlock());
	entityFactory.RegisterPrototype("Paddle", createPaddle());
}

void EntityPrototypeService::OnShutdown()
{
	  // Cleanup.
	  ASTU_SERVICE(EntityFactoryService).DeregisterAllPrototypes();
}

shared_ptr<Entity> EntityPrototypeService::CreateBoundary(float w, float h, bool kill)
{
	  auto entity = make_shared<Entity>();
	  entity->AddComponent(make_shared<CPose>());

      entity->AddComponent(make_shared<cBound>());


	entity->AddComponent(make_shared<CScene>(PolylineBuilder()
	    .Color(BOUNDARY_COLOR)
	    .VertexBuffer(ShapeGenerator().PolylineMode().GenRectangle(w, h))
	    .Build())
        );

	  entity->AddComponent(CBodyBuilder()
	      .Type(CBody::Type::Static)
	      .Build());

	  entity->AddComponent(CPolygonColliderBuilder()
	      .Polygon(ShapeGenerator().GenRectangle(w, h))
	      .Friction(0)
	      .Restitution(1)
		  .CategoryBits(BOUNDARY_CATEGORY)
	      .Build());
    if(kill){
        entity->AddComponent(make_shared<cDeath>());
    }
    

	  return entity;
}

shared_ptr<Entity> EntityPrototypeService::createBlock(){
	
    auto entity = make_shared<Entity>();

    entity-> AddComponent(make_shared<cBlock>());

    entity -> AddComponent(make_shared<CPose>());

    entity -> AddComponent(make_shared<CScene>(PolylineBuilder()
        .Color(BLOCK_COLOR)
        .VertexBuffer(ShapeGenerator().GenRectangleVb(BLOCK_X,BLOCK_Y))
        .Build()
        ));

    entity-> AddComponent(CBodyBuilder()
        .Type(CBody::Type::Static)
        .Build()
        );

    entity -> AddComponent(CPolygonColliderBuilder()
        .MakeRectangle(BLOCK_X, BLOCK_Y)
        .Friction(0)
        .CategoryBits(BLOCKS_CATEGORY)
        .MaskBits(BOUNDARY_CATEGORY | PADDLE_CATEGORY)
        .Build()
        );

		return entity;
}

shared_ptr<Entity> EntityPrototypeService::createBall(){

    auto entity = make_shared<Entity>();

    entity->AddComponent(make_shared<cBall>());

    entity->AddComponent(make_shared<CPose>(BALL_INIT_POS));

    entity->AddComponent(make_shared<CScene>(PolylineBuilder()
        .Color(BALL_COLOR)
        .VertexBuffer(ShapeGenerator().GenCircleVb(BALL_SIZE))
        .Build())

    );

    entity->AddComponent(CBodyBuilder()
        .Type(CBody::Type::Dynamic)
        .LinearDamping(BALL_DAMPENING)
        .LinearVelocity(0.0f,BALL_INITSPEED)
        .Build()
        );

    entity->AddComponent(CCircleColliderBuilder()
        .Radius(BALL_SIZE)
        .Friction(0)
		.Restitution(1)
        .CategoryBits(BALL_CATEGORY)
        .Build()
    );

	return entity;
}


shared_ptr<Entity> EntityPrototypeService::createPaddle(){

    shared_ptr<VertexBuffer2f> rect = ShapeGenerator().GenRectangleVb(PADDLE_X,PADDLE_Y);

	auto entity = make_shared<Entity>();

    entity->AddComponent(make_shared<cPaddle>());

    entity->AddComponent(make_shared<CPose>(0.0f,PADDLE_START_Y));

    entity->AddComponent(make_shared<CScene>(PolylineBuilder()
    .Color(PADDLE_COLOR)
    .VertexBuffer(rect)
    .Build())
    );

    entity->AddComponent(CBodyBuilder()
    .Type(CBody::Type::Kinematic)
    .Build()
    );

    entity->AddComponent(CPolygonColliderBuilder()
    .MakeRectangle(PADDLE_X, PADDLE_Y)
    .Friction(0)
    .CategoryBits(PADDLE_CATEGORY)
    .Build()
    );

	return entity;
}