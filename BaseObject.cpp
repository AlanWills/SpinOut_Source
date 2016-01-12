#include "pch.h"
#include "ScreenManager.h"
#include "BaseObject.h"
#include "RectangleCollider.h"

#include <DirectXMath.h>


//-----------------------------------------------------------------------------------------------------------------------------------
BaseObject::BaseObject(const std::string& dataAsset, LoadType loadType, BaseObject* parent) :
BaseObject(Vector2(0, 0), Vector2(0, 0), dataAsset, loadType, parent)
{

}


//-----------------------------------------------------------------------------------------------------------------------------------
BaseObject::BaseObject(const Vector2& localPosition, const std::string& dataAsset, LoadType loadType, BaseObject* parent) :
BaseObject(Vector2(0, 0), localPosition, dataAsset, loadType, parent)
{

}


//-----------------------------------------------------------------------------------------------------------------------------------
BaseObject::BaseObject(const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, LoadType loadType, BaseObject* parent) :
m_name(""),
m_localPosition(localPosition),
m_localRotation(0),
m_dataAsset(dataAsset),
m_loadType(loadType),
m_parent(parent),
m_textureHandler(nullptr),
m_size(size),
m_mouseOver(false),
m_shouldHaveCollider(true),
m_collider(nullptr),
m_active(false),
m_visible(false),
m_acceptsInput(false),
m_alive(false),
m_colour(Color(1, 1, 1, 1)),
m_opacity(1.0f),
m_onDeathFunction(nullptr)
{
  // Initialise the click and select arrays
  FlushClickArray();
  FlushSelectArray();
}


//-----------------------------------------------------------------------------------------------------------------------------------
BaseObject::~BaseObject()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseObject::LoadContent(ID3D11Device* device)
{
	m_textureHandler.reset(new Texture2D());

	// If we have set this flag to kNoLoad, we do not want to perform any loading of data or textures
	if (m_loadType != kTexture)
	{
		return;
	}

  LoadTexture(device, m_dataAsset);

  // Sets the size (if no size was specified originally) because we have loaded a texture
	if (m_size == Vector2::Zero && m_textureHandler.get())
	{
		m_size = m_textureHandler->GetDimensions();
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseObject::LoadTexture(ID3D11Device* device, const std::string& textureAsset)
{
  const wchar_t* wTextureAsset = GenericUtils::CharToWChar(textureAsset.c_str());
  m_textureHandler->Load(device, wTextureAsset);

  assert(m_textureHandler->GetTexture());

  delete[] wTextureAsset;
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseObject::Initialize()
{
	// To catch any instances where this slips through the net (i.e. custom texture loading)
	if (m_size == Vector2::Zero && m_textureHandler.get())
	{
		m_size = m_textureHandler->GetDimensions();
	}

	// All state variables for the object need to be set to true now that the object is about to be inserted into the game
	Create();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseObject::AddCollider()
{
  if (m_shouldHaveCollider)
  {
    m_collider.reset(new RectangleCollider(this));
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseObject::Update(float elapsedSeconds)
{
	if (!m_active)
	{
		return;
	}

  if (m_collider)
  {
    m_collider->UpdateCollider();
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseObject::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
  CheckVisible();

	if (!m_visible)
	{
		return;
	}

	// Put draw code here
	assert(GetTexture()->GetTexture());
	spriteBatch->Draw(
		GetTexture()->GetTexture(), 
		GetWorldPosition(), 
		nullptr, 
		m_colour * m_opacity, 
		GetWorldRotation(), 
		m_textureHandler->GetCentre(), 
		XMVectorDivide(m_size, m_textureHandler->GetDimensions()));
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseObject::HandleInput(float elapsedSeconds, const Vector2& mousePosition)
{
  // Reset the clicked status of this object - this can now only be set to true if we click OVER the object again
  FlushClickArray();

  // If we do not have a collider we should not continue
  if (!m_shouldHaveCollider)
  {
    return;
  }
  
	if (!m_acceptsInput)
	{
		return;
	}

	// Input handling code

	// We should have a collider - if an inherited class is reaching here without a collider, something is wrong
	assert(m_collider);

  for (unsigned int mouseButton = static_cast<unsigned int>(MouseButton::kLeftButton); mouseButton < static_cast<unsigned int>(MouseButton::kNumButtons); mouseButton++)
  {
    // Work out whether the mouse is over the object using the collider and mouse in game position
    m_mouseOver = m_collider->CheckCollisionWith(mousePosition);

    // If mouse button isn't clicked we do not need to change the selection state and can continue
    if (!ScreenManager::GetGameMouse().IsClicked(static_cast<MouseButton>(mouseButton)))
    {
      continue;
    }

    // We have clicked the mouse left button so need to check the selection status
    if (m_mouseOver)
    {
      // Object has been clicked on
      m_clicked[mouseButton] = true;

      if (!m_selected[mouseButton])
      {
        // Mouse is over the object and not already selected so we select it
        m_selected[mouseButton] = true;
      }
    }
    else
    {
      // Otherwise we have not clicked on the object so it is not selected
      m_selected[mouseButton] = false;
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseObject::Create()
{
	m_alive = true;
	
	Show();
	AddCollider();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseObject::Die()
{
  if (m_onDeathFunction != nullptr)
  {
    m_onDeathFunction();
  }

	m_alive = false;

	Hide();
}


//-----------------------------------------------------------------------------------------------------------------------------------
const Vector2 BaseObject::GetWorldPosition() const
{
	if (!m_parent)
	{
		return m_localPosition;
	}

	// Horrible, but like this for optimization purposes
	return m_parent->GetWorldPosition() + Vector2::Transform(m_localPosition, Matrix::CreateRotationZ(GetWorldRotation()));
}


//-----------------------------------------------------------------------------------------------------------------------------------
const Vector2 BaseObject::GetWorldPosition(const Vector2& localPosition) const
{
	if (!m_parent)
	{
		return localPosition;
	}

	// Horrible, but like this for optimization purposes
	return m_parent->GetWorldPosition() + Vector2::Transform(localPosition, Matrix::CreateRotationZ(GetWorldRotation()));
}


//-----------------------------------------------------------------------------------------------------------------------------------
const float BaseObject::GetWorldRotation() const
{
	if (!m_parent)
	{
		return m_localRotation;
	}

	return XMScalarModAngle(m_parent->GetWorldRotation() + m_localRotation);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseObject::FlushClickArray()
{
  for (unsigned int button = static_cast<unsigned int>(MouseButton::kLeftButton); button < static_cast<unsigned int>(MouseButton::kNumButtons); button++)
  {
    m_clicked[button] = false;
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseObject::FlushSelectArray()
{
  for (unsigned int button = static_cast<unsigned int>(MouseButton::kLeftButton); button < static_cast<unsigned int>(MouseButton::kNumButtons); button++)
  {
    m_selected[button] = false;
  }
}