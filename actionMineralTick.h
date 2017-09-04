#pragma once

#include "action.h"

class ActionMineralTick : public Action
{
  public:
    virtual bool canAct(const State &state) const
    {
      return true;
    }

    virtual State actOn(const State &state) const
    {
      State mutated = state;

      mutated.mineralCount += state.scvCount * 5;

      return mutated;
    }

    virtual const char* getName() const
    {
      return "ActionMineralTick";
    }
};

