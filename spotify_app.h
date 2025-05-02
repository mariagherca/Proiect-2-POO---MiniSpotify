#ifndef SPOTIFY_APP_H
#define SPOTIFY_APP_H

#include "user.h"
#include <vector>
#include <memory>

class SpotifyApp {
private:
    User user;
    std::vector<std::unique_ptr<Song>> allSongs;

    void loadInitialData();
    void displayMainMenu();
    void browseLibrary();
    void playSongFromLibrary(const std::string& artist);
    void managePlaylists();
    void showFavorites();
    void showHistory();
    void searchSongs();

public:
    SpotifyApp(const std::string& username);
    void run();
};

#endif
