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
	entityFactory.RegisterPrototype("HBoundary", CreateBoundary(WORLD_WIDTH, BOUNDARY_THICKNESS));
	entityFactory.RegisterPrototype("VBoundary", CreateBoundary(BOUNDARY_THICKNESS, WORLD_HEIGHT));

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

shared_ptr<Entity> EntityPrototypeService::CreateBoundary(float w, float h)
{
	  auto entity = make_shared<Entity>();
	  entity->AddComponent(make_shared<CPose>());

	  if (debug) {
	      entity->AddComponent(make_shared<CScene>(PolylineBuilder()
	          .Color(BOUNDARY_COLOR)
	          .VertexBuffer(ShapeGenerator().PolylineMode().GenRectangle(w, h))
	          .Build()));
	  }

	  entity->AddComponent(CBodyBuilder()
	      .Type(CBody::Type::Static)
	      .Build());

	  entity->AddComponent(CPolygonColliderBuilder()
	      .Polygon(ShapeGenerator().GenRectangle(w, h))
	      .Friction(0)
	      .Restitution(1)
		  .CategoryBits(BOUNDARY_CATEGORY)
		  .MaskBits(0xFFFF)
	      .Build());

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
        .Build()
        );

		return entity;
}

shared_ptr<Entity> EntityPrototypeService::createBall(){

    auto entity = make_shared<Entity>();

    entity->AddComponent(make_shared<cBall>(BALL_MAXIMUM_SPEED));

    entity->AddComponent(make_shared<CPose>(0.0f,50.0f));

    entity->AddComponent(make_shared<CScene>(PolylineBuilder()
        .Color(BALL_COLOR)
        .VertexBuffer(ShapeGenerator().GenCircleVb(BALL_SIZE))
        .Build())

    );

    entity->AddComponent(CBodyBuilder()
        .Type(CBody::Type::Dynamic)
        .LinearDamping(BALL_DAMPENING)
        .LinearVelocity(0.0f,-BALL_INITSPEED)
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

	auto entity = make_shared<Entity>();

	return entity;
}