#include "pch.h"

#include "LevelDesignDecal.h"
#include "ScreenManager.h"


//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignDecal::LevelDesignDecal(const Vector2& localPosition, const std::string& dataAsset, bool hasCollider) :
  LevelDesignDecal(Vector2::Zero, localPosition, dataAsset, hasCollider)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignDecal::LevelDesignDecal(const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, bool hasCollider) :
  LevelDesignObject(size, localPosition, dataAsset, hasCollider)
{
  SetObjectType(hasCollider ? kCollisionDecal : kNormalDecal);
}


//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignDecal::~LevelDesignDecal()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void LevelDesignDecal::HandleInput(float elapsedSeconds, const Vector2& mousePosition)
{
  LevelDesignObject::HandleInput(elapsedSeconds, mousePosition);

  if (AcceptsInput())
  {
    if (IsSelected())
    {
      if (ScreenManager::GetKeyboardInput().IsKeyDown(Keyboard::A))
      {
        SetLocalRotation(GetLocalRotation() - 0.01f);
      }

      if (ScreenManager::GetKeyboardInput().IsKeyDown(Keyboard::D))
      {
        SetLocalRotation(GetLocalRotation() + 0.01f);
      }
    }
  }
}