#pragma once

#include "BlockCreator.h"
#include "cBlock.h"
#include "constants.h"

#include <AstuServices.h>
#include <AstuSuite2D.h>
#include <AstuECS.h>

using namespace astu2d;
using namespace astu;
using namespace std;

BlockCreator::BlockCreator()
    :BaseService("BlockCreator Service")
{

}


void BlockCreator::OnStartup(){
    createBlocks();
}

void BlockCreator::OnShutdown(){

}

void BlockCreator::createBlocks(){
    createBlock(0,0);
}

void BlockCreator::createBlock(float x, float y){
    auto entity = make_shared<Entity>();
    entity-> AddComponent(make_shared<cBlock>());
    entity -> AddComponent(make_shared<CPose>(x,y));
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
    ASTU_SERVICE(EntityService).AddEntity(entity);
}