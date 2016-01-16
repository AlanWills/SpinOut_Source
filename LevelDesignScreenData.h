#pragma once

#include "BaseScreenData.h"

#include "LevelDesignObject.h"
#include "LevelDesignTile.h"
#include "LevelDesignDecal.h"
#include "LevelDesignStartingPosition.h"

#include <list>

class LevelDesignScreenData : public BaseScreenData
{
public:
  LevelDesignScreenData(const std::string& dataAsset);
  virtual ~LevelDesignScreenData();

  /// \brief Takes a list of level design objects and serializes them under four groups corresponding to their type
  virtual void SerializeLevel(const std::list<LevelDesignObject*>& levelObjects);

  /// \brief Takes an list of level design objects, then loads a level file and deserializes all the elements, populating the list with the resulting level objects
  virtual void DeserializeLevel(std::list<LevelDesignObject*>& levelObjects);

private:
  XMLElement* SerializeLevelObject(const LevelDesignObject* levelObject, tinyxml2::XMLDocument* document, tinyxml2::XMLElement* container, XMLElement* previousSibling);

  template <typename T>
  T* DeserializeLevelObject(const tinyxml2::XMLElement* levelElement);
};


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
T* LevelDesignScreenData::DeserializeLevelObject(const tinyxml2::XMLElement* element)
{
  Vector2 position;
  element->QueryVector2Attribute("position", &position);

  std::string dataAsset(element->GetText());

  float rotation = 0;
  element->QueryFloatAttribute("rotation", &rotation);

  bool hasCollider = false;
  element->QueryBoolAttribute("collider", &hasCollider);

  T* levelObject = new T(position, dataAsset, hasCollider);
  levelObject->SetLocalRotation(rotation);

  return levelObject;
}