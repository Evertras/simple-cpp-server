#pragma once

#include <queue>
#include <vector>

#include "action.h"
#include "display.h"
#include "state.h"

class Game
{
  public:
    Game();
    ~Game();

    void run();

  private:

    class ExecutedAction
    {
      public:
        ExecutedAction(int frame, const Action* action, const State &state)
          : frame(frame), action(action), state(state)
        {
        }

        int getFrame() const { return frame; }
        const Action* getAction() const { return action; }
        const State& getResultingState() const { return state; }

      private:
        int frame;
        const Action* action;
        const State &state;
    };

    Display display;
    State state;
    bool wantQuit;
    int frameCount;
    std::queue<Action*> pendingActions;
    std::vector<ExecutedAction> executedActions;

    void update();
    void runPendingActions();
};

