// ObjectWindows - (C) Copyright 1992 by Borland International

#include <math.h>
#include "wcdefs.h"
#include "externs.h"

MAXTYPE RootValue;
BOARDTYPE Board[0x78];

#undef max
#undef min
#define max(a, b)  (((a) > (b)) ? (a) : (b))
#define min(a, b)  (((a) < (b)) ? (a) : (b))

#define     TOLERANCE           8  /*  Tolerance width  */
#define     EXCHANGEVALUE      32
     /*  Value for exchanging pieces when ahead (not pawns)  */
#define     ISOLATEDPAWN       20
    /*  Isolated pawn.  Double isolated pawn is 3 * 20  */
#define     DOUBLEPAWN          8   /*  Double pawn  */
#define     SIDEPAWN            6   /*  Having a pawn on the side  */
#define     CHAINPAWN           3   /*  Being covered by a pawn  */
#define     COVERPAWN           3   /*  covering a pawn  */
#define     NOTMOVEPAWN         2   /*  Penalty for moving pawn  */
#define     BISHOPBLOCKVALUE   20
    /*  Penalty for bishop blocking d2/e2 pawn  */
#define     ROOKBEHINDPASSPAWN 16   /*  Bonus for Rook behind passed pawn  */


typedef unsigned char FILETYPE;  /*  file numbers  */
typedef unsigned char RANKTYPE;  /*  rank numbers  */
typedef unsigned char SETOFFILE;
typedef struct
    {
        SETOFFILE one, dob;
    } PAWNBITTYPE[2];

/*
 *  Global variables for this module
 */

int PieceValue[7] = {0, 0x1000, 0x900, 0x4c0, 0x300, 0x300, 0x100};
const char distan[8] = { 3, 2, 1, 0, 0, 1, 2, 3 };
    /*  The value of a pawn is the sum of Rank and file values.
        The file value is equal to PawnFileFactor * (Rank Number + 2) */
const char pawnrank[8] = {0, 0, 0, 2, 4, 8, 30, 0};
const char passpawnrank[8] = {0, 0, 10, 20, 40, 60, 70, 0};
const char pawnfilefactor[8] = {0, 0, 2, 5, 6, 2, 0, 0};
const char castvalue[2] = {4, 32};  /*  Value of castling  */

const SETOFFILE filebittab[8] = {1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80};
PAWNBITTYPE pawnbitt[MAXPLY + 2];
PAWNBITTYPE *pawnbit = &pawnbitt[1];
int totalmaterial, pawntotalmaterial, material;
  /*  Material level of the game
        (early middlegame = 43 - 32, endgame = 0)  */
int materiallevel;
const unsigned char squarerankvalue[8] = { 0, 0, 0, 0, 1, 2, 4, 4};
COLORTYPE tempcolor;
int temp, temp2;  /*  temporary junk  */



/*
 *  count the number of set bits in b
 */

static int count(SETOFFILE b)
{
    char cnt = 0;

    while (b)
    {
        if (b % 2 == 1) cnt++;
        b >>= 1;
    }
    return cnt;
}


/*
 *  Calculate value of the pawn structure in pawnbit[depth][color]
 */

static int pawnstrval(DEPTHTYPE depth, COLORTYPE color)
{
    SETOFFILE iso;  /*  contains FILEs with isolated pawns  */

    iso = pawnbit[depth][color].one &
        ~((pawnbit[depth][color].one << 1) | (pawnbit[depth][color].one
            >> 1));
    return (-(count(pawnbit[depth][color].dob) * DOUBLEPAWN +
            count(iso) * ISOLATEDPAWN + count(iso &
                pawnbit[depth][color].dob) * ISOLATEDPAWN * 2));
}


/*
 *  calculate the value of the piece on the square
 */

inline int PiecePosVal(PIECETYPE piece, COLORTYPE color, SQUARETYPE square)
{
    return (PieceValue[piece] + PVTable[color][piece][square]);
}


