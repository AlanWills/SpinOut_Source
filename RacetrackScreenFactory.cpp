#include "pch.h"

#include "RacetrackScreenFactory.h"

#include "Lesson1RacetrackScreen.h"
#include "Lesson2RacetrackScreen.h"
#include "Lesson3RacetrackScreen.h"
#include "Lesson4RacetrackScreen.h"


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
  std::string dataAsset = name + ".xml";

  if (name == "Lesson1RacetrackScreen")
  {
    return new Lesson1RacetrackScreen(screenManager, dataAsset, checkPoint);
  }
  else if (name == "Lesson2RacetrackScreen")
  {
    return new Lesson2RacetrackScreen(screenManager, dataAsset, checkPoint);
  }
  else if (name == "Lesson3RacetrackScreen")
  {
    return new Lesson3RacetrackScreen(screenManager, dataAsset, checkPoint);
  }
  else if (name == "Lesson4RacetrackScreen")
  {
    return new Lesson4RacetrackScreen(screenManager, dataAsset, checkPoint);
  }

  assert(false);
  return nullptr;
}