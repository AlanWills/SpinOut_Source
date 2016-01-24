#pragma once

#include "MenuScreen.h"

#include "RacetrackScreenData.h"
#include "DescriptionUIContainer.h"
#include "RacetrackDescriptionUI.h"

class ChooseDrivingLessonScreen : public MenuScreen
{
public:
  ChooseDrivingLessonScreen(ScreenManager* screenManager, const std::string& dataAsset = "ChooseDrivingLessonScreen.xml");
  ~ChooseDrivingLessonScreen();

  void AddInitialUI() override;

private:
  typedef std::pair<std::string, std::string> LessonNameAndFile;
  typedef std::vector<LessonNameAndFile> LessonNames;

  // Our lesson UI container
  DescriptionUIContainer* m_racetrackDescriptionContainer;

  // Map which holds the data asset for the level and the appropriate UI
  LessonNames m_lessons;
};