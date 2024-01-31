#include "MidiGenerator.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

MidiGenerator::MidiGenerator() {}

MidiGenerator::~MidiGenerator() {
    if (midiOut.isPortOpen())
        midiOut.closePort();
}

void MidiGenerator::initialize() {
    try {
        midiOut.openVirtualPort("StockhausenPiano");
    } catch (RtMidiError &error) {
        error.printMessage();
        exit(EXIT_FAILURE);
    }
}

void MidiGenerator::sendMidiMessage(int status, int data1, int data2, int channel) {
    std::vector<unsigned char> message;
    message.push_back(static_cast<unsigned char>(status | channel));
    message.push_back(static_cast<unsigned char>(data1));
    message.push_back(static_cast<unsigned char>(data2));

    midiOut.sendMessage(&message);
}

void MidiGenerator::generateStockhausenPiece() {
    // Random number generator for pitch and duration
    std::default_random_engine generator;
    std::uniform_int_distribution<int> pitchDistribution(48, 72); // MIDI notes C3 to C5
    std::uniform_int_distribution<int> durationDistribution(500, 2000); // Milliseconds

    // Generate a sequence of 10 notes
    for (int i = 0; i < 10; ++i) {
        int pitch = pitchDistribution(generator);
        int duration = durationDistribution(generator);

        // Note On
        sendMidiMessage(0x90, pitch, 127);
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));

        // Note Off
        sendMidiMessage(0x80, pitch, 0);

        // Pause between notes
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}