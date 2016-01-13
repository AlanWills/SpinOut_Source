#pragma once

#include "MenuScreen.h"

#include "CarData.h"
#include "CarDescriptionUI.h"

class GarageScreen : public MenuScreen
{
public:
  GarageScreen(ScreenManager* screenManager, const std::string& dataAsset = "GarageScreen.xml");
  ~GarageScreen();

  void AddInitialUI() override;
  void Initialize() override;
  void HandleInput(float elapsedGameTime) override;

private:
  typedef std::pair<std::string, CarDescriptionUI*> CarInfo;
  typedef std::vector<CarInfo> CarInfos;

  void ShowCurrentCarUI();

  // Our current selected car
  size_t m_currentCar;

  // Map which holds the data asset for the car and the appropriate UI
  CarInfos m_carInfos;
};

