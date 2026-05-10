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
        GameBoard::reset(GameType::PVP);
    }

    void GameBoard::reset(GameType gameType)
    {
        /* Set to black's turn */
        isBlackTurn = true;

        /* Reset player info */
        playerInfo[BLACK].name = "Player 1";

        if (gameType == GameType::PVP) {

            playerInfo[WHITE].name = "Player 2";
            setGameState(GameState::NewGamePVP);
        }
        else {

            playerInfo[WHITE].name = "Computer";
            setGameState(GameState::NewGamePVC);
        }
        playerInfo[BLACK].score = 0;
        playerInfo[WHITE].score = 0;

        /* Clear all cells on board */
        for (int row = 0; row < BOARD_SIZE; row++) {

            for (int col = 0; col < BOARD_SIZE; col++) {
                board[row][col] = CellState::Empty;
            }
        }

        /* Set starting positions */
        setCell({3, 3}, CellState::White);
        setCell({4, 4}, CellState::White);
        setCell({4, 3}, CellState::Black);
        setCell({3, 4}, CellState::Black);
    }

    GameState GameBoard::getGameState() const
    {
        return (gameState);
    }

    void GameBoard::setGameState(GameState state)
    {
        gameState = state;
    }

    const std::array<PlayerInfo, NUM_PLAYERS>& GameBoard::getPlayerInfo() const
    {
        return (playerInfo);
    }

    bool GameBoard::getIsBlackTurn() const
    {
        return (isBlackTurn);
    }

    void GameBoard::toggleIsBlackTurn()
    {
        isBlackTurn = !isBlackTurn;
    }

    CellState GameBoard::getCell(Position pos) const
    {
        return (board[pos.row][pos.col]);
    }

    void GameBoard::setCell(Position pos, CellState state)
    {
        CellState prevState = board[pos.row][pos.col];

        /* Modify state */
        board[pos.row][pos.col] = state;

        /* Modify score */
        if (prevState != state) {

            if (prevState == CellState::Empty) {

                if (state == CellState::Black) {
                    incScore(BLACK);
                }
                else if (state == CellState::White) {
                    incScore(WHITE);
                }
            }
            else {

                if (state == CellState::Black) {
                    incScore(BLACK);
                    decScore(WHITE);
                }
                else if (state == CellState::White) {
                    incScore(WHITE);
                    decScore(BLACK);
                }
            }
        }
    }

    int GameBoard::getScore(enum Player player)
    {
        return(playerInfo[player].score);
    }

    void GameBoard::incScore(enum Player player)
    {
        playerInfo[player].score++;
    }

    void GameBoard::decScore(enum Player player)
    {
        playerInfo[player].score--;
    }

    void GameBoard::move(GameInput& gameInput)
    {
        /* Input has been verified before calling this function */

        /* Check if move is valid */
        // TODO: isMoveValid(getIsBlackTurn(), gameInput.pos)
        {
            /* Update game board */
            setCell(gameInput.pos, (getIsBlackTurn() ? CellState::Black : CellState::White));
            toggleIsBlackTurn();
            setGameState(GameState::ValidMove);

            // TODO: Update flipped cells as well
        }
        // else {
        //     setGameState(GameState::InvalidMove);
        // }

    }
}
