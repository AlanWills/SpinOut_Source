#pragma once

#include "Collider.h"

class RectangleCollider : public Collider
{
public:
  friend class CircleCollider;

	RectangleCollider(BaseObject* parent);
	~RectangleCollider();

	bool CheckCollisionWith(const Vector2& point) override;
  bool CheckCollisionWith(const BoundingOrientedBox& boundingBox) override;
  bool CheckCollisionWith(const BoundingSphere& boundingSphere) override;
  bool CheckCollisionWith(Collider* collider) override;

  void UpdateCollider() override;

private:
	BoundingOrientedBox m_boundingBox;
};

