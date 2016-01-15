#pragma once

#include "MenuScreen.h"

class MainMenuScreen : public MenuScreen
{
public:
	MainMenuScreen(ScreenManager* screenManager, const std::string& dataAsset = "MainMenuScreen.xml");
	~MainMenuScreen();

	void AddInitialUI() override;
  void Initialize() override;
};