#pragma once

#include "WaitForKeyPressScript.h"

#include "ScreenManager.h"

class TransitionOnKeyPressScript : public WaitForKeyPressScript
{
public:
  /// \brief Use Keys::NumKeys for automatic transition with no key press wait
  TransitionOnKeyPressScript(ScreenManager* screenManager, BaseScreen* transitionTo, Keyboard::Keys key, bool shouldUpdateGame = true, bool canRun = true);
  ~TransitionOnKeyPressScript();

  IMPLEMENT_SIMPLE_SCRIPT_HANDLE_INPUT;

private:
  ScreenManager* m_screenManager;
  BaseScreen* m_transitionTo;
};

