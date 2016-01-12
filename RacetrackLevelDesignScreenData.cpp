#include "pch.h"
#include "RacetrackLevelDesignScreenData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackLevelDesignScreenData::RacetrackLevelDesignScreenData(const std::string& dataAsset) :
  LevelDesignScreenData(dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackLevelDesignScreenData::~RacetrackLevelDesignScreenData()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackLevelDesignScreenData::SerializeTrackPoints(const std::list<Vector2>& trackPoints)
{
  tinyxml2::XMLDocument* xmlDocument = GetDocument();
  tinyxml2::XMLElement* rootElement = xmlDocument->FirstChildElement("Root");
  assert(rootElement);

  tinyxml2::XMLElement* lastElement = rootElement->LastChildElement();
  assert(lastElement);

  tinyxml2::XMLElement* trackPointContainer = xmlDocument->NewElement("TrackPoints");
  rootElement->InsertAfterChild(lastElement, trackPointContainer);

  tinyxml2::XMLElement* previousTrackPointElement = nullptr;

  for (const Vector2& trackPoint : trackPoints)
  {
    tinyxml2::XMLElement* element = xmlDocument->NewElement("TrackPoint");
    element->SetAttribute("x", trackPoint.x);
    element->SetAttribute("y", trackPoint.y);

    if (previousTrackPointElement)
    {
      trackPointContainer->InsertAfterChild(previousTrackPointElement, element);
    }
    else
    {
      trackPointContainer->InsertFirstChild(element);
    }

    previousTrackPointElement = element;
  }

  xmlDocument->SaveFile(GetDataAsset().c_str());
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackLevelDesignScreenData::DeserializeTrackPoints(std::list<Vector2>& trackPoints)
{
  assert(ConstGetDocument());
  const tinyxml2::XMLDocument* xmlDocument = ConstGetDocument();
  const tinyxml2::XMLElement* rootElement = xmlDocument->FirstChildElement("Root");
  assert(rootElement);

  const tinyxml2::XMLElement* trackPointContainer = rootElement->FirstChildElement("TrackPoints");
  assert(trackPointContainer);

  for (const tinyxml2::XMLElement* child = trackPointContainer->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    float x = 0, y = 0;
    child->QueryFloatAttribute("x", &x);
    child->QueryFloatAttribute("y", &y);

    trackPoints.push_back(Vector2(x, y));
  }
}