// main.cpp
#include "MarimbaPlayer.h"

int main() {
    // Create MarimbaPlayers for three parts
    MarimbaPlayer player1("Part1");
    MarimbaPlayer player2("Part2");
    MarimbaPlayer player3("Part3");

    // Set the tempo and note range for each part
    double tempo = 120.0; // Beats per minute
    double beatDuration = 60.0 / tempo; // Duration of one beat in seconds

    // Play marimba-like patterns for each part
    std::thread threadPart1(&MarimbaPlayer::playMarimbaPattern, &player1, 60, 72, 1);
    std::thread threadPart2(&MarimbaPlayer::playMarimbaPattern, &player2, 48, 60, 2);
    std::thread threadPart3(&MarimbaPlayer::playMarimbaPattern, &player3, 72, 84, 3);

    // Wait for user input to exit
    std::cout << "Press Enter to exit." << std::endl;
    std::cin.ignore();

    // Join the threads
    threadPart1.join();
    threadPart2.join();
    threadPart3.join();

    return 0;
}
