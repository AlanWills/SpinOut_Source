#include "pch.h"

#include "ScreenManager.h"
#include "LoadingScreen.h"
#include "GameplayScreen.h"

static Vector2 m_screenCentre;
static Camera m_camera;
static GameMouse m_gameMouse;
static KeyboardInput m_keyboard;


//-----------------------------------------------------------------------------------------------------------------------------------
const Vector2& ScreenManager::GetScreenCentre()
{
	return m_screenCentre;
}


//-----------------------------------------------------------------------------------------------------------------------------------
Camera& ScreenManager::GetCamera()
{
	return m_camera;
}


//-----------------------------------------------------------------------------------------------------------------------------------
GameMouse& ScreenManager::GetGameMouse()
{
	return m_gameMouse;
}


//-----------------------------------------------------------------------------------------------------------------------------------
KeyboardInput& ScreenManager::GetKeyboardInput()
{
	return m_keyboard;
}


//-----------------------------------------------------------------------------------------------------------------------------------
ScreenManager::ScreenManager(ID3D11Device* device, ID3D11DeviceContext* deviceContext, float screenWidth, float screenHeight) :
m_device(device),
m_deviceContext(deviceContext),
m_spriteBatch(new SpriteBatch(deviceContext)),
m_spriteFont(new SpriteFont(device, L"Font.spritefont")),
m_states(new CommonStates(device))
{
	m_screenCentre = Vector2(screenWidth, screenHeight) * 0.5f;
  m_camera.SetUpFrame(m_screenCentre);
}


//-----------------------------------------------------------------------------------------------------------------------------------
ScreenManager::~ScreenManager()
{
	// Need to delete all the screens here
	for (BaseScreen* screen : m_activeScreens)
	{
		delete screen;
	}

	m_activeScreens.clear();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScreenManager::LoadContent()
{
	m_gameMouse.LoadContent(m_device);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScreenManager::Initialize()
{
	m_gameMouse.Initialize();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScreenManager::Update(float elapsedSeconds)
{
	m_keyboard.Update();
	m_camera.Update(elapsedSeconds);
	m_gameMouse.Update(elapsedSeconds);

	for (BaseScreen* screen : m_activeScreens)
	{
		// Screen updating
		screen->Update(elapsedSeconds);
	}

	for (BaseScreen* screen : m_screensToDelete)
	{
		// Clean up dead screens
		m_activeScreens.remove(screen);
		delete screen;
	}

	m_screensToDelete.clear();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScreenManager::Draw()
{
	// Draw the background
	m_spriteBatch->Begin(SpriteSortMode_Immediate, m_states->NonPremultiplied());

	m_activeScreens.back()->DrawBackground(m_spriteBatch.get(), m_spriteFont.get());

	m_spriteBatch->End();

	// Draw the camera dependent game objects
	m_spriteBatch->Begin(SpriteSortMode_Immediate, m_states->NonPremultiplied(), nullptr, nullptr, nullptr, nullptr, m_camera.GetViewMatrix());

	for (BaseScreen* screen : m_activeScreens)
	{
		screen->DrawInGameObjects(m_spriteBatch.get(), m_spriteFont.get());
	}

	m_spriteBatch->End();

	// Draw the screen (camera independent) objects
	m_spriteBatch->Begin(SpriteSortMode_Immediate, m_states->NonPremultiplied());

	for (BaseScreen* screen : m_activeScreens)
	{
		screen->DrawScreenObjects(m_spriteBatch.get(), m_spriteFont.get());
	}

	// Draw the game mouse - camera independent
	m_gameMouse.Draw(m_spriteBatch.get(), m_spriteFont.get());

	m_spriteBatch->End();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScreenManager::HandleInput(float elapsedSeconds)
{
	m_gameMouse.HandleInput(elapsedSeconds);

	for (BaseScreen* screen : m_activeScreens)
	{
		// Screen input handling
		screen->HandleInput(elapsedSeconds);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------
BaseScreen* ScreenManager::GetCurrentScreen()
{
  assert(m_activeScreens.size() > 0);
  return m_activeScreens.front();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScreenManager::AddScreen(BaseScreen* screenToAdd, bool load, bool initialize)
{
  if (load)
  {
    screenToAdd->LoadContent();
  }

  if (initialize)
  {
    screenToAdd->Initialize();
  }

	// push_front is a MUST
	// Subtle reason why - if we push_back, if we transition from one screen to another, we will handle input on that screen in the same update loop
	// This can lead to automatic button clicking if we transition from one screen to another via a button
	m_activeScreens.push_front(screenToAdd);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScreenManager::RemoveScreen(BaseScreen* screenToRemove)
{
	m_screensToDelete.push_back(screenToRemove);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScreenManager::Transition(BaseScreen* transitionFrom, BaseScreen* transitionTo, bool load, bool initialize)
{
  // Want to make sure that our screen exists to delete
  bool screenExists = false;
  for (BaseScreen* screen : m_activeScreens)
  {
    screenExists = screenExists || screen == transitionFrom;
  }

  assert(screenExists);

  // Want to do the same as BaseScreen transition here and add a loading screen if necessary
  if (dynamic_cast<GameplayScreen*>(transitionTo) && !dynamic_cast<LoadingScreen*>(transitionFrom))
  {
    AddScreen(new LoadingScreen(this, transitionTo));
  }
  else
  {
    AddScreen(transitionTo, load, initialize);
  }

  RemoveScreen(transitionFrom);
}