short mating;  /*  mating evaluation function is used  */

/*
 *  calculates piece-value table for the static evaluation function
 */

void CalcPVTable(void)
{
    typedef SETOFFILE PAWNTABTYPE[8];

    PAWNTABTYPE pawntab[2];
    /*  Bit tables for static pawn structure evaluation  */
    SETOFFILE pawnfiletab, bit, oppasstab, behindoppass,
        leftsidetab, rightsidetab, sidetab, leftchaintab,
        rightchaintab, chaintab, leftcovertab, rightcovertab;

    /*  Importance of an attack of the square  */
    char attackvalue[2][0x78];
    /*  Value of squares controlled from the square  */
    int pvcontrol[2][5][0x78];

    COLORTYPE losingcolor;     /*  the color which is being mated  */
    int posval;                /*  The positional value of piece  */
    int attval;                /*  The attack value of the square  */
    FILETYPE line;             /*  The file of the piece  */
    RANKTYPE rank;             /*  The rank of the piece  */
    char dist, kingdist;       /*  Distance to center, to opponents king */
    CASTTYPE cast;             /*  Possible castlings  */
    short direct;              /*  Indicates direct attack  */
    int cnt;                   /*  Counter for attack values  */
    int strval;                /*  Pawnstructure value  */
    COLORTYPE color, oppcolor; /*  Color and opponents color  */
    PIECETYPE piececount;      /*  Piece counter  */
    SQUARETYPE square;         /*  Square counter  */
    DIRTYPE dir;               /*  Direction counter  */
    EDGESQUARETYPE sq;         /*  Square counter  */
    int temp, temp2;           /*  temporary junk  */

    /*  Calculate SAMMAT, PAWNSAMMAT and Material  */
    material = pawntotalmaterial = totalmaterial = mating = 0;

    for (square = 0; square < 0x78; square++)
        if (!(square & 0x88))
            if (Board[square].piece != empty)
                if (Board[square].piece != king)
                {
                    temp = PieceValue[Board[square].piece];
                    totalmaterial += temp;
                    if (Board[square].piece == pawn)
                        pawntotalmaterial += PieceValue[pawn];
                    if (Board[square].color == white) temp = -temp;
                    material -= temp;
                }
    materiallevel = max(0, totalmaterial - 0x2000) / 0x100;
    /*  Set mating if weakest player has less than the equivalence
    of two bishops and the advantage is at least a rook for a bishop  */
    if (material < 0)
        losingcolor = white;
    else
        losingcolor = black;
    mating = ((totalmaterial - abs(material)) / 2 <= PieceValue[bishop] * 2)
        && (abs(material) >= PieceValue[rook] - PieceValue[bishop]);
    /*  Calculate ATTACKVAL (importance of each square)  */
    for (rank = 0; rank < 8; rank++)
        for (line = 0; line < 8; line++)
        {
            square = (rank << 4) + line;
            attval = max(0, 8 - 3 * (distan[rank] + distan[line]));
                    /*  center importance */
                    /*  Rank importrance  */
            for (color = white; color <= black; ((int)color)++)
            {
                attackvalue[color][square] = ((squarerankvalue[rank] * 3 *
                        (materiallevel + 8)) >> 5) + attval;
                square ^= 0x70;
            }
        }
    for (color = white; color <= black; ((int)color)++)
    {
        oppcolor = (COLORTYPE)(1 - color);
        CalcCastling(oppcolor, &cast);
        if (cast != shrt && materiallevel > 0)
            /*  Importance of the 8 squares around the opponent's King  */
        for (dir = 0; dir < 8; dir++)
        {
            sq = PieceTab[oppcolor][0].isquare + DirTab[dir];
            if (!(sq & 0x88))
                attackvalue[color][sq] += ((12 * (materiallevel + 8)) >> 5);
        }
    }

    /*  Calculate PVControl  */
    for (square = 0x77; square >=0; square--)
        if(!(square & 0x88))
            for (color = white; color <= black; ((int)color)++)
                for (piececount = rook; piececount <= bishop; ((int)piececount)++)
                    pvcontrol[color][piececount][square] = 0;
    for (square = 0x77; square >=0; square--)
        if(!(square & 0x88))
            for (color = white; color <= black; ((int)color)++)
            {
                for (dir = 7; dir >= 0; dir--)
                {
                    if (dir < 4)
                        piececount = rook;
                    else
                        piececount = bishop;
                /*  Count value of all attacs from the square in
                    the Direction.
                    The Value of attacking a Square is Found in ATTACKVAL.
                    Indirect Attacks (e.g. a Rook attacking through
                    another Rook) counts for a Normal attack,
                    Attacks through another Piece counts half  */
                    cnt = 0;
                    sq = square;
                    direct = 1;
                    do
                    {
                        sq += DirTab[dir];
                        if (sq & 0x88) goto TEN;
                        temp = attackvalue[color][sq];
                        if (direct)
                            cnt += temp;
                        else
                            cnt += (temp >> 1);
                        if (Board[sq].piece != empty)
                            if ((Board[sq].piece != piececount)
                              && (Board[sq].piece != queen))
                                direct = 0;
                    } while (Board[sq].piece != pawn);
TEN:                pvcontrol[color][piececount][square] += (cnt >> 2);
                }
            }

    /*  Calculate PVTable, value by value  */
    for (square = 0x77; square >= 0; square--)
      if (!(square & 0x88))
      {
         for (color = white; color <= black; ((int)color)++)
         {
            oppcolor = (COLORTYPE)(1 - color);
            line = square & 7;
            rank = square >> 4;
            if (color == black) rank = 7 - rank;
            dist = distan[rank] + distan[line];
            kingdist = abs((square >> 4) - (PieceTab[oppcolor][0].isquare
                   >> 4)) + ((square - PieceTab[oppcolor][0].isquare) & 7);
            for (piececount = king; piececount <= pawn; ((int)piececount)++)
            {
                posval = 0;        /*  Calculate POSITIONAL Value for  */
                                   /*  The piece on the Square  */
                if (mating && (piececount != pawn))
                {
                    if (piececount == king)
                        if (color == losingcolor)  /*  Mating evaluation  */
                        {
                            posval = 128 - 16 * distan[rank]
                                - 12 * distan[line];
                            if (distan[rank] == 3)
                                posval -= 16;
                        }
                        else
                        {
                            posval = 128 - 4 * kingdist;
                            if ((distan[rank] >= 2) || (distan[line] == 3))
                                posval -= 16;
                        }
                }
                else
                {
                    temp = pvcontrol[color][rook][square];
                    temp2 = pvcontrol[color][bishop][square];
                    /*  Normal evaluation function  */
                    switch (piececount)
                    {
                        case king :
                            if (materiallevel <= 0) posval = -2 * dist;
                            break;
                        case queen :
                            posval = (temp + temp2) >> 2;
                            break;
                        case rook :
                            posval = temp;
                            break;
                        case bishop :
                            posval = temp2;
                            break;
                        case knight :
                            cnt = 0;
                            for (dir = 0; dir < 8; dir++)
                            {
                                sq = square + KnightDir[dir];
                                if (!(sq & 0x88))
                                    cnt += attackvalue[color][sq];
                            }
                            posval = (cnt >> 1) - dist * 3;
                            break;
                        case pawn :
                            if ((rank != 0) && (rank != 7))
                                posval = pawnrank[rank] +
                                  pawnfilefactor[line] * (rank + 2) - 12;
                    }
                }
                PVTable[color][piececount][square] = posval;
            }
         }
      }

    /*  Calculate pawntab (indicates which squares contain pawns)  */

    for (color = white; color <= black; ((int)color)++)
        for (rank = 0; rank < 8; rank++)
            pawntab[color][rank] = 0;
    for (square = 0x77; square >= 0; square--)
        if (!(square & 0x88))
            if (Board[square].piece == pawn)
            {
                rank = square >> 4;
                if (Board[square].color == black) rank = 7 - rank;
                pawntab[Board[square].color][rank] |=
                    filebittab[square & 7];
            }
    for (color = white; color <= black; ((int)color)++)  /*  initialize pawnbit  */
    {
        pawnbit[-1][color].one = pawnbit[-1][color].dob = 0;
        for (rank = 1; rank < 7; rank++)
        {
            temp = pawntab[color][rank];
            pawnbit[-1][color].dob |= (pawnbit[-1][color].one & temp);
            pawnbit[-1][color].one |= temp;
        }
    }
    /*  Calculate pawnstructurevalue  */
    RootValue = pawnstrval(-1, Player) - pawnstrval(-1, Opponent);

    /*  Calculate static value for pawn structure  */
    for (color = white; color <= black; ((int)color)++)
    {
        oppcolor = (COLORTYPE)(1 - color);
        pawnfiletab = leftsidetab = rightsidetab = behindoppass = 0;
        oppasstab = 0xff;
        for (rank = 1; rank < 7; rank++)
        /*  Squares where opponents pawns are passed pawns  */
        {
            oppasstab &= (~(pawnfiletab | leftsidetab | rightsidetab));
            /*  Squares behind the opponents passed pawns  */
            behindoppass |= (oppasstab & pawntab[oppcolor][7 - rank]);
            /*  squares which are covered by a pawn  */
            leftchaintab = leftsidetab;
            rightchaintab = rightsidetab;
            pawnfiletab = pawntab[color][rank]; /*  squares w/ pawns  */
            /*  squares w/ a pawn beside them  */
            leftsidetab = (pawnfiletab << 1) & 0xff;
            rightsidetab = (pawnfiletab >> 1) & 0xff;
            sidetab = leftsidetab | rightsidetab;
            chaintab = leftchaintab | rightchaintab;
            /*  squares covering a pawn  */
            temp = pawntab[color][rank+1];
            leftcovertab = (temp << 1) & 0xff;
            rightcovertab = (temp >> 1 ) & 0xff;
            sq = rank << 4;
            if (color == black) sq ^= 0x70;
            bit = 1;
            while (bit)
            {
                strval = 0;
                if (bit & sidetab)
                    strval = SIDEPAWN;
                else if (bit & chaintab)
                    strval = CHAINPAWN;
                if (bit & leftcovertab)
                    strval += COVERPAWN;
                if (bit & rightcovertab)
                    strval += COVERPAWN;
                if (bit & pawnfiletab)
                    strval += NOTMOVEPAWN;
                PVTable[color][pawn][sq] += strval;
                if ((materiallevel <= 0) || (oppcolor != ProgramColor))
                {
                    if (bit & oppasstab)
                        PVTable[oppcolor][pawn][sq] += passpawnrank[7 - rank];
                    if (bit & behindoppass)
                    {
                        temp = sq ^ 0x10;
                        for (tempcolor = black; tempcolor >= white
                            ; ((int)tempcolor)--)
                        {
                            PVTable[tempcolor][rook][sq] +=
                                ROOKBEHINDPASSPAWN;
                            if (rank == 6)
                                PVTable[tempcolor][rook][temp] +=
                                    ROOKBEHINDPASSPAWN;
                        }
                    }
                }
                sq++;
                bit = (bit << 1) & 0xff;
            }
        }
    }
    /*  Calculate penalty for blocking center pawns with a bishop  */
    for (sq = 3; sq < 5; sq ++)
    {
        if ((Board[sq + 0x10].piece == pawn) && (Board[sq + 0x10].color
            == white))
            PVTable[white][bishop][sq + 0x20] -= BISHOPBLOCKVALUE;
        if ((Board[sq+0x60].piece == pawn) && (Board[sq+0x60].color == black))
            PVTable[black][bishop][sq+0x50] -= BISHOPBLOCKVALUE;
    }
    for (square = 0x77; square >= 0; square--) /*  Calculate RootValue  */
        if (!(square & 0x88))
            if (Board[square].piece != empty)
                if (Board[square].color == Player)
                    RootValue +=
                        PiecePosVal(Board[square].piece, Player, square);
                else
                    RootValue -=
                        PiecePosVal(Board[square].piece, Opponent, square);
}

