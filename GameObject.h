#pragma once

#include "BaseObject.h"
#include "RigidBody.h"

#include <list>

class GameObject : public BaseObject
{
public:
	GameObject(const std::string& dataAsset, LoadType loadType = LoadType::kData, BaseObject* parent = nullptr);
	GameObject(const Vector2& localPosition, const std::string& dataAsset, LoadType loadType = LoadType::kData, BaseObject* parent = nullptr);
	GameObject(const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, LoadType loadType = LoadType::kData, BaseObject* parent = nullptr);
  virtual ~GameObject();

	void Initialize() override;
	void Update(float elapsedSeconds) override;

	RigidBody* GetRigidBody() const { return m_rigidBody.get(); }

  bool CheckCollisionWithObjects(const std::list<GameObject*>& collisionObjects);

  /// \brief Sets the no collision bool.  A value of true will result in no collision checking - used for static colliders
  void SetNoCollisions(bool noCollisions) { m_noCollisions = noCollisions; }

protected:
  virtual void OnCollision() { }
  void CheckVisible() override;

private:
	float m_health;
	std::unique_ptr<RigidBody> m_rigidBody;

  // A bool used to skip the checking collision step
  bool m_noCollisions;
};

