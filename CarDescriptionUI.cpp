#include "pch.h"

#include "ScreenManager.h"

#include "CarDescriptionUI.h"
#include "Image.h"
#include "Label.h"


//-----------------------------------------------------------------------------------------------------------------------------------
CarDescriptionUI::CarDescriptionUI(ID3D11Device* device, const std::string& carDataAsset) :
  Menu(device, ScreenManager::GetScreenDimensions(), ScreenManager::GetScreenCentre(), "", LoadType::kNoLoad),
  m_carData(new CarData(carDataAsset))
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
CarDescriptionUI::~CarDescriptionUI()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void CarDescriptionUI::LoadContent(ID3D11Device* device)
{
  // Must be called in this order
  m_carData->LoadData();

  Menu::LoadContent(device);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void CarDescriptionUI::AddInitialUI()
{
  Image* image = new Image(Vector2(80, 80), Vector2::Zero, m_carData->GetTextureAsset());
  AddUIObject(image);

  Label* carName = new Label(Vector2(0, -(100 + image->GetSize().y * 0.5f)), GenericUtils::CharToWChar(m_carData->GetDisplayName()), image);
  AddUIObject(carName);

  Label* carDescription = new Label(Vector2(0, 100 + image->GetSize().y * 0.5f), GenericUtils::CharToWChar(m_carData->GetDescription()), image);
  AddUIObject(carDescription);
}