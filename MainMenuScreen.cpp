#include "pch.h"

#include "MainMenuScreen.h"
#include "ChooseDrivingLessonScreen.h"
#include "GarageScreen.h"

#include "AddTextBoxScript.h"

#include "Button.h"


//-----------------------------------------------------------------------------------------------------------------------------------
MainMenuScreen::MainMenuScreen(ScreenManager* screenManager, const std::string& dataAsset) :
  MenuScreen(screenManager, dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
MainMenuScreen::~MainMenuScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void MainMenuScreen::AddInitialUI()
{
  MenuScreen::AddInitialUI();

	Button* playButton = new Button(GetScreenCentre(), L"Go Race!");
	playButton->SetClickFunction([this]()
	{
		// Transition to game screen
		//Transition(new RacetrackScreen(GetScreenManager(), "Level1RacetrackScreen.xml"));
	});

	AddScreenUIObject(playButton);

  Button* tutorialButton = new Button(Vector2(0, 100), L"Driving School", "Button.png", BaseObject::kTexture, playButton);
  tutorialButton->SetClickFunction([this]()
  {
    // Transition to choose driving lesson screen
    Transition(new ChooseDrivingLessonScreen(GetScreenManager()));
  });

  AddScreenUIObject(tutorialButton);

  Button* garageButton = new Button(Vector2(0, 100), L"Garage", "Button.png", BaseObject::kTexture, tutorialButton);
  garageButton->SetClickFunction([this]()
  {
    // Transition to garage screen
    Transition(new GarageScreen(GetScreenManager()));
  });

  AddScreenUIObject(garageButton);

  Button* exitButton = new Button(Vector2(0, 100), L"Quit", "Button.png", BaseObject::kTexture, garageButton);
  exitButton->SetClickFunction([this]()
  {
    PostQuitMessage(0);
  });

  AddScreenUIObject(exitButton);
}