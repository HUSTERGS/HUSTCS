// ObjectWindows - (C) Copyright 1992 by Borland International

#include <math.h>
#include "wcdefs.h"
#include "externs.h"

/*
 *  Globals
 */

static ATTACKTABTYPE attack[240];
ATTACKTABTYPE *AttackTab = &attack[120];
SETOFPIECE BitTab[7] = {0, 1, 2, 4, 8, 0x10, 0x20};
int DirTab[8] = { 1, -1, 0x10, -0x10, 0x11, -0x11, 0x0f, -0x0f};
int KnightDir[8] = {0x0E, -0x0E, 0x12, -0x12, 0x1f, -0x1f, 0x21, -0x21};
int PawnDir[2] = {0x10, -0x10};
MOVETYPE Next;
int BufCount, BufPnt;
MOVETYPE Buffer[81];
CASTMOVETYPE  CastMove[2][2] = { {{2, 4}, {6, 4}}, {{0x72, 0x74}, {0x76, 0x74}} };


void CalcAttackTab(void)
{
    DIRTYPE dir;
    int sq;
    unsigned char i;

    for (sq = -0x77; sq <= 0x77; sq++)
    {
        AttackTab[sq].pieceset = 0;
        AttackTab[sq].direction = 0;        
    }
    for (dir = 7; dir >=0; dir--)
    {
        for (i = 1; i < 8; i++)
        {
            if (dir < 4)
                AttackTab[DirTab[dir]*i].pieceset = BitTab[queen]+BitTab[rook];
            else
                AttackTab[DirTab[dir]*i].pieceset = BitTab[queen]+BitTab[bishop];
            AttackTab[DirTab[dir]*i].direction = DirTab[dir];
        }
        AttackTab[DirTab[dir]].pieceset += BitTab[king];
        AttackTab[KnightDir[dir]].pieceset = BitTab[knight];
        AttackTab[KnightDir[dir]].direction = KnightDir[dir];
    }
}


/*
 *  calculate whether apiece placed on asquare attacks the square
 */

short PieceAttacks(PIECETYPE apiece, COLORTYPE acolor,
                     SQUARETYPE asquare, SQUARETYPE square)
{
    EDGESQUARETYPE sq;
    int x;

    x = square - asquare;
    if (apiece == pawn)   /*  pawn attacks  */
        return (abs(x - PawnDir[acolor]) == 1);
    /*  other attacks: can the piece move to the square?  */
    else if (AttackTab[x].pieceset & BitTab[apiece])
    {
        if (apiece == king || apiece == knight)
            return 1;
        else
        {
        /*  are there any blocking pieces in between?  */
            sq = asquare;
            do
            {
                sq += AttackTab[x].direction;
            } while (sq != square && Board[sq].piece == empty );
            return (sq == square);
        }
    }
    else
        return 0;
}


/*
 *  calculate whether acolor attacks the square with at pawn
 */

short PawnAttacks(COLORTYPE acolor, SQUARETYPE square)
{
    EDGESQUARETYPE sq;

    sq = square - PawnDir[acolor] - 1;  /*  left square  */
    if (!(sq & 0x88))
        if (Board[sq].piece == pawn && Board[sq].color == acolor)
            return 1;
    sq += 2;   /*  right square  */
    if (!(sq & 0x88))
        if (Board[sq].piece == pawn && Board[sq].color == acolor)
            return 1;
    return 0;
}


/*
 *  Calculates whether acolor attacks the square
 */

short Attacks(COLORTYPE acolor, SQUARETYPE square)
{
    INDEXTYPE i;

    if (PawnAttacks(acolor, square))    /*  pawn attacks  */
        return 1;
    /*  Other attacks:  try all pieces, starting with the smallest  */
    for (i = OfficerNo[acolor]; i >= 0; i--)
        if (PieceTab[acolor][i].ipiece != empty)
            if (PieceAttacks(PieceTab[acolor][i].ipiece, acolor,
                    PieceTab[acolor][i].isquare, square))
                return 1;
    return 0;
}


/*
 *  check whether inpiece is placed on square and has never moved
 */

