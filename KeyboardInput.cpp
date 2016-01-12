#include "pch.h"
#include "KeyboardInput.h"


//-----------------------------------------------------------------------------------------------------------------------------------
KeyboardInput::KeyboardInput() :
	m_keyboard(new Keyboard())
{
	
}


//-----------------------------------------------------------------------------------------------------------------------------------
KeyboardInput::~KeyboardInput()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void KeyboardInput::Update()
{
	m_previousKeyboardState = m_currentKeyboardState;
	m_currentKeyboardState = m_keyboard->GetState();
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool KeyboardInput::IsKeyDown(Keyboard::Keys key) const
{
	return m_currentKeyboardState.IsKeyDown(key);
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool KeyboardInput::IsKeyPressed(Keyboard::Keys key) const
{
	return IsKeyDown(key) && m_previousKeyboardState.IsKeyUp(key);
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool KeyboardInput::IsOnlyKeyDown(Keyboard::Keys key) const
{
  // If our entered key is not down then we return false
  if (!IsKeyDown(key))
  {
    return false;
  }

  for (unsigned int keyIndex = 0; keyIndex < Keyboard::Keys::NumKeys; keyIndex++)
  {
    // If any other key is down we return false as our key is not te only one down
    if (IsKeyDown((Keyboard::Keys)keyIndex) && (Keyboard::Keys)keyIndex != key)
    {
      return false;
    }
  }

  return true;
}