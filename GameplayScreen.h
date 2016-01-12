#pragma once

#include "BaseScreen.h"

#include "HUD.h"

class GameplayScreen : public BaseScreen
{
public:
  GameplayScreen(ScreenManager* screenManager, const std::string& dataAsset);
  ~GameplayScreen();

protected:
  const HUD* ConstGetHUD() const { m_hud.get(); }
  HUD* GetHUD() { return m_hud.get(); }

private:
  std::unique_ptr<HUD> m_hud;
};

