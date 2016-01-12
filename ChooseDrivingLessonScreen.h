#pragma once

#include "BaseScreen.h"

#include "RacetrackScreenData.h"
#include "RacetrackDescriptionUI.h"

class ChooseDrivingLessonScreen : public BaseScreen
{
public:
  ChooseDrivingLessonScreen(ScreenManager* screenManager, const std::string& dataAsset = "ChooseDrivingLessonScreen.xml");
  ~ChooseDrivingLessonScreen();

  void AddInitialUI() override;
  void Initialize() override;
  void HandleInput(float elapsedGameTime) override;

private:
  typedef std::pair<std::string, RacetrackDescriptionUI*> Lesson;
  typedef std::vector<Lesson> Lessons;

  void ShowCurrentLessonUI();

  // Our current selected lesson
  size_t m_currentLesson;

  // Map which holds the data asset for the level and the appropriate UI
  Lessons m_lessons;
};