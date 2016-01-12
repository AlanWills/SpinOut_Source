#pragma once

#include "CarData.h"

#include "Menu.h"

class CarDescriptionUI : public Menu
{
public:
  CarDescriptionUI(ID3D11Device* device, const std::string& carDataAsset);
  ~CarDescriptionUI();

  void LoadContent(ID3D11Device* device) override;
  void AddInitialUI() override;

private:
  std::unique_ptr<CarData> m_carData;
};

