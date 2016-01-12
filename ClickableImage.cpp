#include "pch.h"

#include "ClickableImage.h"


//-----------------------------------------------------------------------------------------------------------------------------------
ClickableImage::ClickableImage(const Vector2& localPosition, const std::string& dataAsset, Sizing sizing, LoadType loadType, BaseObject* parent, float lifeTime)
  : ClickableImage(Vector2::Zero, localPosition, dataAsset, sizing, loadType, parent, lifeTime)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
ClickableImage::ClickableImage(const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, Sizing sizing, LoadType loadType, BaseObject* parent, float lifeTime)
  : Image(size, localPosition, dataAsset, sizing, loadType, parent, lifeTime),
  m_clickState(kIdle),
  m_resetTime(0.05f),
  m_clickResetTimer(0.05f)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
ClickableImage::~ClickableImage()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ClickableImage::Update(float elapsedSeconds)
{
  Image::Update(elapsedSeconds);

  if (IsActive())
  {
    m_clickResetTimer += elapsedSeconds;
    if (m_clickResetTimer >= m_resetTime)
    {
      m_clickState = ClickState::kIdle;
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ClickableImage::HandleInput(float elapsedSeconds, const Vector2& mousePosition)
{
  Image::HandleInput(elapsedSeconds, mousePosition);

  if (AcceptsInput())
  {
    if (IsMouseOver() && m_clickState != ClickState::kPressed)
    {
      m_clickState = ClickState::kHighlighted;
    }

    if (IsClicked())
    {
      if (m_clickState != ClickState::kPressed)
      {
        assert(m_clickFunction);

        m_clickFunction();
        m_clickState = ClickState::kPressed;
        m_clickResetTimer = 0;
      }
    }
  }
}