#include "pch.h"

#include "UIObject.h"
#include "GameMouse.h"
#include "ScreenManager.h"


//-----------------------------------------------------------------------------------------------------------------------------------
GameMouse::GameMouse()
	: UIObject("cursor_blue.png", LoadType::kTexture),
	m_mouse(new Mouse()),
	m_mouseButtonState(new Mouse::ButtonStateTracker()),
	m_clickDelayTimer(0.02f)
{
	// This hides the window cursor so that we can draw our own one instead
	// We still maintain the functionality though (wrapped up in Mouse.h DirectXTK)
	//ShowCursor(false);

	for (unsigned int i = 0; i < static_cast<unsigned int>(MouseButton::kNumButtons); i++)
	{
		m_mouseClickStates[i] = false;
	}

  SetType(UIObject::kScreen);
}


//-----------------------------------------------------------------------------------------------------------------------------------
GameMouse::~GameMouse()
{
	
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameMouse::Update(float elapsedSeconds)
{
	UIObject::Update(elapsedSeconds);

	// Update mouse states
	m_currentMouseState = m_mouse->GetState();
	m_mouseButtonState->Update(m_currentMouseState);

	// Update mouse position
	SetLocalPosition(Vector2((float)m_currentMouseState.x, (float)m_currentMouseState.y));
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameMouse::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	if (IsVisible())
	{
		spriteBatch->Draw(
			GetTexture()->GetTexture(), 
			GetWorldPosition(), 
			nullptr, 
			GetColour() * GetOpacity(),
			GetWorldRotation(), 
			Vector2::Zero, 
			XMVectorDivide(GetSize(), GetTexture()->GetDimensions()));
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameMouse::HandleInput(float elapsedSeconds)
{
	// If the value in the Mouse.h class is true that means it is down
	if (m_mouseButtonState->leftButton == Mouse::ButtonStateTracker::PRESSED && m_clickDelayTimer >= 0.02f)
	{
		m_mouseClickStates[static_cast<unsigned int>(MouseButton::kLeftButton)] = true;
		m_clickDelayTimer = 0;
	}
	else
	{
		m_mouseClickStates[static_cast<unsigned int>(MouseButton::kLeftButton)] = false;
		m_clickDelayTimer += elapsedSeconds;
	}

	if (m_mouseButtonState->middleButton == Mouse::ButtonStateTracker::PRESSED && m_clickDelayTimer >= 0.02f)
	{
		m_mouseClickStates[static_cast<unsigned int>(MouseButton::kMiddleButton)] = true;
		m_clickDelayTimer = 0;
	}
	else
	{
		m_mouseClickStates[static_cast<unsigned int>(MouseButton::kMiddleButton)] = false;
		m_clickDelayTimer += elapsedSeconds;
	}

	if (m_mouseButtonState->rightButton == Mouse::ButtonStateTracker::PRESSED && m_clickDelayTimer >= 0.02f)
	{
		m_mouseClickStates[static_cast<unsigned int>(MouseButton::kRightButton)] = true;
		m_clickDelayTimer = 0;
	}
	else
	{
		m_mouseClickStates[static_cast<unsigned int>(MouseButton::kRightButton)] = false;
		m_clickDelayTimer += elapsedSeconds;
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
Vector2 GameMouse::GetInGamePosition()
{
	return ScreenManager::GetCamera().ScreenToGameCoords(GetLocalPosition());
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool GameMouse::IsPressed(MouseButton mouseButton)
{
	switch (mouseButton)
	{
		case MouseButton::kLeftButton:
			return m_mouseButtonState->leftButton == Mouse::ButtonStateTracker::HELD;

		case MouseButton::kMiddleButton:
			return m_mouseButtonState->middleButton == Mouse::ButtonStateTracker::HELD;

		case MouseButton::kRightButton:
			return m_mouseButtonState->rightButton == Mouse::ButtonStateTracker::HELD;
			
		default:
			return false;
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void GameMouse::Flush()
{
  m_mouseButtonState->leftButton = Mouse::ButtonStateTracker::RELEASED;
  m_mouseButtonState->middleButton = Mouse::ButtonStateTracker::RELEASED;
  m_mouseButtonState->rightButton = Mouse::ButtonStateTracker::RELEASED;

  for (int i = 0; i < static_cast<int>(MouseButton::kNumButtons); i++)
  {
    m_mouseClickStates[i] = false;
  }
}