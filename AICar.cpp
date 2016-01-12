#include "pch.h"

#include "AICar.h"


//-----------------------------------------------------------------------------------------------------------------------------------
AICar::AICar(const Vector2& localPosition, const std::string& carDataAsset, const std::vector<Vector2>& trackPoints) :
  Car(localPosition, carDataAsset),
  m_trackPoints(trackPoints),
  m_trackPointIndex(0)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
AICar::~AICar()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void AICar::Update(float elapsedGameTime)
{
  Car::Update(elapsedGameTime);

  if (IsActive())
  {
    RigidBody* rigidBody = GetRigidBody();
    const CarData* carData = GetCarData();

    float distanceToTrackPoint = Vector2::DistanceSquared(m_trackPoints[m_trackPointIndex], GetWorldPosition());
    if (distanceToTrackPoint < GetSize().LengthSquared())
    {
      m_trackPointIndex++;
      m_trackPointIndex %= m_trackPoints.size();
    }

    float targetAngle = MathUtils::GetAngleBetweenObjectAndWorldSpaceVector(this, m_trackPoints[m_trackPointIndex]);
    float angleDiff = std::abs(targetAngle - GetWorldRotation());
    angleDiff = XMScalarModAngle(angleDiff);

    rigidBody->SetLinearAcceleration(Vector2(0, carData->GetAcceleration() * (carData->GetHandling() - std::abs(angleDiff))));

    if (angleDiff > 0.15f)
    {
      rigidBody->SetAngularAcceleration(0.25f * angleDiff / elapsedGameTime * MathUtils::GetDirectionToRotate(targetAngle, GetWorldRotation()));
    }
    else
    {
      rigidBody->FullAngularStop();
      SetLocalRotation(targetAngle);
    }
  }
}