#include "pch.h"

#include "Lesson3RacetrackScreen.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson3RacetrackScreen::Lesson3RacetrackScreen(ScreenManager* screenManager, const std::string& dataAsset) :
  RacetrackScreen(screenManager, dataAsset),
  m_currentArrow(0)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson3RacetrackScreen::~Lesson3RacetrackScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson3RacetrackScreen::AddInitialScripts()
{

}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson3RacetrackScreen::LoadLevel()
{
  RacetrackScreen::LoadLevel();

  for (const Vector2& position : GetTrackPoints())
  {
    std::string dataAsset = position.x < 1250 ? "AntiClockwiseRightTurn.png" : "ClockwiseLeftTurn.png";
    Image* arrow = new Image(position, dataAsset);
    arrow->SetShouldHaveCollider(false);
    m_arrows.push_back(arrow);
    AddInGameUIObject(arrow, true);
  }
}