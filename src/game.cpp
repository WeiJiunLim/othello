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
        GameBoard::reset();
    }

    void GameBoard::reset()
    {
        for (int row = 0; row < SIZE; row++) {

            for (int col = 0; col < SIZE; col++) {
                board[row][col] = CellState::Empty;
            }
        }

        /* Set starting positions */
        setCell({3, 3}, CellState::White);
        setCell({4, 4}, CellState::White);
        setCell({4, 3}, CellState::Black);
        setCell({3, 4}, CellState::Black);
    }

    CellState GameBoard::getCell(Position pos) const
    {
        return (board[pos.row][pos.col]);
    }

    void GameBoard::setCell(Position pos, CellState state)
    {
        board[pos.row][pos.col] = state;
    }
}
