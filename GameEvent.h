#pragma once

#include <AstuServices.h>

class GameEvent {
    public:

    enum class Type {
        BallOut,
        AllBlocksDestroyed,
        BlockDestroyed,
        BlocksCreated
    };

    Type type;

    int intValue;

    GameEvent(Type t): type(t), intValue(0)
    {
       
    }

    GameEvent(Type t, int val): type(t), intValue(val)
    {

    }

    static GameEvent CreateLifeUpdate(int numLifes){
        GameEvent result = GameEvent(Type::BallOut);
        result.intValue = numLifes;
        return result;
    }
};


using GameEventService = astu::SignalService<GameEvent>;