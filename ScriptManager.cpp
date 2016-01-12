#include "pch.h"

#include "BaseScreen.h"
#include "ScriptManager.h"


//-----------------------------------------------------------------------------------------------------------------------------------
ScriptManager::ScriptManager(BaseScreen* baseScreen) :
	m_baseScreen(baseScreen)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
ScriptManager::~ScriptManager()
{
  for (Script* script : m_activeScripts)
  {
    m_scriptsToDelete.push_back(script);
  }

  for (Script* script : m_scriptsToDelete)
  {
    m_activeScripts.remove(script);
    delete script;
  }

  m_scriptsToDelete.clear();
  m_activeScripts.clear();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScriptManager::LoadAndInit()
{
  for (Script* script : m_activeScripts)
  {
    script->LoadAndInit(m_baseScreen->GetDevice());
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScriptManager::Update(float elapsedSeconds)
{
  for (Script* script : m_activeScripts)
  {
    if (script->CanRun())
    {
      script->Run(elapsedSeconds);
    }

    if (script->IsCompleted())
    {
      m_scriptsToDelete.push_back(script);
    }
  }

  for (Script* script : m_scriptsToDelete)
  {
    m_activeScripts.remove(script);
    delete script;
  }

  m_scriptsToDelete.clear();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScriptManager::DrawInGameObjects(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
  for (Script* script : m_activeScripts)
  {
    if (script->IsRunning())
    {
      script->DrawInGameObjects(spriteBatch, spriteFont);
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScriptManager::DrawScreenObjects(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
  for (Script* script : m_activeScripts)
  {
    if (script->IsRunning())
    {
      script->DrawScreenObjects(spriteBatch, spriteFont);
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScriptManager::HandleInput(float elapsedSeconds)
{
  for (Script* script : m_activeScripts)
  {
    if (script->IsRunning())
    {
      script->HandleInput(elapsedSeconds);
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void ScriptManager::AddScript(Script* script)
{
  script->LoadAndInit(m_baseScreen->GetDevice());

  m_activeScripts.push_back(script);
}


//-----------------------------------------------------------------------------------------------------------------------------------
bool ScriptManager::ShouldUpdateGame() const
{
  // If we have no active scripts we should update the game
  if (m_activeScripts.size() == 0)
  {
    return true;
  }

  for (Script* script : m_activeScripts)
  {
    if (script->IsRunning())
    {
      // If we have one script which shouldn't update the game, we shouldn't update
      if (!script->ShouldUpdateGame())
      {
        return false;
      }
    }
  }

  // No scripts are running so we can update the game
  return true;
}


//-----------------------------------------------------------------------------------------------------------------------------------
Script* ScriptManager::GetLastAddedScript() const
{
  if (m_activeScripts.size() > 0)
  {
    return m_activeScripts.back();
  }

  return nullptr;
}