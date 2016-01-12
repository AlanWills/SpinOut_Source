#pragma once

#include "BaseObject.h"

class UIObject : public BaseObject
{
public:
  enum UIType
  {
    kScreen,
    kInGame,

    kUnSet
  };

	UIObject(const std::string& dataAsset, LoadType loadType = LoadType::kTexture, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
	UIObject(const Vector2& localPosition, const std::string& dataAsset, LoadType loadType = LoadType::kTexture, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
	UIObject(const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, LoadType loadType = LoadType::kTexture, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
  virtual ~UIObject();

	void Update(float elapsedSeconds) override;

  void SetStoredObject(void* storedObject) { m_storedObject = storedObject; }

  template <typename T>
  T GetStoredObjectAs() const { return static_cast<T>(m_storedObject); }

  void SetType(UIType type) { m_type = type; }
  UIType GetType() const { return m_type; }

protected:
  void CheckVisible() override;

private:
	float m_lifeTime;
	float m_currentLifeTime;

  void* m_storedObject;

  UIType m_type;
};

