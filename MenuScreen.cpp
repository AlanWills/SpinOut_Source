#include "pch.h"

#include "ScreenManager.h"
#include "MenuScreen.h"


//-----------------------------------------------------------------------------------------------------------------------------------
MenuScreen::MenuScreen(ScreenManager* screenManager, const std::string& dataAsset) :
  BaseScreen(screenManager, dataAsset),
  m_previousScreen(nullptr)
{
  ScreenManager::GetCamera().Reset();
  ScreenManager::GetCamera().SetCameraMode(Camera::CameraMode::kFixed);
}


//-----------------------------------------------------------------------------------------------------------------------------------
MenuScreen::~MenuScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void MenuScreen::HandleInput(float elapsedSeconds)
{
  BaseScreen::HandleInput(elapsedSeconds);

  if (IsActive())
  {
    if (m_previousScreen, ScreenManager::GetKeyboardInput().IsKeyPressed(Keyboard::Keys::Escape))
    {
      Transition(m_previousScreen);
    }
  }
}