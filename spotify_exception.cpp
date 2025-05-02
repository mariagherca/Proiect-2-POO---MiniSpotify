#include "spotify_exception.h"

FileException::FileException(const std::string& filename)
    : SpotifyException("Eroare fisier: " + filename) {}

SongException::SongException(const std::string& title)
    : SpotifyException("Eroare melodie: " + title) {}

PlaylistException::PlaylistException(const std::string& name)
    : SpotifyException("Eroare playlist: " + name) {}