short Check(SQUARETYPE square, PIECETYPE inpiece, COLORTYPE incolor)
{
    DEPTHTYPE dep;

    if(Board[square].piece == inpiece && Board[square].color == incolor)
    {
        dep = Depth - 1;
        while (MovTab[dep].movpiece != empty)
        {
            if (MovTab[dep].new1 == square)
                return 0;
            dep--;
        }
        return 1;
    }
    return 0;
}


/*
 *  Calculate whether incolor can castle
 */

void CalcCastling(COLORTYPE incolor,  CASTDIRTYPE *cast)
{
    SQUARETYPE square = 0;

    if (incolor == black) square = 0x70;
    *cast = zero;
    if (Check(square + 4, king, incolor))  /*  check king  */
    {
        if (Check(square, rook, incolor))
            ((int)*cast) += lng;  /*  check a-rook  */
        if (Check(square + 7, rook, incolor))
            ((int)*cast) += shrt;  /*  check h-rook  */
    }
}


/*
 *  check if move is a pawn move or a capture
 */

inline short RepeatMove(MOVETYPE *move)
{
    return (move->movpiece != empty && move->movpiece != pawn &&
              move->content == empty && !move->spe);
}

/****************************************************************************/

/*
 *  Count the number of moves since last capture or pawn move
 *  The game is a draw when fiftymovecnt = 100
 */

FIFTYTYPE FiftyMoveCnt(void)
{
    FIFTYTYPE cnt = 0;

    while (RepeatMove(&MovTab[Depth - cnt]))
        cnt++;
    return cnt;
}


/*
 *  Calculate how many times the position has occured before
 *  The game is a draw when repetition = 3;
 *  movetab[back..Depth] contains the previous moves
 *  When immediate is set, only immediate repetion is checked
 */

REPEATTYPE Repetition(short immediate)
{
    DEPTHTYPE lastdep, compdep, tracedep, checkdep, samedepth;
    SQUARETYPE tracesq, checksq;
    REPEATTYPE repeatcount;

    repeatcount = 1;
    lastdep = samedepth = Depth + 1;    /*  current postion  */
    compdep = samedepth - 4;            /*  First position to compare  */

    /*  MovTab[lastdep..Depth] contains previous relevant moves  */
    while (RepeatMove(&MovTab[lastdep - 1]) && (compdep < lastdep ||
                 !immediate))
        lastdep--;
    if (compdep < lastdep)
        return repeatcount;
    checkdep = samedepth;
    do
    {
        checkdep--;
        checksq = MovTab[checkdep].new1;
        for (tracedep = checkdep + 2; tracedep < samedepth; tracedep += 2)
            if (MovTab[tracedep].old == checksq) goto TEN;

        /*  Trace the move backward to see if it has been 'undone' earlier  */
        tracedep = checkdep;
        tracesq = MovTab[tracedep].old;
        do
        {
            if (tracedep-2 < lastdep) return repeatcount;
            tracedep -= 2;
            /*  Check if piece has been moved before  */
            if (tracesq == MovTab[tracedep].new1) tracesq =
                    MovTab[tracedep].old;
        } while (tracesq != checksq || tracedep > compdep + 1);
        if (tracedep < compdep)    /*  Adjust evt. compdep  */
        {
            compdep = tracedep;
            if ((samedepth - compdep) % 2 == 1)
            {
                if (compdep == lastdep) return repeatcount;
                compdep --;
            }
            checkdep = samedepth;
        }
        /*  All moves between SAMEDEP and compdep have been checked,
            so a repetition is found  */
TEN :   if (checkdep <= compdep)
        {
            repeatcount++;
            if (compdep - 2 < lastdep) return repeatcount;
            checkdep = samedepth = compdep;
            compdep -= 2;
        }
    } while (1);
}


/*
 *  Test whether a move is possible
 *
 *  On entry:
 *    Move contains a full description of a move, which
 *    has been legally generated in a different position.
 *    MovTab[Depth - 1] contains last performed move.
 *
 *  On exit:
 *    KillMovGen indicates whether the move is possible
 */

