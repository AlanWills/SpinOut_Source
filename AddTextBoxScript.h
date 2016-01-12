#pragma once

#include "Script.h"

#include "TextBox.h"

class AddTextBoxScript : public Script
{
public:
  AddTextBoxScript(const std::wstring& text, float lifeTime = FLT_MAX, bool shouldUpdateGame = false, bool canRun = true);
  AddTextBoxScript(const Vector2& textBoxPosition, const std::wstring& text, float lifeTime = FLT_MAX, bool shouldUpdateGame = false, bool canRun = true);
  AddTextBoxScript(TextBox* textBox, bool shouldUpdateGame = false, bool canRun = true);
  ~AddTextBoxScript();

  void LoadAndInit(ID3D11Device* device) override;
  void Run(float elapsedSeconds) override;
  void DrawScreenObjects(SpriteBatch* spriteBatch, SpriteFont* spriteFont) override;
  void HandleInput(float elapsedSeconds) override;

private:
  std::unique_ptr<TextBox> m_textBox;
};

