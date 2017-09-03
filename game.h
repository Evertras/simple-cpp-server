#pragma once

#include "display.h"
#include "state.h"

class Game
{
  public:
    Game();
    ~Game();

    void run();

  private:
    Display display;
    State state;
    bool wantQuit;
    int frameCount;

    void update();
};

