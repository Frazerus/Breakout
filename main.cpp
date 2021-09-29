/** 
 * Example Application: 2D Scene Graph Demo #3
 * 
 * @file main.cpp
 * @version 1.0.0
 * @author Roman Divotkey
 * @copyright MIT License
 */

// Local includes
#include "MainService.h"
#include "HandleBall.h"
#include "HandleBlock.h"
#include "BlockCreator.h"
#include "cBall.h"


// AST Utilities includes
#include <AstuSuiteSDL.h>
#include <AstuInput.h>
#include <AstuECS.h>
#include <AstuSuite2D.h>

// ASTU/Box2D includes
#include <AstuBox2D.h>

// C++ Standard Library includes
#include <iostream>
#include <stdexcept>

using namespace astu2d;
using namespace astu;
using namespace std;

// Main entry point of the application.
int main()
{
    SdlApplication app;
    

    ASTU_CREATE_AND_ADD_SERVICE(CameraService);
    ASTU_CREATE_AND_ADD_SERVICE(CameraControlService);

    ASTU_CREATE_AND_ADD_SERVICE(EntityService);
    ASTU_CREATE_AND_ADD_SERVICE(GameEventService);
    ASTU_CREATE_AND_ADD_SERVICE(SceneSystem);
	ASTU_CREATE_AND_ADD_SERVICE(Box2DPhysicsSystem);
	ASTU_CREATE_AND_ADD_SERVICE(CollisionSignalService);



    // Let's add our main service that runs the application.
    ASTU_CREATE_AND_ADD_SERVICE(MainService);
    ASTU_CREATE_AND_ADD_SERVICE(HandleBall);
    ASTU_CREATE_AND_ADD_SERVICE(HandleBlock);
    ASTU_CREATE_AND_ADD_SERVICE(BlockCreator);
    



    app.SetApplicationName("Breakout-Clone");
    app.SetVersionString("1.0.0");
    // Run the application.
    try {
        app.Run();
    }
    catch (const runtime_error & e) {
        cerr << e.what() << endl;
        return -1;
    }
    catch (const logic_error & e) {
        cerr << "programmer error: " << e.what() << endl;
        return -1;
    }

    return 0;
} 