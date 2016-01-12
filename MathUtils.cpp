#include "pch.h"

#include "MathUtils.h"
#include "BaseObject.h"


//-----------------------------------------------------------------------------------------------------------------------------------
MathUtils::MathUtils()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
MathUtils::~MathUtils()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
const float MathUtils::GetAngleBetweenObjectAndWorldSpaceVector(const BaseObject* object, const Vector2& v)
{
	Vector2 diffVector2 = v - object->GetWorldPosition();
	float rotation = atan2(diffVector2.x, -diffVector2.y);
	rotation = XMScalarModAngle(rotation);

	return rotation;
}


//-----------------------------------------------------------------------------------------------------------------------------------
const float MathUtils::LerpDown(float currentValue, float targetValue, float amount)
{
	return Clamp<float>(currentValue - amount, targetValue, currentValue);
}


//-----------------------------------------------------------------------------------------------------------------------------------
const int MathUtils::Sign(float input)
{
  return input >= 0 ? 1 : -1;
}


//-----------------------------------------------------------------------------------------------------------------------------------
const float MathUtils::ShortestDistanceBetweenTwoAngles(float angle1, float angle2)
{
  if (angle1 > 0 && angle2 > 0)
  {
    return std::abs(angle1 - angle2);
  }
  else if (angle1 < 0 && angle2 < 0)
  {
    return std::abs(angle1 - angle2);
  }
  else
  {
    return ShortestDistanceBetweenTwoAngles(-angle1, angle1);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
const int MathUtils::GetDirectionToRotate(float angle1, float angle2)
{
  float min = min(angle1, angle2);

  enum MinAngle
  {
    kAngle1,
    kAngle2
  };

  MinAngle minAngle = min == angle1 ? kAngle1 : kAngle2;

  // Map both angles so that one is zero and the other is positive
  angle1 -= min;
  angle2 -= min;

  if (minAngle == kAngle1)
  {
    if (std::abs(angle2 - angle1) < XM_PI)
    {
      return 1;
    }
    else
    {
      return -1;
    }
  }
  else
  {
    if (std::abs(angle1 - angle2) < XM_PI)
    {
      return 1;
    }
    else
    {
      return -1;
    }
  }
}