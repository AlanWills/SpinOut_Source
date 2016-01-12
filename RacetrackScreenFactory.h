#pragma once

#include "RacetrackScreen.h"

class RacetrackScreenFactory
{
public:
  RacetrackScreenFactory();
  ~RacetrackScreenFactory();

  static RacetrackScreen* CreateRacetrack(ScreenManager* screenManager, const std::string& name);
};