#pragma once

#include "LevelDesignScreen.h"

#include "RacetrackLevelDesignScreenData.h"

class RacetrackLevelDesignScreen : public LevelDesignScreen
{
public:
  RacetrackLevelDesignScreen(ScreenManager* screenManager, const std::string& screenDataAsset, const std::string& levelDataAsset);
  ~RacetrackLevelDesignScreen();

  void LoadContent() override;
  void HandleInput(float elapsedGameTime) override;

protected:
  void SerializeLevel() override;
  void DeserializeLevel() override;

private:
  std::list<Vector2> m_trackPoints;
  std::list<Vector2> m_startLinePoints;

  /// \brief Pointer to the data class which will be used to serialize the level data
  std::unique_ptr<RacetrackLevelDesignScreenData> m_racetrackLevelData;
};