// StringQuartet.h
#ifndef STRING_QUARTET_H
#define STRING_QUARTET_H

#include "RtMidi.h"

class StringQuartet {
public:
    StringQuartet();
    ~StringQuartet();

    void playMelody();

private:
    RtMidiOut midiOut;
    void noteOn(int channel, int note, int velocity);
    void noteOff(int channel, int note);
    int rrand(int min, int max);
};

#endif // STRING_QUARTET_H
