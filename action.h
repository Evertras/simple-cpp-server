#pragma once

#include "state.h"

class Action
{
  public:
    virtual ~Action()
    {
    }

    virtual bool canAct(const State &state) const = 0;
    virtual State actOn(const State &state) const = 0;
    virtual const char* getName() const = 0;
};

