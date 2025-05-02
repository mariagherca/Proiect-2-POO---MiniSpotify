#include "song.h"
#include "spotify_exception.h"
#include <iostream>
#include <memory>
#include <stdexcept>

Song::Song(const std::string& title, const std::string& artist, int duration, const std::string& genre)
    : title(title), artist(artist), duration(duration), genre(genre) {}

void Song::incrementPlays() { plays++; }
const std::string& Song::getTitle() const { return title; }
const std::string& Song::getArtist() const { return artist; }
int Song::getDuration() const { return duration; }
const std::string& Song::getGenre() const { return genre; }
int Song::getPlays() const { return plays; }

std::unique_ptr<Song> Song::createSong(const std::string& type, const std::string& title,
                                    const std::string& artist, int duration, const std::string& extra) {
    if (type == "pop") {
        float energy = stof(extra);
        return std::make_unique<PopSong>(title, artist, duration, energy);
    } else if (type == "rock") {
        bool isHeavy = (extra == "heavy");
        return std::make_unique<RockSong>(title, artist, duration, isHeavy);
    } else if (type == "classical") {
        return std::make_unique<ClassicalSong>(title, artist, duration, extra);
    }
    throw SongException("Tip melodie necunoscut: " + type);
}

PopSong::PopSong(const std::string& title, const std::string& artist, int duration, float energy)
    : Song(title, artist, duration, "Pop"), energy(energy) {
    if (energy < 0 || energy > 1) throw SongException(title + " - energie invalida");
}

std::unique_ptr<Song> PopSong::clone() const {
    return std::make_unique<PopSong>(*this);
}

void PopSong::play() const {
    std::cout << " Redare melodie pop: " << title << " de " << artist
             << " [" << duration << "s] Energie: " << energy << "\n";
}

void PopSong::display() const {
    std::cout << " " << title << " - " << artist << " (" << duration << "s) [Pop]";
    std::cout << " " << static_cast<int>(energy * 100) << "%";
}

float PopSong::getPopularity() const {
    return (energy * 80) + (duration < 210 ? 20 : 0) + (plays * 0.5);
}

std::string PopSong::getType() const { return "pop"; }

RockSong::RockSong(const std::string& title, const std::string& artist, int duration, bool isHeavy)
    : Song(title, artist, duration, "Rock"), isHeavy(isHeavy) {}

std::unique_ptr<Song> RockSong::clone() const {
    return std::make_unique<RockSong>(*this);
}

void RockSong::play() const {
    std::cout << " Redare " << (isHeavy ? "heavy" : "") << " rock: " << title
             << " de " << artist << " [" << duration << "s]\n";
}

void RockSong::display() const {
    std::cout << " " << title << " - " << artist << " (" << duration << "s) [";
    std::cout << (isHeavy ? "Heavy Rock" : "Rock") << "]";
}

float RockSong::getPopularity() const {
    return (isHeavy ? 70 : 60) + (duration > 240 ? 20 : 0) + (plays * 0.3);
}

std::string RockSong::getType() const { return "rock"; }

ClassicalSong::ClassicalSong(const std::string& title, const std::string& artist, int duration, const std::string& era)
    : Song(title, artist, duration, "Clasica"), era(era) {}

std::unique_ptr<Song> ClassicalSong::clone() const {
    return std::make_unique<ClassicalSong>(*this);
}

void ClassicalSong::play() const {
    std::cout << " Redare melodie clasica (" << era << "): " << title
             << " de " << artist << " [" << duration << "s]\n";
}

void ClassicalSong::display() const {
    std::cout << " " << title << " - " << artist << " (" << duration << "s) [Clasica, " << era << "]";
}

float ClassicalSong::getPopularity() const {
    float base = 50;
    if (era == "Baroc") base += 10;
    else if (era == "Romantism") base += 20;
    return base + (plays * 0.2);
}

std::string ClassicalSong::getType() const { return "classical"; }
