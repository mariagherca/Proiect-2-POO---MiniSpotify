#ifndef USER_H
#define USER_H

#include "playlist.h"
#include <string>
#include <vector>
#include <memory>
#include <map>

class User {
private:
    std::string username;
    std::vector<std::unique_ptr<Playlist>> playlists;
    std::vector<std::unique_ptr<Song>> favorites;
    std::vector<std::string> favoriteArtists;
    std::vector<std::unique_ptr<Song>> history;
    std::map<std::string, std::vector<std::unique_ptr<Song>>> artistLibrary;

public:
    User(const std::string& name);

    void addPlaylist(std::unique_ptr<Playlist> playlist);
    void createPlaylist(const std::string& name, const std::string& desc = "");
    void removePlaylist(const std::string& name);
    void addToFavorites(Song* song);
    void addFavoriteArtist(const std::string& artist);
    void addToHistory(Song* song);
    void addSongToLibrary(std::unique_ptr<Song> song);
    void playSong(Song* song);
    void displayLibrary() const;
    void displayArtistSongs(const std::string& artist) const;
    void displayPlaylists() const;
    void displayFavorites() const;
    void displayHistory() const;

    const std::vector<std::unique_ptr<Playlist>>& getPlaylists() const;
    const std::vector<std::unique_ptr<Song>>& getFavorites() const;
    const std::vector<std::string>& getFavoriteArtists() const;
    const std::vector<std::unique_ptr<Song>>& getHistory() const;
    const std::map<std::string, std::vector<std::unique_ptr<Song>>>& getArtistLibrary() const;
};

#endif
