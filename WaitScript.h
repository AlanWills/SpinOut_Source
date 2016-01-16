#pragma once

#include "Script.h"

class WaitScript : public Script
{
public:
  WaitScript(float timeToWaitFor, bool shouldUpdateGame, bool canRun = true);
  ~WaitScript();

  IMPLEMENT_SIMPLE_SCRIPT_RUN;

private:
  float m_time;
};