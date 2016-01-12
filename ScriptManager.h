#pragma once

#include "Script.h"

#include <list>

class BaseScreen;

class ScriptManager
{
public:
	ScriptManager(BaseScreen* baseScreen);
	~ScriptManager();

  void LoadAndInit();
  void Update(float elapsedSeconds);
  void DrawInGameObjects(SpriteBatch* spriteBatch, SpriteFont* spriteFont);
  void DrawScreenObjects(SpriteBatch* spriteBatch, SpriteFont* spriteFont);
  void HandleInput(float elapsedSeconds);

  void AddScript(Script* script);

  bool ShouldUpdateGame() const;

  Script* GetLastAddedScript() const;

private:
	/// brief Typedefs
	typedef std::list<Script*> Scripts;

	Scripts m_activeScripts;
	Scripts m_scriptsToDelete;

	BaseScreen* m_baseScreen;
};