/****************************************************************************/

int value;
SQUARETYPE castsquare, cornersquare, epsquare;


/*
 *  Update pawnbit and calculates value when a pawn is removed from line
 */

inline int decpawnstrval(COLORTYPE color, FILETYPE line)
{
    temp = ~filebittab[line];
    pawnbit[Depth][color].one = (pawnbit[Depth][color].one & temp) |
            pawnbit[Depth][color].dob;
    pawnbit[Depth][color].dob &= temp;
    return (pawnstrval(Depth, color) - pawnstrval(Depth - 1, color));
}

/*
 *  Update pawnbit and calculates value when a pawn moves
 *  from old to new1 file
 */

static int movepawnstrval(COLORTYPE color, FILETYPE new1, FILETYPE old)
{
    temp = filebittab[new1];
    temp2 = ~filebittab[old];
    pawnbit[Depth][color].dob |= (pawnbit[Depth][color].one & temp);
    pawnbit[Depth][color].one = ((pawnbit[Depth][color].one & temp2) |
        pawnbit[Depth][color].dob) | temp;
    pawnbit[Depth][color].dob &= temp2;
    return (pawnstrval(Depth, color) - pawnstrval(Depth - 1, color));
}

/****************************************************************************/

/*
 *  Calculate STATIC evaluation of the move
 */

