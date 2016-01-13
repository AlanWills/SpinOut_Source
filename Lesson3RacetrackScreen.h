#pragma once

#include "RacetrackScreen.h"

#include "Image.h"

class Lesson3RacetrackScreen : public RacetrackScreen
{
  REGISTER_RACETRACK(Lesson3RacetrackScreen, "Lesson3RacetrackScreen.xml");

public:
  void AddInitialScripts() override;
  void LoadLevel() override;

private:
  std::vector<Image*> m_arrows;
  size_t m_currentArrow;
};


//-----------------------------------------------------------------------------------------------------------------------------------
class CheckCollisionsScript : public Script
{
  IMPLEMENT_SIMPLE_SCRIPT_RUN;

  CheckCollisionsScript(PlayerCar* playerCar, bool shouldUpdateGame = true, bool canRun = true);
  ~CheckCollisionsScript();

private:
  PlayerCar* m_playerCar;
};