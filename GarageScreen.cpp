#include "pch.h"

#include "PlayerData.h"

#include "ScreenManager.h"
#include "GarageScreen.h"

#include "Button.h"


//-----------------------------------------------------------------------------------------------------------------------------------
GarageScreen::GarageScreen(ScreenManager* screenManager, const std::string& dataAsset) :
  BaseScreen(screenManager, dataAsset),
  m_currentCar(0)
{
  m_carInfos.push_back(CarInfo("Corvette.xml", new CarDescriptionUI(GetDevice(), "Corvette.xml")));
}


//-----------------------------------------------------------------------------------------------------------------------------------
GarageScreen::~GarageScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GarageScreen::AddInitialUI()
{
  BaseScreen::AddInitialUI();

  for (const CarInfo& info : m_carInfos)
  {
    assert(info.second);

    AddScreenUIObject(info.second);
  }

  Button* chooseCarButton = new Button(Vector2(GetScreenCentre().x, GetScreenDimensions().y - 100), L"Drive Car");
  chooseCarButton->SetClickFunction([this]()
  {
    //Transition(RacetrackScreenFactory::CreateRacetrack(GetScreenManager(), m_lessons[m_currentLesson].first));
  });
  AddScreenUIObject(chooseCarButton);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GarageScreen::Initialize()
{
  BaseScreen::Initialize();

  ShowCurrentCarUI();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GarageScreen::HandleInput(float elapsedGameTime)
{
  BaseScreen::HandleInput(elapsedGameTime);

  if (AcceptsInput())
  {
    const KeyboardInput& keyboard = ScreenManager::GetKeyboardInput();

    if (keyboard.IsKeyPressed(Keyboard::Keys::Left))
    {
      m_currentCar = MathUtils::Clamp<size_t>(m_currentCar - 1, 0, PlayerData::GetInstance().GetCarAssets().size());

      // Hide the other car UIs
      ShowCurrentCarUI();
    }

    if (keyboard.IsKeyPressed(Keyboard::Keys::Right))
    {
      m_currentCar = MathUtils::Clamp<size_t>(m_currentCar + 1, 0, PlayerData::GetInstance().GetCarAssets().size());

      // Hide the other level UIs
      ShowCurrentCarUI();
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GarageScreen::ShowCurrentCarUI()
{
  for (size_t i = 0; i < m_carInfos.size(); i++)
  {
    // Set it's visibility based on whether it is the current selected lesson
    m_carInfos[i].second->SetVisible(i == m_currentCar);
  }
}