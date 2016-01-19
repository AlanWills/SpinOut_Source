#pragma once

#include "BaseScreen.h"
#include "PrizeDescriptionUI.h"

class PrizeScreen : public BaseScreen
{
private:
  typedef std::list<Prize> Prizes;

public:
  PrizeScreen(const Prizes& prizes, ScreenManager* screenManager, const std::string& dataAsset = "PrizeScreen.xml");
  ~PrizeScreen();

  void AddInitialUI() override;

private:
  Prizes m_prizes;
};

