#pragma once

#include "Collider.h"

class CircleCollider : public Collider
{
public:
  friend class RectangleCollider;

	CircleCollider(BaseObject* parent);
	~CircleCollider();

	bool CheckCollisionWith(const Vector2& point) override;
  bool CheckCollisionWith(const BoundingOrientedBox& boundingBox) override;
  bool CheckCollisionWith(const BoundingSphere& boundingSphere) override;
  bool CheckCollisionWith(Collider* collider) override;

  void UpdateCollider() override;

private:
	BoundingSphere m_boundingSphere;
};

