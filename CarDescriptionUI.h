#pragma once

#include "CarData.h"

#include "DescriptionUI.h"

class CarDescriptionUI : public DescriptionUI
{
public:
  CarDescriptionUI(ID3D11Device* device, const std::string& carDataAsset);
  ~CarDescriptionUI();

  void LoadContent(ID3D11Device* device) override;
  void AddInitialUI() override;

private:
  std::unique_ptr<CarData> m_carData;
};

