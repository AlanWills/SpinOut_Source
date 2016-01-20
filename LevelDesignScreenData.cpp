#include "pch.h"

#include "LevelDesignScreenData.h"

//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignScreenData::LevelDesignScreenData(const std::string& dataAsset) :
  BaseScreenData(dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignScreenData::~LevelDesignScreenData()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void LevelDesignScreenData::SerializeLevel(const std::list<LevelDesignObject*>& levelObjects)
{
  // Create here for non-const and also we are serializing to a file so create feels more appropriate anyway
  tinyxml2::XMLDocument* xmlDocument = CreateDocument();
  
  tinyxml2::XMLDeclaration* declaration = xmlDocument->NewDeclaration();
  xmlDocument->InsertFirstChild(declaration);

  tinyxml2::XMLElement* rootElement = xmlDocument->NewElement("Root");
  xmlDocument->InsertAfterChild(declaration, rootElement);

  tinyxml2::XMLElement* displayNameElement = xmlDocument->NewElement("DisplayName");
  rootElement->InsertFirstChild(displayNameElement);

  tinyxml2::XMLElement* backgroundTextureAsset = xmlDocument->NewElement("BackgroundTextureAsset");
  backgroundTextureAsset->SetText("EmptyBackground.png");
  rootElement->InsertAfterChild(displayNameElement, backgroundTextureAsset);

  tinyxml2::XMLElement* musicContainer = xmlDocument->NewElement("MusicAssets");
  rootElement->InsertAfterChild(backgroundTextureAsset, musicContainer);

  tinyxml2::XMLElement* normalTileContainer = xmlDocument->NewElement("NormalTiles");
  rootElement->InsertAfterChild(musicContainer, normalTileContainer);

  tinyxml2::XMLElement* collisionTileContainer = xmlDocument->NewElement("CollisionTiles");
  rootElement->InsertAfterChild(normalTileContainer, collisionTileContainer);

  tinyxml2::XMLElement* normalDecalContainer = xmlDocument->NewElement("NormalDecals");
  rootElement->InsertAfterChild(collisionTileContainer, normalDecalContainer);

  tinyxml2::XMLElement* collisionDecalContainer = xmlDocument->NewElement("CollisionDecals");
  rootElement->InsertAfterChild(normalDecalContainer, collisionDecalContainer);

  tinyxml2::XMLElement* startingPointContainer = xmlDocument->NewElement("StartingPoints");
  rootElement->InsertAfterChild(collisionDecalContainer, startingPointContainer);

  tinyxml2::XMLElement* previousNormalTile = nullptr;
  tinyxml2::XMLElement* previousCollisionTile = nullptr;
  tinyxml2::XMLElement* previousNormalDecal = nullptr;
  tinyxml2::XMLElement* previousCollisionDecal = nullptr;
  tinyxml2::XMLElement* previousStartingPoint = nullptr;

  // Now serialize all the level objects now that the containers have been set up
  for (LevelDesignObject* levelObject : levelObjects)
  {
    switch (levelObject->GetObjectType())
    {
      case LevelDesignObjectType::kNormalTile:
        previousNormalTile = SerializeLevelObject(levelObject, xmlDocument, normalTileContainer, previousNormalTile);
        break;

      case LevelDesignObjectType::kCollisionTile:
        previousCollisionTile = SerializeLevelObject(levelObject, xmlDocument, collisionTileContainer, previousCollisionTile);
        break;

      case LevelDesignObjectType::kNormalDecal:
        previousNormalDecal = SerializeLevelObject(levelObject, xmlDocument, normalDecalContainer, previousNormalDecal);
        break;

      case LevelDesignObjectType::kCollisionDecal:
        previousCollisionDecal = SerializeLevelObject(levelObject, xmlDocument, collisionDecalContainer, previousCollisionDecal);
        break;

      case LevelDesignObjectType::kStartingPosition:
        previousStartingPoint = SerializeLevelObject(levelObject, xmlDocument, startingPointContainer, previousStartingPoint);
        break;
    }
  }

  xmlDocument->SaveFile(GetDataAsset().c_str());
}


//-----------------------------------------------------------------------------------------------------------------------------------
XMLElement* LevelDesignScreenData::SerializeLevelObject(
  const LevelDesignObject* levelObject, 
  tinyxml2::XMLDocument* document, 
  tinyxml2::XMLElement* container,
  XMLElement* previousSibling)
{
  std::string name = levelObject->GetName().empty() ? "Item" : levelObject->GetName();

  tinyxml2::XMLElement* levelObjectElement = document->NewElement(name.c_str());
  levelObjectElement->SetText(levelObject->GetDataAsset().c_str());

  levelObjectElement->SetAttribute("position", levelObject->GetWorldPosition());
  levelObjectElement->SetAttribute("rotation", levelObject->GetWorldRotation());
  levelObjectElement->SetAttribute("collider", levelObject->HasCollider());

  if (previousSibling)
  {
    container->InsertAfterChild(previousSibling, levelObjectElement);
  }
  else
  {
    container->InsertFirstChild(levelObjectElement);
  }

  return levelObjectElement;
}


//-----------------------------------------------------------------------------------------------------------------------------------
void LevelDesignScreenData::DeserializeLevel(std::list<LevelDesignObject*>& levelObjects)
{
  assert(ConstGetDocument());
  const tinyxml2::XMLDocument* xmlDocument = ConstGetDocument();
  const tinyxml2::XMLElement* rootElement = xmlDocument->FirstChildElement("Root");
  assert(rootElement);

  const tinyxml2::XMLElement* normalTileContainer = rootElement->FirstChildElement("NormalTiles");
  assert(normalTileContainer);
  const tinyxml2::XMLElement* collisionTileContainer = rootElement->FirstChildElement("CollisionTiles");
  assert(collisionTileContainer);
  const tinyxml2::XMLElement* normalDecalContainer = rootElement->FirstChildElement("NormalDecals");
  assert(normalDecalContainer);
  const tinyxml2::XMLElement* collisionDecalContainer = rootElement->FirstChildElement("CollisionDecals");
  assert(collisionDecalContainer);
  const tinyxml2::XMLElement* startingPointContainer = rootElement->FirstChildElement("StartingPoints");
  assert(startingPointContainer);

  for (const tinyxml2::XMLElement* child = normalTileContainer->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    levelObjects.push_back(DeserializeLevelObject<LevelDesignTile>(child));
  }

  for (const tinyxml2::XMLElement* child = collisionTileContainer->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    levelObjects.push_back(DeserializeLevelObject<LevelDesignTile>(child));
  }

  for (const tinyxml2::XMLElement* child = normalDecalContainer->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    levelObjects.push_back(DeserializeLevelObject<LevelDesignDecal>(child));
  }

  for (const tinyxml2::XMLElement* child = collisionDecalContainer->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    levelObjects.push_back(DeserializeLevelObject<LevelDesignDecal>(child));
  }

  for (const tinyxml2::XMLElement* child = startingPointContainer->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    levelObjects.push_back(DeserializeLevelObject<LevelDesignStartingPosition>(child));
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void LevelDesignScreenData::SerializeVectorList(const std::list<Vector2>& points, const std::string& containerName)
{
  tinyxml2::XMLDocument* xmlDocument = GetDocument();
  tinyxml2::XMLElement* rootElement = xmlDocument->FirstChildElement("Root");
  assert(rootElement);

  tinyxml2::XMLElement* lastElement = rootElement->LastChildElement();
  assert(lastElement);

  tinyxml2::XMLElement* container = xmlDocument->NewElement(containerName.c_str());
  rootElement->InsertAfterChild(lastElement, container);

  tinyxml2::XMLElement* previousTrackPointElement = nullptr;

  for (const Vector2& startLinePoint : points)
  {
    tinyxml2::XMLElement* element = xmlDocument->NewElement("Item");
    element->SetAttribute("position", startLinePoint);

    if (previousTrackPointElement)
    {
      container->InsertAfterChild(previousTrackPointElement, element);
    }
    else
    {
      container->InsertFirstChild(element);
    }

    previousTrackPointElement = element;
  }

  xmlDocument->SaveFile(GetDataAsset().c_str());
}


//-----------------------------------------------------------------------------------------------------------------------------------
void LevelDesignScreenData::DeserializeVectorList(std::list<Vector2>& points, const std::string& containerName)
{
  assert(ConstGetDocument());
  const tinyxml2::XMLDocument* xmlDocument = ConstGetDocument();
  const tinyxml2::XMLElement* rootElement = xmlDocument->FirstChildElement("Root");
  assert(rootElement);

  const tinyxml2::XMLElement* container = rootElement->FirstChildElement(containerName.c_str());
  assert(container);

  for (const tinyxml2::XMLElement* child = container->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
  {
    Vector2 point;
    child->QueryVector2Attribute("position", &point);

    points.push_back(point);
  }
}