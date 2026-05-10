/*
 *  File        : types.hpp
 *  Description : Header file for types declarations
 *  Author      : Wei Jiun Lim
 *  Created     : 10 May 2026
 */

#pragma once

/* ====================================================================================================================
 *  Includes
 * ================================================================================================================= */

#include <string>

/* ====================================================================================================================
 *  Namespace Declarations
 * ================================================================================================================= */

namespace othello
{

    /* ================================================================================================================
    *  Class Definitions
    * ============================================================================================================== */

    /* Each cell on the game board */
    enum class CellState
    {
        Empty,
        Black,
        White
    };

    /* Player Input Types */
    enum class InputType
    {
        Move,
        NewGamePVP,
        NewGamePVC,
        Exit,
        Invalid
    };

    /* Position structure */
    struct Position {

        int row;
        int col;
    };

    /* Game Input Structure */
    struct GameInput {

        /* Type of input */
        InputType type;

        /* Position, only valid for a Move Type input */
        Position pos;
    };
}
