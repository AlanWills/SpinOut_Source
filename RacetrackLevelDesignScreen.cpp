#include "pch.h"

#include "RacetrackLevelDesignScreen.h"
#include "ScreenManager.h"


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackLevelDesignScreen::RacetrackLevelDesignScreen(ScreenManager* screenManager, const std::string& screenDataAsset, const std::string& levelDataAsset) :
  LevelDesignScreen(screenManager, screenDataAsset, levelDataAsset),
  m_racetrackLevelData(new RacetrackLevelDesignScreenData(levelDataAsset))
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackLevelDesignScreen::~RacetrackLevelDesignScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackLevelDesignScreen::LoadContent()
{
  LevelDesignScreen::LoadContent();

  m_racetrackLevelData->LoadData();

  DeserializeLevel();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackLevelDesignScreen::HandleInput(float elapsedGameTime)
{
  LevelDesignScreen::HandleInput(elapsedGameTime);

  if (AcceptsInput())
  {
    GameMouse& gameMouse = GetScreenManager()->GetGameMouse();

    if (gameMouse.IsClicked(MouseButton::kMiddleButton))
    {
      m_trackPoints.push_back(gameMouse.GetInGamePosition());
      AddInGameUIObject(new UIObject(gameMouse.GetInGamePosition(), "Marker.png"), true, true);
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackLevelDesignScreen::SerializeLevel()
{
  std::list<LevelDesignObject*> levelObjects;
  FindInGameUIObjectsAs<LevelDesignObject>(levelObjects);

  m_racetrackLevelData->SerializeLevel(levelObjects);
  m_racetrackLevelData->SerializeTrackPoints(m_trackPoints);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackLevelDesignScreen::DeserializeLevel()
{
  std::list<LevelDesignObject*> levelObjects;
  m_racetrackLevelData->DeserializeLevel(levelObjects);

  for (LevelDesignObject* levelObject : levelObjects)
  {
    AddInGameUIObject(levelObject, true, true);
  }

  m_racetrackLevelData->DeserializeTrackPoints(m_trackPoints);

  for (const Vector2& trackPoint : m_trackPoints)
  {
    AddInGameUIObject(new UIObject(trackPoint, "Marker.png"), true, true);
  }
}