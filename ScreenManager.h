#pragma once

#include "SpriteBatch.h"
#include "BaseScreen.h"

#include "GameMouse.h"
#include "KeyboardInput.h"
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class ScreenManager
{
public:
	ScreenManager(ID3D11Device* device, ID3D11DeviceContext* deviceContext, float screenWidth, float screenHeight);
	~ScreenManager();

	// Five basic game functions
	void LoadContent();
	void Initialize();
	void Update(float elapsedSeconds);
	void Draw();
	void HandleInput(float elapsedSeconds);

	/// \brief Add a screen (will automatically load and initialize for you)
	void AddScreen(BaseScreen* screenToAdd, bool load = true, bool initialize = true);
	void RemoveScreen(BaseScreen* screenToAdd);

  /// \brief Mirror function for screens, but requires screen you are transitioning from too
  void Transition(BaseScreen* transitionFrom, BaseScreen* transitionTo, bool load = true, bool initialize = true);

  ID3D11Device* GetDevice() const { return m_device; }

  /// \brief Gets the latest screen to have been added to active screens - i.e. at the front
  BaseScreen* GetCurrentScreen();

	/// \brief Utility function for obtaining the centre of back buffer
	static const Vector2& GetScreenCentre();
	static const Vector2 GetScreenDimensions() { return 2 * GetScreenCentre(); }

	// Viewport
	CD3D11_VIEWPORT m_viewport;

	/// \brief Gets the camera
	static Camera& GetCamera();

	/// \brief Gets the GameMouse
	static GameMouse& GetGameMouse();

	/// \brief Gets the KeyboardInput
	static KeyboardInput& GetKeyboardInput();

private:
	// General device and device context we get from creation - will need these for a lot of things
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;

	// SpriteBatch
	std::unique_ptr<SpriteBatch> m_spriteBatch;

	// SpriteFont
	std::unique_ptr<SpriteFont> m_spriteFont;

	// Used for alpha blending sprites
	std::unique_ptr<CommonStates> m_states;

	// Screens
	std::list<BaseScreen*> m_activeScreens;
	
	// Container for screens about to be deleted
	std::list<BaseScreen*> m_screensToDelete;
};