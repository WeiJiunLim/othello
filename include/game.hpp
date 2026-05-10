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
            static constexpr int NUM_PLAYERS = 2;

            GameBoard();

            void reset(GameType gameType);
            void setGameState(GameState state);
            GameState getGameState() const;
            CellState getCell(Position pos) const;
            const std::array<PlayerInfo, NUM_PLAYERS>& getPlayerInfo() const;
            bool getIsBlackTurn() const;
            void move(GameInput& gameInput);

        private:
            GameState gameState;
            CellState board[BOARD_SIZE][BOARD_SIZE];
            std::array<PlayerInfo, NUM_PLAYERS> playerInfo;
            bool isBlackTurn;

            void setCell(Position pos, CellState state);
            void toggleIsBlackTurn();

    };

}
