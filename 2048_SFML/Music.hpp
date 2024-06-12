#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <SFML/Audio.hpp>
#include <filesystem>
#include <iostream>

class Music {
private:
    sf::Music* tracks;
    int trackCount = 0;
    int currentTrack = 0;
public:
    Music() : tracks(nullptr) {}
    Music(const std::string& directory);

    /**
    * @brief Deallocate memory for the tracks
    */
    ~Music() {
        delete[] tracks;
    }

    sf::SoundSource::Status getStatus() const;

    void play();

    void pause();

    void next();

    void previous();

    void setVolume(float volume);

    float getVolume() const;
};


#endif

