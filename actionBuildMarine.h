#pragma once

#include "action.h"

class ActionBuildMarine : public Action
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
      ++mutated.marineCount;

      return mutated;
    }

    virtual const char* getName() const
    {
      return "ActionBuildMarine";
    }
};

