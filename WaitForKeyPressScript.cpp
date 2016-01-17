#include "pch.h"

#include "WaitForKeyPressScript.h"
#include "ScreenManager.h"


//-----------------------------------------------------------------------------------------------------------------------------------
WaitForKeyPressScript::WaitForKeyPressScript(Keyboard::Keys key, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_keyToPress(key)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
WaitForKeyPressScript::~WaitForKeyPressScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void WaitForKeyPressScript::HandleInput(float elapsedSeconds)
{
  if (IsRunning())
  {
    SetCompleted(m_keyToPress == Keyboard::Keys::NumKeys || ScreenManager::GetKeyboardInput().IsKeyPressed(m_keyToPress));
  }
}