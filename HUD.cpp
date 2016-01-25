#include "pch.h"

#include "HUD.h"
#include "ScreenManager.h"


//-----------------------------------------------------------------------------------------------------------------------------------
HUD::HUD(ID3D11Device* device) :
  UIPanel(device, ScreenManager::GetScreenDimensions(), ScreenManager::GetScreenCentre())
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
HUD::~HUD()
{
}