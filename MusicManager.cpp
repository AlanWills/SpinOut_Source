#include "pch.h"

#include "MusicManager.h"


//-----------------------------------------------------------------------------------------------------------------------------------
MusicManager::MusicManager() :
  m_audioEngine(new AudioEngine()),
  m_currentSong(0)
{
  m_audioEngine->SetMasterVolume(0);
}


//-----------------------------------------------------------------------------------------------------------------------------------
MusicManager::~MusicManager()
{
  // Don't know why, but this has to be called otherwise we get an exception
  m_audioEngine->Suspend();
}


//-----------------------------------------------------------------------------------------------------------------------------------
MusicManager& MusicManager::GetInstance()
{
  static MusicManager musicManager;

  return musicManager;
}


//-----------------------------------------------------------------------------------------------------------------------------------
void MusicManager::Update()
{
  bool result = m_audioEngine->Update();
  assert(result);

  if (m_playlist.size() > 0)
  {
    if (!m_playlist[m_currentSong]->IsInUse())
    {
      m_currentSong++;
      
      if (m_currentSong == m_playlist.size())
      {
        PlayFromPlaylistBeginning();
      }
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void MusicManager::SetPlaylist(const std::list<std::wstring>& songs, PlaylistSettings setting)
{
  if (songs.empty() && setting == PlaylistSettings::kKeepCurrentSongsIfEmpty)
  {
    return;
  }

  for (auto& song : m_playlist)
  {
    song.reset(nullptr);
  }

  m_playlist.clear();

  for (const std::wstring& songName : songs)
  {
    m_playlist.push_back(Song(new SoundEffect(m_audioEngine.get(), songName.c_str())));
  }

  m_currentSong = 0;
}


//-----------------------------------------------------------------------------------------------------------------------------------
void MusicManager::PlayFromPlaylistBeginning()
{
  assert(m_playlist.size() > 0);

  m_currentSong = 0;
  m_playlist[m_currentSong]->Play();
}