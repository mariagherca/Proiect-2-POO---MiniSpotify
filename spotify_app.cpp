#include "spotify_app.h"
#include "playlist.h"
#include "spotify_exception.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <ctime>

SpotifyApp::SpotifyApp(const std::string& username) : user(username) {
    std::srand(std::time(0));
    loadInitialData();
}

void SpotifyApp::loadInitialData() {
    try {
        user.addPlaylist(Playlist::createFromFile("Hituri Pop", "pop_songs.txt"));
        user.addPlaylist(Playlist::createFromFile("Clasice Rock", "rock_songs.txt"));
        user.addPlaylist(Playlist::createFromFile("Muzica Clasica", "classical_songs.txt"));

        auto loadSongsFromFile = [this](const std::string& filename) {
            auto playlist = Playlist::createFromFile("temp", filename);
            for (const auto& song : playlist->getSongs()) {
                allSongs.push_back(song->clone());
                user.addSongToLibrary(song->clone());
            }
        };

        loadSongsFromFile("pop_songs.txt");
        loadSongsFromFile("rock_songs.txt");
        loadSongsFromFile("classical_songs.txt");

        user.addFavoriteArtist("The Weeknd");

    } catch (const std::exception& e) {
        std::cerr << " Eroare la incarcarea datelor initiale: " << e.what() << "\n";
    }
}

void SpotifyApp::displayMainMenu() {
    std::cout << "\n=== MiniSpotify ===\n"
             << "1. Exploreaza biblioteca\n"
             << "2. Playlist-urile tale\n"
             << "3. Melodiile favorite\n"
             << "4. Istoric redari\n"
             << "5. Cauta melodii\n"
             << "0. Iesire\n"
             << "Alege optiunea: ";
}

void SpotifyApp::browseLibrary() {
    int choice;
    do {
        std::cout << "\n=== Biblioteca muzicala ===\n"
                 << "1. Vezi toti artistii\n"
                 << "2. Vezi artistii preferati\n"
                 << "3. Vezi cele mai populare melodii\n"
                 << "0. Inapoi\n"
                 << "Alege optiunea: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                user.displayLibrary();
                std::cout << "\nIntrodu numele artistului (sau 0 pentru anulare): ";
                std::string artist;
                getline(std::cin, artist);
                if (artist != "0") {
                    try {
                        user.displayArtistSongs(artist);
                        playSongFromLibrary(artist);
                    } catch (const std::exception& e) {
                        std::cerr << "Eroare: " << e.what() << "\n";
                    }
                }
                break;
            }
            case 2: {
                const auto& favArtists = user.getFavoriteArtists();
                std::cout << "\n Artistii tai preferati:\n";
                for (size_t i = 0; i < favArtists.size(); ++i) {
                    std::cout << i+1 << ". " << favArtists[i] << "\n";
                }
                if (!favArtists.empty()) {
                    std::cout << "Introdu numarul artistului (sau 0 pentru anulare): ";
                    size_t num;
                    std::cin >> num;
                    std::cin.ignore();
                    if (num > 0 && num <= favArtists.size()) {
                        try {
                            user.displayArtistSongs(favArtists[num-1]);
                            playSongFromLibrary(favArtists[num-1]);
                        } catch (const std::exception& e) {
                            std::cerr << "Eroare: " << e.what() << "\n";
                        }
                    }
                }
                break;
            }
            case 3: {
                std::vector<Song*> sortedSongs;
                for (const auto& song : allSongs) {
                    sortedSongs.push_back(song.get());
                }
                std::sort(sortedSongs.begin(), sortedSongs.end(),
                    [](const Song* a, const Song* b) {
                        return a->getPopularity() > b->getPopularity();
                    });

                std::cout << "\n Cele mai populare melodii:\n";
                for (size_t i = 0; i < std::min(sortedSongs.size(), size_t(10)); ++i) {
                    std::cout << i+1 << ". ";
                    sortedSongs[i]->display();
                    std::cout << " [Popularitate: " << sortedSongs[i]->getPopularity() << "]\n";
                }
                break;
            }
        }
    } while (choice != 0);
}

void SpotifyApp::playSongFromLibrary(const std::string& artist) {
    const auto& library = user.getArtistLibrary();
    auto it = library.find(artist);
    if (it == library.end()) return;

    std::cout << "Introdu numarul melodiei (sau 0 pentru anulare): ";
    size_t num;
    std::cin >> num;
    std::cin.ignore();

    if (num > 0 && num <= it->second.size()) {
        user.playSong(it->second[num-1].get());
        std::cout << "Adauga la favorite? (y/n): ";
        char choice;
        std::cin >> choice;
        std::cin.ignore();
        if (choice == 'y' || choice == 'Y') {
            user.addToFavorites(it->second[num-1].get());
            std::cout << "Adaugata la favorite!\n";
        }
    }
}

