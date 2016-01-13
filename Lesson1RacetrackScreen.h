#pragma once

#include "RacetrackScreen.h"
#include "Script.h"

class Lesson1RacetrackScreen : public RacetrackScreen
{
public:
  enum Lesson1CheckPoints
  {
    kLevelStart,
    kLevelEnd,
  };

  REGISTER_RACETRACK_CHECKPOINTS(Lesson1RacetrackScreen, "Lesson1RacetrackScreen.xml", Lesson1CheckPoints);

public:
  void AddInitialScripts() override;
};


//-----------------------------------------------------------------------------------------------------------------------------------
class CheckAccelerateScript : public Script
{
public:
  CheckAccelerateScript(PlayerCar* playerCar, bool shouldUpdateGame = true, bool canRun = true);
  ~CheckAccelerateScript();

  IMPLEMENT_SIMPLE_SCRIPT_RUN_HANDLE_INPUT

private:
  bool m_accelerationPressed;
  float m_timeSinceAccelerationPressed;

  PlayerCar* m_playerCar;
};


//-----------------------------------------------------------------------------------------------------------------------------------
class CheckDeccelerateScript : public Script
{
public:
  CheckDeccelerateScript(PlayerCar* playerCar, bool shouldUpdateGame = true, bool canRun = true);
  ~CheckDeccelerateScript();

  IMPLEMENT_SIMPLE_SCRIPT_RUN_HANDLE_INPUT

private:
  bool m_deccelerationPressed;
  float m_timeSinceDeccelerationPressed;

  PlayerCar* m_playerCar;
};


//-----------------------------------------------------------------------------------------------------------------------------------
class CheckLeftAndRightTurnScript : public Script
{
public:
  CheckLeftAndRightTurnScript(PlayerCar* playerCar, bool shouldUpdateGame = true, bool canRun = true);
  ~CheckLeftAndRightTurnScript();

  IMPLEMENT_SIMPLE_SCRIPT_RUN_HANDLE_INPUT

private:
  bool m_leftTurnPressed;
  bool m_rightTurnPressed;
  float m_timeSinceTurnsPressed;

  PlayerCar* m_playerCar;
};