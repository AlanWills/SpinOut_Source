#pragma once

#include "BaseScreenData.h"

#include "UIObject.h"
#include "GameObject.h"

#include <list>

struct RacetrackObjectInfo
{
  Vector2       m_position;
  std::string   m_dataAsset;
  float         m_rotation;
  bool          m_shouldHaveCollider;
};

typedef std::list<RacetrackObjectInfo> RacetrackObjects;

class RacetrackScreenData : public BaseScreenData
{
public:
  RacetrackScreenData(const std::string& dataAsset);
  ~RacetrackScreenData();

  const char* GetTrackName() const;
  const char* GetDescription() const;
  const char* GetThumbnailAsset() const;

  void FindNormalTiles(RacetrackObjects& levelObjects) const;
  void FindCollisionTiles(RacetrackObjects& levelObjects) const;
  void FindNormalDecals(RacetrackObjects& levelObjects) const;
  void FindCollisionDecals(RacetrackObjects& levelObjects) const;
  void FindStartingPoints(RacetrackObjects& levelObjects) const;
  void FindTrackPoints(std::vector<Vector2>& trackPoints) const;

private:
  RacetrackObjectInfo DeserializeObject(const tinyxml2::XMLElement* element) const;
};