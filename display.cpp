#include <ncurses.h>
#include <iostream>

#include "display.h"
#include "state.h"

Display::Display()
{
  initscr();
  cbreak();
}

Display::~Display()
{
  endwin();
}

void Display::draw(const State &snapshot)
{
  char statusLine[256];

  clear();

  snprintf(
      statusLine,
      sizeof(statusLine),
      "(S)CV: %02d - (M)arines: %02d - Minerals: %04d",
      snapshot.scvCount,
      snapshot.marineCount,
      snapshot.mineralCount);

  mvprintw(0, 0, statusLine);

  refresh();
}

