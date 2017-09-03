#include <iostream>
#include <ncurses.h>

#include "game.h"

using namespace std;

int main()
{
  Game g = Game();

  g.run();

  return 0;
}

