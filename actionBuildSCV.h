#pragma once

#include "action.h"

class ActionBuildSCV : public Action
{
  public:
    virtual bool canAct(const State &state) const
    {
      return state.mineralCount >= 50;
    }

    virtual State actOn(const State &state) const
    {
      State mutated = state;

      mutated.mineralCount -= 50;
      ++mutated.scvCount;

      return mutated;
    }


    virtual const char* getName() const
    {
      return "ActionBuildSCV";
    }
};

