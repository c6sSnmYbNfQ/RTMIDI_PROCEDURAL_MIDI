// main.cpp
#include "StochasticMusicGenerator.h"

int main() {
    StochasticMusicGenerator musicGenerator;

    // Rhythmical-melodic pattern
    std::vector<int> pattern = {1, 0, 0, 1, 0, 1, 0, 1}; // 1 represents a note, 0 represents a rest

    // Generate and play the melody
    musicGenerator.playMelody(pattern);

    return 0;
}
