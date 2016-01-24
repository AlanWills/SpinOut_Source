#pragma once

#include "DescriptionUI.h"

struct Prize
{
  std::string m_name;
  std::string m_textureAsset;
  std::string m_description;
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