#include "pch.h"

#include "RectangleCollider.h"
#include "CircleCollider.h"

#include "BaseObject.h"


//-----------------------------------------------------------------------------------------------------------------------------------
RectangleCollider::RectangleCollider(BaseObject* parent) :
	Collider(parent)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
RectangleCollider::~RectangleCollider()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RectangleCollider::UpdateCollider()
{
  Collider::UpdateCollider();

	const Vector2& parentWorldPos = GetParent()->GetWorldPosition();
	float parentWorldRot = GetParent()->GetWorldRotation();

	m_boundingBox.Center = Vector3(parentWorldPos.x, parentWorldPos.y, 0); 
	m_boundingBox.Extents = Vector3(GetParent()->GetSize().x * 0.5f, GetParent()->GetSize().y * 0.5f, 0.001f);
	m_boundingBox.Orientation = Quaternion::CreateFromRotationMatrix(Matrix::CreateRotationZ(parentWorldRot));

	// May need to use this instead
	//m_boundingBox.Transform(m_boundingBox, 1, Vector3(parentWorldRot), Vector3(parentWorldPos.x, parentWorldPos.y, 0));
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool RectangleCollider::CheckCollisionWith(const Vector2& point)
{
	ContainmentType containmentType = m_boundingBox.Contains(point);
	bool result = containmentType != ContainmentType::DISJOINT;

  if (result)
  {
    CollisionOccurred();
  }

  return result;
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool RectangleCollider::CheckCollisionWith(const BoundingOrientedBox& boundingBox)
{
  bool result = m_boundingBox.Intersects(boundingBox);

  if (result)
  {
    CollisionOccurred();
  }

  return result;
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool RectangleCollider::CheckCollisionWith(const BoundingSphere& boundingSphere)
{
  bool result = m_boundingBox.Intersects(boundingSphere);

  if (result)
  {
    CollisionOccurred();
  }

  return result;
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool RectangleCollider::CheckCollisionWith(Collider* collider)
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