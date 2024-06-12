#include "Music.hpp"

Music::Music(const std::string& directory)
{
    // Count the number of .wav files in the directory
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".wav") {
            trackCount++;
        }
    }
    tracks = nullptr;

    // Allocate memory for the tracks if there are any
    if (trackCount > 0) {
        tracks = new sf::Music[trackCount];
    }

    // Load the .wav files into the tracks array
    int i = 0;
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".wav") {
            if (!tracks[i].openFromFile(entry.path().string())) {
                std::cout << "Failed to load " << entry.path() << "\n";
                continue;
            }
            i++;
        }
    }
}

sf::SoundSource::Status Music::getStatus() const {
    if (trackCount > 0) {
        return tracks[currentTrack].getStatus();
    }
    return sf::SoundSource::Status::Stopped;  // Default status if there are no tracks
}

void Music::play()
{
	if (trackCount > 0)
		tracks[currentTrack].play();
}

void Music::pause()
{
    if (trackCount > 0)
        tracks[currentTrack].pause();
}

void Music::next()
{
    if (trackCount > 0) {
        tracks[currentTrack].stop();
        currentTrack = (currentTrack + 1) % trackCount;
        tracks[currentTrack].play();
    }
}

void Music::previous()
{
    if (trackCount > 0) {
        tracks[currentTrack].stop();
        currentTrack = (currentTrack - 1 + trackCount) % trackCount;
        tracks[currentTrack].play();
    }
}

void Music::setVolume(float volume)
{
    if (trackCount > 0)
        tracks[currentTrack].setVolume(volume);
}

float Music::getVolume() const
{
    return tracks[currentTrack].getVolume();
}
