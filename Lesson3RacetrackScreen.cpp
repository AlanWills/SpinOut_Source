#include "pch.h"

#include "Lesson3RacetrackScreen.h"

#include "AddTextBoxScript.h"


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
  AddScript(new AddTextBoxScript(L"Lesson 3!"));
  AddScript(new AddTextBoxScript(L"This might look a lot like lessson 2,\nbut will not be so easy."));
  AddScript(new AddTextBoxScript(L"Here you will learn one of the\nhardest skills in becoming a driver."));
  AddScript(new AddTextBoxScript(L"Slalom your way between the cones like last level,\nbut this time you will start at the top."));
  AddScript(new AddTextBoxScript(L"This is called 'Driving Down the Screen' and can be rather tricky."));

  CheckCollisionsScript* collisionScript = new CheckCollisionsScript(GetPlayerCar());
  AddScript(collisionScript, nullptr);
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


//-----------------------------------------------------------------------------------------------------------------------------------
CheckCollisionsScript::CheckCollisionsScript(PlayerCar* playerCar, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_playerCar(playerCar)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
CheckCollisionsScript::~CheckCollisionsScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void CheckCollisionsScript::Run(float elapsedGameTime)
{
  Script::Run(elapsedGameTime);

  if (IsRunning())
  {
    SetCompleted(m_playerCar->GetCollider()->HasCollided());
  }
}