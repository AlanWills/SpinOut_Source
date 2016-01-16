#pragma once

#include "BaseScreen.h"

class LoadingScreen : public BaseScreen
{
public:
  LoadingScreen(ScreenManager* screenManager, const std::string& dataAsset = "LoadingScreen.xml");
  ~LoadingScreen();
};

