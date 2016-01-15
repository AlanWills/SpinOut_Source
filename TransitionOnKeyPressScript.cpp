#include "pch.h"

#include "TransitionOnKeyPressScript.h"


//-----------------------------------------------------------------------------------------------------------------------------------
TransitionOnKeyPressScript::TransitionOnKeyPressScript(ScreenManager* screenManager, BaseScreen* transitionTo, Keyboard::Keys key, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_screenManager(screenManager),
  m_transitionTo(transitionTo),
  m_key(key)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
TransitionOnKeyPressScript::~TransitionOnKeyPressScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void TransitionOnKeyPressScript::HandleInput(float elapsedSeconds)
{
  if (IsRunning())
  {
    if (m_key == Keyboard::Keys::NumKeys || m_screenManager->GetKeyboardInput().IsKeyPressed(m_key))
    {
      SetCompleted(true);
      m_screenManager->Transition(m_screenManager->GetCurrentScreen(), m_transitionTo);
    }
  }
}