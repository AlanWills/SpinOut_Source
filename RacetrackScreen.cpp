#include "pch.h"

#include "RacetrackScreen.h"
#include "ScreenManager.h"
#include "Camera.h"

#include "PlayerData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackScreen::RacetrackScreen(ScreenManager* screenManager, const std::string& dataAsset) :
  GameplayScreen(screenManager, dataAsset),
  m_raceScreenData(new RacetrackScreenData(dataAsset)),
  m_playerCar(nullptr)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackScreen::~RacetrackScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreen::LoadContent()
{
  GameplayScreen::LoadContent();

  LoadLevel();

  PlayerCar* playerCar = new PlayerCar(m_startingPositions.front(), PlayerData::GetInstance().GetCurrentCarAsset());
  AddPlayerCar(playerCar);

  //AddAICar(new AICar(m_startingPositions.front(), "Corvette.xml", m_trackPoints));
  
  ScreenManager::GetCamera().FocusOnPosition(playerCar->GetWorldPosition());
  GetScreenManager()->GetCamera().SetToFollowPosition(&playerCar->GetLocalPosition());
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreen::LoadLevel()
{
  m_raceScreenData->LoadData();

  LoadNormalTiles();
  LoadCollisionTiles();
  LoadNormalDecals();
  LoadCollisionDecals();
  LoadStartingPoints();

  m_raceScreenData->FindTrackPoints(m_trackPoints);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreen::LoadNormalTiles()
{
  LevelObjects normalTiles;
  m_raceScreenData->FindNormalTiles(normalTiles);

  for (const LevelObjectInfo& info : normalTiles)
  {
    GameObject* gameObject = new GameObject(info.m_position, info.m_dataAsset, BaseObject::LoadType::kTexture);
    gameObject->SetLocalRotation(info.m_rotation);

    AddGameObject(gameObject, true, true);

    if (info.m_shouldHaveCollider)
    {
      AddCollisionObject(gameObject, true);
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreen::LoadCollisionTiles()
{
  LevelObjects collisionTiles;
  m_raceScreenData->FindCollisionTiles(collisionTiles);

  for (const LevelObjectInfo& info : collisionTiles)
  {
    GameObject* gameObject = new GameObject(info.m_position, info.m_dataAsset, BaseObject::LoadType::kTexture);
    gameObject->SetLocalRotation(info.m_rotation);

    AddGameObject(gameObject, true, true);

    if (info.m_shouldHaveCollider)
    {
      AddCollisionObject(gameObject, true);
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreen::LoadNormalDecals()
{
  LevelObjects normalDecals;
  m_raceScreenData->FindNormalDecals(normalDecals);

  for (const LevelObjectInfo& info : normalDecals)
  {
    GameObject* gameObject = new GameObject(info.m_position, info.m_dataAsset, BaseObject::LoadType::kTexture);
    gameObject->SetLocalRotation(info.m_rotation);

    AddGameObject(gameObject, true, true);

    if (info.m_shouldHaveCollider)
    {
      AddCollisionObject(gameObject, true);
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreen::LoadCollisionDecals()
{
  LevelObjects collisionDecals;
  m_raceScreenData->FindCollisionDecals(collisionDecals);

  for (const LevelObjectInfo& info : collisionDecals)
  {
    GameObject* gameObject = new GameObject(info.m_position, info.m_dataAsset, BaseObject::LoadType::kTexture);
    gameObject->SetLocalRotation(info.m_rotation);

    AddGameObject(gameObject, true, true);

    if (info.m_shouldHaveCollider)
    {
      AddCollisionObject(gameObject, true);
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreen::LoadStartingPoints()
{
  LevelObjects startingPoints;
  m_raceScreenData->FindStartingPoints(startingPoints);

  for (const LevelObjectInfo& info : startingPoints)
  {
    GameObject* gameObject = new GameObject(info.m_position, info.m_dataAsset, BaseObject::LoadType::kTexture);
    gameObject->SetLocalRotation(info.m_rotation);

    AddGameObject(gameObject, true, true);

    if (info.m_shouldHaveCollider)
    {
      AddCollisionObject(gameObject, true);
    }

    m_startingPositions.push_back(info.m_position);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreen::AddPlayerCar(PlayerCar* playerCar)
{
  // Should only have one player car on the racetrack screen
  assert(!m_playerCar);

  AddGameObject(playerCar, true, true);
  m_startingPositions.pop_front();
  m_cars.push_back(playerCar);

  m_playerCar = playerCar;
  //AddCollisionObject(playerCar);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreen::AddAICar(AICar* aiCar)
{
  AddGameObject(aiCar, true, true);
  m_startingPositions.pop_front();
  m_cars.push_back(aiCar);
  //AddCollisionObject(aiCar);
}