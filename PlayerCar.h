#pragma once

#include "Car.h"

class PlayerCar : public Car
{
public:
  PlayerCar(const Vector2& localPosition, const std::string& playerCarDataAsset);
  ~PlayerCar();

  void HandleInput(float elapsedGameTime, const Vector2& mousePosition) override;
};

