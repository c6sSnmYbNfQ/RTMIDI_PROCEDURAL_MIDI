// MarimbaPlayer.cpp
#include "MarimbaPlayer.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

MarimbaPlayer::MarimbaPlayer(const std::string& portName)
    : midiOut(), tempo(120.0), beatDuration(60.0 / tempo) {
    // Seed the random number generator
    std::srand(std::time(0));

    try {
        midiOut.openVirtualPort(portName);
    } catch (RtMidiError& error) {
        error.printMessage();
        exit(EXIT_FAILURE);
    }
}

MarimbaPlayer::~MarimbaPlayer() {
    // Close the MIDI output on destruction
    midiOut.close();
}

void MarimbaPlayer::sendMidiNote(int note, int velocity, int channel) {
    std::vector<unsigned char> message;
    message.push_back(0x90 + channel); // Note On event on channel 1
    message.push_back(note);
    message.push_back(velocity);
    midiOut.sendMessage(&message);
}

int MarimbaPlayer::getRandomNoteInRange(int minNote, int maxNote) {
    return minNote + rand() % (maxNote - minNote + 1);
}

void MarimbaPlayer::playMarimbaPattern(int minNote, int maxNote, int channel) {
    // Pattern for each part
    std::vector<int> pattern = {60, 62, 64, 65, 67, 69, 71, 72};

    // Repeat the pattern
    while (true) {
        for (int i = 0; i < pattern.size(); ++i) {
            // Play a note
            int note = getRandomNoteInRange(minNote, maxNote);
            int velocity = 64 + rand() % 32; // Random velocity between 64 and 95
            sendMidiNote(note, velocity, channel);

            // Sleep for a short duration to create a marimba-like effect
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}
