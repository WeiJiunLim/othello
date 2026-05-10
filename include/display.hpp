/*
 *  File        : display.hpp
 *  Description : Header file for Display module
 *  Author      : Wei Jiun Lim
 *  Created     : 9 May 2026
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

    class GameBoard;

    class Display
    {
        public:

            Display(const std::string& title, const std::string& version, const std::string& instructions);

            void refreshGame(const GameBoard& board);

        private:

            void clear();
            void clearSection(Position pos, int row_size);
            void moveCursor(Position pos);
            void drawText(const std::string& text);

            void drawHeader(const std::string& title, const std::string& version);
            void drawScoreBoard(const std::array<PlayerInfo, 2>& playerInfo);
            void drawGameBoard(const GameBoard& board);
            void drawInstructions(const std::string& text);
            void drawInput(const GameBoard& board);
    };
}
