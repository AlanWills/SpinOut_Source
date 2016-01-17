#include "pch.h"

#include "LoadingScreen.h"

#include "WaitScript.h"
#include "TransitionOnKeyPressScript.h"


//-----------------------------------------------------------------------------------------------------------------------------------
LoadingScreen::LoadingScreen(ScreenManager* screenManager, BaseScreen* screenToTransitionTo, const std::string& dataAsset) :
  BaseScreen(screenManager, dataAsset),
  m_screenToTransitionTo(screenToTransitionTo)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
LoadingScreen::~LoadingScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void LoadingScreen::Begin()
{
  BaseScreen::Begin();

  // Because we are calling transition, this should load and initialize the screen if we need to
  // but don't want to immediately show it - a nice pause for effect (could be removed at a later date
  // if we load larger stuff)
  AddScript(new WaitScript(1, false));
  AddScript(new TransitionOnKeyPressScript(GetScreenManager(), m_screenToTransitionTo, Keyboard::Keys::NumKeys), false);
}