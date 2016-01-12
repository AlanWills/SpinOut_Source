#pragma once

#include "RacetrackScreen.h"
#include "AddTextBoxScript.h"

#include "Image.h"

class Lesson2RacetrackScreen :  public RacetrackScreen 
{
  REGISTER_RACETRACK(Lesson2RacetrackScreen, "Lesson2RacetrackScreen.xml")

public:
  void AddInitialScripts() override;
  void LoadLevel() override;

private:
  std::vector<Image*> m_arrows;
  size_t m_currentArrow;

  friend class UpdateArrowsScript;
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


//-----------------------------------------------------------------------------------------------------------------------------------
class LessonFailedScript : public AddTextBoxScript
{
  IMPLEMENT_SIMPLE_SCRIPT_HANDLE_INPUT;

  LessonFailedScript(ScreenManager* screenManager, const std::wstring& lessonFailedText, bool shouldUpdateGame = false, bool canRun = true);
  ~LessonFailedScript();

private:
  ScreenManager* m_screenManager;
};


//-----------------------------------------------------------------------------------------------------------------------------------
class UpdateArrowsScript : public Script
{
  IMPLEMENT_SIMPLE_SCRIPT_LOADINIT_RUN;

  UpdateArrowsScript(Lesson2RacetrackScreen* lessonScreen, bool shouldUpdateGame = true, bool canRun = true);
  ~UpdateArrowsScript();

private:
  void UpdateArrowsVisibility();

  Lesson2RacetrackScreen* m_lessonScreen;
};