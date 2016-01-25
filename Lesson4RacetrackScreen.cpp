#include "pch.h"

#include "ScreenManager.h"
#include "RacetrackScreenFactory.h"
#include "Lesson4RacetrackScreen.h"

#include "PlayerData.h"
#include "CarData.h"

#include "AddTextBoxScript.h"
#include "WaitForKeyPressScript.h"
#include "TransitionOnKeyPressScript.h"

#define TIME_TO_COMPLETE 60

//-----------------------------------------------------------------------------------------------------------------------------------
Lesson4RacetrackScreen::Lesson4RacetrackScreen(ScreenManager* screenManager, const std::string& dataAsset, unsigned int checkPoint) :
  RacetrackScreen(screenManager, dataAsset),
  m_checkPoint((Lesson4CheckPoints)checkPoint),
  m_timer(TIME_TO_COMPLETE),
  m_timerLabel(nullptr)
{
  SetMaxLapNumber(3);
  PlayerData::GetInstance().SetCurrentCarAsset("Corvette.xml");
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson4RacetrackScreen::~Lesson4RacetrackScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson4RacetrackScreen::AddInitialUI()
{
  RacetrackScreen::AddInitialUI();

  m_timerLabel = new Label(Vector2(GetScreenCentre().x, GetScreenDimensions().y * 0.15f), L"Time Left: " + std::to_wstring(m_timer));

  AddScreenUIObject(m_timerLabel);

  AddLapNumberLabel(Color(0, 0, 0, 1));
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson4RacetrackScreen::AddInitialScripts()
{
  if (m_checkPoint == Lesson4CheckPoints::kLevelStart)
  {
    if (m_checkPoint == Lesson4CheckPoints::kLevelStart)
    {
      AddScript(new AddTextBoxScript(L"Welcome to your first license test."));
      AddScript(new AddTextBoxScript(L"If you successfully pass, your qualification\nwill unlock many new opportunities for you."));
      AddScript(new AddTextBoxScript(L"This one is simple - just complete three laps in the allotted time."));
    }

    AddScript(new AddTextBoxScript(L"Hit 'Enter' whenever you are ready to start."));
    AddScript(new WaitForKeyPressScript(Keyboard::Keys::Enter, false));
    AddScript(new StartTestScript(this));
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson4RacetrackScreen::Initialize()
{
  RacetrackScreen::Initialize();

  std::unique_ptr<CarData> prizeCarData(new CarData("Corvette.xml"));
  prizeCarData->LoadData();

  Prize licensePrize;
  licensePrize.m_description = "Now you can compete in races which require a Level 1 License!";
  licensePrize.m_type = kLicenseLevel;
  licensePrize.m_name = "Level 1 License";
  licensePrize.m_asset = "Logo.png";

  m_prizes.push_back(licensePrize);

  Prize carPrize;
  carPrize.m_description = prizeCarData->GetDescription();
  carPrize.m_type = kCar;
  carPrize.m_name = prizeCarData->GetDisplayName();
  carPrize.m_asset = prizeCarData->GetTextureAsset();

  m_prizes.push_back(carPrize);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson4RacetrackScreen::Update(float elapsedSeconds)
{
  RacetrackScreen::Update(elapsedSeconds);

  if (ShouldUpdateGame())
  {
    m_timer -= elapsedSeconds;
    m_timerLabel->SetText(L"Time Left: " + std::to_wstring(m_timer));

    if (m_timer <= 0)
    {
      AddScript(new AddTextBoxScript(L"You ran out of time!", 2));
      AddScript(new TransitionOnKeyPressScript(
        GetScreenManager(), RacetrackScreenFactory::CreateRacetrack(GetScreenManager(), "Lesson4RacetrackScreen", Lesson4CheckPoints::kGameplayStart), Keyboard::Keys::NumKeys));
    }

    if (LapsCompleted())
    {
      AddScript(new AddTextBoxScript(L"Congratulations, you have passed the test!"));
      AddScript(new TransitionOnKeyPressScript(GetScreenManager(), new PrizeScreen(m_prizes, GetScreenManager()), Keyboard::Keys::NumKeys));
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson4RacetrackScreen::StartTestScript::StartTestScript(Lesson4RacetrackScreen* lessonScreen, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_lessonScreen(lessonScreen)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Lesson4RacetrackScreen::StartTestScript::~StartTestScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson4RacetrackScreen::StartTestScript::LoadAndInit(ID3D11Device* device)
{
  m_goLabel = new Label(Vector2(300, 150), ScreenManager::GetScreenCentre(), L"GO!", nullptr, 1);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Lesson4RacetrackScreen::StartTestScript::Run(float elapsedSeconds)
{
  Script::Run(elapsedSeconds);

  if (IsRunning())
  {
    m_lessonScreen->AddScreenUIObject(m_goLabel, true, true);
    SetCompleted(true);
  }
}