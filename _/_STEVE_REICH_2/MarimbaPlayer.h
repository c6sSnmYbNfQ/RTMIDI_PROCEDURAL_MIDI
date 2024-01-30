
// MarimbaPlayer.h
#ifndef MARIMBA_PLAYER_H
#define MARIMBA_PLAYER_H

#include <RtMidi.h>
#include <iostream>
#include <vector>
#include <thread>

class MarimbaPlayer {
private:
    RtMidiOut midiOut;
    double tempo;
    double beatDuration;

public:
    MarimbaPlayer(const std::string& portName);
    ~MarimbaPlayer();

    void sendMidiNote(int note, int velocity, int channel);
    int getRandomNoteInRange(int minNote, int maxNote);
    void playMarimbaPattern(int minNote, int maxNote, int channel);
};

#endif // MARIMBA_PLAYER_H
