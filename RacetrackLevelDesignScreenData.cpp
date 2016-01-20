#include "pch.h"
#include "RacetrackLevelDesignScreenData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackLevelDesignScreenData::RacetrackLevelDesignScreenData(const std::string& dataAsset) :
  LevelDesignScreenData(dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackLevelDesignScreenData::~RacetrackLevelDesignScreenData()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackLevelDesignScreenData::SerializeTrackPoints(const std::list<Vector2>& trackPoints)
{
  SerializeVectorList(trackPoints, "TrackPoints");
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackLevelDesignScreenData::DeserializeTrackPoints(std::list<Vector2>& trackPoints)
{
  DeserializeVectorList(trackPoints, "TrackPoints");
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackLevelDesignScreenData::SerializeStartLinePoints(const std::list<Vector2>& startLinePoints)
{
  SerializeVectorList(startLinePoints, "StartingLinePoints");
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackLevelDesignScreenData::DeserializeStartLinePoints(std::list<Vector2>& startLinePoints)
{
  DeserializeVectorList(startLinePoints, "StartingLinePoints");
}