#pragma once

#include "BaseScreen.h"

class MainMenuScreen : public BaseScreen
{
public:
	MainMenuScreen(ScreenManager* screenManager, const std::string& dataAsset = "MainMenuScreen.xml");
	~MainMenuScreen();

	void AddInitialUI() override;
};