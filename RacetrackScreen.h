#pragma once

#include "GameplayScreen.h"

#include "RacetrackScreenData.h"

#include "Car.h"
#include "PlayerCar.h"
#include "AICar.h"

#define REGISTER_RACETRACK(name, defaultAsset) \
protected: \
  name(ScreenManager* screenManager, const std::string& dataAsset = defaultAsset); \
public: \
  virtual ~name(); \
  name(name const&) = delete; \
  void operator=(name const&) = delete; \
\
friend class RacetrackScreenFactory;

#define REGISTER_RACETRACK_CHECKPOINTS(name, defaultAsset, checkPoints) \
protected: \
  name(ScreenManager* screenManager, const std::string& dataAsset = defaultAsset, unsigned int checkPoint = 0); \
public: \
  virtual ~name(); \
  name(name const&) = delete; \
  void operator=(name const&) = delete; \
\
private: \
checkPoints m_checkPoint;\
\
friend class RacetrackScreenFactory;


class RacetrackScreen : public GameplayScreen
{
public:
  REGISTER_RACETRACK(RacetrackScreen, "")

  void LoadContent() override;
  virtual void LoadLevel();

  PlayerCar* GetPlayerCar() const { return m_playerCar; }

protected:
  virtual void LoadNormalTiles();
  virtual void LoadCollisionTiles();
  virtual void LoadNormalDecals();
  virtual void LoadCollisionDecals();
  virtual void LoadStartingPoints();

protected:
  const std::vector<Vector2>& GetTrackPoints() const { return m_trackPoints; }

private:
  void AddPlayerCar(PlayerCar* playerCar);
  void AddAICar(AICar* aiCar);

  std::unique_ptr<RacetrackScreenData> m_raceScreenData;

  std::list<Vector2> m_startingPositions;
  std::vector<Vector2> m_trackPoints;
  std::list<Car*> m_cars;

  PlayerCar* m_playerCar;
};