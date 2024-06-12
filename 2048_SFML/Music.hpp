#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

/**
 * @class Music
 * @brief This class is responsible for handling music tracks.
 */
class Music {
private:
    sf::Music* tracks; ///< Pointer to an array of music tracks
    int trackCount = 0; ///< Number of music tracks
    int currentTrack = 0; ///< Index of the currently playing track

public:
    /**
     * @brief Default constructor. Initializes tracks pointer to nullptr.
     */
    Music() : tracks(nullptr) {}

    /**
     * @brief Constructor that loads music tracks from a directory.
     * @param directory Path to the directory containing the music tracks.
     */
    Music(const std::string& directory);

    /**
     * @brief Destructor. Deallocates memory for the tracks.
     */
    ~Music() {
        delete[] tracks;
    }

    /**
     * @brief Get the status of the current music track.
     * @return Status of the current music track.
     */
    sf::SoundSource::Status getStatus() const;

    /**
     * @brief Start or resume playing the current music track.
     */
    void play();

    /**
     * @brief Pause the current music track.
     */
    void pause();

    /**
     * @brief Skip to the next music track.
     */
    void next();

    /**
     * @brief Skip to the previous music track.
     */
    void previous();

    /**
     * @brief Set the volume of the music.
     * @param volume New volume of the music.
     */
    void setVolume(float volume);

    /**
     * @brief Get the volume of the music.
     * @return Volume of the music.
     */
    float getVolume() const;

    /**
     * @brief Handle a SFML event.
     * @param event SFML event to handle.
     */
    void handleEvent(sf::Event event);

    /**
	 * @brief Get the index of the currently playing track.
	 * @return Index of the currently playing track.
	 */
    int getCurrentTrack() const {
        return currentTrack;
    }
};

#endif
