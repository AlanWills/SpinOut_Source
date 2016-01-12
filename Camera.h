#pragma once

using namespace DirectX::SimpleMath;

class Camera
{
public:
	enum CameraMode
	{
		kFree,
		kFixed,
		kFollow
	};

	Camera();
	~Camera();

  void SetUpFrame(const Vector2& screenCentre);

	/// \brief Updates the camera to process input if it is in free mode
	void Update(float elapsedSeconds);

	/// \brief Calculates and returns the view matrix based on the camera position and zoom
	Matrix GetViewMatrix() const;

	/// \brief Sets the camera mode 
	void SetCameraMode(const CameraMode cameraMode) { m_cameraMode = cameraMode; }

	/// \brief Converts a position on the screen to a position in game world space
	Vector2 ScreenToGameCoords(const Vector2 screenPosition) const;

	/// \brief Converts a position in game world space to screen space
	Vector2 GameToScreenCoords(const Vector2 gamePosition) const;

  /// \brief Resets the camera position to Vector2::Zero
  void Reset() { m_position = Vector2::Zero; }

  /// \brief Set position of the camera
  void SetPosition(const Vector2& position) { m_position = position; }

  /// \brief Rather than setting the position of the camera, it sets the camera position to focus on the inputted position
  void FocusOnPosition(const Vector2& position);

  /// \brief Sets up a position for the camera to follow
  void SetToFollowPosition(const Vector2* followPosition) 
  { 
    m_cameraMode = kFollow;
    m_followPosition = followPosition; 
  }

  float GetZoom() const { return m_zoom; }

  const BoundingBox& GetBoundingFrame() const { return m_boundingFrame; }

private:
	// Describes the behaviour of the camera - whether it can be manually moved or not
	CameraMode m_cameraMode;

	// Position of the camera
	Vector2 m_position;

	// Pan speed of the camera
	float m_panSpeed;

	// Zoom of the camera
	float m_zoom;

  const Vector2* m_followPosition;

  BoundingBox m_boundingFrame;
};

