#include "pch.h"

#include "ScreenManager.h"

#include "CarDescriptionUI.h"
#include "Image.h"
#include "Label.h"


//-----------------------------------------------------------------------------------------------------------------------------------
CarDescriptionUI::CarDescriptionUI(ID3D11Device* device, const std::string& carDataAsset) :
  Menu(device, ScreenManager::GetScreenDimensions(), Vector2(ScreenManager::GetScreenCentre().x, ScreenManager::GetScreenCentre().y * 0.5f), "", LoadType::kNoLoad),
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
  const Vector2 imageSize(80, 80);

  Image* image = new Image(imageSize, Vector2::Zero, m_carData->GetTextureAsset());
  AddUIObject(image);

  Label* carName = new Label(Vector2(0, -(100 + imageSize.y * 0.5f)), GenericUtils::CharToWChar(m_carData->GetDisplayName()), image);
  AddUIObject(carName);

  Label* carDescription = new Label(Vector2(0, 100 + imageSize.y * 0.5f), GenericUtils::CharToWChar(m_carData->GetDescription()), image);
  AddUIObject(carDescription);

  Label* accelerationLabel = new Label(Vector2(0, 100), L"Acceleration    " + std::to_wstring(m_carData->GetAcceleration()), carDescription);
  AddUIObject(accelerationLabel);

  Label* brakingLabel = new Label(Vector2(0, 50), L"Braking   " + std::to_wstring(m_carData->GetBraking()), accelerationLabel);
  AddUIObject(brakingLabel);

  Label* handlingLabel = new Label(Vector2(0, 50), L"Handling   " + std::to_wstring(m_carData->GetHandling()), brakingLabel);
  AddUIObject(handlingLabel);
}