// ObjectWindows - (C) Copyright 1992 by Borland International

#ifndef __WCDEFS_H
#define __WCDEFS_H

/*
 *  Constants
 */

const  BACK  =  -104;
const  MAXPLY  =  23;
const LOSEVALUE  = 0x7D00;
const MATEVALUE  = 0x7C80;
const DEPTHFACTOR  = 0x80;
const COMMANDLENGTH  = 10;
const MAXLEN         = 64;
const SQUARE_SIZE = 36;
const MAXBDSIZE = 8;
const MYFRAMESIZE = 3;
#define     MAXINT      32767

/*
 *  typedefs
 */

typedef int MAXTYPE;  /*  Evaluation type  */
enum PIECETYPE {empty, king, queen, rook, bishop, knight, pawn};
enum COLORTYPE {white, black};
typedef int INDEXTYPE;
typedef int SQUARETYPE;
typedef int EDGESQUARETYPE;
typedef short DEPTHTYPE;
struct MOVETYPE
    {
        int new1, old;  /*  new1 and old square  */
        short spe;           /*  Indicates special move:
                                 case movepiece of
                                  king: castling
                                  pawn: e.p. capture
                                  else : pawnpromotion  */
        PIECETYPE movpiece, content;  /* moving piece and
                                        evt. captured piece  */
    };

struct  BOARDTYPE
    {
        PIECETYPE piece;
        COLORTYPE color;
        short index;
        unsigned char attacked;
    };

typedef MOVETYPE LINETYPE[MAXPLY];  /*  Principal variation type  */
typedef unsigned char *LIBTYPE;      /*  The opening library  */

struct CLOCKTYPE
    {
        int hour, minute, second, sec100;
        int totalhours, totmin, totalsecs, tots100;
        int number;
        double totaltime;
    };

typedef char DIRTYPE;
typedef short SETOFPIECE;
enum CASTDIRTYPE {zero, lng, shrt};
typedef CASTDIRTYPE CASTTYPE;
typedef unsigned char FIFTYTYPE;
typedef unsigned char REPEATTYPE;

struct NODEVAL
    {
        unsigned long nodebase, nodeoffset;
    };

typedef char STR80[81];

typedef char COMMANDSTRING[COMMANDLENGTH];

enum LEVELTYPE { normal, fullgametime, easygame, infinite, plysearch,
                matesearch, matching };

struct TEXTCOLORTYPE
    {
        unsigned char background, color;
    };

struct SCREENPOSTYPE
    {
        unsigned char x, y;
        unsigned char background, color;
    };

typedef char STR6[6];

typedef struct
    {
        int x;
        STR6 s;
    } PICTURETYPE[3];

struct BOARDIDTYPE
    {
        PIECETYPE piece;
        COLORTYPE color;
    };

typedef char MAXSTRING[MAXLEN];

struct PIECETAB
{
   SQUARETYPE isquare;
   PIECETYPE ipiece;
};


struct ATTACKTABTYPE
{
    /*  A set of king..pawn.  gives the pieces, which can move to the
     *  square
     */
    SETOFPIECE pieceset;
    int direction;  /*  The direction from the piece to the square  */
};

struct CASTMOVETYPE
    {
        SQUARETYPE castnew, castold;
    };
    


#endif  // __WCDEFS_H
