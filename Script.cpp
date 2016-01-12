#include "pch.h"
#include "Script.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Script::Script(bool shouldUpdateGame, bool canRun) :
	m_canRun(canRun),
	m_shouldUpdateGame(shouldUpdateGame),
	m_running(false),
	m_completed(false),
	m_timeRunFor(0),
	m_previousScript(nullptr)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Script::~Script()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Script::SetCanRunOnScriptCompleted(const Script* previousScript)
{
  m_previousScript = previousScript;
	m_canRunFunction = [this]()
	{
		return m_previousScript->IsCompleted();
	};
}


//-----------------------------------------------------------------------------------------------------------------------------------
const bool Script::CanRun()
{
	if (IsRunning())
	{
		return true;
	}

	if (m_canRunFunction)
	{
		return m_canRunFunction();
	}

	return m_canRun;
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Script::Run(float elapsedSeconds)
{
	m_running = true;
	m_timeRunFor += static_cast<float>(elapsedSeconds);
}