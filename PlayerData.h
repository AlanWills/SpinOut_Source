#pragma once

#include "BaseData.h"

#include <list>

#define LICENSE_TEST_1 4

class PlayerData : public BaseData
{
public:
  ~PlayerData();

  static PlayerData& GetInstance();

  PlayerData(PlayerData const&) = delete;
  void operator=(PlayerData const&) = delete;

  // Gets and sets the current car used by the player in races
  const std::string& GetCurrentCarAsset() const { return m_currentCarAsset; }
  void SetCurrentCarAsset(const std::string& currentCarAsset) { m_currentCarAsset = currentCarAsset; }

  const std::list<std::string>& GetCarAssets() const { return m_carAssets; }
  void AddCarAsset(const std::string& carAsset) { m_carAssets.push_back(carAsset); }

  size_t GetCurrentLicenseLevel() const { return m_currentLicenseLevel; }

  /// \brief Sets the current license level of the player to the max of either the input or their current level
  void SetCurrentLicenseLevel(int currentLicenseLevel);

  bool HasPassedTest(size_t test) { return m_currentLicenseLevel >= test; }

private:
  PlayerData();

  std::string m_currentCarAsset;
  std::list<std::string> m_carAssets;

  size_t m_currentLicenseLevel;
};