short KillMovGen(MOVETYPE *move)
{
    SQUARETYPE castsq;
    PIECETYPE promote;
    CASTDIRTYPE castdir;
    CASTTYPE cast;
    short killmov;

    killmov = 0;
    if (move->spe && (move->movpiece == king))
    {
        CalcCastling(Player, &cast);     /*  Castling  */
        if (move->new1 > move->old)
            castdir = shrt;
        else
            castdir = lng;

        if (cast & castdir)    /*  Has king or rook moved before  */
        {
            castsq = (int)((move->new1 + move->old) / 2);
            /*  Are the squares empty ?  */
            if  (Board[move->new1].piece == empty)
              if (Board[castsq].piece == empty)
                if ((move->new1 > move->old) || (Board[move->new1-1].piece
                             == empty))
                  /*  Are the squares unattacked  */
                  if (!Attacks(Opponent, move->old))
                    if (!Attacks(Opponent, move->new1))
                      if (!Attacks(Opponent, castsq))
                        killmov = 1;
        }
    }
    else
    {
    if (move->spe && (move->movpiece == pawn))
    {
            /*  E.p. capture  */
            /*  Was the Opponent's move a 2 square move?  */
        if (MovTab[Depth-1].movpiece == pawn)
            if (abs(MovTab[Depth-1].new1 - MovTab[Depth-1].old) >= 0x20)
                if ((Board[move->old].piece == pawn) && (Board[move->old].color
                        == Player))
                        killmov = (move->new1 == ((MovTab[Depth-1].new1
                            + MovTab[Depth-1].old) / 2));
    }
    else
    {
        if (move->spe)                  /*  Normal test  */
        {
            promote = move->movpiece;   /*  Pawnpromotion  */
            move->movpiece = pawn;
        }

        /*  Is the content of Old and New1 squares correct?  */
        if (Board[move->old].piece == move->movpiece)
          if (Board[move->old].color == Player)
            if (Board[move->new1].piece == move->content)
              if (move->content == empty || Board[move->new1].color == Opponent)
              {
                if (move->movpiece == pawn)   /*  Is the move possible?  */
                {
                  if (abs(move->new1 - move->old) < 0x20)
                    killmov = 1;
                  else
                    killmov = Board[(move->new1+move->old) / 2].piece == empty;
                }
                else
                  killmov = PieceAttacks(move->movpiece, Player,
                                 move->old, move->new1);
              }
              if (move->spe)
                move->movpiece = promote;
    }
    }
    return killmov;
}


/*
 *  Store a move in buffer
 */

static void Generate(void)
{
    BufCount++;
    Buffer[BufCount] = Next;
}


/*
 *  Generates pawnpromotion
 */

static void PawnPromotionGen(void)
{
    PIECETYPE promote;

    Next.spe = 1;
    for (promote = queen; promote <= knight; ((int)promote)++)
    {
        Next.movpiece = promote;
        Generate();
    }
    Next.spe = 0;
}


/*
 *  Generates captures of the piece on new1 using PieceTab
 */

static void CapMovGen(void)
{
    EDGESQUARETYPE nextsq, sq;
    INDEXTYPE i;

    Next.spe = 0;
    Next.content = Board[Next.new1].piece;
    Next.movpiece = pawn;
    nextsq = Next.new1 - PawnDir[Player];
    for (sq = nextsq-1; sq <= nextsq+1; sq++)
        if (sq != nextsq)
          if ((sq & 0x88) == 0)
            if (Board[sq].piece == pawn && Board[sq].color == Player)
            {
                Next.old = sq;
                if (Next.new1 < 8 || Next.new1 >= 0x70)
                    PawnPromotionGen();
                else
                    Generate();
            }
            /*  Other captures, starting with the smallest pieces  */
    for (i = OfficerNo[Player]; i >= 0; i--)
        if (PieceTab[Player][i].ipiece != empty && PieceTab[Player][i].ipiece
                != pawn)
          if (PieceAttacks(PieceTab[Player][i].ipiece, Player,
                PieceTab[Player][i].isquare, Next.new1))
          {
              Next.old = PieceTab[Player][i].isquare;
              Next.movpiece = PieceTab[Player][i].ipiece;
              Generate();
          }
}


/*
 *  generates non captures for the piece on old
 */

