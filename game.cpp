#include <chrono>
#include <thread>
#include <ncurses.h>

#include "game.h"

using namespace std::chrono;
using namespace std::this_thread;

const nanoseconds UPDATE_STEP = duration_cast<nanoseconds>(milliseconds(10));
const nanoseconds DRAW_STEP_TARGET = duration_cast<nanoseconds>(milliseconds(100));

Game::Game()
{
  notimeout(stdscr, TRUE);
  wantQuit = false;
}

Game::~Game()
{
}

void Game::run()
{
  high_resolution_clock::time_point last = high_resolution_clock::now();
  nanoseconds lag(0);

  state.scvCount = 1;
  state.marineCount = 1;
  state.mineralCount = 0;
  frameCount = 0;

  while (!wantQuit) {
    auto start = high_resolution_clock::now();

    lag += duration_cast<nanoseconds>(start - last);

    while (lag > UPDATE_STEP) {
      lag -= UPDATE_STEP;
      update();
    }

    auto remaining = DRAW_STEP_TARGET - (high_resolution_clock::now() - start);
    last = start;

    sleep_for(remaining);

    display.draw(state);
  }
}

void Game::update()
{
  ++frameCount;
  auto c = getch();

  switch (c) {
    case 's':
      if (state.mineralCount >= 50)
      {
        state.mineralCount -= 50;
        state.scvCount += 1;
      }
      break;

    case 'm':
      if (state.mineralCount >= 50)
      {
        state.mineralCount -= 50;
        state.marineCount += 1;
      }
      break;

    case 'q':
      wantQuit = true;
      break;
  }


  if (frameCount % 100 == 0)
  {
    state.mineralCount += state.scvCount * 5;
  }
}

