#ifndef SONG_H
#define SONG_H

#include <memory>
#include <string>

class Song {
protected:
    std::string title;
    std::string artist;
    int duration;
    std::string genre;
    int plays = 0;

public:
    Song(const std::string& title, const std::string& artist, int duration, const std::string& genre);
    virtual ~Song() = default;

    virtual std::unique_ptr<Song> clone() const = 0;
    virtual void play() const = 0;
    virtual void display() const = 0;
    virtual float getPopularity() const = 0;
    virtual std::string getType() const = 0;

    void incrementPlays();
    const std::string& getTitle() const;
    const std::string& getArtist() const;
    int getDuration() const;
    const std::string& getGenre() const;
    int getPlays() const;

    static std::unique_ptr<Song> createSong(const std::string& type, const std::string& title,
                                         const std::string& artist, int duration, const std::string& extra);
};

class PopSong : public Song {
private:
    float energy; // 0-1

public:
    PopSong(const std::string& title, const std::string& artist, int duration, float energy);
    std::unique_ptr<Song> clone() const override;
    void play() const override;
    void display() const override;
    float getPopularity() const override;
    std::string getType() const override;
};

class RockSong : public Song {
private:
    bool isHeavy;

public:
    RockSong(const std::string& title, const std::string& artist, int duration, bool isHeavy);
    std::unique_ptr<Song> clone() const override;
    void play() const override;
    void display() const override;
    float getPopularity() const override;
    std::string getType() const override;
};

class ClassicalSong : public Song {
private:
    std::string era;

public:
    ClassicalSong(const std::string& title, const std::string& artist, int duration, const std::string& era);
    std::unique_ptr<Song> clone() const override;
    void play() const override;
    void display() const override;
    float getPopularity() const override;
    std::string getType() const override;
};

#endif
