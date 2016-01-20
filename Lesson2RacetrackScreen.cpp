#include "pch.h"

#include "ScreenManager.h"
#include "RacetrackScreenFactory.h"
#include "Lesson2RacetrackScreen.h"

#include "PlayerData.h"

#include "TransitionOnKeyPressScript.h"

//-----------------------------------------------------------------------------------------------------------------------------------
Lesson2RacetrackScreen::Lesson2RacetrackScreen(ScreenManager* screenManager, const std::string& dataAsset, unsigned int checkPoint) : 
  RacetrackScreen(screenManager, dataAsset),
  m_currentArrow(0),
  m_checkPoint((Lesson2CheckPoints)checkPoint)
{
  PlayerData::GetInstance().SetCurrentCarAsset("Corvette.xml");
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson2RacetrackScreen::~Lesson2RacetrackScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson2RacetrackScreen::AddInitialScripts()
{
  PlayerCar* playerCar = GetPlayerCar();
  assert(playerCar);

  if (m_checkPoint == Lesson2CheckPoints::kLevelStart)
  {
    AddScript(new AddTextBoxScript(L"Welcome to Lesson 2."));
    AddScript(new AddTextBoxScript(L"Here you will practice some more realistic driving."));
    AddScript(new AddTextBoxScript(L"Follow the arrows and slalom round the cones.\nIf you hit a cone, you will have to start again"));
  }

  AddScript(new UpdateArrowsScript(this));
  AddScript(new AddTextBoxScript(L"Well done!\nHit 'Enter' to move to the next lesson."));
  AddScript(new TransitionOnKeyPressScript(GetScreenManager(), RacetrackScreenFactory::CreateRacetrack(GetScreenManager(), "Lesson3RacetrackScreen"), Keyboard::Keys::Enter));

  CheckCollisionsScript* collisionScript = new CheckCollisionsScript(playerCar);
  AddScript(collisionScript, nullptr);
  AddScript(new LessonFailedScript(GetScreenManager(), L"Try to avoid the cones!\nPress 'Enter' to restart."), collisionScript);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson2RacetrackScreen::LoadLevel()
{
  RacetrackScreen::LoadLevel();

  for (const Vector2& position : GetTrackPoints())
  {
    std::string dataAsset = position.x < 1250 ? "ClockwiseRightTurn.png" : "AntiClockwiseLeftTurn.png";
    Image* arrow = new Image(position, dataAsset);
    arrow->SetShouldHaveCollider(false);
    m_arrows.push_back(arrow);
    AddInGameUIObject(arrow, true);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson2RacetrackScreen::CheckCollisionsScript::CheckCollisionsScript(PlayerCar* playerCar, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_playerCar(playerCar)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson2RacetrackScreen::CheckCollisionsScript::~CheckCollisionsScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson2RacetrackScreen::CheckCollisionsScript::Run(float elapsedGameTime)
{
  Script::Run(elapsedGameTime);

  if (IsRunning())
  {
    SetCompleted(m_playerCar->GetCollider()->HasCollided());
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson2RacetrackScreen::LessonFailedScript::LessonFailedScript(ScreenManager* screenManager, const std::wstring& lessonFailedText, bool shouldUpdateGame, bool canRun) :
  AddTextBoxScript(lessonFailedText),
  m_screenManager(screenManager)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson2RacetrackScreen::LessonFailedScript::~LessonFailedScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson2RacetrackScreen::LessonFailedScript::HandleInput(float elapsedGameTime)
{
  // Don't want to handle input for text box, because we don't want to quit if mouse clicked

  if (IsRunning())
  {
    if (ScreenManager::GetKeyboardInput().IsKeyPressed(Keyboard::Keys::Enter))
    {
      SetCompleted(true);
      m_screenManager->Transition(m_screenManager->GetCurrentScreen(), RacetrackScreenFactory::CreateRacetrack(m_screenManager, "Lesson2RacetrackScreen.xml", Lesson2CheckPoints::kGameplayStart));
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson2RacetrackScreen::UpdateArrowsScript::UpdateArrowsScript(Lesson2RacetrackScreen* lessonScreen, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_lessonScreen(lessonScreen)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson2RacetrackScreen::UpdateArrowsScript::~UpdateArrowsScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson2RacetrackScreen::UpdateArrowsScript::LoadAndInit(ID3D11Device* device)
{
  UpdateArrowsVisibility();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson2RacetrackScreen::UpdateArrowsScript::Run(float elapsedGameTime)
{
  Script::Run(elapsedGameTime);

  if (IsRunning())
  {
    if (Vector2::DistanceSquared(m_lessonScreen->GetPlayerCar()->GetWorldPosition(), m_lessonScreen->m_arrows[m_lessonScreen->m_currentArrow]->GetWorldPosition()) <= 40 * 40)
    {
      if (m_lessonScreen->m_currentArrow == m_lessonScreen->m_arrows.size() - 1)
      {
        // We are done if we have driven near the final arrow
        SetCompleted(true);
        return;
      }

      m_lessonScreen->m_currentArrow = MathUtils::Clamp<size_t>(m_lessonScreen->m_currentArrow + 1, 0, m_lessonScreen->m_arrows.size() - 1);

      UpdateArrowsVisibility();
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson2RacetrackScreen::UpdateArrowsScript::UpdateArrowsVisibility()
{
  for (size_t index = 0; index < m_lessonScreen->m_arrows.size(); index++)
  {
    m_lessonScreen->m_arrows[index]->SetVisible(index == m_lessonScreen->m_currentArrow);
  }
}