#include "pch.h"

#include "SFXManager.h"


//-----------------------------------------------------------------------------------------------------------------------------------
SFXManager::SFXManager() :
  m_audioEngine(new AudioEngine())
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
SFXManager::~SFXManager()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
SFXManager& SFXManager::GetInstance()
{
  static SFXManager sfxManager;

  return sfxManager;
}


//-----------------------------------------------------------------------------------------------------------------------------------
void SFXManager::Update()
{
  bool result = m_audioEngine->Update();
  assert(result);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void SFXManager::AddSoundEffect(const std::string& soundEffectAsset)
{
  m_soundEffects.insert(SoundEffectPair(soundEffectAsset, std::unique_ptr<SoundEffect>(new SoundEffect(m_audioEngine.get(), GenericUtils::CharToWChar(soundEffectAsset.c_str())))));
}


//-----------------------------------------------------------------------------------------------------------------------------------
std::unique_ptr<SoundEffectInstance> SFXManager::CreateSoundEffectInstance(const std::string& soundEffectAsset) const
{
  assert(m_soundEffects.find(soundEffectAsset) != m_soundEffects.end());

  return m_soundEffects.at(soundEffectAsset)->CreateInstance();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void SFXManager::PlaySound(const std::string& soundEffectAsset)
{
  assert(m_soundEffects.find(soundEffectAsset) != m_soundEffects.end());

  m_soundEffects.at(soundEffectAsset)->Play();
}