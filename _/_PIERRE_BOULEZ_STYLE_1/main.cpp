// main.cpp

#include "MidiGenerator.h"

int main() {
    MidiGenerator midiGenerator;
    midiGenerator.initialize();
    midiGenerator.generateBoulezStylePiece();

    // Keep the program running for a while to allow the MIDI notes to be played
    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}
