// StringQuartet.cpp
#include "StringQuartet.h"
#include <chrono>
#include <thread>
#include <vector>
#include <cstdlib>

StringQuartet::StringQuartet() {
    midiOut.openVirtualPort("String Quartet Example");
}

StringQuartet::~StringQuartet() {
    midiOut.close();
}

void StringQuartet::noteOn(int channel, int note, int velocity) {
    std::vector<unsigned char> message;
    message.push_back(0x90 + channel);
    message.push_back(note);
    message.push_back(velocity);
    midiOut.sendMessage(&message);
}

void StringQuartet::noteOff(int channel, int note) {
    std::vector<unsigned char> message;
    message.push_back(0x80 + channel);
    message.push_back(note);
    message.push_back(0);
    midiOut.sendMessage(&message);
}

int StringQuartet::rrand(int min, int max) {
    return min + std::rand() % (max - min + 1);
}

void StringQuartet::playMelody() {
    const int violin1 = 0;
    const int violin2 = 1;
    const int viola = 2;
    const int cello = 3;

    const int tempo = 120;
    const int quarterNoteDuration = 60000 / tempo;

    // Melody pitches distributed across different octaves
    std::vector<int> melodyPitches = {60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82};

    // Single-dimensional array to store notes for all four parts
    int quartetNotes[4];

    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 4; ++j) {
            quartetNotes[j] = melodyPitches[rrand(0, melodyPitches.size() - 1)];
        }

        // Play the notes for each part
        noteOn(violin1, quartetNotes[0], 64);
        noteOn(violin2, quartetNotes[1] + 12, 64);
        noteOn(viola, quartetNotes[2] + 24, 64);
        noteOn(cello, quartetNotes[3] + 36, 64);

        std::this_thread::sleep_for(std::chrono::milliseconds(quarterNoteDuration));

        // Stop playing the notes
        noteOff(violin1, quartetNotes[0]);
        noteOff(violin2, quartetNotes[1] + 12);
        noteOff(viola, quartetNotes[2] + 24);
        noteOff(cello, quartetNotes[3] + 36);
    }
}
