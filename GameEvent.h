#pragma once

#include <AstuServices.h>

class GameEvent {
    public:

    enum class Type {
        BallOut,
        AllBlocksDestroyed,
        BlockDestroyed
    };

    Type type;

    int intValue;

    GameEvent(Type t): type(t){

    }

    static GameEvent CreateLifeUpdate(int numLifes){
        GameEvent result = GameEvent(Type::BallOut);
        result.intValue = numLifes;
        return result;
    }
};


using GameEventService = astu::SignalService<GameEvent>;