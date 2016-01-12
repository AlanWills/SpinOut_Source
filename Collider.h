#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;

// Get a circulate dependency otherwise with BaseObject.h - DO NOT REMOVE THIS
class BaseObject;

enum CollisionStatus
{
  kJustCollided,
  kStillCollided,
  kJustNotCollided,
  kStillNotCollided,
};

class Collider
{
public:
	Collider(BaseObject* m_parent);
	virtual ~Collider();

	virtual bool CheckCollisionWith(const Vector2& point) = 0;
  virtual bool CheckCollisionWith(const BoundingOrientedBox& boundingBox) = 0;
  virtual bool CheckCollisionWith(const BoundingSphere& boundingSphere) = 0;
  virtual bool CheckCollisionWith(Collider* collider) = 0;

  /// \brief Updates the collider to match up with the parent's size and position
  /// and the collision status of the collider too
  /// IMPORTANT, THIS MUST BE CALLED BEFORE ANY COLLISION CHECKING
  virtual void UpdateCollider();

  CollisionStatus GetCollisionStatus() const { return m_collisionStatus; }
  bool HasCollided() const;

protected:
  void CollisionOccurred() { m_collidedThisFrame = true; }

	const BaseObject* GetParent() const { return m_parent; }

private:
	// Can't use a unique_ptr because we need the header file to do so
	BaseObject* m_parent;

  // Indication of collision status
  CollisionStatus m_collisionStatus;
  bool m_collidedThisFrame;
};