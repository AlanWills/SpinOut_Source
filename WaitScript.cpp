#include "pch.h"

#include "WaitScript.h"


//-----------------------------------------------------------------------------------------------------------------------------------
WaitScript::WaitScript(float timeToWaitFor, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_time(timeToWaitFor)
{
  assert(timeToWaitFor >= 0);
}


//-----------------------------------------------------------------------------------------------------------------------------------
WaitScript::~WaitScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void WaitScript::Run(float elapsedSeconds)
{
  Script::Run(elapsedSeconds);

  if (IsRunning())
  {
    bool done = m_time <= GetTimeRunFor();
    SetCompleted(done);
  }
}