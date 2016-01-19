#pragma once

#include <Audio.h>
#include <unordered_map>

class SFXManager
{
public:
  ~SFXManager();

  static SFXManager& GetInstance();

  SFXManager(SFXManager const&) = delete;
  void operator=(SFXManager const&) = delete;

  void Update();

  void AddSoundEffect(const std::string& soundEffectAsset);
  std::unique_ptr<SoundEffectInstance> CreateSoundEffectInstance(const std::string& soundEffectAsset) const;
  void PlaySound(const std::string& soundEffectAsset);

private:
  SFXManager();

  typedef std::unordered_map<std::string, std::unique_ptr<SoundEffect>> SoundEffects;

  SoundEffects m_soundEffects;
  std::unique_ptr<AudioEngine> m_audioEngine;

  // Need big map of preset SFX which we create instance of
};

