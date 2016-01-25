#include "pch.h"

#include "UIPanel.h"


//-----------------------------------------------------------------------------------------------------------------------------------
UIPanel::UIPanel(ID3D11Device* device, const Vector2& localPosition, const std::string& dataAsset, LoadType loadType, BaseObject* parent, float lifeTime) :
	UIPanel(device, Vector2::Zero, localPosition, dataAsset, loadType, parent, lifeTime)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
UIPanel::UIPanel(ID3D11Device* device, const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, LoadType loadType, BaseObject* parent, float lifeTime) :
	UIObject(size, localPosition, dataAsset, loadType, parent, lifeTime),
	m_uiObjects(new UIObjects(device))
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
UIPanel::~UIPanel()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void UIPanel::LoadContent(ID3D11Device* device)
{
	UIObject::LoadContent(device);

	AddInitialUI();

	m_uiObjects->LoadContent();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void UIPanel::Initialize()
{
	UIObject::Initialize();

	m_uiObjects->Initialize();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void UIPanel::Update(float elapsedSeconds)
{
	UIObject::Update(elapsedSeconds);

	if (IsActive())
	{
		m_uiObjects->Update(elapsedSeconds);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void UIPanel::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	//UIObject::Draw(spriteBatch, spriteFont);

	if (IsVisible())
	{
		m_uiObjects->Draw(spriteBatch, spriteFont);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void UIPanel::HandleInput(float elapsedSeconds, const Vector2& mousePosition)
{
	UIObject::HandleInput(elapsedSeconds, mousePosition);

	if (AcceptsInput())
	{
		m_uiObjects->HandleInput(elapsedSeconds, mousePosition);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void UIPanel::Show()
{
	SetActive(true);
	SetVisible(true);
	SetAcceptsInput(true);

	m_uiObjects->ShowAll();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void UIPanel::Hide()
{
	SetActive(false);
	SetVisible(false);
	SetAcceptsInput(false);

	m_uiObjects->HideAll();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void UIPanel::Die()
{
	UIObject::Die();

	m_uiObjects->DieAll();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void UIPanel::AddUIObject(UIObject* uiObject, bool load, bool initialize)
{
  if (!uiObject->GetParent())
  {
    uiObject->SetParent(this);
  }

  uiObject->SetType(GetType());
	m_uiObjects->AddObject(uiObject, load, initialize);
}


//-----------------------------------------------------------------------------------------------------------------------------------
UIObject* UIPanel::FindObject(const std::string& uiobjectName) const
{
  return m_uiObjects->FindObject(uiobjectName);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void UIPanel::RemoveUIObject(UIObject* uiObject)
{
	m_uiObjects->RemoveObject(uiObject);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void UIPanel::RemoveUIObject(const std::string& uiObjectName)
{
  RemoveUIObject(m_uiObjects->FindObject(uiObjectName));
}