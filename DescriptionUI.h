#pragma once

#include "Menu.h"

class DescriptionUI : public Menu
{
public:
  DescriptionUI(ID3D11Device* device);
  ~DescriptionUI();

protected:
  void AddImage(const std::string& imageAsset);
  void AddName(const std::string& name);
  void AddDescription(const std::string& description);
};

