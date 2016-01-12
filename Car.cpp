#include "pch.h"

#include "Car.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Car::Car(const Vector2& localPosition, const std::string& carDataAsset) :
  GameObject(localPosition, carDataAsset),
  m_carData(new CarData(carDataAsset))
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Car::~Car()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Car::LoadContent(ID3D11Device* device)
{
  BaseObject::LoadContent(device);

  m_carData->LoadData();

  LoadTexture(device, m_carData->GetTextureAsset());
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Car::Initialize()
{
  GameObject::Initialize();

  GetRigidBody()->SetMaxLinearVelocity(m_carData->GetTopSpeed());
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Car::OnCollision()
{
  if (IsActive())
  {
    RigidBody* rigidBody = GetRigidBody();

    if (GetCollider()->GetCollisionStatus() == CollisionStatus::kJustCollided)
    {
      // If this causes us to collide with something next frame we are in trouble
      // Need to handle this when still colliding somehow
      rigidBody->SetLinearAcceleration(Vector2(0, -rigidBody->GetLinearAcceleration().y * 0.5f));
      rigidBody->SetLinearVelocity(Vector2(0, -rigidBody->GetLinearVelocity().y * 0.5f));
    }
  }
}