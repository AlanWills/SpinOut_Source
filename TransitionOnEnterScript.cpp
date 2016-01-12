#include "pch.h"

#include "TransitionOnEnterScript.h"


//-----------------------------------------------------------------------------------------------------------------------------------
TransitionOnEnterScript::TransitionOnEnterScript(ScreenManager* screenManager, BaseScreen* transitionTo, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_screenManager(screenManager),
  m_transitionTo(transitionTo)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
TransitionOnEnterScript::~TransitionOnEnterScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void TransitionOnEnterScript::HandleInput(float elapsedSeconds)
{
  if (IsRunning())
  {
    if (m_screenManager->GetKeyboardInput().IsKeyPressed(Keyboard::Keys::Enter))
    {
      SetCompleted(true);
      m_screenManager->Transition(m_screenManager->GetCurrentScreen(), m_transitionTo);
    }
  }
}