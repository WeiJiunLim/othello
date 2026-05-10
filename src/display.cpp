/*
 *  File        : display.cpp
 *  Description : Source file for Display module
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

namespace
{
    /* Screen manipulation ANSI codes */
    constexpr const char* CLEAR_SCREEN = "\033[2J";
    constexpr const char* CLEAR_LINE = "\x1b[2K";
    constexpr const char* MOVE_HOME = "\033[H";

    /* UI element locations */
    constexpr int HEADER_ROW_START = 0;
    constexpr int HEADER_COL_START = 0;
    constexpr int HEADER_ROW_SIZE  = 3;

    constexpr int SCOREBOARD_ROW_START = HEADER_ROW_START + HEADER_ROW_SIZE;
    constexpr int SCOREBOARD_COL_START = 0;
    constexpr int SCOREBOARD_ROW_SIZE  = 3;

    constexpr int GAMEBOARD_ROW_START = SCOREBOARD_ROW_START + SCOREBOARD_ROW_SIZE;
    constexpr int GAMEBOARD_COL_START = 0;
    constexpr int GAMEBOARD_ROW_SIZE  = 1 + 8 + 1;

    constexpr int INSTRUCTIONS_ROW_START = GAMEBOARD_ROW_START + GAMEBOARD_ROW_SIZE;
    constexpr int INSTRUCTIONS_COL_START = 0;
    constexpr int INSTRUCTIONS_ROW_SIZE  = 2;

    constexpr int INPUT_ROW_START = INSTRUCTIONS_ROW_START + INSTRUCTIONS_ROW_SIZE;
    constexpr int INPUT_COL_START = 0;
    constexpr int INPUT_ROW_SIZE  = 1;
}

/* ====================================================================================================================
 *  Private Helper Function
 * ================================================================================================================= */

 /* ===================================================================================================================
 *  Public Class Implementations
 * ================================================================================================================= */

namespace othello
{
    Display::Display()
    {
        Display::clear();
    }

    void Display::clear()
    {
        std::cout << CLEAR_SCREEN << MOVE_HOME;
    }

    void Display::moveCursor(int row, int col)
    {
        std::cout << "\033[" << row << ";" << col << "H";
    }

    void Display::drawText(const std::string& text)
    {
        // std::cout << CLEAR_LINE << "\r";
        std::cout << text << std::endl;
    }

    void Display::drawHeader(const std::string& title, const std::string& version)
    {
        moveCursor(HEADER_ROW_START, HEADER_COL_START);
        drawText(title + " v" + version);
    }

    void Display::drawScoreBoard(const std::string& p1_name, const std::string& p2_name, const int p1_score, const int p2_score)
    {
        moveCursor(SCOREBOARD_ROW_START, SCOREBOARD_COL_START);
        drawText("WHITE (" + p1_name + "): " + std::to_string(p1_score) + " pieces");
        drawText("BLACK (" + p2_name + "): " + std::to_string(p2_score) + " pieces");
    }

    void Display::drawGameBoard(const GameBoard& board)
    {
        moveCursor(GAMEBOARD_ROW_START, GAMEBOARD_COL_START);

        // drawText("  A B C D E F G H");
        // drawText("1 - - - - - - - - ");
        // drawText("2 - - - - - - - - ");
        // drawText("3 - - - - - - - - ");
        // drawText("4 - - - W B - - - ");
        // drawText("5 - - - B W - - - ");
        // drawText("6 - - - - - - - - ");
        // drawText("7 - - - - - - - - ");
        // drawText("8 - - - - - - - - ");
        // drawText("                  ");

        drawText("  A B C D E F G H");

        for (int row = 0; row < GameBoard::SIZE; row++) {

            std::string row_str = std::to_string(row + 1) + " ";

            for (int col = 0; col < GameBoard::SIZE; col++) {

                std::string cell = ".";

                switch (board.getCell(row, col)) {

                    case CellState::Empty:
                        cell = "-";
                        break;

                    case CellState::Black:
                        cell = "B";
                        break;

                    case CellState::White:
                        cell = "W";
                        break;
                }

                row_str += cell + " ";
            }

            drawText(row_str);
        }
    }

    void Display::drawInstructions(const std::string& text)
    {
        moveCursor(INSTRUCTIONS_ROW_START, INSTRUCTIONS_COL_START);
        drawText(text);
    }

    void Display::drawInput(const std::string& text)
    {
        moveCursor(INPUT_ROW_START, INPUT_COL_START);
        drawText(text);
        std::cout << "\b\b\b\033[K";
    }
}

