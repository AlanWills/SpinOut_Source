#include "pch.h"

#include "PlayerData.h"

//-----------------------------------------------------------------------------------------------------------------------------------
PlayerData::PlayerData() :
  BaseData("PlayerData.xml"),
  m_currentLicenseLevel(3)
{
  m_carAssets.push_back("Corvette.xml");

  m_currentCarAsset = m_carAssets.front();
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