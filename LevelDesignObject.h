#pragma once

#include "Image.h"

enum LevelDesignObjectType
{
  kNormalTile,
  kCollisionTile,
  kNormalDecal,
  kCollisionDecal,
  kStartingPosition
};

class LevelDesignObject : public Image
{
public:
  LevelDesignObject(const Vector2& gridPosition, const std::string& dataAsset, bool hasCollider);
  LevelDesignObject(const Vector2& size, const Vector2& gridPosition, const std::string& dataAsset, bool hasCollider);
  ~LevelDesignObject();

  void HandleInput(float elapsedSeconds, const Vector2& localPosition) override;

  bool HasCollider() const { return m_hasCollider; }
  LevelDesignObjectType GetObjectType() const { return m_objectType; }

protected:
  void SetObjectType(LevelDesignObjectType type) { m_objectType = type; }

private:
  // Used purely for serialization - does not affect the collider of the level object itself
  bool m_hasCollider;
  LevelDesignObjectType m_objectType;
};