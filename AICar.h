#pragma once

#include "Car.h"

class AICar : public Car
{
public:
  AICar(const Vector2& localPosition, const std::string& carDataAsset, const std::vector<Vector2>& trackPoints);
  ~AICar();

  void Update(float elapsedGameTime) override;

private:
  const std::vector<Vector2>& m_trackPoints;
  int m_trackPointIndex;
};