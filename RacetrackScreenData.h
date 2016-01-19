#pragma once

#include "BaseScreenData.h"

#include "UIObject.h"
#include "GameObject.h"

#include <list>

struct LevelObjectInfo
{
  Vector2       m_position;
  std::string   m_dataAsset;
  float         m_rotation;
  bool          m_shouldHaveCollider;
};

typedef std::list<LevelObjectInfo> LevelObjects;

class RacetrackScreenData : public BaseScreenData
{
public:
  RacetrackScreenData(const std::string& dataAsset);
  ~RacetrackScreenData();

  const char* GetTrackName() const;
  const char* GetDescription() const;
  const char* GetThumbnailAsset() const;

  void FindNormalTiles(LevelObjects& levelObjects) const;
  void FindCollisionTiles(LevelObjects& levelObjects) const;
  void FindNormalDecals(LevelObjects& levelObjects) const;
  void FindCollisionDecals(LevelObjects& levelObjects) const;
  void FindStartingPoints(LevelObjects& levelObjects) const;
  void FindTrackPoints(std::vector<Vector2>& trackPoints) const;

private:
  LevelObjectInfo DeserializeObject(const tinyxml2::XMLElement* element) const;
};