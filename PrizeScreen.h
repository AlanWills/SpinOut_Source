#pragma once

#include "BaseScreen.h"

class PrizeScreen : public BaseScreen
{
public:
  PrizeScreen(ScreenManager* screenManager, const std::string& dataAsset = "PrizeScreen.xml");
  ~PrizeScreen();

  void AddInitialUI() override;
};

