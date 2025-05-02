#include "playlist.h"
#include "spotify_exception.h"
#include <algorithm>
#include <map>
#include <iostream>

Playlist::Playlist(const std::string& name, const std::string& creator, const std::string& desc)
    : name(name), creator(creator), description(desc) {}

Playlist::Playlist(const Playlist& other) : name(other.name), creator(other.creator), description(other.description) {
    for (const auto& song : other.songs) {
        songs.push_back(song->clone());
    }
}

Playlist& Playlist::operator=(Playlist other) {
    swap(other);
    return *this;
}

void Playlist::swap(Playlist& other) noexcept {
    using std::swap;
    swap(name, other.name);
    swap(songs, other.songs);
    swap(creator, other.creator);
    swap(description, other.description);
}

void Playlist::addSong(std::unique_ptr<Song> song) {
    songs.push_back(std::move(song));
}

void Playlist::removeSong(const std::string& title) {
    auto it = std::remove_if(songs.begin(), songs.end(),
        [&title](const std::unique_ptr<Song>& s) {
            return s->getTitle() == title;
        });

    if (it == songs.end()) {
        throw SongException(title + " negasita in playlist");
    }

    songs.erase(it, songs.end());
}

void Playlist::playAll() const {
    std::cout << "\n Redare playlist: " << name << " (" << songs.size() << " melodii)\n";
    for (const auto& song : songs) {
        song->play();
    }
}

void Playlist::display(bool detailed) const {
    std::cout << "\nPlaylist: " << name << " (de " << creator << ")\n";
    if (!description.empty()) {
        std::cout << " " << description << "\n";
    }
    std::cout << " " << songs.size() << " melodii | ";

    int totalSec = 0;
    std::map<std::string, int> genreCount;
    for (const auto& song : songs) {
        totalSec += song->getDuration();
        genreCount[song->getGenre()]++;
    }

    std::cout << "Durata: " << totalSec/60 << "m " << totalSec%60 << "s\n";
    std::cout << "Genuri: ";
    for (const auto& [genre, count] : genreCount) {
        std::cout << genre << "(" << count << ") ";
    }
    std::cout << "\n";

    if (detailed) {
        std::cout << "\nMelodii:\n";
        for (size_t i = 0; i < songs.size(); ++i) {
            std::cout << i+1 << ". ";
            songs[i]->display();
            std::cout << "\n";
        }
    }
}

const std::vector<std::unique_ptr<Song>>& Playlist::getSongs() const { return songs; }
const std::string& Playlist::getName() const { return name; }
size_t Playlist::getSongCount() const { return songs.size(); }

std::unique_ptr<Playlist> Playlist::createFromFile(const std::string& name, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw FileException(filename);
    }

    auto playlist = std::make_unique<Playlist>(name);
    std::string type, title, artist, extra;
    int duration;

    while (file >> type >> std::ws && getline(file, title, ',') &&
           getline(file, artist, ',') && file >> duration >> std::ws) {

        getline(file, extra);
        extra.erase(0, extra.find_first_not_of(" \t"));

        try {
            playlist->addSong(Song::createSong(type, title, artist, duration, extra));
        } catch (const std::exception& e) {
            std::cerr << " Eroare la incarcarea melodiei " << title << ": " << e.what() << "\n";
        }
    }

    return playlist;
}
