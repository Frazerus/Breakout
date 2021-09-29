#pragma once

#include <AstuServices.h>
#include <AstuSuite2D.h>
#include <AstuECS.h>

class BlockCreator
    :public astu::BaseService
{
    public:
        BlockCreator();

    private:

    // Inherited via BaseService
        virtual void OnStartup() override;
        virtual void OnShutdown() override;

        void createBlocks();
        void createBlock(float x, float y);
};