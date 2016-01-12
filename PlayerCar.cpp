#include "pch.h"

#include "ScreenManager.h"

#include "PlayerCar.h"


//-----------------------------------------------------------------------------------------------------------------------------------
PlayerCar::PlayerCar(const Vector2& localPosition, const std::string& playerCarDataAsset) :
  Car(localPosition, playerCarDataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
PlayerCar::~PlayerCar()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void PlayerCar::HandleInput(float elapsedGameTime, const Vector2& mousePosition)
{
  Car::HandleInput(elapsedGameTime, mousePosition);

  if (AcceptsInput())
  {
    const KeyboardInput& keyboard = ScreenManager::GetKeyboardInput();
    float velocityDiff = 0;
    float angleDiff = 0;

    bool notCollided = GetCollider()->GetCollisionStatus() == CollisionStatus::kStillNotCollided;

    if (keyboard.IsKeyDown(Keyboard::Keys::W) && notCollided)
    {
      velocityDiff += GetCarData()->GetAcceleration();
    }

    if (keyboard.IsKeyDown(Keyboard::Keys::S) && notCollided)
    {
      velocityDiff += -GetCarData()->GetBraking();
    }

    if (keyboard.IsKeyDown(Keyboard::Keys::A))
    {
      angleDiff = -GetCarData()->GetHandling();
    }

    if (keyboard.IsKeyDown(Keyboard::Keys::D))
    {
      angleDiff = GetCarData()->GetHandling();
    }

    GetRigidBody()->SetLinearAcceleration(Vector2(0, velocityDiff));
    GetRigidBody()->SetAngularVelocity(angleDiff);
  }
}