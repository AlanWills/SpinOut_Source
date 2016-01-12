#pragma once

#include "LevelDesignObject.h"

class LevelDesignStartingPosition : public LevelDesignObject
{
public:
  LevelDesignStartingPosition(const Vector2& localPosition, const std::string& dataAsset, bool hasCollider);
  LevelDesignStartingPosition(const Vector2& size, const Vector2& gridPosition, const std::string& dataAsset, bool hasCollider);
  ~LevelDesignStartingPosition();
};

