#include "pch.h"

#include "GameObject.h"
#include "ScreenManager.h"
#include "RigidBody.h"


//-----------------------------------------------------------------------------------------------------------------------------------
GameObject::GameObject(const std::string& dataAsset, LoadType loadType, BaseObject* parent) :
	GameObject(Vector2::Zero, Vector2::Zero, dataAsset, loadType, parent)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
GameObject::GameObject(const Vector2& localPosition, const std::string& dataAsset, LoadType loadType, BaseObject* parent) :
	GameObject(Vector2::Zero, localPosition, dataAsset, loadType, parent)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
GameObject::GameObject(const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, LoadType loadType, BaseObject* parent) :
	BaseObject(size, localPosition, dataAsset, loadType, parent),
	m_rigidBody(nullptr),
	m_health(1),
  m_noCollisions(false)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
GameObject::~GameObject()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameObject::Initialize()
{
	BaseObject::Initialize();

	m_rigidBody.reset(new RigidBody(this));
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameObject::Update(float elapsedSeconds)
{
	BaseObject::Update(elapsedSeconds);

	if (IsActive())
	{
		if (m_health <= 0)
		{
			Die();
		}

		assert(m_rigidBody);
		m_rigidBody->Update(elapsedSeconds);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameObject::CheckVisible()
{
  Vector2 worldPos(ScreenManager::GetCamera().GameToScreenCoords(GetWorldPosition()));
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
    else if (worldPos.x >= ScreenManager::GetScreenDimensions().x)
    {
      worldPos.x -= halfMaxDimensions;
    }

    if (worldPos.y <= 0)
    {
      worldPos.y += halfMaxDimensions;
    }
    else if (worldPos.y >= ScreenManager::GetScreenDimensions().y)
    {
      worldPos.y -= halfMaxDimensions;
    }

    SetVisible(ScreenManager::GetCamera().GetBoundingFrame().Contains(worldPos) != ContainmentType::DISJOINT);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool GameObject::CheckCollisionWithObjects(const std::list<GameObject*>& collisionObjects)
{
  if (!GetCollider() || m_noCollisions)
  {
    return false;
  }

  for (GameObject* gameObject : collisionObjects)
  {
    if (gameObject == this)
    {
      continue;
    }

    // Check distance away from object before doing proper collision detection
    if (Vector2::DistanceSquared(GetWorldPosition(), gameObject->GetWorldPosition()) >= (GetSize() * 0.5f).LengthSquared() + (gameObject->GetSize() * 0.5f).LengthSquared())
    {
      continue;
    }

    if (GetCollider()->CheckCollisionWith(gameObject->GetCollider()))
    {
      OnCollision();

      return true;
    }
  }

  return false;
}