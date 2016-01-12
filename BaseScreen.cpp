#include "pch.h"

#include "BaseScreen.h"
#include "ScreenManager.h"

#include "Label.h"


//-----------------------------------------------------------------------------------------------------------------------------------
BaseScreen::BaseScreen(ScreenManager* screenManager, const std::string& dataAsset) :
m_screenManager(screenManager),
m_scriptManager(new ScriptManager(this)),
m_device(screenManager->GetDevice()),
m_baseScreenData(new BaseScreenData(dataAsset)),
m_begun(false),
m_active(false),
m_visible(false),
m_acceptsInput(false),
m_alive(false),
m_background(nullptr)
{
	m_gameObjects.reset(new GameObjects(m_screenManager->GetDevice()));
	m_inGameUIObjects.reset(new UIObjects(m_screenManager->GetDevice()));
	m_screenUIObjects.reset(new UIObjects(m_screenManager->GetDevice()));
}


//-----------------------------------------------------------------------------------------------------------------------------------
BaseScreen::~BaseScreen()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::LoadContent()
{
	m_baseScreenData->LoadData();

	AddInitialUI();

	m_gameObjects->LoadContent();
	m_inGameUIObjects->LoadContent();
	m_screenUIObjects->LoadContent();
}

//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::AddInitialUI()
{
	// This has to be separate so we can draw it behind all the other objects
	m_background.reset(new UIObject(GetScreenCentre() * 2, GetScreenCentre(), m_baseScreenData->GetBackgroundAsset(), BaseObject::LoadType::kTexture));
	m_background->LoadContent(GetDevice());
  m_background->SetShouldHaveCollider(false);

	AddScreenUIObject(new Label(Vector2(GetScreenCentre().x, GetScreenCentre().y * 0.25f), m_baseScreenData->GetDisplayName()));
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::Initialize()
{
	m_gameObjects->Initialize();
	m_inGameUIObjects->Initialize();
	m_screenUIObjects->Initialize();

	if (m_background.get())
	{
		m_background->Initialize();
	}

  AddInitialScripts();
  m_scriptManager->LoadAndInit();

	m_alive = true;
	Show();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::Begin()
{
	m_begun = true;
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::Update(float elapsedSeconds)
{
	if (m_active)
	{
		if (!m_begun)
		{
			Begin();
		}

    m_scriptManager->Update(elapsedSeconds);

    if (m_scriptManager->ShouldUpdateGame())
    {
      for (GameObject* gameObject : m_gameObjects->GetObjects())
      {
        gameObject->CheckCollisionWithObjects(m_collisionObjects);
      }

      m_gameObjects->Update(elapsedSeconds);
      m_inGameUIObjects->Update(elapsedSeconds);
      m_screenUIObjects->Update(elapsedSeconds);
    }
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::DrawInGameObjects(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	if (m_visible)
	{
		m_gameObjects->Draw(spriteBatch, spriteFont);
		m_inGameUIObjects->Draw(spriteBatch, spriteFont);

    m_scriptManager->DrawInGameObjects(spriteBatch, spriteFont);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::DrawScreenObjects(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	if (m_visible)
	{
		m_screenUIObjects->Draw(spriteBatch, spriteFont);

    m_scriptManager->DrawScreenObjects(spriteBatch, spriteFont);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::DrawBackground(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	if (m_visible)
	{
		m_background->Draw(spriteBatch, spriteFont);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::HandleInput(float elapsedSeconds)
{
	if (m_acceptsInput)
	{
    m_scriptManager->HandleInput(elapsedSeconds);

    const Vector2& mouseScreenPosition = m_screenManager->GetGameMouse().GetWorldPosition();
    const Vector2& mouseInGamePosition = m_screenManager->GetGameMouse().GetInGamePosition();

		m_gameObjects->HandleInput(elapsedSeconds, mouseInGamePosition);
		m_inGameUIObjects->HandleInput(elapsedSeconds, mouseInGamePosition);
		m_screenUIObjects->HandleInput(elapsedSeconds, mouseScreenPosition);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::Transition(BaseScreen* transitionTo)
{
	m_screenManager->AddScreen(transitionTo);
	m_screenManager->RemoveScreen(this);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::Show()
{
	m_active = true;
	m_visible = true;
	m_acceptsInput = true;
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::Hide()
{
	m_active = false;
	m_visible = false;
	m_acceptsInput = false;
}


//-----------------------------------------------------------------------------------------------------------------------------------
const Vector2& BaseScreen::GetScreenCentre() const
{
	return ScreenManager::GetScreenCentre();
}


//-----------------------------------------------------------------------------------------------------------------------------------
const Vector2 BaseScreen::GetScreenDimensions() const
{
  return ScreenManager::GetScreenDimensions();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::AddScript(Script* script)
{
  AddScript(script, GetLastAddedScript());
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::AddScript(Script* script, Script* previousScript)
{
  if (previousScript)
  {
    script->SetCanRunOnScriptCompleted(previousScript);
  }

  m_scriptManager->AddScript(script);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::AddCollisionObject(GameObject* gameObject, bool noCollisions)
{
  gameObject->SetNoCollisions(noCollisions);
  m_collisionObjects.push_back(gameObject);
}


/////////////// Utility function wrappers for the object managers

//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::AddGameObject(GameObject* gameObject, bool load, bool initialize)
{
	m_gameObjects->AddObject(gameObject, load, initialize);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::RemoveGameObject(GameObject* gameObject)
{
	m_gameObjects->RemoveObject(gameObject);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::AddInGameUIObject(UIObject* inGameUIObject, bool load, bool initialize)
{
  inGameUIObject->SetType(UIObject::kInGame);
	m_inGameUIObjects->AddObject(inGameUIObject, load, initialize);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::RemoveInGameUIObject(UIObject* inGameUIObject)
{
	m_inGameUIObjects->RemoveObject(inGameUIObject);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::AddScreenUIObject(UIObject* screenUIObject, bool load, bool initialize)
{
  screenUIObject->SetType(UIObject::kScreen);
	m_screenUIObjects->AddObject(screenUIObject, load, initialize);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseScreen::RemoveScreenUIObject(UIObject* screenUIObject)
{
	m_screenUIObjects->RemoveObject(screenUIObject);
}

/////////////// end
