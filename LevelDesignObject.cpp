#include "pch.h"

#include "LevelDesignObject.h"
#include "ScreenManager.h"


//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignObject::LevelDesignObject(const Vector2& localPosition, const std::string& dataAsset, bool hasCollider) :
  LevelDesignObject(Vector2::Zero, localPosition, dataAsset, hasCollider)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignObject::LevelDesignObject(const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, bool hasCollider) :
  Image(size, localPosition, dataAsset),
  m_hasCollider(hasCollider)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignObject::~LevelDesignObject()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void LevelDesignObject::HandleInput(float elapsedSeconds, const Vector2& localPosition)
{
  Image::HandleInput(elapsedSeconds, localPosition);

  if (AcceptsInput())
  {
    if (IsMouseOver() && ScreenManager::GetGameMouse().IsClicked(MouseButton::kRightButton))
    {
      Die();
    }
  }
}