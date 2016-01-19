#pragma once

#include "Menu.h"

struct Prize
{
  std::wstring m_name;
  std::string m_textureAsset;
  std::wstring m_description;
};

class PrizeDescriptionUI : public Menu
{
public:
  PrizeDescriptionUI(ID3D11Device* device, const Vector2& size, const Vector2& position, const Prize& prize);
  ~PrizeDescriptionUI();

  void AddInitialUI() override;

private:
  Prize m_prize;
};