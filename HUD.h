#pragma once

#include "Menu.h"

class HUD : public Menu
{
public:
  HUD(ID3D11Device* device);
  ~HUD();
};

