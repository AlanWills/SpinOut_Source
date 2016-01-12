#include "pch.h"

#include "CircleCollider.h"
#include "RectangleCollider.h"

#include "BaseObject.h"


//-----------------------------------------------------------------------------------------------------------------------------------
CircleCollider::CircleCollider(BaseObject* parent) :
	Collider(parent)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
CircleCollider::~CircleCollider()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void CircleCollider::UpdateCollider()
{
  Collider::UpdateCollider();

	Vector2 parentWorldPos = GetParent()->GetWorldPosition();
	float radius = max(GetParent()->GetSize().x * 0.5f, GetParent()->GetSize().y * 0.5f);

	m_boundingSphere.Center = Vector3(parentWorldPos.x, parentWorldPos.y, 0);
	m_boundingSphere.Radius = radius;
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool CircleCollider::CheckCollisionWith(const Vector2& point)
{
	ContainmentType containmentType = m_boundingSphere.Contains(point);
	bool result = containmentType != ContainmentType::DISJOINT;

  if (result)
  {
    CollisionOccurred();
  }

  return result;
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool CircleCollider::CheckCollisionWith(const BoundingOrientedBox& boundingBox)
{
  bool result = m_boundingSphere.Intersects(boundingBox);

  if (result)
  {
    CollisionOccurred();
  }

  return result;
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool CircleCollider::CheckCollisionWith(const BoundingSphere& boundingSphere)
{
  bool result = m_boundingSphere.Intersects(boundingSphere);

  if (result)
  {
    CollisionOccurred();
  }

  return result;
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool CircleCollider::CheckCollisionWith(Collider* collider)
{
  bool result = false;
  
  if (dynamic_cast<CircleCollider*>(collider))
  {
    result = CheckCollisionWith(dynamic_cast<CircleCollider*>(collider)->m_boundingSphere);
  }
  else if (dynamic_cast<RectangleCollider*>(collider))
  {
    result = CheckCollisionWith(dynamic_cast<RectangleCollider*>(collider)->m_boundingBox);
  }
  else
  {
    assert(false);
  }

  if (result)
  {
    CollisionOccurred();
  }

  return result;
}