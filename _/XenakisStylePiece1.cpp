#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <cmath>
#include <RtMidi.h>

// Function to initialize and open the MIDI output
RtMidiOut createMidiOutput(const std::string& portName) {
    RtMidiOut midiOut;
    try {
        midiOut.openVirtualPort(portName);
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

// Function to generate a random note within a given range
int getRandomNoteInRange(int minNote, int maxNote) {
    return minNote + rand() % (maxNote - minNote + 1);
}

// Function to play a Xenakis-inspired pattern
void playXenakisPattern(RtMidiOut& midiOut, int minNote, int maxNote, int channel) {
    // Xenakis-inspired pattern
    while (true) {
        // Generate a random duration and pitch
        double duration = static_cast<double>(rand() % 3000 + 500) / 1000.0; // Random duration between 0.5 and 3.5 seconds
        int pitch = getRandomNoteInRange(minNote, maxNote);

        // Play a note
        sendMidiNote(midiOut, pitch, 64, channel);

        // Sleep for the generated duration
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(duration * 1000)));

        // Randomly add a rest
        if (rand() % 2 == 0) {
            // Sleep for a short rest
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

int main() {
    // Seed the random number generator
    std::srand(std::time(0));

    // Create MIDI output
    RtMidiOut midiOut = createMidiOutput("XenakisPiece");

    // Set the tempo and note range
    double tempo = 120.0; // Beats per minute
    double beatDuration = 60.0 / tempo; // Duration of one beat in seconds

    // Play Xenakis-inspired pattern
    std::thread threadXenakis(playXenakisPattern, std::ref(midiOut), 48, 72, 1);

    // Wait for user input to exit
    std::cout << "Press Enter to exit." << std::endl;
    std::cin.ignore();

    // Close the MIDI output and join the thread
    midiOut.close();
    threadXenakis.join();

    return 0;
}
