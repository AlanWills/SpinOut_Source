#pragma once

#include "GameObject.h"
#include <vector>

class Tile : public GameObject
{
public:
  enum Neighbours
  {
    kUp,
    kRight,
    kDown,
    kLeft,
    kNumNeighbours
  };

	Tile(const Vector2& localPosition, std::pair<int, int> tilemapCoords, const std::string& dataAsset, LoadType loadType = LoadType::kTexture, BaseObject* baseObject = nullptr);
	~Tile();

  const bool IsOccupied() const { return m_storedObject != nullptr; }

  void SetStoredObject(BaseObject* storedObject) { m_storedObject = storedObject; }
  const BaseObject* GetStoredObject() const { return m_storedObject; }

  template <typename T>
  T* GetStoredObjectAs() const { return dynamic_cast<T*>(m_storedObject); }

  void SetNeighbour(Tile* tile, const Neighbours neighbour) { m_neighbours[neighbour] = tile; }
  const Tile* GetNeighbour(const Neighbours neighbour) const { return m_neighbours[neighbour]; }

private:
  /// \brief A variable for an object that can be stored on a tile - just a reference
  BaseObject* m_storedObject;

  /// \brief A pair of ints to indicate it's position in a tilemap
  const std::pair<int, int> m_tilemapCoords;

  /// \brief Pointers to tiles above/below/left/right
  std::vector<Tile*> m_neighbours;
};