#include "pch.h"

#include "ScreenManager.h"
#include "PrizeScreen.h"

#include "Label.h"


//-----------------------------------------------------------------------------------------------------------------------------------
PrizeScreen::PrizeScreen(const Prizes& prizes, ScreenManager* screenManager, const std::string& dataAsset) :
  BaseScreen(screenManager, dataAsset),
  m_prizes(prizes)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
PrizeScreen::~PrizeScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void PrizeScreen::AddInitialUI()
{
  BaseScreen::AddInitialUI();

  const Vector2& screenDimensions = ScreenManager::GetScreenDimensions();

  Label* congratsLabel = new Label(Vector2(screenDimensions.x * 0.5f, screenDimensions.y * 0.15f), L"Congratulations!");
  AddScreenUIObject(congratsLabel);

  Label* infoLabel = new Label(Vector2(0, screenDimensions.y * 0.1f), L"You have won:", congratsLabel);
  AddScreenUIObject(infoLabel);

  for (const Prize& prize : m_prizes)
  {
    AddScreenUIObject(new PrizeDescriptionUI(GetDevice(), GetScreenCentre(), GetScreenCentre(), prize));
  }
}