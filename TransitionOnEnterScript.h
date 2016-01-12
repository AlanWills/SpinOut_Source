#pragma once

#include "Script.h"

#include "ScreenManager.h"

class TransitionOnEnterScript : public Script
{
public:
  TransitionOnEnterScript(ScreenManager* screenManager, BaseScreen* transitionTo, bool shouldUpdateGame = true, bool canRun = true);
  ~TransitionOnEnterScript();

  IMPLEMENT_SIMPLE_SCRIPT_HANDLE_INPUT

private:
  ScreenManager* m_screenManager;
  BaseScreen* m_transitionTo;
};

