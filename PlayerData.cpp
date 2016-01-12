#include "pch.h"

#include "PlayerData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
PlayerData::PlayerData() :
  BaseData("PlayerData.xml"),
  m_currentLicenseLevel(1)
{
  m_carAssets.push_back("Corvette.xml");
}


//-----------------------------------------------------------------------------------------------------------------------------------
PlayerData::~PlayerData()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
PlayerData& PlayerData::GetInstance()
{
  static PlayerData playerData;

  return playerData;
}


//-----------------------------------------------------------------------------------------------------------------------------------
void PlayerData::SetCurrentLicenseLevel(int currentLicenseLevel)
{
  m_currentLicenseLevel = MathUtils::Clamp<size_t>(m_currentLicenseLevel, m_currentLicenseLevel, currentLicenseLevel);
}