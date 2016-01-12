#include "pch.h"

#include "DrivingLessonScreenData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
DrivingLessonScreenData::DrivingLessonScreenData(const std::string& dataAsset) :
  RaceScreenData(dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
DrivingLessonScreenData::~DrivingLessonScreenData()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
const char* DrivingLessonScreenData::GetLessonDescription() const
{
  return ConstGetDocument()->RootElement()->FirstChildElement("LessonDescription")->GetText();
}