#include "pch.h"

#include "ScreenManager.h"

#include "PrizeDescriptionUI.h"
#include "Image.h"
#include "Label.h"


//-----------------------------------------------------------------------------------------------------------------------------------
PrizeDescriptionUI::PrizeDescriptionUI(ID3D11Device* device, const Vector2& size, const Vector2& position, const Prize& prize) :
  Menu(device, size, position, "", LoadType::kNoLoad),
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
  float ySpacing = ScreenManager::GetScreenDimensions().y * 0.8f;

  Image* prizeImage = new Image(Vector2::Zero, m_prize.m_textureAsset);
  AddUIObject(prizeImage, true);

  Label* prizeName = new Label(Vector2(0, -prizeImage->GetSize().y * 0.5f - ySpacing), m_prize.m_name, prizeImage);
  AddUIObject(prizeName);

  Label* prizeDescription = new Label(Vector2(0, prizeImage->GetSize().x * 0.5f), m_prize.m_description, prizeImage);
  AddUIObject(prizeDescription);
}