/*
 *  File        : input.cpp
 *  Description : Source file for game input module
 *  Author      : Wei Jiun Lim
 *  Created     : 10 May 2026
 */

/* ====================================================================================================================
 *  Includes
 * ================================================================================================================= */

#include "input.hpp"
#include <iostream>

/* ====================================================================================================================
 *  Constants / Macros
 * ================================================================================================================= */

/* ====================================================================================================================
 *  Private Helper Function
 * ================================================================================================================= */

 /* ===================================================================================================================
 *  Public Class Implementations
 * ================================================================================================================= */

namespace othello
{

    PlayerInput::PlayerInput()
    {
    }

    GameInput PlayerInput::parseInput(std::string& inputText)
    {
        GameInput parsedInput = {.type = InputType::Invalid,
                                 .pos = {.row = 0, .col = 0}};

        /* Convert all to upper case */
        for (char& c : inputText) {
            c = std::toupper(c);
        }

        /* Check for commands first */
        if (inputText == "P") {
            parsedInput.type = InputType::NewGamePVP;
        }
        else if (inputText == "N") {
            parsedInput.type = InputType::NewGamePVC;
        }
        else if (inputText == "X") {
            parsedInput.type = InputType::Exit;
        }
        else {

            /* Check length for moves*/
            if (inputText.length() == MOVE_STR_LENGTH) {

                /* Get row and col */
                char charCol = inputText[0];
                char charRow = inputText[1];
                bool isValidMove = true;

                /* Check for valid col */
                if ((charCol >= 'A') && (charCol <= 'H')) {
                    parsedInput.pos.col = charCol - 'A';
                }
                else {
                    isValidMove = false;
                }

                /* Check for valid row */
                if ((charRow >= '1') && (charRow <= '8')) {
                    parsedInput.pos.row = charRow - '1';
                }
                else {
                    isValidMove = false;
                }

                if (isValidMove) {
                    parsedInput.type = InputType::Move;
                }
            }
        }

        return (parsedInput);
    }
}
