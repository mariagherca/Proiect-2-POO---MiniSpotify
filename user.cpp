#include "user.h"
#include "spotify_exception.h"
#include <algorithm>
#include <iostream>

User::User(const std::string& name) : username(name) {}

void User::addPlaylist(std::unique_ptr<Playlist> playlist) {
    playlists.push_back(std::move(playlist));
}

void User::createPlaylist(const std::string& name, const std::string& desc) {
    playlists.push_back(std::make_unique<Playlist>(name, username, desc));
}

void User::removePlaylist(const std::string& name) {
    auto it = std::remove_if(playlists.begin(), playlists.end(),
        [&name](const std::unique_ptr<Playlist>& p) {
            return p->getName() == name;
        });

    if (it == playlists.end()) {
        throw PlaylistException(name + " negasit");
    }

    playlists.erase(it, playlists.end());
}

void User::addToFavorites(Song* song) {
    favorites.push_back(song->clone());
}

void User::addFavoriteArtist(const std::string& artist) {
    if (std::find(favoriteArtists.begin(), favoriteArtists.end(), artist) == favoriteArtists.end()) {
        favoriteArtists.push_back(artist);
    }
}

void User::addToHistory(Song* song) {
    history.insert(history.begin(), song->clone());
    if (history.size() > 20) {
        history.pop_back();
    }
}

void User::addSongToLibrary(std::unique_ptr<Song> song) {
    artistLibrary[song->getArtist()].push_back(std::move(song));
}

void User::playSong(Song* song) {
    song->play();
    song->incrementPlays();
    addToHistory(song);
}

void User::displayLibrary() const {
    std::cout << "\n Biblioteca muzicala (" << artistLibrary.size() << " artisti)\n";
    for (const auto& [artist, songs] : artistLibrary) {
        std::cout << " " << artist << ": " << songs.size() << " melodii\n";
    }
}

void User::displayArtistSongs(const std::string& artist) const {
    auto it = artistLibrary.find(artist);
    if (it == artistLibrary.end()) {
        throw SpotifyException("Artist negasit: " + artist);
    }

    std::cout << "\n Melodii de " << artist << ":\n";
    for (size_t i = 0; i < it->second.size(); ++i) {
        std::cout << i+1 << ". ";
        it->second[i]->display();
        std::cout << "\n";
    }
}

void User::displayPlaylists() const {
    std::cout << "\n Playlist-urile tale (" << playlists.size() << ")\n";
    for (const auto& playlist : playlists) {
        playlist->display();
    }
}

void User::displayFavorites() const {
    std::cout << "\n Favorite (" << favorites.size() << " melodii)\n";
    for (size_t i = 0; i < favorites.size(); ++i) {
        std::cout << i+1 << ". ";
        favorites[i]->display();
        std::cout << "\n";
    }
}

void User::displayHistory() const {
    std::cout << "\n Redate recent (" << history.size() << " melodii)\n";
    for (size_t i = 0; i < history.size(); ++i) {
        std::cout << i+1 << ". ";
        history[i]->display();
        std::cout << " (redata de " << history[i]->getPlays() << " ori)\n";
    }
}

const std::vector<std::unique_ptr<Playlist>>& User::getPlaylists() const { return playlists; }
const std::vector<std::unique_ptr<Song>>& User::getFavorites() const { return favorites; }
const std::vector<std::string>& User::getFavoriteArtists() const { return favoriteArtists; }
const std::vector<std::unique_ptr<Song>>& User::getHistory() const { return history; }
const std::map<std::string, std::vector<std::unique_ptr<Song>>>& User::getArtistLibrary() const { return artistLibrary; }
