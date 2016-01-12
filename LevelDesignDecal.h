#pragma once

#include "LevelDesignObject.h"

class LevelDesignDecal : public LevelDesignObject
{
public:
  LevelDesignDecal(const Vector2& localPosition, const std::string& dataAsset, bool hasCollider);
  LevelDesignDecal(const Vector2& size, const Vector2& gridPosition, const std::string& dataAsset, bool hasCollider);
  ~LevelDesignDecal();

  void HandleInput(float elapsedSeconds, const Vector2& mousePosition) override;
};

