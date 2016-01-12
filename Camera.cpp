#include "pch.h"

#include "Camera.h"
#include "ScreenManager.h"
#include "KeyboardInput.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Camera::Camera() :
	m_cameraMode(CameraMode::kFixed),
	m_position(Vector2::Zero),
	m_panSpeed(1000),
	m_zoom(1.0f),
  m_followPosition(nullptr)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Camera::~Camera()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Camera::SetUpFrame(const Vector2& screenCentre)
{
  m_boundingFrame.Center = Vector3(ScreenManager::GetScreenCentre().x, ScreenManager::GetScreenCentre().y, 0);
  m_boundingFrame.Extents = Vector3(ScreenManager::GetScreenDimensions().x * 0.5f, ScreenManager::GetScreenDimensions().y * 0.5f, 0);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Camera::Update(float elapsedSeconds)
{
	// If the camera is fixed we should not do any more updating
	if (m_cameraMode == CameraMode::kFixed)
	{
		return;
	}

  if (m_cameraMode == CameraMode::kFollow)
  {
    assert(m_followPosition);
    FocusOnPosition(*m_followPosition);
    return;
  }

	KeyboardInput& keyboard = ScreenManager::GetKeyboardInput();
	Vector2 diff = Vector2::Zero;

	if (keyboard.IsKeyDown(Keyboard::Keys::Left))
	{
		diff.x = -1;
	}
	if (keyboard.IsKeyDown(Keyboard::Keys::Right))
	{
		diff.x = 1;
	}
	if (keyboard.IsKeyDown(Keyboard::Keys::Up))
	{
		diff.y = -1;
	}
	if (keyboard.IsKeyDown(Keyboard::Keys::Down))
	{
		diff.y = 1;
	}

	if (diff != Vector2::Zero)
	{
		diff.Normalize();
		m_position += diff * elapsedSeconds * m_panSpeed;
	}

  if (keyboard.IsKeyPressed(Keyboard::Keys::PageUp))
  {
    m_zoom -= 0.25f;

    if (m_zoom < 0.25f)
    {
      m_zoom = 0.25f;
    }
  }

  if (keyboard.IsKeyPressed(Keyboard::Keys::PageDown))
  {
    m_zoom += 0.25f;

    if (m_zoom > 3)
    {
      m_zoom = 3;
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
Matrix Camera::GetViewMatrix() const
{
	// It's -ve position because it is - don't change it
	return Matrix::CreateScale(m_zoom) * Matrix::CreateTranslation(-m_position.x, -m_position.y, 0);
}


//-----------------------------------------------------------------------------------------------------------------------------------
Vector2 Camera::ScreenToGameCoords(const Vector2 screenPosition) const
{
  return (m_position + screenPosition) / m_zoom;
}


//-----------------------------------------------------------------------------------------------------------------------------------
Vector2 Camera::GameToScreenCoords(const Vector2 gamePosition) const
{
  return gamePosition * m_zoom - m_position;
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Camera::FocusOnPosition(const Vector2& focusPosition)
{
  SetPosition(focusPosition - ScreenManager::GetScreenDimensions() * 0.5f);
}