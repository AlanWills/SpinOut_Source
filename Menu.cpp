#include "pch.h"
#include "Menu.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Menu::Menu(ID3D11Device* device, const Vector2& localPosition, const std::string& dataAsset, LoadType loadType, BaseObject* parent, float lifeTime) :
	Menu(device, Vector2::Zero, localPosition, dataAsset, loadType, parent, lifeTime)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Menu::Menu(ID3D11Device* device, const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, LoadType loadType, BaseObject* parent, float lifeTime) :
	UIObject(size, localPosition, dataAsset, loadType, parent, lifeTime),
	m_uiObjects(new UIObjects(device))
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Menu::~Menu()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Menu::LoadContent(ID3D11Device* device)
{
	UIObject::LoadContent(device);

	AddInitialUI();

	m_uiObjects->LoadContent();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Menu::Initialize()
{
	UIObject::Initialize();

	m_uiObjects->Initialize();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Menu::Update(float elapsedSeconds)
{
	UIObject::Update(elapsedSeconds);

	if (IsActive())
	{
		m_uiObjects->Update(elapsedSeconds);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Menu::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	//UIObject::Draw(spriteBatch, spriteFont);

	if (IsVisible())
	{
		m_uiObjects->Draw(spriteBatch, spriteFont);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Menu::HandleInput(float elapsedSeconds, const Vector2& mousePosition)
{
	UIObject::HandleInput(elapsedSeconds, mousePosition);

	if (AcceptsInput())
	{
		m_uiObjects->HandleInput(elapsedSeconds, mousePosition);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Menu::Show()
{
	SetActive(true);
	SetVisible(true);
	SetAcceptsInput(true);

	m_uiObjects->ShowAll();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Menu::Hide()
{
	SetActive(false);
	SetVisible(false);
	SetAcceptsInput(false);

	m_uiObjects->HideAll();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Menu::Die()
{
	UIObject::Die();

	m_uiObjects->DieAll();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Menu::AddUIObject(UIObject* uiObject, bool load, bool initialize)
{
  if (!uiObject->GetParent())
  {
    uiObject->SetParent(this);
  }

  uiObject->SetType(GetType());
	m_uiObjects->AddObject(uiObject, load, initialize);
}


//-----------------------------------------------------------------------------------------------------------------------------------
UIObject* Menu::FindObject(const std::string& uiobjectName) const
{
  return m_uiObjects->FindObject(uiobjectName);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Menu::RemoveUIObject(UIObject* uiObject)
{
	m_uiObjects->RemoveObject(uiObject);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Menu::RemoveUIObject(const std::string& uiObjectName)
{
  RemoveUIObject(m_uiObjects->FindObject(uiObjectName));
}