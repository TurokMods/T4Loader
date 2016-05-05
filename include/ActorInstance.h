#pragma once
#include "ATITypes.h"

namespace T4
{
    class ATIBlock;
    class ActorInstance
    {
        public:
            ActorInstance() { }
            ~ActorInstance() { }
        
            bool Load(ATIBlock* Parent,string& Error,size_t& Pos);
            bool Save(ATIBlock* Parent,string& Error,size_t& Pos);
    };
};

