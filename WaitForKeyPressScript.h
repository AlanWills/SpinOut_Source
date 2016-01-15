#pragma once

#include "Script.h"

class WaitForKeyPressScript : public Script
{
public:
  WaitForKeyPressScript(Keyboard::Keys key, bool shouldUpdateGame, bool canRun = true);
  ~WaitForKeyPressScript();

  IMPLEMENT_SIMPLE_SCRIPT_HANDLE_INPUT;

private:
  Keyboard::Keys m_keyToPress;
};

