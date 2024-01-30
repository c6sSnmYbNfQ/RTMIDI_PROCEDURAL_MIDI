// XenakisPlayer.h
#ifndef XENAKIS_PLAYER_H
#define XENAKIS_PLAYER_H

#include <RtMidi.h>
#include <iostream>
#include <thread>

class XenakisPlayer {
private:
    RtMidiOut midiOut;
    double tempo;
    double beatDuration;

public:
    XenakisPlayer(const std::string& portName);
    ~XenakisPlayer();

    void sendMidiNote(int note, int velocity, int channel);
    int getRandomNoteInRange(int minNote, int maxNote);
    void playXenakisPattern(int minNote, int maxNote, int channel);
};

#endif // XENAKIS_PLAYER_H
