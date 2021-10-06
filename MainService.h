#pragma once

#include "GameEvent.h"

// AST Utilities includes
#include <AstuServices.h>
#include <AstuSuite2D.h>
#include <AstuECS.h>

class MainService 
    : public astu::BaseService
	, private astu2d::CameraClient
	, private astu::EntityFactoryClient
    ,private astu::SignalEmitter<GameEvent>
    ,private astu::SignalListener<GameEvent>
{
public:
    
    /** Constructor. */
    MainService(int updatePriority = astu::Priority::Normal);

private:

    static const astu:: EntityFamily FAMILY;

    int numOfBlocks;

    int numLifes;

    void UpdateLife(int deltaLife = 0);



    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;


    virtual bool OnSignal(const GameEvent & signal) override;

    /**
     * Returns the current center of the screen.
     * 
     * @return the center of the screen in screen coordinates
     */
    astu::Vector2f GetCenter();
};