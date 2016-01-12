#pragma once

#include "UIObject.h"
#include "Label.h"

#define DIALOGBOX_DEFAULT_TEXTUREASSET "DialogBox.png"

class TextBox : public UIObject
{
public:
  TextBox(const Vector2& localPosition, const std::wstring& text, const std::string& dataAsset = DIALOGBOX_DEFAULT_TEXTUREASSET, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
  ~TextBox();

  static const Vector2& GetPadding();

  void Initialize() override;
  void Draw(SpriteBatch* spritBatch, SpriteFont* spriteFont) override;
  void Die() override;

private:
  void Resize();

  std::unique_ptr<Label> m_text;
  bool m_resized;
};