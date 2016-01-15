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

  IMPLEMENT_SIMPLE_SCRIPT_LOAD;
  IMPLEMENT_SIMPLE_SCRIPT_RUN_HANDLE_INPUT;
  IMPLEMENT_SIMPLE_SCRIPT_DRAW_SCREENOBJECTS;

private:
  std::unique_ptr<TextBox> m_textBox;
};

