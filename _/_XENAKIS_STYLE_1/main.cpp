// main.cpp
#include "XenakisPlayer.h"

int main() {
    // Create XenakisPlayers
    XenakisPlayer xenakisPlayer("XenakisPiece");

    // Set the tempo and note range
    double tempo = 120.0; // Beats per minute
    double beatDuration = 60.0 / tempo; // Duration of one beat in seconds

    // Play Xenakis-inspired pattern
    std::thread threadXenakis(&XenakisPlayer::playXenakisPattern, &xenakisPlayer, 48, 72, 1);

    // Wait for user input to exit
    std::cout << "Press Enter to exit." << std::endl;
    std::cin.ignore();

    // Join the thread
    threadXenakis.join();

    return 0;
}
