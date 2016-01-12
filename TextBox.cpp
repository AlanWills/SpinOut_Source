#include "pch.h"
#include "TextBox.h"


//-----------------------------------------------------------------------------------------------------------------------------------
TextBox::TextBox(const Vector2& localPosition, const std::wstring& text, const std::string& dataAsset, BaseObject* parent, float lifeTime) :
  UIObject(localPosition, dataAsset, BaseObject::kTexture, parent, lifeTime),
  m_text(new Label(text, this)),
  m_resized(false)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
TextBox::~TextBox()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void TextBox::Initialize()
{
  UIObject::Initialize();

  // Set size to zero so that we can resize
  SetSize(Vector2::Zero);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void TextBox::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
  UIObject::Draw(spriteBatch, spriteFont);

  m_text->Draw(spriteBatch, spriteFont);

  if (!m_resized)
  {
    Resize();
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void TextBox::Die()
{
  UIObject::Die();

  m_text->Die();
}


//-----------------------------------------------------------------------------------------------------------------------------------
const Vector2& TextBox::GetPadding()
{
  static Vector2 padding(Vector2(8, 8));

  return padding;
}


//-----------------------------------------------------------------------------------------------------------------------------------
void TextBox::Resize()
{
  const Vector2& textSize = m_text->GetSize();
  const Vector2& padding = GetPadding();

  SetSize(textSize + 2 * padding);

  m_resized = true;
}