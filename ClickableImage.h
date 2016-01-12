#pragma once

#include "Image.h"

class ClickableImage : public Image
{
public:
  ClickableImage(
    const Vector2& localPosition, 
    const std::string& dataAsset, 
    Sizing sizing = Sizing::kPreserveAspectRatio, 
    LoadType loadType = LoadType::kTexture, 
    BaseObject* parent = nullptr, 
    float lifeTime = FLT_MAX);

  ClickableImage(
    const Vector2& size, 
    const Vector2& localPosition, 
    const std::string& dataAsset, 
    Sizing sizing = Sizing::kPreserveAspectRatio,
    LoadType loadType = LoadType::kTexture, 
    BaseObject* parent = nullptr, 
    float lifeTime = FLT_MAX);

  virtual ~ClickableImage();

  void Update(float elapsedSeconds) override;
  void HandleInput(float elapsedSeconds, const Vector2& mousePosition) override;

  /// \brief Set the click function for this object
  void SetClickFunction(const std::function<void()>& clickFunction) { m_clickFunction = clickFunction; }

  enum ClickState
  {
    kIdle,
    kHighlighted,
    kPressed,
    kDisabled,
    kNumStates
  };

protected:
  const ClickState GetClickState() const { return m_clickState; }

private:
  ClickState m_clickState;

  float m_clickResetTimer;
  const float m_resetTime;

  /// \brief The function that will be execusted when the button is clicked
  std::function<void()> m_clickFunction;
};

