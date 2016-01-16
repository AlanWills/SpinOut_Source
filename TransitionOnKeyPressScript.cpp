#include "pch.h"

#include "TransitionOnKeyPressScript.h"


//-----------------------------------------------------------------------------------------------------------------------------------
TransitionOnKeyPressScript::TransitionOnKeyPressScript(ScreenManager* screenManager, BaseScreen* transitionTo, Keyboard::Keys key, bool shouldUpdateGame, bool canRun) :
  WaitForKeyPressScript(key, shouldUpdateGame, canRun),
  m_screenManager(screenManager),
  m_transitionTo(transitionTo)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
TransitionOnKeyPressScript::~TransitionOnKeyPressScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void TransitionOnKeyPressScript::HandleInput(float elapsedSeconds)
{
  WaitForKeyPressScript::HandleInput(elapsedSeconds);

  if (IsRunning())
  {
    if (IsCompleted())
    {
      m_screenManager->Transition(m_screenManager->GetCurrentScreen(), m_transitionTo);
    }
  }
}