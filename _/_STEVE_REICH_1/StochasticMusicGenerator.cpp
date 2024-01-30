// StochasticMusicGenerator.cpp
#include "StochasticMusicGenerator.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

StochasticMusicGenerator::StochasticMusicGenerator()
    : midiOut(), tempo(120.0), beatDuration(60.0 / tempo), octave(4), channel(0) {
    // Seed the random number generator
    std::srand(std::time(0));

    try {
        midiOut.openVirtualPort("StochasticMusicGenerator");
    } catch (RtMidiError& error) {
        error.printMessage();
        exit(EXIT_FAILURE);
    }
}

StochasticMusicGenerator::~StochasticMusicGenerator() {
    // Close the MIDI output on destruction
    midiOut.close();
}

void StochasticMusicGenerator::sendMidiNote(int note, int velocity) {
    std::vector<unsigned char> message;
    message.push_back(0x90 + channel); // Note On event on channel 1
    message.push_back(note);
    message.push_back(velocity);
    midiOut.sendMessage(&message);
}

int StochasticMusicGenerator::getRandomPentatonicNote() {
    // Pentatonic scale: C, D, E, G, A (in MIDI note numbers)
    int pentatonicNotes[] = {60, 62, 64, 67, 69};
    int randomIndex = rand() % 5;
    return pentatonicNotes[randomIndex];
}

void StochasticMusicGenerator::playMelody(const std::vector<int>& pattern) {
    for (int i = 0; i < pattern.size(); ++i) {
        if (pattern[i] == 1) {
            // Play a note
            int note = getRandomPentatonicNote() + 12 * octave; // Transpose to the current octave
            int velocity = 64 + rand() % 32; // Random velocity between 64 and 95
            sendMidiNote(note, velocity);
        }

        // Sleep for the duration of one beat
        double sleepTime = beatDuration;
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleepTime * 1000)));

        // Offset the playback in the beginning by creating a pattern that starts and ends in different locations
        if (i == pattern.size() - 1) {
            // At the end of the pattern, move to a different octave for the next iteration
            octave = (octave + 1) % 3; // Move to the next octave (mod 3 to limit the range)
        }
    }
}
