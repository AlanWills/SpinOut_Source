#pragma once

#include "BaseObjectManager.h"
#include "ScriptManager.h"

#include "GameObject.h"
#include "UIObject.h"

#include "GameMouse.h"
#include "KeyboardInput.h"

#include "BaseScreenData.h"

using namespace std;

class ScreenManager;

class BaseScreen
{
public:
	BaseScreen(ScreenManager* screenManager, const std::string& dataAsset);
	virtual ~BaseScreen();

	/// \brief Adds initial UI before the load context and initialize steps
	/// Adds a title automatically from the XML Display Name element
	virtual void AddInitialUI();

	/// \brief Loads the content of all the objects we have already set up
	virtual void LoadContent();

	/// \brief Initializes all of the objects we have already set up
	virtual void Initialize();

  /// \brief Adds initial scripts after all objects have been initialized, but before first update loop
  virtual void AddInitialScripts() { }

	/// \brief Run when we started updating - good for initializing music etc.
	virtual void Begin();

	/// \brief Updates all the objects in the screen (game, then gameUI, then screenUI)
	virtual void Update(float elapsedSeconds);

	/// \brief Draws all the objects in the screen that are dependent on camera and game world (game, then gameUI)
	virtual void DrawInGameObjects(SpriteBatch* spriteBatch, SpriteFont* spriteFont);

	/// \brief Draws all the objects in the screen that are not dependent on camera or game world (Screen UI)
	virtual void DrawScreenObjects(SpriteBatch* spriteBatch, SpriteFont* spriteFont);

	/// \brief Draws the background
	void DrawBackground(SpriteBatch* spriteBatch, SpriteFont* spriteFont);

	/// \brief Handles all the input for the objects in the screen (game, then gameUI, then screenUI)
	virtual void HandleInput(float elapsedSeconds);

	/// \brief Utility function to let the screen update, draw and handle input
	void Show();

	/// \brief Utility function to stop the screen updating, drawing and handling input
	void Hide();

	/// \brief Wrapper functions for adding/removing game objects
	void AddGameObject(GameObject* gameObject, bool load = false, bool initialize = false);
	void RemoveGameObject(GameObject* gameObject);

	/// \brief Wrapper functions for adding/removing in game UI objects
	void AddInGameUIObject(UIObject* inGameUIObject, bool load = false, bool initialize = false);
	void RemoveInGameUIObject(UIObject* inGameUIObject);

	/// \brief Wrapper functions for adding/removing screen UI objects
	void AddScreenUIObject(UIObject* screenUIObject, bool load = false, bool initialize = false);
	void RemoveScreenUIObject(UIObject* screenUIObject);

  template <typename T>
  void FindScreenUIObjectsAs(std::list<T*>& objects) const;
  void FindScreenUIObjects(std::list<UIObject*>& objects) const { m_screenUIObjects->FindObjectsOfType<UIObject>(objects); }

  template <typename T>
  void FindInGameUIObjectsAs(std::list<T*>& objects) const;
  void FindInGameUIObjects(std::list<UIObject*>& objects) const { m_inGameUIObjects->FindObjectsOfType<UIObject>(objects); }

  template <typename T>
  void FindGameObjectsAs(std::list<T*>& objects) const;
  void FindGameObjects(std::list<GameObject*>& objects) const { m_gameObjects->FindObjectsOfType<GameObject>(objects); }

  ID3D11Device* GetDevice() const { return m_device.Get(); }

  const Vector2 GetScreenDimensions() const;
  const Vector2& GetScreenCentre() const;

protected:
  /// \brief Typedefs
  typedef BaseObjectManager<GameObject> GameObjects;
  typedef BaseObjectManager<UIObject> UIObjects;

  void AddScript(Script* script);
  void AddScript(Script* script, Script* previousScript);
  Script* GetLastAddedScript() const { return m_scriptManager->GetLastAddedScript(); }

	void Transition(BaseScreen* transitionTo, bool load = true, bool initialize = true);

	/// \brief Get a pointer to the ScreenManager
	ScreenManager* GetScreenManager() const { return m_screenManager; }

  GameObjects* GetGameObjects() const { return m_gameObjects.get(); }
  const GameObjects* ConstGetGameObjects() const { return m_gameObjects.get(); }

  UIObjects* GetInGameUIObjects() const { return m_inGameUIObjects.get(); }
  const UIObjects* ConstGetInGameUIObjects() const { return m_inGameUIObjects.get(); }

  UIObjects* GetScreenUIObjects() const { return m_screenUIObjects.get(); }
  const UIObjects* ConstGetScreenUIObjects() const { return m_screenUIObjects.get(); }

  void AddCollisionObject(GameObject* gameObject, bool noCollisions = false);
  const std::list<GameObject*>& GetCollisionObjects() { return m_collisionObjects; }

  bool IsLoaded() const { return m_loaded; }
  bool IsInitialized() const { return m_initialized; }
	bool IsVisible() const { return m_visible; }
	bool AcceptsInput() const { return m_acceptsInput; }
  bool ShouldUpdateGame() const { return IsActive() && m_scriptManager->ShouldUpdateGame(); }

private:
  // This should not be used to check whether we should update, but rather is used in the ShouldUpdateGame function which sould be used instead
  bool IsActive() const { return m_active; }

	// ScreenManager pointer
	ScreenManager* m_screenManager;

  // ScriptManager pointer
  std::unique_ptr<ScriptManager> m_scriptManager;

	// Device pointer
	Microsoft::WRL::ComPtr<ID3D11Device> m_device;

	// Screen data
	std::unique_ptr<BaseScreenData> m_baseScreenData;

	// States variables
  bool m_loaded;    // If true, LoadContent has been called on this screen
  bool m_initialized;  // If true, Initialize has been called on this screen
	bool m_begun;			// If false, we will run the Begin function in the first loop of this screen's update
	bool m_active;			// If true the screen updates
	bool m_visible;			// If true the screen renders
	bool m_acceptsInput;	// If true the screen handles and accepts input
	bool m_alive;			// if false the screen will be removed by the screen manager

	// Object managers
	std::unique_ptr<GameObjects>		m_gameObjects;			// Handles all the game objects
	std::unique_ptr<UIObjects>			m_inGameUIObjects;		// Handles all the in game (camera dependent) UI Objects
	std::unique_ptr<UIObjects>			m_screenUIObjects;		// Handles all the screen UI

  // Collision Objects
  std::list<GameObject*> m_collisionObjects;

	// Background
	std::unique_ptr<UIObject> m_background;
};


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseScreen::FindScreenUIObjectsAs(std::list<T*>& objects) const
{
  for (UIObject* uiObject : m_screenUIObjects->GetObjects())
  {
    if (dynamic_cast<T*>(uiObject))
    {
      objects.push_back(dynamic_cast<T*>(uiObject));
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseScreen::FindInGameUIObjectsAs(std::list<T*>& objects) const
{
  for (UIObject* uiObject : m_inGameUIObjects->GetObjects())
  {
    if (dynamic_cast<T*>(uiObject))
    {
      objects.push_back(dynamic_cast<T*>(uiObject));
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void BaseScreen::FindGameObjectsAs(std::list<T*>& objects) const
{
  for (GameObject* gameObject : m_gameObjects->GetObjects())
  {
    if (dynamic_cast<T*>(gameObject))
    {
      objects.push_back(dynamic_cast<T*>(gameObject));
    }
  }
}