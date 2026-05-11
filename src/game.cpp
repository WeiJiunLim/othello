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
        turnPlayer = CellState::Black;

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

    CellState GameBoard::getTurnPlayer() const
    {
        return (turnPlayer);
    }

    void GameBoard::toggleTurnPlayer()
    {
        turnPlayer = (turnPlayer == CellState::Black) ? CellState::White : CellState::Black;
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
        /* Move is valid if all criteria are met:
         * - position is unoccupied
         * - can capture opponent's cells in at least one direction */
        bool isValid = false;
        CellState playerColour = getTurnPlayer();

        if (getCell(gameInput.pos) == CellState::Empty)
        {
            /* Scan for captures around the position in all directions */
            for (int idx = 0; idx < NUM_DIR; idx++) {

                std::vector<Position> captures = getCapturesInDirection(gameInput.pos,
                                                                        DIRECTIONS[idx],
                                                                        playerColour);
                if (captures.empty() == false) {

                    /* Able to capture opponent's cells, move is valid,
                     * apply move (flip captured cells), and continue scanning. */
                    isValid = true;

                    for (Position capPos : captures) {
                        setCell(capPos, playerColour);
                    }
                }
            }
        }

        if (isValid) {

            setCell(gameInput.pos, playerColour);
            toggleTurnPlayer();
            setGameState(GameState::ValidMove);
        }
        else {

            setGameState(GameState::InvalidMove);
        }
    }

    CellState GameBoard::getOppColour(const CellState playerColour)
    {
        return ((playerColour == CellState::Black) ? CellState::White : CellState::Black);
    }

    std::vector<Position> GameBoard::getCapturesInDirection(const Position pos,
                                                            const Position direction,
                                                            const CellState playerColour)
    {
        std::vector<Position> captures;
        Position currentPos = pos;
        CellState oppColour = getOppColour(playerColour);
        bool oppCellFound = false;
        bool ableToCapture = false;

        while (1)
        {
            CellState cellColour;

            /* Check for edge */
            if (((currentPos.row + direction.row) < 0) || ((currentPos.row + direction.row) >= BOARD_SIZE) ||
                ((currentPos.col + direction.col) < 0) || ((currentPos.col + direction.col) >= BOARD_SIZE)) {
                /* Over the board edge, stop scan, unable to capture */
                break;
            }

            /* Get next cell in direction */
            currentPos.row += direction.row;
            currentPos.col += direction.col;
            cellColour = getCell(currentPos);

            if (oppCellFound == false) {

                /* Only look for opponent's cell */
                if (cellColour == oppColour) {

                    /* Opponent's cell found.
                     * Set flag, and continue scan.
                     * Tentatively add cell to captures vector. */
                    oppCellFound = true;
                    captures.push_back(currentPos);

                } else {

                    /* Not opponent's cell, stop scan */
                    break;
                }
            }
            else {

                /* At least one opponent's cell found previously, now scan for:
                 * - opponent's cell: continue scan
                 * - own cell: stop scan, able to capture
                 * - empty cell: stop scan, unable to capture */
                if (cellColour == oppColour) {

                    oppCellFound = true;
                    captures.push_back(currentPos);

                } else if (cellColour == playerColour) {

                    ableToCapture = true;
                    captures.push_back(currentPos);
                    break;

                }
                else {
                    /* Empty cell */
                    break;
                }
            }
        }

        if (ableToCapture == false) {

            /* Unable to capture, so clear vector */
            captures.clear();
        }

        return (captures);
    }
}
