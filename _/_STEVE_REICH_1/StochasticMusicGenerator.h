// StochasticMusicGenerator.h
#ifndef STOCHASTICMUSICGENERATOR_H
#define STOCHASTICMUSICGENERATOR_H

#include <vector>

class StochasticMusicGenerator {
private:
    RtMidiOut midiOut;
    double tempo;
    double beatDuration;
    int octave;
    int channel;

public:
    StochasticMusicGenerator();
    ~StochasticMusicGenerator();

    void sendMidiNote(int note, int velocity);
    int getRandomPentatonicNote();
    void playMelody(const std::vector<int>& pattern);
};

#endif // STOCHASTICMUSICGENERATOR_H
