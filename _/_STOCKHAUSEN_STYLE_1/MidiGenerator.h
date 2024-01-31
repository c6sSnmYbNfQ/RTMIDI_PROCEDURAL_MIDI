#ifndef MIDIGENERATOR_H
#define MIDIGENERATOR_H

#include <rtmidi/RtMidi.h>
#include <vector>

class MidiGenerator {
public:
    MidiGenerator();
    ~MidiGenerator();

    void initialize();
    void generateStockhausenPiece();

private:
    RtMidiOut midiOut;
    void sendMidiMessage(int status, int data1, int data2, int channel = 0);
};

#endif // MIDIGENERATOR_H
