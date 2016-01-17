#pragma once

#include "BaseScreen.h"

class LoadingScreen : public BaseScreen
{
public:
  LoadingScreen(ScreenManager* screenManager, BaseScreen* screenToTransitionTo, const std::string& dataAsset = "LoadingScreen.xml");
  ~LoadingScreen();

  void Begin() override;

private:
  BaseScreen* m_screenToTransitionTo;
};

