#include "pch.h"

#include "SFXManager.h"

#include "Button.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Button::Button(const Vector2& localPosition, const std::wstring& text, const std::string& dataAsset, LoadType loadType, BaseObject* parent, float lifeTime) :
	Button(Vector2::Zero, localPosition, text, dataAsset, loadType, parent, lifeTime)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Button::Button(const Vector2& size, const Vector2& localPosition, const std::wstring& text, const std::string& dataAsset, LoadType loadType, BaseObject* parent, float lifeTime) :
	ClickableImage(size, localPosition, dataAsset, Sizing::kDoNotPreserveAspectRatio, loadType, parent, lifeTime),
	m_label(new Label(text, this))
{
  SFXManager::GetInstance().AddSoundEffect(BUTTON_HOVER_SOUND_ASSET);
}


//-----------------------------------------------------------------------------------------------------------------------------------
Button::~Button()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Button::Initialize()
{
	ClickableImage::Initialize();

	m_label->Initialize();

	// Set up the colours here
	SetColour(m_defaultColour);
	m_label->SetColour(Color(0, 0, 0, 1));
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Button::Update(float elapsedSeconds)
{
	ClickableImage::Update(elapsedSeconds);

	if (IsActive())
	{
		// Lerp our current colour to the default one to create effect when mouse over button
		SetColour(Color::Lerp(GetColour(), m_defaultColour, elapsedSeconds * 3));
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Button::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	ClickableImage::Draw(spriteBatch, spriteFont);

	if (IsVisible())
	{
		m_label->Draw(spriteBatch, spriteFont);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Button::HandleInput(float elapsedSeconds, const Vector2& mousePosition)
{
	ClickableImage::HandleInput(elapsedSeconds, mousePosition);

	if (AcceptsInput())
	{
    if (HasMouseEntered())
    {
      SFXManager::GetInstance().PlaySound(BUTTON_HOVER_SOUND_ASSET);
    }

		if (IsMouseOver() && GetClickState() != ClickState::kPressed)
		{
			SetColour(m_highlightedColour);
		}
	}
}