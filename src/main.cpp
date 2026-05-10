/*
 *  File        : main.cpp
 *  Description : Main code entry point
 *  Author      : Wei Jiun Lim
 *  Created     : 9 May 2026
 */

/* ====================================================================================================================
 *  Includes
 * ================================================================================================================= */

#include "types.hpp"
#include "display.hpp"
#include "game.hpp"
#include "input.hpp"
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
    othello::PlayerInput playerInput;

    /* Set up display */
    display.drawHeader("Othello", "0.1");
    display.drawScoreBoard("Player 1", "Player 2", 123, 456);
    display.drawGameBoard(gameBoard);
    display.drawInstructions(
"P: New Game (Player vs Player)\n\
N: New Game (Player vs Computer)\n\
X: Exit Game\n\
[col][row]: Make a move [A-H][1-8], e.g. D3, E6\n");
    display.drawInput("New Game started.\nYour move: ");

    while (1) {

        bool exitGame = false;

        /* Get user input */
        std::string inputStr;
        std::getline(std::cin, inputStr);

        /* Parse user input */
        othello::GameInput gameInput = playerInput.parseInput(inputStr);

        /* Take action on user input */
        switch (gameInput.type)
        {
            case othello::InputType::NewGamePVP:
                // TODO: Start new game
                display.drawInput("New PvP Game started.\nYour move: ");
                break;

            case othello::InputType::NewGamePVC:
                // TODO: Start new game
                display.drawInput("New PvC Game started.\nYour move: ");
                break;

            case othello::InputType::Exit:
                display.drawInput("Good bye!");
                exitGame = true;
                break;

            case othello::InputType::Move:
                // TODO: Call game logic to execute move
                display.drawInput("Move " + inputStr + " executed.\nYour move: ");
                break;

            default:
                /* Invalid input */
                display.drawInput("Invalid input - " + inputStr + "\nYour move: ");
                break;
        }

        if (exitGame) {
            break;
        }
    }

    return 0;
}

