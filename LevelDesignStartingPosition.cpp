#include "pch.h"

#include "LevelDesignStartingPosition.h"


//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignStartingPosition::LevelDesignStartingPosition(const Vector2& localPosition, const std::string& dataAsset, bool hasCollider) :
  LevelDesignStartingPosition(Vector2::Zero, localPosition, dataAsset, hasCollider)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignStartingPosition::LevelDesignStartingPosition(const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, bool hasCollider) :
  LevelDesignObject(size, localPosition, dataAsset, hasCollider)
{
  SetObjectType(kStartingPosition);
}


//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignStartingPosition::~LevelDesignStartingPosition()
{
}
