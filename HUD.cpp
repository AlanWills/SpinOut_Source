#include "pch.h"

#include "HUD.h"
#include "ScreenManager.h"


//-----------------------------------------------------------------------------------------------------------------------------------
HUD::HUD(ID3D11Device* device) :
  Menu(device, ScreenManager::GetScreenDimensions(), ScreenManager::GetScreenCentre(), "", LoadType::kNoLoad)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
HUD::~HUD()
{
}