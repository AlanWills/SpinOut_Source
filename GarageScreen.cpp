#include "pch.h"

#include "PlayerData.h"

#include "ScreenManager.h"
#include "MainMenuScreen.h"
#include "GarageScreen.h"

#include "Button.h"


//-----------------------------------------------------------------------------------------------------------------------------------
GarageScreen::GarageScreen(ScreenManager* screenManager, const std::string& dataAsset) :
  MenuScreen(screenManager, dataAsset),
  m_carDescriptionUIContainer(nullptr)
{
  SetPreviousScreen(new MainMenuScreen(GetScreenManager()));
}


//-----------------------------------------------------------------------------------------------------------------------------------
GarageScreen::~GarageScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GarageScreen::AddInitialUI()
{
  MenuScreen::AddInitialUI();

  m_carDescriptionUIContainer = new DescriptionUIContainer(GetDevice());
  AddScreenUIObject(m_carDescriptionUIContainer);

  for (const std::string& carAsset : PlayerData::GetInstance().GetCarAssets())
  {
    CarDescriptionUI* carDescription = new CarDescriptionUI(GetDevice(), carAsset);
    m_carDescriptionUIContainer->AddDescriptionUI(carDescription);
  }

  Button* chooseCarButton = new Button(Vector2(GetScreenCentre().x, GetScreenDimensions().y - 100), L"Drive Car");
  chooseCarButton->SetClickFunction([this]()
  {
    std::string newCarAsset = PlayerData::GetInstance().GetCarAssets()[m_carDescriptionUIContainer->GetCurrentUIIndex()];
    PlayerData::GetInstance().SetCurrentCarAsset(newCarAsset);
  });

  AddScreenUIObject(chooseCarButton);
}