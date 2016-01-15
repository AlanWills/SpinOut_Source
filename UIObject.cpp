#include "pch.h"

#include "UIObject.h"
#include "ScreenManager.h"


//-----------------------------------------------------------------------------------------------------------------------------------
UIObject::UIObject(const std::string& dataAsset, LoadType loadType, BaseObject* parent, float lifeTime) :
	UIObject(Vector2::Zero, Vector2::Zero, dataAsset, loadType, parent, lifeTime)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
UIObject::UIObject(const Vector2& localPosition, const std::string& dataAsset, LoadType loadType, BaseObject* parent, float lifeTime) :
	UIObject(Vector2::Zero, localPosition, dataAsset, loadType, parent, lifeTime)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
UIObject::UIObject(const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, LoadType loadType, BaseObject* parent, float lifeTime) :
	BaseObject(size, localPosition, dataAsset, loadType, parent),
	m_lifeTime(lifeTime),
	m_currentLifeTime(0),
  m_storedObject(nullptr),
  m_type(kUnSet)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
UIObject::~UIObject()
{
  m_storedObject = nullptr;
}


//-----------------------------------------------------------------------------------------------------------------------------------
void UIObject::Update(float elapsedSeconds)
{
  assert(m_type != UIType::kUnSet);

	BaseObject::Update(elapsedSeconds);

	m_currentLifeTime += elapsedSeconds;
	if (m_currentLifeTime > m_lifeTime)
	{
		// This UIObject has been alive for longer than its lifetime so it dies
		// and will be cleared up by whatever manager is in charge of it
		Die();
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void UIObject::CheckVisible()
{
  if (GetType() == kScreen)
  {
    // If we have a screen UIObject we do not care about using it's collider to update visibility
    return;
  }

  if (GetShouldHaveCollider())
  {
    Vector2 worldPos;

    if (m_type == kScreen)
    {
      worldPos = GetWorldPosition();
    }
    else
    {
      // Translate into screen space
      worldPos = ScreenManager::GetCamera().GameToScreenCoords(GetWorldPosition());
    }

    SetVisible(ScreenManager::GetCamera().GetBoundingFrame().Contains(worldPos) != ContainmentType::DISJOINT);

    if (!IsVisible())
    {
      const Vector2& screenDimensions = ScreenManager::GetScreenDimensions();
      const Vector2& size = GetSize();

      if (size.x > screenDimensions.x || size.y > screenDimensions.y)
      {
        // If we have a really big object just set it's visibility to true for now - improves stability
        SetVisible(true);
        return;
      }

      float halfMaxDimensions = max(size.x, size.y) * 0.5f;

      if (worldPos.x <= 0)
      {
        worldPos.x += halfMaxDimensions;
      }
      else if (worldPos.x >= screenDimensions.x)
      {
        worldPos.x -= halfMaxDimensions;
      }

      if (worldPos.y <= 0)
      {
        worldPos.y += halfMaxDimensions;
      }
      else if (worldPos.y >= screenDimensions.y)
      {
        worldPos.y -= halfMaxDimensions;
      }

      SetVisible(ScreenManager::GetCamera().GetBoundingFrame().Contains(worldPos) != ContainmentType::DISJOINT);
    }
  }
}