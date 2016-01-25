#pragma once

#include "DescriptionUI.h"

enum PrizeType
{
  kCar,
  kLicenseLevel
};

struct Prize
{
  std::string m_name;
  PrizeType m_type;
  std::string m_asset;
  std::string m_description;
  int m_data;
};

class PrizeDescriptionUI : public DescriptionUI
{
public:
  PrizeDescriptionUI(ID3D11Device* device, const Prize& prize);
  ~PrizeDescriptionUI();

  void AddInitialUI() override;

private:
  Prize m_prize;
};