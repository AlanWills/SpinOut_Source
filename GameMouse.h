#pragma once

#include "MouseButton.h"
#include "UIObject.h"

class GameMouse : public UIObject
{
public:
	GameMouse();
	~GameMouse();

	void Update(float elapsedSeconds);

	/// \brief We have to draw the mouse so that the top left corner is the origin and so hence need to specify a custom draw function
	void Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont) override;

	void HandleInput(float elapsedSeconds);

	/// \brief Since the mouse is defined in screen space, this function returns the in game position using the camera
	Vector2 GetInGamePosition();

	/// \brief Utility function for finding the mouse button state - whether it was clicked
	/// \param Pass in the appropriate button to find whether it was pressed and released (clicked) or not
	bool IsClicked(MouseButton mouseButton) { return m_mouseClickStates[static_cast<unsigned int>(mouseButton)]; }

	bool IsPressed(MouseButton mouseButton);

  /// \brief Sets all mouse click states to false
  void Flush();

private:
	std::unique_ptr<Mouse> m_mouse;

	// We do not want our mouse to be able to click too rapidly so this just spreads out mouse clicks
	float m_clickDelayTimer;

	// Hold all the information for the mouse state - can be found in Mouse.h in DirectXTK
	Mouse::State m_currentMouseState;

	// Array for holding mouse button click state
	bool m_mouseClickStates[static_cast<unsigned int>(MouseButton::kNumButtons)];

	// Helper class for tracking mouse button clicks
	std::unique_ptr<Mouse::ButtonStateTracker> m_mouseButtonState;
};