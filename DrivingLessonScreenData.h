#pragma once

#include "RaceScreenData.h"

class DrivingLessonScreenData : public RaceScreenData
{
public:
  DrivingLessonScreenData(const std::string& dataAsset);
  ~DrivingLessonScreenData();

  const char* GetLessonDescription() const;
};