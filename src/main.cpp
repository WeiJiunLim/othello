/*
 *  File        : main.cpp
 *  Description : Main code entry point
 *  Author      : Wei Jiun Lim
 *  Created     : 9 May 2026
 */

/* ====================================================================================================================
 *  Includes
 * ================================================================================================================= */

#include "display.hpp"
#include "game.hpp"
#include <iostream>

/* ====================================================================================================================
 *  Constants / Macros
 * ================================================================================================================= */

 /* ====================================================================================================================
 *  Public Functions
 * ================================================================================================================= */

int main() {

    othello::Display display;
    othello::GameBoard gameBoard;

    /* Set up display */
    display.drawHeader("Othello", "0.1");
    display.drawScoreBoard("Player 1", "Player 2", 123, 456);
    display.drawGameBoard(gameBoard);
    display.drawInstructions("X to exit, any other key to refresh\n");

    while (1) {

        // TODO: remove temporary input code
        display.drawInput("Your input: ");

        std::string input;
        std::cin >> input;

        if (input == "X") {
            break;
        }

        display.drawInstructions("X to exit, any other key to refresh\nPrevious input = " + input);
    }

    return 0;
}

