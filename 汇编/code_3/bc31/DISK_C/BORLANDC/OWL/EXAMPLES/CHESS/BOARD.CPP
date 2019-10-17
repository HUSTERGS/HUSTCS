// ObjectWindows - (C) Copyright 1992 by Borland International

#include <windows.h>
#include "wcdefs.h"
#include "externs.h"

/*
 *  globals
 */

int OfficerNo[2], PawnNo[2];


/*
 *  Clear the board and initialize the board-module
 */

void ClearBoard()
{
   SQUARETYPE Square;
    for (Square = 0; Square <= 0x77; Square++)
    {
        Board[Square].piece = empty;
        Board[Square].color = white;
    }
}


/*
 *  Clears indexes in board and piecetab
 */

void ClearIndex(void)
{
    SQUARETYPE square;
    COLORTYPE col;
    INDEXTYPE index;

    for (square = 0; square <= 0x77; square++)
        Board[square].index = 16;
    for (col = white; col <= black; ((int)col)++)
        for (index = 0; index < 16; index++)
            PieceTab[col][index].ipiece = empty;
    OfficerNo[white] = PawnNo[white] = -1;
    OfficerNo[black] = PawnNo[black] = -1;
}


/*
 *  Calcualates Piece table from scratch
 */

void CalcPieceTab(void)
{
    SQUARETYPE square;
    PIECETYPE piece1;

    ClearIndex();

    for (piece1 = king; piece1 <= pawn; ((int)piece1)++)
     {
        if (piece1 == pawn)
        {
            OfficerNo[white] = PawnNo[white];
            OfficerNo[black] = PawnNo[black];
        }
        square = 0;
        do
        {
            if (Board[square].piece == piece1)
            {
                PawnNo[Board[square].color]++;
                PieceTab[Board[square].color][PawnNo[Board[square].color]].ipiece
                  = piece1;
                PieceTab[Board[square].color][PawnNo[Board[square].color]].isquare
                  = square;
                Board[square].index = PawnNo[Board[square].color];
            }
            square ^=  0x77;
            if (!(square & 4))
            {
                if (square >= 0x70)
                    square = (square + 0x11) & 0x73;
                else
                    square += 0x10;
            }
        } while (square);
    }
}


/*
 *  move a piece to a new location on the board
 */

inline void MovePiece(SQUARETYPE new1, SQUARETYPE old)
{
    BOARDTYPE b;
    b = Board[new1];
    Board[new1] = Board[old];
    Board[old] = b;
    PieceTab[Board[new1].color][Board[new1].index].isquare = new1;
}


/*
 *  Calculate the squares for the rook move in castling
 */

void GenCastSquare(SQUARETYPE new1, SQUARETYPE *castsquare,
                    SQUARETYPE *cornersquare)
{
    if ((new1 & 7) >= 4)          /* short castle */
    {
        *castsquare = new1 - 1;
        *cornersquare = new1 + 1;
    }
    else                           /* long castle */
    {
        *castsquare = new1 + 1;
        *cornersquare = new1 - 2;
    }
}


/*
 *  This function used in captures.  insquare must not be empty.
 */

inline void DeletePiece(SQUARETYPE insquare)
{
    Board[insquare].piece = empty;
    PieceTab[Board[insquare].color][Board[insquare].index].ipiece = empty;
}


/*
 *  Take back captures
 */

inline void InsertPTabPiece(PIECETYPE inpiece, COLORTYPE incolor,
   SQUARETYPE insquare)
{
    Board[insquare].piece = PieceTab[incolor][Board[insquare].index].ipiece
            = inpiece;
    Board[insquare].color = incolor;
    PieceTab[incolor][Board[insquare].index].isquare = insquare;
}


/*
 *  Used for pawn promotion
 */

inline void ChangeType(PIECETYPE newtype, SQUARETYPE insquare)
{
    Board[insquare].piece
        = PieceTab[Board[insquare].color][Board[insquare].index].ipiece
            = newtype;
    if (OfficerNo[Board[insquare].color] < Board[insquare].index)
        OfficerNo[Board[insquare].color] = Board[insquare].index;
}



/*
 *  Perform or take back move (takes back if resetmove is true),
 *  and perform the updating of Board and PieceTab.  Player must
 *  contain the color of the moving player, Opponent the color of the
 *  Opponent.
 *
 *  MovePiece, DeletePiece, InsertPTabPiece and ChangeType are used to update
 *  the Board module.
 */

void Perform(MOVETYPE *move, BOOL resetmove)
{
    SQUARETYPE /*new1*/ castsquare, cornersquare, epsquare;

    if (resetmove)
    {
        MovePiece(move->old, move->new1);
        if (move->content != empty)
            InsertPTabPiece(move->content, Opponent, move->new1);
    }
    else         
    {
        if (move->content != empty)
            DeletePiece(move->new1);
        MovePiece(move->new1, move->old);
    }

    if (move->spe)
    {
        if (move->movpiece == king)
        {
            GenCastSquare(move->new1, &castsquare, &cornersquare);
            if (resetmove)
            {
                MovePiece(cornersquare, castsquare);
            }
            else
            {
                MovePiece(castsquare, cornersquare);
            }
        }
        else
        {
            if (move->movpiece == pawn)
            {
                epsquare = (move->new1 & 7) + (move->old & 0x70); /* E.p. capture */
                if (resetmove)
                    InsertPTabPiece(pawn, Opponent, epsquare);
                else
                    DeletePiece(epsquare);
            }
            else
            {
                if (resetmove)
                    ChangeType(pawn, move->old);
                else
                    ChangeType(move->movpiece,move->new1);
            }
        }
    }
}


/*
 * Compare two moves
 */

BOOL EqMove(MOVETYPE *a, MOVETYPE *b)
{
    if (a->movpiece == b->movpiece)
        if (a->new1 == b->new1)
            if (a->old == b->old)
                if (a->content == b->content)
                    if (a->spe == b->spe)
                        return TRUE;
    return FALSE;
}