int StatEvalu(MOVETYPE *move)
{
    value = 0;
    if (move->spe)
        if (move->movpiece == king)
        {
            GenCastSquare(move->new1, &castsquare, &cornersquare);
            value = PiecePosVal(rook, Player, castsquare) -
                    PiecePosVal(rook,Player, cornersquare);
            if (move->new1 > move->old)
                value += castvalue[shrt-1];
            else
                value += castvalue[lng-1];
        }
        else if (move->movpiece == pawn)
        {
            epsquare = move->new1 - PawnDir[Player];  /*  E.p. capture  */
            value = PiecePosVal(pawn, Opponent, epsquare);
        }
        else            /*  Pawnpromotion  */
            value = PiecePosVal(move->movpiece, Player, move->old) -
                    PiecePosVal(pawn, Player, move->old) +
                    decpawnstrval(Player, move->old & 7);
        if (move->content != empty)  /*  normal moves  */
        {
            value += PiecePosVal(move->content, Opponent, move->new1);
            /*  Penalty for exchanging pieces when behind in material  */
            if (abs(MainEvalu) >= 0x100)
                if (move->content != pawn)
                    if ((ProgramColor == Opponent) == (MainEvalu >= 0))
                        value -= EXCHANGEVALUE;
        }
        pawnbit[Depth][black] = pawnbit[Depth - 1][black];  /*  calculate pawnbit  */
        pawnbit[Depth][white] = pawnbit[Depth - 1][white];
        if ((move->movpiece == pawn) && ((move->content != empty)
                || move->spe))
            value += movepawnstrval(Player, move->new1 & 7, move->old & 7);
        if ((move->content == pawn) || move->spe && (move->movpiece == pawn))
            value -= decpawnstrval(Opponent, move->new1 & 7);
        /*  Calculate value of move  */
        return (value + PiecePosVal(move->movpiece, Player, move->new1)-
                PiecePosVal(move->movpiece, Player, move->old));
}

