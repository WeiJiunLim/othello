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
    constexpr int INSTRUCTIONS_ROW_SIZE  = 5;

    constexpr int INPUT_ROW_START = INSTRUCTIONS_ROW_START + INSTRUCTIONS_ROW_SIZE;
    constexpr int INPUT_COL_START = 0;
    constexpr int INPUT_ROW_SIZE  = 3;
}

/* ====================================================================================================================
 *  Private Helper Function
 * ================================================================================================================= */

 /* ===================================================================================================================
 *  Public Class Implementations
 * ================================================================================================================= */

namespace othello
{
    Display::Display(const std::string& title, const std::string& version, const std::string& instructions)
    {
        Display::clear();

        /* Set up permanent display sections */
        drawHeader(title, version);
        drawInstructions(instructions);
    }

    void Display::refreshGame(const GameBoard& board){

        /* Refresh Score board */
        drawScoreBoard(board.getPlayerInfo());

        /* Refresh Game board */
        drawGameBoard(board);

        /* Refresh Input section */
        drawInput(board);
    }

    void Display::clear()
    {
        std::cout << CLEAR_SCREEN << MOVE_HOME;
    }

    void Display::clearSection(Position pos, int row_size)
    {
        for (int row = pos.row; row < (pos.row + row_size); row++) {
            moveCursor({.row = row, .col = pos.col});
            std::cout << CLEAR_LINE << "\r";
        }
    }

    void Display::moveCursor(Position pos)
    {
        std::cout << "\033[" << pos.row << ";" << pos.col << "H";
    }

    void Display::drawText(const std::string& text)
    {
        // std::cout << CLEAR_LINE << "\r";
        std::cout << text << std::endl;
    }

    void Display::drawHeader(const std::string& title, const std::string& version)
    {
        Position pos = {.row = HEADER_ROW_START, .col = HEADER_COL_START};
        clearSection(pos, HEADER_ROW_SIZE);
        moveCursor(pos);
        drawText(title + " v" + version);
    }

    void Display::drawScoreBoard(const std::array<PlayerInfo, NUM_PLAYERS>& playerInfo)
    {
        Position pos = {.row = SCOREBOARD_ROW_START, .col = SCOREBOARD_COL_START};
        clearSection(pos, SCOREBOARD_ROW_SIZE);
        moveCursor(pos);
        drawText("BLACK (" + playerInfo[BLACK].name + "): " + std::to_string(playerInfo[BLACK].score) + " pieces");
        drawText("WHITE (" + playerInfo[WHITE].name + "): " + std::to_string(playerInfo[WHITE].score) + " pieces");
    }

    void Display::drawGameBoard(const GameBoard& board)
    {
        Position pos = {.row = GAMEBOARD_ROW_START, .col = GAMEBOARD_COL_START};
        clearSection(pos, GAMEBOARD_ROW_SIZE);
        moveCursor(pos);

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

        for (int row = 0; row < GameBoard::BOARD_SIZE; row++) {

            std::string row_str = std::to_string(row + 1) + " ";

            for (int col = 0; col < GameBoard::BOARD_SIZE; col++) {

                std::string cell = ".";

                switch (board.getCell({row, col})) {

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
        Position pos = {.row = INSTRUCTIONS_ROW_START, .col = INSTRUCTIONS_COL_START};
        clearSection(pos, INSTRUCTIONS_ROW_SIZE);
        moveCursor(pos);
        drawText(text);
    }

    void Display::drawInput(const GameBoard& board)
    {
        Position pos = {.row = INPUT_ROW_START, .col = INPUT_COL_START};
        clearSection(pos, INPUT_ROW_SIZE);
        moveCursor(pos);

        std::string str;
        std::string strPlayerColour;
        std::string strOppColour;

        /* Update string based on turn */
        if (board.getTurnPlayer() == CellState::Black) {
            strPlayerColour = "BLACK";
            strOppColour = "WHITE";
        }
        else {
            strPlayerColour = "WHITE";
            strOppColour = "BLACK";
        }

        /* Change text depending on Game State */
        switch (board.getGameState())
        {
            case GameState::NewGamePVP:
                str = "New PvP Game started.\n" + strPlayerColour + "'s turn: ";
                break;

            case GameState::NewGamePVC:
                str = "New PvC Game started.\n" + strPlayerColour + "'s turn: ";
                break;

            case GameState::Exit:
                str = "Good bye!";
                break;

            case GameState::ValidMoveAndNextPlayerHasMoves:
                str = "Move executed - " + board.gameInput.strInput + "\n" + strPlayerColour + "'s turn: ";
                break;

            case GameState::ValidMoveAndNextPlayerNoMoves:
                str = "Move executed - " + board.gameInput.strInput + ". " +
                      strOppColour + " has no valid moves, turn passes back to " + strPlayerColour + "\n" +
                      strPlayerColour + "'s turn: ";
                break;

            case GameState::InvalidMove:
                str = "Invalid Move! - " + board.gameInput.strInput + "\n" + strPlayerColour + "'s turn: ";
                break;

            case GameState::GameEnded:
            {
                Player winner = board.getWinner();
                std::string strWinner = "It's a TIE, we are all winners!";

                if (winner == BLACK) {
                    strWinner = "BLACK wins!";
                }
                else if (winner == WHITE) {
                    strWinner = "WHITE wins!";
                }

                str = "Game completed - no valid moves left! " + strWinner + "\nnew pv(P) game, (N)ew pvc game, or e(X)it?";
                break;
            }

            case GameState::InvalidInputAtGameEnded:
                str = "Invalid Input!\nnew pv(P) game, (N)ew pvc game, or e(X)it?";
                break;

            case GameState::InvalidInput:
                str = "Invalid Input!\n" + strPlayerColour + "'s turn: ";
                break;

            default:
                str = "Error: Unknown Game state!";
                break;
        }

        drawText(str);

        /* Clear user input field on terminal */
        std::cout << "\b\b\b\033[K";
    }
}

