#include "pch.h"

#include "ScreenManager.h"

#include "PrizeDescriptionUI.h"
#include "Image.h"
#include "Label.h"


//-----------------------------------------------------------------------------------------------------------------------------------
PrizeDescriptionUI::PrizeDescriptionUI(ID3D11Device* device, const Prize& prize) :
  DescriptionUI(device),
  m_prize(prize)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
PrizeDescriptionUI::~PrizeDescriptionUI()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void PrizeDescriptionUI::AddInitialUI()
{
  DescriptionUI::AddInitialUI();

  float ySpacing = ScreenManager::GetScreenDimensions().y * 0.08f;

  Image* prizeImage = new Image(Vector2::Zero, m_prize.m_asset);
  AddUIObject(prizeImage, true);

  Label* prizeName = new Label(Vector2(0, -prizeImage->GetSize().y * 0.5f - ySpacing), GenericUtils::CharToWChar(m_prize.m_name.c_str()), prizeImage);
  AddUIObject(prizeName);

  Label* prizeDescription = new Label(Vector2(0, prizeImage->GetSize().x * 0.5f + ySpacing), GenericUtils::CharToWChar(m_prize.m_description.c_str()), prizeImage);
  AddUIObject(prizeDescription);
}