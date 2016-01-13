#include "pch.h"

#include "ScreenManager.h"
#include "RacetrackScreenFactory.h"
#include "Lesson1RacetrackScreen.h"

#include "PlayerData.h"

#include "AddTextBoxScript.h"
#include "TransitionOnEnterScript.h"

//-----------------------------------------------------------------------------------------------------------------------------------
Lesson1RacetrackScreen::Lesson1RacetrackScreen(ScreenManager* screenManager, const std::string& dataAsset, unsigned int checkPoint) :
  RacetrackScreen(screenManager, dataAsset),
  m_checkPoint((Lesson1CheckPoints)checkPoint)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson1RacetrackScreen::~Lesson1RacetrackScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson1RacetrackScreen::AddInitialScripts()
{
  PlayerCar* playerCar = GetPlayerCar();
  assert(playerCar);

  if (m_checkPoint == Lesson1CheckPoints::kLevelStart)
  {
    AddScript(new AddTextBoxScript(L"Welcome to Lesson 1!"));
    AddScript(new AddTextBoxScript(L"Here you will learn the basics\nof handling and driving your car."));
    AddScript(new AddTextBoxScript(L"Lets get started!"));
  }

  AddScript(new AddTextBoxScript(L"Hold the 'W' key to accelerate."));
  AddScript(new CheckAccelerateScript(playerCar), GetLastAddedScript());
  AddScript(new AddTextBoxScript(L"Good!  Now try deccelerating\nby holding the 'S' key."));
  AddScript(new CheckDeccelerateScript(playerCar), GetLastAddedScript());
  AddScript(new AddTextBoxScript(L"Awesome!  Now try turning left and right\nby using the 'A' and 'D' keys."));
  AddScript(new CheckLeftAndRightTurnScript(playerCar));
  AddScript(new AddTextBoxScript(L"Great!"));
  AddScript(new AddTextBoxScript(L"That's it for this lesson.\nFeel free to carry on driving,\nor press 'Enter' to go to the next lesson."));
  AddScript(new TransitionOnEnterScript(GetScreenManager(), RacetrackScreenFactory::CreateRacetrack(GetScreenManager(), "Lesson2RacetrackScreen.xml")));
}


//-----------------------------------------------------------------------------------------------------------------------------------
CheckAccelerateScript::CheckAccelerateScript(PlayerCar* playerCar, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_playerCar(playerCar),
  m_accelerationPressed(false),
  m_timeSinceAccelerationPressed(0)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
CheckAccelerateScript::~CheckAccelerateScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void CheckAccelerateScript::Run(float elapsedGameTime)
{
  Script::Run(elapsedGameTime);

  if (IsRunning())
  {
    if (m_accelerationPressed)
    {
      m_timeSinceAccelerationPressed += elapsedGameTime;

      SetCompleted(m_timeSinceAccelerationPressed >= 1);
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void CheckAccelerateScript::HandleInput(float elapsedGameTime)
{
  if (IsRunning())
  {
    const KeyboardInput& keyboard = ScreenManager::GetKeyboardInput();

    bool isOnlyWDown = keyboard.IsOnlyKeyDown(Keyboard::Keys::W);
    m_accelerationPressed = m_accelerationPressed || isOnlyWDown;

    m_playerCar->SetAcceptsInput(isOnlyWDown);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
CheckDeccelerateScript::CheckDeccelerateScript(PlayerCar* playerCar, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_playerCar(playerCar),
  m_deccelerationPressed(false),
  m_timeSinceDeccelerationPressed(0)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
CheckDeccelerateScript::~CheckDeccelerateScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void CheckDeccelerateScript::Run(float elapsedGameTime)
{
  Script::Run(elapsedGameTime);

  if (IsRunning())
  {
    if (m_deccelerationPressed)
    {
      m_timeSinceDeccelerationPressed += elapsedGameTime;

      SetCompleted(m_timeSinceDeccelerationPressed >= 1);
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void CheckDeccelerateScript::HandleInput(float elapsedGameTime)
{
  if (IsRunning())
  {
    const KeyboardInput& keyboard = ScreenManager::GetKeyboardInput();

    bool isOnlySDown = keyboard.IsOnlyKeyDown(Keyboard::Keys::S);
    m_deccelerationPressed = m_deccelerationPressed || isOnlySDown;

    m_playerCar->SetAcceptsInput(isOnlySDown);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
CheckLeftAndRightTurnScript::CheckLeftAndRightTurnScript(PlayerCar* playerCar, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_playerCar(playerCar),
  m_leftTurnPressed(false),
  m_rightTurnPressed(false),
  m_timeSinceTurnsPressed(0)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
CheckLeftAndRightTurnScript::~CheckLeftAndRightTurnScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void CheckLeftAndRightTurnScript::Run(float elapsedGameTime)
{
  Script::Run(elapsedGameTime);

  if (IsRunning())
  {
    if (m_leftTurnPressed && m_rightTurnPressed)
    {
      m_timeSinceTurnsPressed += elapsedGameTime;

      SetCompleted(m_timeSinceTurnsPressed >= 0.6f);
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void CheckLeftAndRightTurnScript::HandleInput(float elapsedGameTime)
{
  if (IsRunning())
  {
    const KeyboardInput& keyboard = ScreenManager::GetKeyboardInput();

    bool isADown = keyboard.IsKeyDown(Keyboard::Keys::A);
    m_leftTurnPressed = m_leftTurnPressed || isADown;

    bool isDDown = keyboard.IsKeyDown(Keyboard::Keys::D);
    m_rightTurnPressed = m_rightTurnPressed || isDDown;

    // Now that the player has full access to all moves, don't think it is right to restrict movement to just steering now
  }
}