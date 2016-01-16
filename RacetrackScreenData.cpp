#include "pch.h"

#include "RacetrackScreenData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackScreenData::RacetrackScreenData(const std::string& dataAsset) :
  BaseScreenData(dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackScreenData::~RacetrackScreenData()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
const char* RacetrackScreenData::GetTrackName() const
{
  return ConstGetDocument()->RootElement()->FirstChildElement("TrackName")->GetText();
}


//-----------------------------------------------------------------------------------------------------------------------------------
const char* RacetrackScreenData::GetDescription() const
{
  return ConstGetDocument()->RootElement()->FirstChildElement("Description")->GetText();
}


//-----------------------------------------------------------------------------------------------------------------------------------
const char* RacetrackScreenData::GetThumbnailAsset() const
{
  return ConstGetDocument()->RootElement()->FirstChildElement("ThumbnailAsset")->GetText();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreenData::FindNormalTiles(RacetrackObjects& normalTiles) const
{
  const tinyxml2::XMLDocument* xmlDocument = ConstGetDocument();
  const tinyxml2::XMLElement* rootElement = xmlDocument->FirstChildElement("Root");
  assert(rootElement);

  const tinyxml2::XMLElement* normalTileContainer = rootElement->FirstChildElement("NormalTiles");
  assert(normalTileContainer);

  for (const tinyxml2::XMLElement* child = normalTileContainer->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    RacetrackObjectInfo tile = DeserializeObject(child);
    tile.m_shouldHaveCollider = false;
    normalTiles.push_back(tile);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreenData::FindCollisionTiles(RacetrackObjects& collisionTiles) const
{
  const tinyxml2::XMLDocument* xmlDocument = ConstGetDocument();
  const tinyxml2::XMLElement* rootElement = xmlDocument->FirstChildElement("Root");
  assert(rootElement);

  const tinyxml2::XMLElement* collisionTileContainer = rootElement->FirstChildElement("CollisionTiles");
  assert(collisionTileContainer);

  for (const tinyxml2::XMLElement* child = collisionTileContainer->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    RacetrackObjectInfo tile = DeserializeObject(child);
    tile.m_shouldHaveCollider = true;
    collisionTiles.push_back(tile);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreenData::FindNormalDecals(RacetrackObjects& normalDecals) const
{
  const tinyxml2::XMLDocument* xmlDocument = ConstGetDocument();
  const tinyxml2::XMLElement* rootElement = xmlDocument->FirstChildElement("Root");
  assert(rootElement);

  const tinyxml2::XMLElement* normalDecalContainer = rootElement->FirstChildElement("NormalDecals");
  assert(normalDecalContainer);

  for (const tinyxml2::XMLElement* child = normalDecalContainer->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    RacetrackObjectInfo decal = DeserializeObject(child);
    decal.m_shouldHaveCollider = false;
    normalDecals.push_back(decal);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreenData::FindCollisionDecals(RacetrackObjects& collisionDecals) const
{
  const tinyxml2::XMLDocument* xmlDocument = ConstGetDocument();
  const tinyxml2::XMLElement* rootElement = xmlDocument->FirstChildElement("Root");
  assert(rootElement);

  const tinyxml2::XMLElement* collisionDecalContainer = rootElement->FirstChildElement("CollisionDecals");
  assert(collisionDecalContainer);

  for (const tinyxml2::XMLElement* child = collisionDecalContainer->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    RacetrackObjectInfo decal = DeserializeObject(child);
    decal.m_shouldHaveCollider = true;
    collisionDecals.push_back(decal);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreenData::FindStartingPoints(RacetrackObjects& startingPoints) const
{
  const tinyxml2::XMLDocument* xmlDocument = ConstGetDocument();
  const tinyxml2::XMLElement* rootElement = xmlDocument->FirstChildElement("Root");
  assert(rootElement);

  const tinyxml2::XMLElement* startingPointContainer = rootElement->FirstChildElement("StartingPoints");
  assert(startingPointContainer);

  for (const tinyxml2::XMLElement* child = startingPointContainer->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    RacetrackObjectInfo startingPoint = DeserializeObject(child);
    startingPoint.m_shouldHaveCollider = false;
    startingPoints.push_back(startingPoint);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackScreenData::FindTrackPoints(std::vector<Vector2>& trackPoints) const
{
  assert(ConstGetDocument());
  const tinyxml2::XMLDocument* xmlDocument = ConstGetDocument();
  const tinyxml2::XMLElement* rootElement = xmlDocument->FirstChildElement("Root");
  assert(rootElement);

  const tinyxml2::XMLElement* trackPointContainer = rootElement->FirstChildElement("TrackPoints");
  assert(trackPointContainer);

  for (const tinyxml2::XMLElement* child = trackPointContainer->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    Vector2 trackPoint;
    child->QueryVector2Attribute("position", &trackPoint);

    trackPoints.push_back(trackPoint);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackObjectInfo RacetrackScreenData::DeserializeObject(const tinyxml2::XMLElement* element) const
{
  RacetrackObjectInfo info;

  Vector2 position;
  element->QueryVector2Attribute("position", &position);

  float rotation = 0;
  element->QueryFloatAttribute("rotation", &rotation);

  info.m_position = position;
  info.m_dataAsset = element->GetText();
  info.m_rotation = rotation;

  return info;
}