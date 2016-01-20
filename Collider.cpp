#include "pch.h"
#include "Collider.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Collider::Collider(BaseObject* parent) :
	m_parent(parent),
  m_collisionStatus(kStillNotCollided),
  m_collidedThisFrame(false)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Collider::~Collider()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Collider::UpdateCollider()
{
  // Take out out of date status and update it using the collision status from the last frame
  switch (m_collisionStatus)
  {
  case CollisionStatus::kJustCollided:
    m_collisionStatus = m_collidedThisFrame ? kStillCollided : kJustNotCollided;
    break;

  case CollisionStatus::kStillCollided:
    m_collisionStatus = m_collidedThisFrame ? kStillCollided : kJustNotCollided;
    break;

  case CollisionStatus::kJustNotCollided:
    m_collisionStatus = m_collidedThisFrame ? kJustCollided : kStillNotCollided;
    break;

  case CollisionStatus::kStillNotCollided:
    m_collisionStatus = m_collidedThisFrame ? kJustCollided : kStillNotCollided;
    break;
  }

  m_collidedThisFrame = false;
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool Collider::HasCollided() const
{
  return m_collisionStatus == CollisionStatus::kJustCollided || m_collisionStatus == CollisionStatus::kStillCollided;
}