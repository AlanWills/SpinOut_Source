#include "pch.h"

#include "PlayerData.h"

#include "ScreenManager.h"
#include "RacetrackScreenFactory.h"

#include "ChooseDrivingLessonScreen.h"
#include "RacetrackScreen.h"

#include "Button.h"

//-----------------------------------------------------------------------------------------------------------------------------------
ChooseDrivingLessonScreen::ChooseDrivingLessonScreen(ScreenManager* screenManager, const std::string& dataAsset) :
  BaseScreen(screenManager, dataAsset),
  m_currentLesson(PlayerData::GetInstance().GetCurrentLicenseLevel())
{
  m_lessons.push_back(Lesson("Lesson1RacetrackScreen.xml", new RacetrackDescriptionUI(GetDevice(), "Lesson1RacetrackScreen.xml")));
  m_lessons.push_back(Lesson("Lesson2RacetrackScreen.xml", new RacetrackDescriptionUI(GetDevice(), "Lesson2RacetrackScreen.xml")));
}


//-----------------------------------------------------------------------------------------------------------------------------------
ChooseDrivingLessonScreen::~ChooseDrivingLessonScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ChooseDrivingLessonScreen::AddInitialUI()
{
  BaseScreen::AddInitialUI();

  for (const Lesson& lesson : m_lessons)
  {
    assert(lesson.second);

    AddScreenUIObject(lesson.second);
  }

  Button* playButton = new Button(Vector2(GetScreenCentre().x, GetScreenDimensions().y - 100), L"Go Race");
  playButton->SetClickFunction([this]()
  {
    Transition(RacetrackScreenFactory::CreateRacetrack(GetScreenManager(), m_lessons[m_currentLesson].first));
  });
  AddScreenUIObject(playButton);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ChooseDrivingLessonScreen::Initialize()
{
  BaseScreen::Initialize();

  ShowCurrentLessonUI();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ChooseDrivingLessonScreen::HandleInput(float elapsedGameTime)
{
  BaseScreen::HandleInput(elapsedGameTime);

  if (AcceptsInput())
  {
    const KeyboardInput& keyboard = ScreenManager::GetKeyboardInput();

    if (keyboard.IsKeyPressed(Keyboard::Keys::Left))
    {
      m_currentLesson = MathUtils::Clamp<size_t>(m_currentLesson - 1, 0, PlayerData::GetInstance().GetCurrentLicenseLevel());

      // Hide the other level UIs
      ShowCurrentLessonUI();
    }
    
    if (keyboard.IsKeyPressed(Keyboard::Keys::Right))
    {
      m_currentLesson = MathUtils::Clamp<size_t>(m_currentLesson + 1, 0, PlayerData::GetInstance().GetCurrentLicenseLevel());

      // Hide the other level UIs
      ShowCurrentLessonUI();
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ChooseDrivingLessonScreen::ShowCurrentLessonUI()
{
  for (size_t i = 0; i < m_lessons.size(); i++)
  {
    // Set it's visibility based on whether it is the current selected lesson
    m_lessons[i].second->SetVisible(i == m_currentLesson);
  }
}