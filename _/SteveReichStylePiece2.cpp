#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
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

// Function to play a marimba-like pattern for a given part
void playMarimbaPattern(RtMidiOut& midiOut, int part, int minNote, int maxNote, int channel) {
    // Pattern for each part
    std::vector<int> pattern = {60, 62, 64, 65, 67, 69, 71, 72};

    // Repeat the pattern
    while (true) {
        for (int i = 0; i < pattern.size(); ++i) {
            // Play a note
            int note = getRandomNoteInRange(minNote, maxNote);
            int velocity = 64 + rand() % 32; // Random velocity between 64 and 95
            sendMidiNote(midiOut, note, velocity, channel);

            // Sleep for a short duration to create a marimba-like effect
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}

int main() {
    // Seed the random number generator
    std::srand(std::time(0));

    // Create MIDI outputs for three parts
    RtMidiOut midiOut1 = createMidiOutput("Part1");
    RtMidiOut midiOut2 = createMidiOutput("Part2");
    RtMidiOut midiOut3 = createMidiOutput("Part3");

    // Set the tempo and note range for each part
    double tempo = 120.0; // Beats per minute
    double beatDuration = 60.0 / tempo; // Duration of one beat in seconds

    // Play marimba-like patterns for each part
    std::thread threadPart1(playMarimbaPattern, std::ref(midiOut1), 1, 60, 72, 1);
    std::thread threadPart2(playMarimbaPattern, std::ref(midiOut2), 2, 48, 60, 2);
    std::thread threadPart3(playMarimbaPattern, std::ref(midiOut3), 3, 72, 84, 3);

    // Wait for user input to exit
    std::cout << "Press Enter to exit." << std::endl;
    std::cin.ignore();

    // Close the MIDI outputs and join the threads
    midiOut1.close();
    midiOut2.close();
    midiOut3.close();

    threadPart1.join();
    threadPart2.join();
    threadPart3.join();

    return 0;
}
