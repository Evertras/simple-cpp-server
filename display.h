#pragma once

#include "state.h"

class Display
{
  public:
    Display();
    ~Display();

    void draw(const State &snapshot);
};

