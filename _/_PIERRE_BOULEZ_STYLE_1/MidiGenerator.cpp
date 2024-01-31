// MidiGenerator.cpp

#include "MidiGenerator.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

MidiGenerator::MidiGenerator() {}

MidiGenerator::~MidiGenerator() {
    if (midiOut.isPortOpen())
        midiOut.closePort();
}

void MidiGenerator::initialize() {
    try {
        midiOut.openVirtualPort("BoulezPiano");
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

void MidiGenerator::generateBoulezStylePiece() {
    // Serialist pitch row
    std::vector<int> pitchRow = {60, 62, 64, 65, 67, 69, 71, 72, 74, 76};

    // Dynamics for each pitch
    std::vector<int> dynamics = {80, 90, 100, 110, 120, 100, 90, 80, 70, 60};

    // Play the serialist pitch sequence with dynamics
    for (size_t i = 0; i < pitchRow.size(); ++i) {
        // Note On with dynamics
        sendMidiMessage(0x90, pitchRow[i], dynamics[i]);
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Adjust duration

        // Note Off
        sendMidiMessage(0x80, pitchRow[i], 0);

        // Pause between notes
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
