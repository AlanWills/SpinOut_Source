#pragma once

#include "BaseScreen.h"

class MenuScreen : public BaseScreen
{
public:
  MenuScreen(ScreenManager* screenManager, const std::string& dataAsset);
  ~MenuScreen();

  void HandleInput(float elapsedSeconds);

protected:
  void SetPreviousScreen(BaseScreen* previousScreen) { m_previousScreen = previousScreen; }

private:
  BaseScreen* m_previousScreen;
};