static void NonCapMovGen(void)
{
    DIRTYPE  first, last, dir;
    int direction;
    EDGESQUARETYPE  newsq;

    Next.spe = 0;
    Next.movpiece = Board[Next.old].piece;
    Next.content = empty;
    switch (Next.movpiece)
    {
        case king :
            for (dir = 7; dir >= 0; dir--)
            {
                newsq = Next.old + DirTab[dir];
                if (!(newsq & 0x88))
                  if (Board[newsq].piece == empty)
                  {
                      Next.new1 = newsq;
                      Generate();
                  }
            }
            break;
        case knight :
            for (dir = 7; dir >= 0; dir--)
            {
                newsq = Next.old + KnightDir[dir];
                if (!(newsq & 0x88))
                  if (Board[newsq].piece == empty)
                  {
                      Next.new1 = newsq;
                      Generate();
                  }
            }
            break;
        case queen :
        case rook  :
        case bishop:
            first = 7;
            last = 0;
            if (Next.movpiece == rook) first = 3;
            if (Next.movpiece == bishop) last = 4;
            for (dir = first; dir >= last; dir--)
            {
                direction = DirTab[dir];
                newsq = Next.old + direction;
                /*  Generate all non captures in the direction  */
                while (!(newsq & 0x88))
                {
                    if (Board[newsq].piece != empty) goto TEN;
                    Next.new1 = newsq;
                    Generate();
                    newsq = Next.new1 + direction;
                }
TEN:            continue;
            }
            break;
        case pawn :
            Next.new1 = Next.old + PawnDir[Player];  /*  one square forward  */
            if (Board[Next.new1].piece == empty)
            {
                if (Next.new1 < 8 || Next.new1 >= 0x70)
                    PawnPromotionGen();
                else
                {
                    Generate();
                    if (Next.old < 0x18 || Next.old >= 0x60)
                    {
                        Next.new1 += (Next.new1 - Next.old); /* 2 squares forward */
                        if (Board[Next.new1].piece == empty) Generate();
                    }
                }
            }
    }  /* switch */
}


/*
 *  The move generator.
 *  InitMovGen generates all possible moves and places them in a buffer.
 *  Movgen will the generate the moves one by one and place them in next.
 *
 *  On entry:
 *    Player contains the color to move.
 *    MovTab[Depth-1] the las performed move.
 *
 *  On exit:
 *    Buffer contains the generated moves.
 *
 *    The moves are generated in the order :
 *      Captures
 *      Castlings
 *      Non captures
 *      E.p. captures
 */

void InitMovGen(void)
{
    CASTDIRTYPE castdir;
    EDGESQUARETYPE sq;
    INDEXTYPE index;

    BufCount = BufPnt = 0;
    /*  generate all captures starting with captures of
        largest pieces  */
    for (index = 1; index <= PawnNo[Opponent]; index++)
        if (PieceTab[Opponent][index].ipiece != empty)
        {
            Next.new1 = PieceTab[Opponent][index].isquare;
            CapMovGen();
        }
    Next.spe = 1;
    Next.movpiece = king;
    Next.content = empty;
    for (castdir = CASTDIRTYPE(lng-1); castdir <= shrt-1; ((int)castdir)++)
    {
        Next.new1 = CastMove[Player][castdir].castnew;
        Next.old = CastMove[Player][castdir].castold;
        if (KillMovGen(&Next)) Generate();
    }

    /*  generate non captures, starting with pawns  */
    for (index = PawnNo[Player]; index >= 0; index--)
        if (PieceTab[Player][index].ipiece != empty)
        {
            Next.old = PieceTab[Player][index].isquare;
            NonCapMovGen();
        }
    if (MovTab[Depth-1].movpiece == pawn)   /*  E.p. captures  */
        if (abs(MovTab[Depth-1].new1 - MovTab[Depth-1].old) >= 0x20)
        {
            Next.spe = 1;
            Next.movpiece = pawn;
            Next.content = empty;
            Next.new1 = (MovTab[Depth-1].new1 + MovTab[Depth-1].old) / 2;
            for (sq = MovTab[Depth-1].new1-1; sq <= MovTab[Depth-1].new1+1;
                             sq++)
                if (sq != MovTab[Depth-1].new1)
                    if (!(sq & 0x88))
                    {
                        Next.old = sq;
                        if (KillMovGen(&Next)) Generate();
                    }
        }
}


/*
 *  place next move from the buffer in next.  Generate zeromove when there
 *  are no more moves.
 */

void MovGen(void)
{
    if (BufPnt >= BufCount)
        Next = ZeroMove;
    else
    {
        BufPnt++;
        Next = Buffer[BufPnt];
    }
}
