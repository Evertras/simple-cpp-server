#pragma once

#include <ncurses.h>

#include "state.h"

class Display
{
  public:
    Display();
    ~Display();

    void draw(const State &snapshot);
};

