#pragma once

using namespace DirectX;

class KeyboardInput
{
public:
	KeyboardInput();
	~KeyboardInput();

	void Update();

	/// \brief Utility functions for input
	bool IsKeyDown(Keyboard::Keys key) const;
	bool IsKeyPressed(Keyboard::Keys key) const;

  bool IsOnlyKeyDown(Keyboard::Keys key) const;

private:
	std::unique_ptr<Keyboard> m_keyboard;

	// Hold all the information for the keyboard state - can be found in Keyboard.h
	Keyboard::State m_previousKeyboardState;
	Keyboard::State m_currentKeyboardState;
};

