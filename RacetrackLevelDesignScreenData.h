#pragma once

#include "LevelDesignScreenData.h"

class RacetrackLevelDesignScreenData : public LevelDesignScreenData
{
public:
  RacetrackLevelDesignScreenData(const std::string& dataAsset);
  ~RacetrackLevelDesignScreenData();

  void SerializeTrackPoints(const std::list<Vector2>& trackPoints);
  void DeserializeTrackPoints(std::list<Vector2>& trackPoints);
};