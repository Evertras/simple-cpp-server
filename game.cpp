#include <chrono>
#include <thread>
#include <ncurses.h>

#include "game.h"

#include "actionBuildSCV.h"
#include "actionBuildMarine.h"
#include "actionMineralTick.h"

using namespace std::chrono;
using namespace std::this_thread;

const nanoseconds UPDATE_STEP =
  duration_cast<nanoseconds>(milliseconds(10));

const nanoseconds DRAW_STEP_TARGET =
  duration_cast<nanoseconds>(milliseconds(100));

Game::Game()
{
  notimeout(stdscr, TRUE);
  wantQuit = false;
}

Game::~Game()
{
  while (!pendingActions.empty())
  {
    delete pendingActions.front();
    pendingActions.pop();
  }

  for (auto a : executedActions)
  {
    delete a.getAction();
  }

  executedActions.clear();
}

void Game::run()
{
  high_resolution_clock::time_point last = high_resolution_clock::now();
  nanoseconds accumulatedLag(0);

  state.scvCount = 1;
  state.marineCount = 0;
  state.mineralCount = 0;
  frameCount = 0;

  while (!wantQuit) {
    auto start = high_resolution_clock::now();

    accumulatedLag += duration_cast<nanoseconds>(start - last);

    while (accumulatedLag > UPDATE_STEP) {
      accumulatedLag -= UPDATE_STEP;
      update();
      runPendingActions();
    }

    auto remaining = DRAW_STEP_TARGET - (high_resolution_clock::now() - start);
    last = start;

    sleep_for(remaining);

    display.draw(state);
  }

  clear();

  // Cheaty for now to print some debug info after run
  char statusLine[256];

  auto i = 0;
  for (auto e : executedActions) {
    snprintf(
        statusLine,
        sizeof(statusLine),
        "%05d %s",
        e.getFrame(),
        e.getAction()->getName());
    mvprintw(i++, 0, statusLine);
  }

  notimeout(stdscr, FALSE);
  getch();
}

void Game::update()
{
  ++frameCount;

  if (frameCount % 100 == 0)
  {
    pendingActions.push(new ActionMineralTick());
  }

  auto c = getch();

  switch (c) {
    case 's':
      pendingActions.push(new ActionBuildSCV());
      break;

    case 'm':
      pendingActions.push(new ActionBuildMarine());
      break;

    case 'q':
      wantQuit = true;
      break;
  }
}

void Game::runPendingActions()
{
  while (!pendingActions.empty())
  {
    auto pending = pendingActions.front();

    if (pending->canAct(state))
    {
      auto mutated = pending->actOn(state);

      executedActions.push_back(ExecutedAction(frameCount, pending, mutated));

      state = mutated;
    }

    pendingActions.pop();
  }
}

