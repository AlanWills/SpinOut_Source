#include "pch.h"

#include "WaitScript.h"


//-----------------------------------------------------------------------------------------------------------------------------------
WaitScript::WaitScript(float timeToWaitFor, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_time(timeToWaitFor)
{
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
    SetCompleted(m_time >= GetTimeRunFor());
  }
}