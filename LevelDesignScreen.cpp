#include "pch.h"

#include "LevelDesignScreen.h"
#include "ScreenManager.h"

#include "ClickableImage.h"
#include "Button.h"

//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignScreen::LevelDesignScreen(ScreenManager* screenManager, const std::string& dataAsset, const std::string& levelDataAsset) :
  BaseScreen(screenManager, dataAsset),
  m_tileDimensions(128, 128),
  m_currentTile(nullptr),
  m_tilemapDimensions(20, 20),
  m_currentType(kNormalTile)
{
  // Check that our tilemap dimensions are even
  assert((int)m_tilemapDimensions.x % 2 == 0);
  assert((int)m_tilemapDimensions.y % 2 == 0);

  for (int i = 1; i < 91; i++)
  {
    m_tileTextureAssets.push_back("road_asphalt" + std::to_string(i) + ".png");
  }

  m_tileTextureAssets.push_back("arrow_white.png");
  m_tileTextureAssets.push_back("arrow_yellow.png");
  m_tileTextureAssets.push_back("barrel_blue.png");
  m_tileTextureAssets.push_back("barrel_blue_down.png");
  m_tileTextureAssets.push_back("barrel_red.png");
  m_tileTextureAssets.push_back("barrel_red_down.png");
  m_tileTextureAssets.push_back("barrier_red.png");
  m_tileTextureAssets.push_back("barrier_red_race.png");
  m_tileTextureAssets.push_back("barrier_white.png");
  m_tileTextureAssets.push_back("barrier_white_race.png");
  m_tileTextureAssets.push_back("cone_down.png");
  m_tileTextureAssets.push_back("cone_straight.png");
  m_tileTextureAssets.push_back("light_white.png");
  m_tileTextureAssets.push_back("light_yellow.png");
  m_tileTextureAssets.push_back("lights.png");
  m_tileTextureAssets.push_back("oil.png");
  m_tileTextureAssets.push_back("rock1.png");
  m_tileTextureAssets.push_back("rock2.png");
  m_tileTextureAssets.push_back("rock3.png");
  m_tileTextureAssets.push_back("skidmark_long_1.png");
  m_tileTextureAssets.push_back("skidmark_long_2.png");
  m_tileTextureAssets.push_back("skidmark_long_3.png");
  m_tileTextureAssets.push_back("skidmark_short_1.png");
  m_tileTextureAssets.push_back("skidmark_short_2.png");
  m_tileTextureAssets.push_back("skidmark_short_3.png");
  m_tileTextureAssets.push_back("tent_blue.png");
  m_tileTextureAssets.push_back("tent_blue_large.png");
  m_tileTextureAssets.push_back("tent_red.png");
  m_tileTextureAssets.push_back("tent_red_large.png");
  m_tileTextureAssets.push_back("tires_red.png");
  m_tileTextureAssets.push_back("tires_red_alt.png");
  m_tileTextureAssets.push_back("tires_white.png");
  m_tileTextureAssets.push_back("tires_white_alt.png");
  m_tileTextureAssets.push_back("tree_large.png");
  m_tileTextureAssets.push_back("tree_small.png");
  m_tileTextureAssets.push_back("tribune_empty.png");
  m_tileTextureAssets.push_back("tribune_full.png");
  m_tileTextureAssets.push_back("tribune_overhang_red.png");
  m_tileTextureAssets.push_back("tribune_overhang_striped.png");
  m_tileTextureAssets.push_back("land_grass11.png");
  m_tileTextureAssets.push_back("Level1_1.png");
  m_tileTextureAssets.push_back("Level1_2.png");
  m_tileTextureAssets.push_back("car_blue_small_1.png");

  ScreenManager::GetCamera().SetCameraMode(Camera::CameraMode::kFree);
  //ScreenManager::GetCamera().SetPosition(m_tileDimensions * m_tilemapDimensions * 0.5f - GetScreenCentre());
}


