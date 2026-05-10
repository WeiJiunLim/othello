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

            Display();

            void clear();
            void drawHeader(const std::string& title, const std::string& version);
            void drawScoreBoard(const std::string& p1_name, const std::string& p2_name, const int p1_score, const int p2_score);
            void drawGameBoard(const GameBoard& board);
            void drawInstructions(const std::string& text);
            void drawInput(const std::string& text);

        private:

            void clearSection(Position pos, int row_size);
            void moveCursor(Position pos);
            void drawText(const std::string& text);
    };
}
