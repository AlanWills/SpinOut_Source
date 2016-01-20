#include "pch.h"

#include "ScreenManager.h"
#include "Lesson3RacetrackScreen.h"
#include "ChooseDrivingLessonScreen.h"
#include "RacetrackScreenFactory.h"

#include "PlayerData.h"

#include "AddTextBoxScript.h"
#include "TransitionOnKeyPressScript.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson3RacetrackScreen::Lesson3RacetrackScreen(ScreenManager* screenManager, const std::string& dataAsset, unsigned int checkPoint) :
  RacetrackScreen(screenManager, dataAsset),
  m_currentArrow(0),
  m_checkPoint((Lesson3CheckPoints)checkPoint)
{
  PlayerData::GetInstance().SetCurrentCarAsset("Corvette.xml");
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson3RacetrackScreen::~Lesson3RacetrackScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson3RacetrackScreen::AddInitialScripts()
{
  PlayerCar* playerCar = GetPlayerCar();
  assert(playerCar);

  playerCar->SetLocalRotation(XM_PI);

  if (m_checkPoint == Lesson3CheckPoints::kLevelStart)
  {
    AddScript(new AddTextBoxScript(L"Lesson 3!"));
    AddScript(new AddTextBoxScript(L"This might look a lot like lessson 2,\nbut will not be so easy."));
    AddScript(new AddTextBoxScript(L"Here you will learn one of the\nhardest skills in becoming a driver."));
    AddScript(new AddTextBoxScript(L"Slalom your way between the cones like last level,\nbut this time you will start at the top."));
    AddScript(new AddTextBoxScript(L"This is called 'Driving Down the Screen' and can be rather tricky."));
  }

  AddScript(new UpdateArrowsScript(this));
  AddScript(new AddTextBoxScript(L"Well done!\nThat was a tough lesson."));
  AddScript(new AddTextBoxScript(L"Press 'Enter' to finish."));
  AddScript(new TransitionOnKeyPressScript(GetScreenManager(), new ChooseDrivingLessonScreen(GetScreenManager()), Keyboard::Keys::Enter));

  CheckCollisionsScript* collisionScript = new CheckCollisionsScript(playerCar);
  AddScript(collisionScript, nullptr);
  AddScript(new LessonFailedScript(GetScreenManager(), L"Try to avoid the cones!\nPress 'Enter' to restart."), collisionScript);
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
Lesson3RacetrackScreen::CheckCollisionsScript::CheckCollisionsScript(PlayerCar* playerCar, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_playerCar(playerCar)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson3RacetrackScreen::CheckCollisionsScript::~CheckCollisionsScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson3RacetrackScreen::CheckCollisionsScript::Run(float elapsedGameTime)
{
  Script::Run(elapsedGameTime);

  if (IsRunning())
  {
    SetCompleted(m_playerCar->GetCollider()->HasCollided());
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson3RacetrackScreen::LessonFailedScript::LessonFailedScript(ScreenManager* screenManager, const std::wstring& lessonFailedText, bool shouldUpdateGame, bool canRun) :
  AddTextBoxScript(lessonFailedText),
  m_screenManager(screenManager)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson3RacetrackScreen::LessonFailedScript::~LessonFailedScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson3RacetrackScreen::LessonFailedScript::HandleInput(float elapsedGameTime)
{
  // Don't want to handle input for text box, because we don't want to quit if mouse clicked

  if (IsRunning())
  {
    if (ScreenManager::GetKeyboardInput().IsKeyPressed(Keyboard::Keys::Enter))
    {
      SetCompleted(true);
      m_screenManager->Transition(m_screenManager->GetCurrentScreen(), RacetrackScreenFactory::CreateRacetrack(m_screenManager, "Lesson3RacetrackScreen.xml", Lesson3CheckPoints::kGameplayStart));
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson3RacetrackScreen::UpdateArrowsScript::UpdateArrowsScript(Lesson3RacetrackScreen* lessonScreen, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_lessonScreen(lessonScreen)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson3RacetrackScreen::UpdateArrowsScript::~UpdateArrowsScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson3RacetrackScreen::UpdateArrowsScript::LoadAndInit(ID3D11Device* device)
{
  UpdateArrowsVisibility();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson3RacetrackScreen::UpdateArrowsScript::Run(float elapsedGameTime)
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
void Lesson3RacetrackScreen::UpdateArrowsScript::UpdateArrowsVisibility()
{
  for (size_t index = 0; index < m_lessonScreen->m_arrows.size(); index++)
  {
    m_lessonScreen->m_arrows[index]->SetVisible(index == m_lessonScreen->m_currentArrow);
  }
}