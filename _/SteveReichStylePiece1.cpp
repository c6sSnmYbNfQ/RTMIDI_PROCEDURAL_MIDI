#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <RtMidi.h>

// Function to initialize and open the MIDI output
RtMidiOut createMidiOutput() {
    RtMidiOut midiOut;
    try {
        midiOut.openVirtualPort("StochasticMusicGenerator");
    } catch (RtMidiError& error) {
        error.printMessage();
        exit(EXIT_FAILURE);
    }
    return midiOut;
}

// Function to send a MIDI note
void sendMidiNote(RtMidiOut& midiOut, int note, int velocity, int channel) {
    std::vector<unsigned char> message;
    message.push_back(0x90 + channel); // Note On event on channel 1
    message.push_back(note);
    message.push_back(velocity);
    midiOut.sendMessage(&message);
}

// Function to generate a random pentatonic note within a given octave
int getRandomPentatonicNote() {
    // Pentatonic scale: C, D, E, G, A (in MIDI note numbers)
    int pentatonicNotes[] = {60, 62, 64, 67, 69};
    int randomIndex = rand() % 5;
    return pentatonicNotes[randomIndex];
}

int main() {
    // Seed the random number generator
    std::srand(std::time(0));

    // Create MIDI output
    RtMidiOut midiOut = createMidiOutput();

    // Set the tempo and rhythmical-melodic pattern
    double tempo = 120.0; // Beats per minute
    double beatDuration = 60.0 / tempo; // Duration of one beat in seconds

    // Rhythmical-melodic pattern
    std::vector<int> pattern = {1, 0, 0, 1, 0, 1, 0, 1}; // 1 represents a note, 0 represents a rest

    // Generate and play the melody
    int octave = 4; // Starting octave
    int channel = 0; // MIDI channel

    for (int i = 0; i < pattern.size(); ++i) {
        if (pattern[i] == 1) {
            // Play a note
            int note = getRandomPentatonicNote() + 12 * octave; // Transpose to the current octave
            int velocity = 64 + rand() % 32; // Random velocity between 64 and 95
            sendMidiNote(midiOut, note, velocity, channel);
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

    // Close the MIDI output
    midiOut.close();

    return 0;
}
