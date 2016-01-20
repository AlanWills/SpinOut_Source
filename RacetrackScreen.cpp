#include "pch.h"

#include "RacetrackScreen.h"
#include "ScreenManager.h"
#include "Camera.h"

#include "PlayerData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackScreen::RacetrackScreen(ScreenManager* screenManager, const std::string& dataAsset) :
  GameplayScreen(screenManager, dataAsset),
  m_raceScreenData(new RacetrackScreenData(dataAsset)),
  m_playerCar(nullptr),
  m_lapNumber(-1),
  m_maxLapNumber(0),
  m_lapNumberLabel(nullptr),
  m_startingLine(nullptr)
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

  // Always add player car first
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

  std::vector<Vector2> startingLinePoints;
  m_raceScreenData->FindStartingLinePoints(startingLinePoints);

  if (startingLinePoints.size() == 2)
  {
    // Assume it is horizontal, probably want to improve this later on by using the angle of the points too
    Vector2 startingLinePosition((startingLinePoints[0] + startingLinePoints[1]) * 0.5f);
    Vector2 size(startingLinePoints[1].x - startingLinePoints[0].x, 1);
    // Argh oh god oh god oh god
    m_startingLine = new UIObject(size, startingLinePosition, "EmptyBackground.png");

    AddInGameUIObject(m_startingLine, true);
  }
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
  // Don't want the startingline position and player starting position y to be the same otherwise we have problems detecting lap numbers
  assert(m_playerStartingPosition.y != m_startingLine->GetWorldPosition().y);

  AddGameObject(playerCar, true, true);
  m_playerStartingPosition = playerCar->GetWorldPosition();
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


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreen::AddLapNumberLabel(Color colour)
{
  assert(m_maxLapNumber > 0);
  m_lapNumberLabel = new Label(Vector2(GetScreenDimensions().x * 0.9f, GetScreenDimensions().y * 0.1f), L"Lap Number: 0/" + std::to_wstring(m_maxLapNumber));
  m_lapNumberLabel->SetColour(colour);

  AddScreenUIObject(m_lapNumberLabel, true, true);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreen::Update(float elapsedSeconds)
{
  GameplayScreen::Update(elapsedSeconds);

  if (ShouldUpdateGame())
  {
    if (m_startingLine)
    {
      assert(m_startingLine->GetCollider());
      m_startingLine->GetCollider()->CheckCollisionWith(GetPlayerCar()->GetCollider());
      // There will be a one frame delay between collision and us entering this condition, so do not try to optimise by using the result from CheckCollisionWith
      if (m_startingLine->GetCollider()->GetCollisionStatus() == CollisionStatus::kJustCollided)
      {
        // 1 corresponds to down the screen, -1 to up the screen
        // Player StartingPosition y is greater that starting line so we need to go up the screen to cross
        int startDirection = m_playerStartingPosition.y - m_startingLine->GetWorldPosition().y > 0 ? -1 : 1;
        // Do same check for player car to see which direction we have crossed the line
        int playerDirection = m_playerCar->GetWorldPosition().y - m_startingLine->GetWorldPosition().y > 0 ? -1 : 1;

        // If playerDirection is the same as the direction we need to go to properly cross the line we increment our lap number, else we decrement it
        playerDirection == startDirection ? m_lapNumber++ : m_lapNumber--;

        // Update lap label UI
        if (m_lapNumberLabel)
        {
          m_lapNumberLabel->SetText(L"Lap Number: " + std::to_wstring(m_lapNumber) + L"/" + std::to_wstring(m_maxLapNumber));
        }
      }
    }
  }
}