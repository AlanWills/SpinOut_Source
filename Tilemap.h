#pragma once

#include "BaseObjectManager.h"

#include "Tile.h"
#include "TilemapData.h"

class Tilemap
{
public:
	Tilemap(Microsoft::WRL::ComPtr<ID3D11Device> device, const std::string& tilemapDataAsset);
	~Tilemap();

	void LoadContent();
	void Initialize();
	void Update(float elapsedSeconds);
	void Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont);
	void HandleInput(float elapsedSeconds, const Vector2& mousePosition);

  /// \brief Work out whether we have clicked on the tilemap using an inputted mouseposition
  const bool IsClicked(const Vector2& mousePosition) const;
  Tile* GetClickedTile(const Vector2& mousePosition) const;
  const Tile* ConstGetClickedTile(const Vector2& mousePosition) const;

  /// \brief Returns the world space coordinates from the inputted tilemap grid coordinates
  const Vector2 GetWorldSpacePositionFromCoords(const int xCoord, const int yCoord);

private:
	/// \brief Typedefs
	typedef std::unique_ptr<BaseObjectManager<Tile>> Tiles;
  typedef std::vector<std::vector<Tile*>> TilemapInfo;

	// Container for the tiles in the tilemap
	Tiles		m_tiles;

	// Will be used to obtain the information to create the Tiles
  std::unique_ptr<TilemapData>	m_tilemapData;

  /// \brief A data structure designed to be able to find neighbours of tiles and plot out the map in a data structure
  /// [row][column]
  TilemapInfo m_tilemap;
};