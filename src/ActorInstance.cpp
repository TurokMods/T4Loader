#include "T4Loader/ActorInstance.h"
#include "T4Loader/ATI.h"

namespace T4
{
    bool ActorInstance::Load(ATIBlock* Parent,string& Error,size_t& Pos)
    {
        return true;
    }
    bool ActorInstance::Save(ATIBlock* Parent,string& Error,size_t& Pos)
    {
        return false;
    }
};
