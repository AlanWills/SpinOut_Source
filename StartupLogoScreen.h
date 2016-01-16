#pragma once

#include "BaseScreen.h"

class StartupLogoScreen : public BaseScreen
{
public:
  StartupLogoScreen(ScreenManager* screenManager, const std::string& dataAsset = "StartuptLogoScreen.xml");
  ~StartupLogoScreen();
};

