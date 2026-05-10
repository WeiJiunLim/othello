/*
 *  File        : game.cpp
 *  Description : Source file for Game logic module
 *  Author      : Wei Jiun Lim
 *  Created     : 9 May 2026
 */

/* ====================================================================================================================
 *  Includes
 * ================================================================================================================= */

#include "game.hpp"
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
    GameBoard::GameBoard()
    {
        GameBoard::clear();

        /* Set starting positions */
        setCell(3, 3, CellState::White);
        setCell(4, 4, CellState::White);
        setCell(4, 3, CellState::Black);
        setCell(3, 4, CellState::Black);
    }

    void GameBoard::clear()
    {
        for (int row = 0; row < SIZE; row++) {

            for (int col = 0; col < SIZE; col++) {
                board[row][col] = CellState::Empty;
            }
        }
    }

    CellState GameBoard::getCell(int row, int col) const
    {
        return (board[row][col]);
    }

    void GameBoard::setCell(int row, int col, CellState state)
    {
        board[row][col] = state;
    }
}
