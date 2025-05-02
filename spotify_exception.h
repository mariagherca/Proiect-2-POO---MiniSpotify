#ifndef SPOTIFY_EXCEPTION_H
#define SPOTIFY_EXCEPTION_H

#include <stdexcept>
#include <string>

class SpotifyException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class FileException : public SpotifyException {
public:
    FileException(const std::string& filename);
};

class SongException : public SpotifyException {
public:
    SongException(const std::string& title);
};

class PlaylistException : public SpotifyException {
public:
    PlaylistException(const std::string& name);
};

#endif

