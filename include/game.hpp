/*
 *  File        : game.hpp
 *  Description : Header file for game logic
 *  Author      : Wei Jiun Lim
 *  Created     : 10 May 2026
 */

#pragma once

/* ====================================================================================================================
 *  Includes
 * ================================================================================================================= */

#include "types.hpp"
#include <array>
#include <vector>

/* ====================================================================================================================
 *  Namespace Declarations
 * ================================================================================================================= */

namespace othello
{

    /* ================================================================================================================
    *  Class Definitions
    * ============================================================================================================== */

    class GameBoard
    {
        public:
            static constexpr int BOARD_SIZE = 8;
            GameInput gameInput;

            GameBoard();

            void reset(GameType gameType);
            void setGameState(GameState state);
            GameState getGameState() const;
            GameType getGameType() const;
            bool isGameRunning();
            CellState getCell(Position pos) const;
            const std::array<PlayerInfo, NUM_PLAYERS>& getPlayerInfo() const;
            CellState getTurnPlayer() const;
            int getScore(Player player);
            Player getWinner() const;
            void playerMove(GameInput& gameInput);
            GameInput compMove();

        private:

            /* Directions to scan for captures around a position */
            static constexpr int NUM_DIR = 8;
            static constexpr Position DIRECTIONS[NUM_DIR] = {{-1, -1}, {-1, 0}, {-1, 1},
                                                             { 0, -1},          { 0, 1},
                                                             { 1, -1}, { 1, 0}, { 1, 1}};

            GameState gameState;
            GameType gameType;
            CellState board[BOARD_SIZE][BOARD_SIZE];
            CellState turnPlayer;
            std::array<PlayerInfo, NUM_PLAYERS> playerInfo;
            Player winner;

            void setGameType(GameType newGameType);
            void setCell(Position pos, CellState state);
            void toggleTurnPlayer();
            void incScore(Player player);
            void decScore(Player player);
            CellState getOppColour(const CellState playerColour);
            bool findFirstValidMove(const CellState playerColour, Position& validMovePos);
            bool hasValidMoves(const CellState playerColour, const bool applyValidMoves);
            bool isMoveValid(const Position pos, const CellState playerColour, const bool applyValidMoves);
            std::vector<Position> getCapturesInDirection(const Position pos,
                                                         const Position direction,
                                                         const CellState playerColour);
    };

}
