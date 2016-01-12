#include "pch.h"

#include "LevelDesignTile.h"


//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignTile::LevelDesignTile(const Vector2& localPosition, const std::string& dataAsset, bool hasCollider) :
  LevelDesignTile(Vector2::Zero, localPosition, dataAsset, hasCollider)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignTile::LevelDesignTile(const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, bool hasCollider) :
  LevelDesignObject(size, localPosition, dataAsset, hasCollider)
{
  SetObjectType(hasCollider ? kCollisionTile : kNormalTile);
}


//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignTile::~LevelDesignTile()
{
}
