#pragma once

#include "BaseScreen.h"

#define LOGO_ASSET "Logo.png"

class StartupLogoScreen : public BaseScreen
{
public:
  StartupLogoScreen(ScreenManager* screenManager, const std::string& dataAsset = "StartupLogoScreen.xml");
  ~StartupLogoScreen();

  void AddInitialScripts() override;
  void AddInitialUI() override;
};

