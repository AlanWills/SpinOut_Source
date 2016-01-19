#pragma once

#include <Audio.h>
#include <list>

class MusicManager
{
public:
  ~MusicManager();

  static MusicManager& GetInstance();

  MusicManager(MusicManager const&) = delete;
  void operator=(MusicManager const&) = delete;

  void Update();

  enum PlaylistSettings
  {
    kKeepCurrentSongsIfEmpty,   /// If we are adding an empty list of songs, we just keep the playlist we have
    kForceNew,                  /// If we are adding an empty list of songs, we clear the playlist
  };

  void SetPlaylist(const std::list<std::wstring>& songs, PlaylistSettings setting = PlaylistSettings::kKeepCurrentSongsIfEmpty);
  void PlayFromPlaylistBeginning();

private:
  MusicManager();

  typedef std::unique_ptr<SoundEffect> Song;
  typedef std::vector<Song> Songs;

  std::unique_ptr<AudioEngine> m_audioEngine;
  Songs m_playlist;
  size_t m_currentSong;
};