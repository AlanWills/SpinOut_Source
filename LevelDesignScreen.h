#pragma once

#include "BaseScreen.h"

#include "LevelDesignStartingPosition.h"
#include "LevelDesignDecal.h"
#include "LevelDesignTile.h"
#include "LevelDesignObject.h"

#include "Label.h"
#include "Image.h"

class LevelDesignScreen : public BaseScreen
{
public:
  LevelDesignScreen(ScreenManager* screenManager, const std::string& dataAsset, const std::string& levelDataAsset);
  virtual ~LevelDesignScreen();

  void AddInitialUI() override;
  void Update(float elapsedSeconds) override;
  void HandleInput(float elapsedSeconds) override ;

protected:
  virtual void SerializeLevel() = 0;
  virtual void DeserializeLevel() = 0;

private:
  bool IsPointInTileMap(const Vector2& point) const;
  void AddObject(const Vector2& position);
  void HandleObjectTypeChange(const KeyboardInput& keyboard);
  
  void AddBackground();
  void AddLevelObject(const Vector2& position);

  std::vector<std::string> m_tileTextureAssets;

  const Vector2 m_tileDimensions;

  /// \brief Pointer to the in game UI object we use to indicate the current selected tile
  Image* m_currentTile;

  ///\ brief Label reference for the object type
  Label* m_objectTypeLabel;
  LevelDesignObjectType m_currentType;

  const Vector2 m_tilemapDimensions;
};