void SpotifyApp::managePlaylists() {
    int choice;
    do {
        std::cout << "\n=== Playlist-urile tale ===\n"
                 << "1. Vezi toate playlist-urile\n"
                 << "2. Creeaza playlist nou\n"
                 << "3. Sterge playlist\n"
                 << "4. Redare playlist\n"
                 << "0. Inapoi\n"
                 << "Alege optiunea: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                user.displayPlaylists();
                break;
            }
            case 2: {
                std::string name, desc;
                std::cout << "Nume playlist: ";
                getline(std::cin, name);
                std::cout << "Descriere (optional): ";
                getline(std::cin, desc);
                user.createPlaylist(name, desc);
                std::cout << "Playlist creat cu succes!\n";
                break;
            }
            case 3: {
                const auto& playlists = user.getPlaylists();
                for (size_t i = 0; i < playlists.size(); ++i) {
                    std::cout << i+1 << ". " << playlists[i]->getName() << "\n";
                }
                if (!playlists.empty()) {
                    std::cout << "Introdu numarul playlist-ului (sau 0 pentru anulare): ";
                    size_t num;
                    std::cin >> num;
                    std::cin.ignore();
                    if (num > 0 && num <= playlists.size()) {
                        try {
                            user.removePlaylist(playlists[num-1]->getName());
                            std::cout << "Playlist sters!\n";
                        } catch (const std::exception& e) {
                            std::cerr << "Eroare: " << e.what() << "\n";
                        }
                    }
                }
                break;
            }
            case 4: {
                const auto& playlists = user.getPlaylists();
                for (size_t i = 0; i < playlists.size(); ++i) {
                    std::cout << i+1 << ". " << playlists[i]->getName() << "\n";
                }
                if (!playlists.empty()) {
                    std::cout << "Introdu numarul playlist-ului (sau 0 pentru anulare): ";
                    size_t num;
                    std::cin >> num;
                    std::cin.ignore();
                    if (num > 0 && num <= playlists.size()) {
                        playlists[num-1]->playAll();
                    }
                }
                break;
            }
        }
    } while (choice != 0);
}

void SpotifyApp::showFavorites() {
    user.displayFavorites();
    const auto& favs = user.getFavorites();
    if (!favs.empty()) {
        std::cout << "Introdu numarul melodiei (sau 0 pentru anulare): ";
        size_t num;
        std::cin >> num;
        std::cin.ignore();
        if (num > 0 && num <= favs.size()) {
            user.playSong(favs[num-1].get());
        }
    }
}

void SpotifyApp::showHistory() {
    user.displayHistory();
    const auto& history = user.getHistory();
    if (!history.empty()) {
        std::cout << "Introdu numarul melodiei (sau 0 pentru anulare): ";
        size_t num;
        std::cin >> num;
        std::cin.ignore();
        if (num > 0 && num <= history.size()) {
            user.playSong(history[num-1].get());
        }
    }
}

void SpotifyApp::searchSongs() {
    std::string query;
    std::cout << "\n Cauta melodii (titlu sau artist): ";
    getline(std::cin, query);

    std::vector<Song*> results;
    for (const auto& song : allSongs) {
        if (song->getTitle().find(query) != std::string::npos ||
            song->getArtist().find(query) != std::string::npos) {
            results.push_back(song.get());
        }
    }

    if (results.empty()) {
        std::cout << "Nu s-au gasit rezultate.\n";
        return;
    }

    std::cout << "\n Rezultate cautare (" << results.size() << "):\n";
    for (size_t i = 0; i < results.size(); ++i) {
        std::cout << i+1 << ". ";
        results[i]->display();
        std::cout << "\n";
    }

    std::cout << "Introdu numarul melodiei (sau 0 pentru anulare): ";
    size_t num;
    std::cin >> num;
    std::cin.ignore();

    if (num > 0 && num <= results.size()) {
        user.playSong(results[num-1]);
        std::cout << "Adauga la favorite? (y/n): ";
        char choice;
        std::cin >> choice;
        std::cin.ignore();
        if (choice == 'y' || choice == 'Y') {
            user.addToFavorites(results[num-1]);
            std::cout << "Adaugata la favorite!\n";
        }
    }
}

void SpotifyApp::run() {
    int choice;
    do {
        displayMainMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: browseLibrary(); break;
            case 2: managePlaylists(); break;
            case 3: showFavorites(); break;
            case 4: showHistory(); break;
            case 5: searchSongs(); break;
            case 0: std::cout << "La revedere!\n"; break;
            default: std::cout << "Optiune invalida!\n";
        }
    } while (choice != 0);
}
