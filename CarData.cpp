#include "pch.h"

#include "CarData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
CarData::CarData(const std::string& carDataAsset) :
  BaseData(carDataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
CarData::~CarData()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
const char* CarData::GetDisplayName() const
{
  return ConstGetDocument()->RootElement()->FirstChildElement("DisplayName")->GetText();
}


//-----------------------------------------------------------------------------------------------------------------------------------
const char* CarData::GetTextureAsset() const
{
  return ConstGetDocument()->RootElement()->FirstChildElement("TextureAsset")->GetText();
}


//-----------------------------------------------------------------------------------------------------------------------------------
const char* CarData::GetDescription() const
{
  return ConstGetDocument()->RootElement()->FirstChildElement("Description")->GetText();
}


//-----------------------------------------------------------------------------------------------------------------------------------
const float CarData::GetTopSpeed() const
{
  float topSpeed = 0;
  ConstGetDocument()->RootElement()->FirstChildElement("TopSpeed")->QueryFloatText(&topSpeed);
  return topSpeed;
}


//-----------------------------------------------------------------------------------------------------------------------------------
const float CarData::GetAcceleration() const
{
  float acceleration = 0;
  ConstGetDocument()->RootElement()->FirstChildElement("Acceleration")->QueryFloatText(&acceleration);
  return acceleration;
}


//-----------------------------------------------------------------------------------------------------------------------------------
const float CarData::GetBraking() const
{
  float braking = 0;
  ConstGetDocument()->RootElement()->FirstChildElement("Braking")->QueryFloatText(&braking);
  return braking;
}


//-----------------------------------------------------------------------------------------------------------------------------------
const float CarData::GetHandling() const
{
  float handling = 0;
  ConstGetDocument()->RootElement()->FirstChildElement("Handling")->QueryFloatText(&handling);
  return handling;
}