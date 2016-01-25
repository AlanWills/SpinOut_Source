#pragma once

#include "UIPanel.h"

class HUD : public UIPanel
{
public:
  HUD(ID3D11Device* device);
  ~HUD();
};

