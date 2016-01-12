#include "pch.h"

#include "RacetrackScreenFactory.h"

#include "Lesson1RacetrackScreen.h"
#include "Lesson2RacetrackScreen.h"


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackScreenFactory::RacetrackScreenFactory()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackScreenFactory::~RacetrackScreenFactory()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackScreen* RacetrackScreenFactory::CreateRacetrack(ScreenManager* screenManager, const std::string& name)
{
  if (name == "Lesson1RacetrackScreen.xml")
  {
    return new Lesson1RacetrackScreen(screenManager, name);
  }
  else if (name == "Lesson2RacetrackScreen.xml")
  {
    return new Lesson2RacetrackScreen(screenManager, name);
  }

  assert(false);
  return nullptr;
}