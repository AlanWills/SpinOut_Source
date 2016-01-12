#pragma once

#include "SpriteBatch.h"

#include "GameMouse.h"
#include "KeyboardInput.h"

#include <DirectXCollision.h>
#include <list>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

///// DO NOT USE UNIQUE_PTRS HERE - IT DOES NOT WORK BECAUSE THE DESTRUCTORS ARE NOT SPECIFIED
template <typename T> class BaseObjectManager
{
public:
	BaseObjectManager(Microsoft::WRL::ComPtr<ID3D11Device> device);
	~BaseObjectManager();

	/// \brief Adds necessary objects and loads content of all active objects
	void LoadContent();

	/// \brief Initializes all active objects
	void Initialize();

	/// \brief Update all active objects and add/remove any necessary objects
	void Update(float elapsedSeconds);

	/// \brief Draws all active objects
	void Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont);

	/// \brief Handles input for all active objects
	void HandleInput(float elapsedSeconds, const Vector2& mousePosition);

	/// \brief Adds an object 
	void AddObject(T* objectToAdd, bool load = false, bool initialize = false);

	/// \brief Find an object with a specific tag
	T* FindObject(const std::string& name);

  /// \brief Finds all objects of the inputted type and adds them to the list
  template <typename K>
  void FindObjectsOfType(std::list<K*>& objects) const;

	/// \brief Removes an object
	void RemoveObject(T* objectToRemove);

  /// \brief Gets all objects
  const std::list<T*>& GetObjects() const { return m_activeObjects; }

	/// \brief Calls Show() on each active object
	void ShowAll()
	{
		for (auto& object : m_activeObjects)
		{
			object->Show();
		}
	}

	/// \brief Calls Hide() on each active object
	void HideAll()
	{
		for (auto& object : m_activeObjects)
		{
			object->Hide();
		}
	}

	/// \brief Calls Die() on each active object
	void DieAll()
	{
		for (T* object : m_activeObjects)
		{
			object->Die();
		}
	}

private:
	/// \brief Typedefs
	typedef std::list<T*> Objects;

	Objects m_activeObjects;
	Objects m_objectsToDelete;

	Microsoft::WRL::ComPtr<ID3D11Device> m_device;
};


///////////// TEMPLATED FUNCTION DEFINITIONS

//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
BaseObjectManager<T>::BaseObjectManager(Microsoft::WRL::ComPtr<ID3D11Device> device) :
	m_device(device)
{

}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
BaseObjectManager<T>::~BaseObjectManager()
{
	m_activeObjects.clear();
	m_objectsToDelete.clear();
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::LoadContent()
{
	for (T* object : m_activeObjects)
	{
		object->LoadContent(m_device.Get());
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::Initialize()
{
	for (T* object : m_activeObjects)
	{
		object->Initialize();
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::Update(float elapsedSeconds)
{
	for (T* object : m_activeObjects)
	{
    assert(object);

		if (object->IsAlive())
		{
			object->Update(elapsedSeconds);
		}
		else
		{
      RemoveObject(object);
      m_objectsToDelete.push_back(object);
		}
	}

	for (T* object : m_objectsToDelete)
	{
		m_activeObjects.remove(object);
    delete object;
	}

	m_objectsToDelete.clear();
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	for (T* object : m_activeObjects)
	{
		object->Draw(spriteBatch, spriteFont);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::HandleInput(float elapsedSeconds, const Vector2& mousePosition)
{
	for (T* object : m_activeObjects)
	{
		object->HandleInput(elapsedSeconds, mousePosition);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::AddObject(T* objectToAdd, bool load, bool initialize)
{
	if (load)
	{
		objectToAdd->LoadContent(m_device.Get());
	}

	if (initialize)
	{
		objectToAdd->Initialize();
	}

	m_activeObjects.push_back(objectToAdd);
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
T* BaseObjectManager<T>::FindObject(const std::string& name)
{
	for (T* object : m_activeObjects)
	{
		if (object->GetName() == name)
		{
			return object;
		}
	}

  return nullptr;
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
template <typename K>
void BaseObjectManager<T>::FindObjectsOfType(std::list<K*>& objects) const
{
  objects.clear();

  for (T* object : m_activeObjects)
  {
    if (dynamic_cast<K*>(object))
    {
      objects.push_back(dynamic_cast<K*>(object));
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseObjectManager<T>::RemoveObject(T* objectToRemove)
{
  if (!objectToRemove)
  {
    return;
  }

  if (objectToRemove->IsAlive())
  {
    objectToRemove->Die();
  }
}