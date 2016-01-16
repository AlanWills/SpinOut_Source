#include "pch.h"
#include "LoadingScreen.h"


//-----------------------------------------------------------------------------------------------------------------------------------
LoadingScreen::LoadingScreen(ScreenManager* screenManager, const std::string& dataAsset = "LoadingScreen.xml") :
  BaseScreen(screenManager, dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
LoadingScreen::~LoadingScreen()
{
}
