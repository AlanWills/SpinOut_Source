#include "pch.h"

#include "PlayerData.h"

#include "ScreenManager.h"
#include "RacetrackScreenFactory.h"

#include "MainMenuScreen.h"
#include "ChooseDrivingLessonScreen.h"
#include "RacetrackScreen.h"

#include "Button.h"

//-----------------------------------------------------------------------------------------------------------------------------------
ChooseDrivingLessonScreen::ChooseDrivingLessonScreen(ScreenManager* screenManager, const std::string& dataAsset) :
  MenuScreen(screenManager, dataAsset),
  m_racetrackDescriptionContainer(nullptr)
{
  SetPreviousScreen(new MainMenuScreen(GetScreenManager()));

  m_lessons.push_back(LessonNameAndFile("Lesson1RacetrackScreen", "Lesson1RacetrackScreen.xml"));
  m_lessons.push_back(LessonNameAndFile("Lesson2RacetrackScreen", "Lesson2RacetrackScreen.xml"));
  m_lessons.push_back(LessonNameAndFile("Lesson3RacetrackScreen", "Lesson3RacetrackScreen.xml"));
  m_lessons.push_back(LessonNameAndFile("Lesson4RacetrackScreen", "Lesson4RacetrackScreen.xml"));
}


//-----------------------------------------------------------------------------------------------------------------------------------
ChooseDrivingLessonScreen::~ChooseDrivingLessonScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ChooseDrivingLessonScreen::AddInitialUI()
{
  MenuScreen::AddInitialUI();

  m_racetrackDescriptionContainer = new DescriptionUIContainer(GetDevice(), PlayerData::GetInstance().GetCurrentLicenseLevel());
  AddScreenUIObject(m_racetrackDescriptionContainer);

  for (size_t index = 0, licenseLevel = PlayerData::GetInstance().GetCurrentLicenseLevel(); index <= licenseLevel; index++)
  {
    RacetrackDescriptionUI* racetrackUI = new RacetrackDescriptionUI(GetDevice(), m_lessons[index].second);
    m_racetrackDescriptionContainer->AddDescriptionUI(racetrackUI);
  }

  Button* playButton = new Button(Vector2(GetScreenCentre().x, GetScreenDimensions().y * 0.9f), L"Go Race");
  playButton->SetClickFunction([this]()
  {
    std::string racetrackName(m_lessons[m_racetrackDescriptionContainer->GetCurrentUIIndex()].first);
    Transition(RacetrackScreenFactory::CreateRacetrack(GetScreenManager(), racetrackName));
  });
  AddScreenUIObject(playButton);
}