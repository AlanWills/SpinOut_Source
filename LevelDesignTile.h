#pragma once

#include "LevelDesignObject.h"

class LevelDesignTile : public LevelDesignObject
{
public:
  LevelDesignTile(const Vector2& localPosition, const std::string& dataAsset, bool hasCollider);
  LevelDesignTile(const Vector2& size, const Vector2& gridPosition, const std::string& dataAsset, bool hasCollider);
  ~LevelDesignTile();
};

