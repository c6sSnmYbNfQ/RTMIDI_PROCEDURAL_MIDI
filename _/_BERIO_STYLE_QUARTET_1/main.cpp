// main.cpp
#include "StringQuartet.h"

int main() {
    try {
        StringQuartet stringQuartet;
        stringQuartet.playMelody();
    } catch (RtMidiError& error) {
        std::cerr << "Error: " << error.getMessage() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
