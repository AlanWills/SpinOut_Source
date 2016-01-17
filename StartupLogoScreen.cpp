#include "pch.h"

#include "StartupLogoScreen.h"
#include "MainMenuScreen.h"

#include "WaitScript.h"
#include "TransitionOnKeyPressScript.h"



//-----------------------------------------------------------------------------------------------------------------------------------
StartupLogoScreen::StartupLogoScreen(ScreenManager* screenManager, const std::string& dataAsset) :
  BaseScreen(screenManager, dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
StartupLogoScreen::~StartupLogoScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void StartupLogoScreen::AddInitialScripts()
{
  AddScript(new WaitScript(3, true));
  AddScript(new TransitionOnKeyPressScript(GetScreenManager(), new MainMenuScreen(GetScreenManager()), Keyboard::Keys::NumKeys));
}