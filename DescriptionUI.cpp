#include "pch.h"

#include "DescriptionUI.h"
#include "ScreenManager.h"


//-----------------------------------------------------------------------------------------------------------------------------------
DescriptionUI::DescriptionUI(ID3D11Device* device) :
  Menu(device, ScreenManager::GetScreenDimensions(), Vector2::Zero)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
DescriptionUI::~DescriptionUI()
{
}