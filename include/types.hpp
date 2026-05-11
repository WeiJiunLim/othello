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

    /* Players */
    enum Player
    {
        BLACK = 0,
        WHITE = 1,
        NUM_PLAYERS
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

    /* Game Type */
    enum class GameType
    {
        PVP,
        PVC
    };

    /* Game state */
    enum class GameState {

        NewGamePVP,
        NewGamePVC,
        ValidMoveAndNextPlayerHasMoves,
        ValidMoveAndNextPlayerNoMoves,
        InvalidMove,
        GameEnded,
        InvalidInput,
        InvalidInputAtGameEnded,
        Exit
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

        /* Input string - stored mostly for display purposes */
        std::string strInput;
    };

    /* Player Info Structure */
    struct PlayerInfo {

        /* Player Name */
        std::string name;

        /* Score */
        int score;
    };

}
