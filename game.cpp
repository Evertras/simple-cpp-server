#include <chrono>
#include <thread>
#include <iostream>

#include "game.h"

using namespace std::chrono;
using namespace std::this_thread;

const nanoseconds UPDATE_STEP = duration_cast<nanoseconds>(milliseconds(100));
const nanoseconds DRAW_STEP_TARGET = duration_cast<nanoseconds>(milliseconds(100));

Game::Game()
{
}

Game::~Game()
{
}

void Game::run()
{
  std::cout << "Starting..." << std::endl;

  high_resolution_clock::time_point last = high_resolution_clock::now();
  nanoseconds lag(0);

  while (true) {
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
  state.mineralCount += 1;
}

