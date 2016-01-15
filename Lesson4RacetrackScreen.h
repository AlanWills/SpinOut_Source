#pragma once

#include "RacetrackScreen.h"

#include "Label.h"

class Lesson4RacetrackScreen : public RacetrackScreen
{
public:
  enum Lesson4CheckPoints
  {
    kLevelStart,
    kGameplayStart,
    kLevelEnd,
  };

  REGISTER_RACETRACK_CHECKPOINTS(Lesson4RacetrackScreen, "Lesson4RacetrackScreen.xml", Lesson4CheckPoints);

  void AddInitialUI() override;
  void AddInitialScripts() override;
  void Update(float elapsedTestSeconds) override;

private:
  float m_timer;
  Label* m_timerLabel;


//-----------------------------------------------------------------------------------------------------------------------------------
class StartTestScript : public Script
{
  IMPLEMENT_SIMPLE_SCRIPT_LOADINIT_RUN;

  StartTestScript(Lesson4RacetrackScreen* lessonScreen, bool shouldUpdateGame = false, bool canRun = true);
  ~StartTestScript();

private:
  Lesson4RacetrackScreen* m_lessonScreen;
  Label* m_goLabel;
};


};