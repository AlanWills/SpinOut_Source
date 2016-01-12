#include "pch.h"

#include "ScreenManager.h"

#include "AddTextBoxScript.h"


//-----------------------------------------------------------------------------------------------------------------------------------
AddTextBoxScript::AddTextBoxScript(const std::wstring& text, float lifeTime, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_textBox(new TextBox(ScreenManager::GetScreenCentre(), text, DIALOGBOX_DEFAULT_TEXTUREASSET, nullptr, lifeTime))
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
AddTextBoxScript::AddTextBoxScript(const Vector2& textBoxPosition, const std::wstring& text, float lifeTime, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_textBox(new TextBox(textBoxPosition, text, DIALOGBOX_DEFAULT_TEXTUREASSET, nullptr, lifeTime))
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
AddTextBoxScript::AddTextBoxScript(TextBox* textBox, bool shouldUpdateGame, bool canRun) :
  Script(shouldUpdateGame, canRun),
  m_textBox(textBox)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
AddTextBoxScript::~AddTextBoxScript()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void AddTextBoxScript::LoadAndInit(ID3D11Device* device)
{
  m_textBox->SetType(UIObject::UIType::kScreen);

  m_textBox->LoadContent(device);
  m_textBox->Initialize();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void AddTextBoxScript::Run(float elapsedSeconds)
{
  Script::Run(elapsedSeconds);

  if (IsRunning())
  {
    m_textBox->Update(elapsedSeconds);

    SetCompleted(m_textBox->IsAlive() == false);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void AddTextBoxScript::DrawScreenObjects(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
  m_textBox->Draw(spriteBatch, spriteFont);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void AddTextBoxScript::HandleInput(float elapsedSeconds)
{
  m_textBox->HandleInput(elapsedSeconds, ScreenManager::GetGameMouse().GetWorldPosition());

  if (ScreenManager::GetGameMouse().IsClicked(MouseButton::kLeftButton))
  {
    m_textBox->Die();
  }
}