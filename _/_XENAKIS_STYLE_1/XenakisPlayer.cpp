// XenakisPlayer.cpp
#include "XenakisPlayer.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

XenakisPlayer::XenakisPlayer(const std::string& portName)
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

XenakisPlayer::~XenakisPlayer() {
    // Close the MIDI output on destruction
    midiOut.close();
}

void XenakisPlayer::sendMidiNote(int note, int velocity, int channel) {
    std::vector<unsigned char> message;
    message.push_back(0x90 + channel); // Note On event on channel 1
    message.push_back(note);
    message.push_back(velocity);
    midiOut.sendMessage(&message);
}

int XenakisPlayer::getRandomNoteInRange(int minNote, int maxNote) {
    return minNote + rand() % (maxNote - minNote + 1);
}

void XenakisPlayer::playXenakisPattern(int minNote, int maxNote, int channel) {
    // Xenakis-inspired pattern
    while (true) {
        // Generate a random duration and pitch
        double duration = static_cast<double>(rand() % 3000 + 500) / 1000.0; // Random duration between 0.5 and 3.5 seconds
        int pitch = getRandomNoteInRange(minNote, maxNote);

        // Play a note
        sendMidiNote(pitch, 64, channel);

        // Sleep for the generated duration
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(duration * 1000)));

        // Randomly add a rest
        if (rand() % 2 == 0) {
            // Sleep for a short rest
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}