//-----------------------------------------------------------------------------------------------------------------------------------
LevelDesignScreen::~LevelDesignScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void LevelDesignScreen::AddInitialUI()
{
  BaseScreen::AddInitialUI();

  // Add tilemap outlines to indicate size
  // Left vertical
  AddInGameUIObject(new UIObject(Vector2(4, m_tilemapDimensions.y * m_tileDimensions.y), Vector2(-2 + 0.5f * m_tileDimensions.x, 0.5f * (m_tilemapDimensions.y + 1) * m_tileDimensions.y), "GridLine.png"));
  // Right vertical
  AddInGameUIObject(new UIObject(Vector2(4, m_tilemapDimensions.y* m_tileDimensions.y), Vector2((m_tilemapDimensions.x + 0.5f) * m_tileDimensions.x + 2, 0.5f * (m_tilemapDimensions.y + 1) * m_tileDimensions.y), "GridLine.png"));
  // Top horizontal
  AddInGameUIObject(new UIObject(Vector2(m_tilemapDimensions.x* m_tileDimensions.x, 4), Vector2(0.5f * (m_tilemapDimensions.x + 1) * m_tileDimensions.x, -2 + m_tileDimensions.y * 0.5f), "GridLine.png"));
  // Bottom horizontal
  AddInGameUIObject(new UIObject(Vector2(m_tilemapDimensions.x * m_tileDimensions.x, 4), Vector2(0.5f * (m_tilemapDimensions.x + 1) * m_tileDimensions.x, (m_tilemapDimensions.y + 0.5f) * m_tileDimensions.y + 2), "GridLine.png"));

  int tileNumber = 1;
  // Used to move things onto a new row if they spill over the screen edges
  int rowNumber = 1;
  float padding = 10;
  Vector2 buttonSize(30, 30);

  // Set up the clickable tiles to change the current tile
  for (const std::string& tileAsset: m_tileTextureAssets)
  {
    // Stops images spilling over the edge and instead puts them on a new row
    if (tileNumber * (buttonSize.x + padding) > GetScreenDimensions().x - 1 * (buttonSize.x + padding))
    {
      tileNumber = 1;
      rowNumber++;
    }

    ClickableImage* tileSelect = new ClickableImage(buttonSize, Vector2(tileNumber * (buttonSize.x + padding), rowNumber * (buttonSize.y + padding)), tileAsset);
    ScreenManager* screenManager = GetScreenManager();
    tileSelect->SetClickFunction([this, tileSelect, screenManager]()
    {
      RemoveInGameUIObject(m_currentTile);
      m_currentTile = new Image(screenManager->GetGameMouse().GetInGamePosition(), tileSelect->GetDataAsset());
      AddInGameUIObject(m_currentTile, true, true);

      screenManager->GetGameMouse().Flush();
    });

    AddScreenUIObject(tileSelect);
    tileNumber++;
  }

  // Label for the object type
  m_objectTypeLabel = new Label(GetScreenDimensions() - Vector2(200, 100), L"Normal Tile");
  AddScreenUIObject(m_objectTypeLabel);

  // Button for serializing the level data
  Button* serializeButton = new Button(GetScreenDimensions() - Vector2(250, 150), L"Serialize");
  serializeButton->SetClickFunction([this]()
  {
    SerializeLevel();
  });

  AddScreenUIObject(serializeButton);

  Button* deserializeButton = new Button(Vector2(250, GetScreenDimensions().y - 150), L"Deserialize");
  deserializeButton->SetClickFunction([this]()
  {
    DeserializeLevel();
  });

  AddScreenUIObject(deserializeButton);

  Button* clearAllButton = new Button(Vector2(GetScreenDimensions() - Vector2(500, 150)), L"Clear All Tiles");
  clearAllButton->SetClickFunction([this]()
  {
    GetInGameUIObjects()->DieAll();
  });

  AddScreenUIObject(clearAllButton);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void LevelDesignScreen::Update(float elapsedSeconds)
{
  BaseScreen::Update(elapsedSeconds);

  if (IsActive())
  {
    // If we have selected a current tile and we are placing a tile rather than a decal then we should snap the mouse to the centre of tiles
    if (m_currentTile)
    {
      GameMouse& mouse = ScreenManager::GetGameMouse();

      if (m_currentType == kNormalTile || m_currentType == kCollisionTile || m_currentType == kStartingPosition)
      {
        float cameraZoom = GetScreenManager()->GetCamera().GetZoom();

        Vector2 localPosition = mouse.GetInGamePosition();
        localPosition.x = std::round(localPosition.x / m_tileDimensions.x) * m_tileDimensions.x;
        localPosition.y = std::round(localPosition.y / m_tileDimensions.y) * m_tileDimensions.y;

        m_currentTile->SetLocalPosition(localPosition);
        mouse.SetLocalPosition(ScreenManager::GetCamera().GameToScreenCoords(localPosition));
      }
      else
      {
        m_currentTile->SetLocalPosition(mouse.GetInGamePosition());
      }
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void LevelDesignScreen::HandleInput(float elapsedSeconds)
{
  BaseScreen::HandleInput(elapsedSeconds);

  if (AcceptsInput())
  {
    GameMouse& gameMouse = GetScreenManager()->GetGameMouse();
    KeyboardInput& keyboard = GetScreenManager()->GetKeyboardInput();

    // If the Q key is pressed we remove the current selected tile
    if (keyboard.IsKeyPressed(Keyboard::Q))
    {
      RemoveInGameUIObject(m_currentTile);
      m_currentTile = nullptr;
    }

    if (keyboard.IsKeyPressed(Keyboard::B))
    {
      AddBackground();
    }

    if (gameMouse.IsClicked(MouseButton::kLeftButton))
    {
      AddLevelObject(gameMouse.GetInGamePosition());
    }

    if (m_currentTile)
    {
      if (keyboard.IsKeyPressed(Keyboard::E))
      {
        m_currentTile->SetLocalRotation(m_currentTile->GetLocalRotation() + XM_PIDIV2);
      }
      else if (keyboard.IsKeyDown(Keyboard::A))
      {
        m_currentTile->SetLocalRotation(m_currentTile->GetLocalRotation() - 0.01f);
      }
      else if (keyboard.IsKeyDown(Keyboard::D))
      {
        m_currentTile->SetLocalRotation(m_currentTile->GetLocalRotation() + 0.01f);
      }
    }

    HandleObjectTypeChange(keyboard);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void LevelDesignScreen::HandleObjectTypeChange(const KeyboardInput& keyboard)
{
  if (keyboard.IsKeyPressed(Keyboard::D1))
  {
    m_currentType = kNormalTile;
    m_objectTypeLabel->SetText(L"Normal Tile");
  }
  else if (keyboard.IsKeyPressed(Keyboard::D2))
  {
    m_currentType = kCollisionTile;
    m_objectTypeLabel->SetText(L"Collision Tile");
  }
  else if (keyboard.IsKeyPressed(Keyboard::D3))
  {
    m_currentType = kNormalDecal;
    m_objectTypeLabel->SetText(L"Normal Decal");
  }
  else if (keyboard.IsKeyPressed(Keyboard::D4))
  {
    m_currentType = kCollisionDecal;
    m_objectTypeLabel->SetText(L"Collision Decal");
  }
  else if (keyboard.IsKeyPressed(Keyboard::D5))
  {
    m_currentType = kStartingPosition;
    m_objectTypeLabel->SetText(L"Starting Position");
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void LevelDesignScreen::AddBackground()
{
  if (!m_currentTile)
  {
    return;
  }

  // Set up the background
  for (int y = 0; y < m_tilemapDimensions.y; y++)
  {
    for (int x = 0; x < m_tilemapDimensions.x; x++)
    {
      AddInGameUIObject(new LevelDesignTile(Vector2((float)x, (float)y) * m_tileDimensions, m_currentTile->GetDataAsset(), false), true, true);
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void LevelDesignScreen::AddLevelObject(const Vector2& position)
{
  if (m_currentTile && IsPointInTileMap(position))
  {
    AddObject(position);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool LevelDesignScreen::IsPointInTileMap(const Vector2& point) const
{
  return point.x > 0 * m_tileDimensions.x && point.x < (m_tilemapDimensions.x + 1) * m_tileDimensions.x &&
         point.y > 0 * m_tileDimensions.y && point.y < (m_tilemapDimensions.y + 1) * m_tileDimensions.y;
}


//-----------------------------------------------------------------------------------------------------------------------------------
void LevelDesignScreen::AddObject(const Vector2& position)
{
  LevelDesignObject* levelObject = nullptr;

  switch (m_currentType)
  {
    case kStartingPosition:
      levelObject = new LevelDesignStartingPosition(position, m_currentTile->GetDataAsset(), false);
      break;

    case kNormalTile:
      levelObject = new LevelDesignTile(position, m_currentTile->GetDataAsset(), false);
      break;

    case kCollisionTile:
      levelObject = new LevelDesignTile(position, m_currentTile->GetDataAsset(), true);
      break;

    case kNormalDecal:
      levelObject = new LevelDesignDecal(position, m_currentTile->GetDataAsset(), false);
      break;

    case kCollisionDecal:
      levelObject = new LevelDesignDecal(position, m_currentTile->GetDataAsset(), true);
      break;
  }

  assert(levelObject);

  levelObject->SetLocalRotation(m_currentTile->GetLocalRotation());
  AddInGameUIObject(levelObject, true, true);
}