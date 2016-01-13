#include "pch.h"

#include "RacetrackScreenFactory.h"

#include "Lesson1RacetrackScreen.h"
#include "Lesson2RacetrackScreen.h"
#include "Lesson3RacetrackScreen.h"


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackScreenFactory::RacetrackScreenFactory()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackScreenFactory::~RacetrackScreenFactory()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackScreen* RacetrackScreenFactory::CreateRacetrack(ScreenManager* screenManager, const std::string& name, unsigned int checkPoint)
{
  if (name == "Lesson1RacetrackScreen.xml")
  {
    return new Lesson1RacetrackScreen(screenManager, name, checkPoint);
  }
  else if (name == "Lesson2RacetrackScreen.xml")
  {
    return new Lesson2RacetrackScreen(screenManager, name, checkPoint);
  }
  else if (name == "Lesson3RacetrackScreen.xml")
  {
    return new Lesson3RacetrackScreen(screenManager, name, checkPoint);
  }

  assert(false);
  return nullptr;
}