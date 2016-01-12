#include "pch.h"
#include "Tilemap.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Tilemap::Tilemap(Microsoft::WRL::ComPtr<ID3D11Device> device, const std::string& tilemapDataAsset) :
	m_tiles(new BaseObjectManager<Tile>(device)),
	m_tilemapData(new TilemapData(tilemapDataAsset))
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Tilemap::~Tilemap()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Tilemap::LoadContent()
{
	// Load the tile data here and create the tiles
	m_tilemapData->LoadData();
	std::list<Tile*> tiles;
	m_tilemapData->GetTiles(tiles, m_tilemap);

	// Push back the tiles to the BaseObjectManager using the elements in 'tiles'
	for (Tile* tile : tiles)
	{
		m_tiles->AddObject(tile);
	}

	m_tiles->LoadContent();

	// Free the memory
	m_tilemapData.release();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Tilemap::Initialize()
{
	m_tiles->Initialize();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Tilemap::Update(float elapsedSeconds)
{
	m_tiles->Update(elapsedSeconds);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Tilemap::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	m_tiles->Draw(spriteBatch, spriteFont);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Tilemap::HandleInput(float elapsedSeconds, const Vector2& mousePosition)
{
	m_tiles->HandleInput(elapsedSeconds, mousePosition);
}


//-----------------------------------------------------------------------------------------------------------------------------------
const bool Tilemap::IsClicked(const Vector2& mousePosition) const
{
  for (auto& tile : m_tiles->GetObjects())
  {
    if (tile->GetCollider()->CheckCollisionWith(mousePosition))
    {
      return true;
    }
  }

  return false;
}


//-----------------------------------------------------------------------------------------------------------------------------------
Tile* Tilemap::GetClickedTile(const Vector2& mousePosition) const
{
  assert(IsClicked(mousePosition));

  for (Tile* tile : m_tiles->GetObjects())
  {
    if (tile->GetCollider()->CheckCollisionWith(mousePosition))
    {
      return tile;
    }
  }

  return nullptr;
}


//-----------------------------------------------------------------------------------------------------------------------------------
const Tile* Tilemap::ConstGetClickedTile(const Vector2& mousePosition) const
{
  assert(IsClicked(mousePosition));

  for (Tile* tile : m_tiles->GetObjects())
  {
    if (tile->GetCollider()->CheckCollisionWith(mousePosition))
    {
      return tile;
    }
  }

  return nullptr;
}


//-----------------------------------------------------------------------------------------------------------------------------------
const Vector2 Tilemap::GetWorldSpacePositionFromCoords(const int xCoord, const int yCoord)
{
  assert(m_tilemap.at(yCoord).at(xCoord));
  return m_tilemap.at(yCoord).at(xCoord)->GetWorldPosition();
}