#pragma once


#include <AstuECS.h>

class cBound : public astu::EntityComponent
     {
    public:



    cBound()
    {
            //intentionally left empty
    }


    virtual std::shared_ptr<EntityComponent> Clone() override {
        return std::make_shared<cBound>(*this);
    }

};