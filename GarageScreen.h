#pragma once

#include "MenuScreen.h"

#include "CarData.h"
#include "CarDescriptionUI.h"
#include "DescriptionUIContainer.h"

class GarageScreen : public MenuScreen
{
public:
  GarageScreen(ScreenManager* screenManager, const std::string& dataAsset = "GarageScreen.xml");
  ~GarageScreen();

  void AddInitialUI() override;

private:
  DescriptionUIContainer* m_carDescriptionUIContainer;
};

