#pragma once

#include "GameObject.h"

#include "CarData.h"

class Car : public GameObject
{
public:
  Car(const Vector2& localPosition, const std::string& carDataAsset);
  ~Car();

  void LoadContent(ID3D11Device* device) override;
  void Initialize() override;

protected:
  const CarData* GetCarData() const { return m_carData.get(); }
  void OnCollision() override;

private:
  std::unique_ptr<CarData> m_carData;
};

