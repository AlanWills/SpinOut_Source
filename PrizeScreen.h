#pragma once

#include "BaseScreen.h"
#include "PrizeDescriptionUI.h"
#include "DescriptionUIContainer.h"

class PrizeScreen : public BaseScreen
{
private:
  typedef std::vector<Prize> Prizes;

public:
  PrizeScreen(const Prizes& prizes, ScreenManager* screenManager, const std::string& dataAsset = "PrizeScreen.xml");
  ~PrizeScreen();

  void AddInitialUI() override;

private:
  Prizes m_prizes;

  DescriptionUIContainer* m_prizeDescriptionUIContainer;
};

