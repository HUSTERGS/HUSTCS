// ObjectWindows - (C) Copyright 1992 by Borland International

#ifndef _BOARD_H
#define _BOARD_H

#include <stack.h>

#define  MAXINT        32000
#define  WIN           20000
#define  LOSS          -20000

#define  CON( s )      (Board[ (s).GetRow() ][ (s).GetCol() ].What)
#define  OPLAYER       ((player == Red) ? Black : Red)

#define SQUARE_SIZE  36
#define PIECE_OFFSET  2
#define BLACK  0x0L
#define RED    0x00000080L

#define  REDMAN        0
#define  REDKING       1
#define  BLACKMAN      2
#define  BLACKKING     3
#define  EMPTY         4
#define  OFFBOARD      5


#define  MAXBDSIZE     8           // maximum board size
#define  MAXMOVES      20          // maximum number of moves to consider
#define  MAXPLY        30          // maximum depth of tree search

extern int BORDERSIZE;




_CLASSDEF(Square)

class Square
{
   int Row;              // Row position on board
   int Col;              // column position on board
   POINT UpperLeftPos;   // actual point on the screen
   HBRUSH hBrush;        // this squares color
   int Value;            // this squares value
  public:
   void SetColor(HBRUSH hBr)
      {
      hBrush = hBr;
      }
   void ClearSquare(HDC hDC);
   void SetValue(int val)
   {
      Value = val;
   }
   int GetValue()
   {
      return Value;
   }
   POINT& GetUpperLeftPos()
      {
      return UpperLeftPos;
      }
   void SetRow(int i) { Row = i; }
   void SetCol(int j) { Col = j; }
   GetRow() {
      return Row;
      }
   GetCol() {
      return Col;
   }
   void SetUpperLeftPos(POINT& p)
   {
         UpperLeftPos.x = p.x + BORDERSIZE;
         UpperLeftPos.y = p.y + BORDERSIZE;
   }
   BOOL HasPoint(POINT& p)
   {
      if (p.x >= UpperLeftPos.x && p.x <= UpperLeftPos.x + SQUARE_SIZE
         && p.y >= UpperLeftPos.y && p.y <= UpperLeftPos.y + SQUARE_SIZE)
         return TRUE;
      return FALSE;
   }
};

_CLASSDEF(Piece)

class Piece
{
   SIDE Side;               // which side is this piece on
   int Value;               // whats the value of this piece
   HBITMAP hBitmap;         // handle to a bitmap for this piece
   BITMAP Bitmap;           // the bitmap that that handle handles
  public:
   Piece()
   {
      Side = Unknown;
      hBitmap = 0;
   }
   void SetSide(SIDE s)
      {
      Side = s;
      }
   SIDE GetSide()
   {
      return Side;
   }
   void SetValue(int val) { Value = val; }
   GetValue() { return Value; }
   void SetBitmap(HBITMAP hbp);
   void DrawPiece(HDC hDC, POINT& p);
   void operator --() { Value--; }
};


struct MOVE
{
   Square org, dest, capt;  // origin, destination, capture squares
   BYTE Capture;
         // Has someone been captured?
   BYTE Crown;              // the king is dead, long live the king
   int Value;               // value of this move
	inline BOOL CompMoves( MOVE &m2 );
   void Stoa(char *str, Square &squ)
      {
      sprintf(str, "%c%d%c", (char)(squ.GetCol() + 64), squ.GetRow(), (char) 0);
      }
   void MoveToStr(char *str)
   {
      Stoa(str, org);
      if (Capture != EMPTY )
         strcat(str, "x");
      else
         strcat(str, "-");

      Stoa(str + strlen(str), dest);

      if (Crown)
         strcat(str, "!");
   }
   int Quiescent(int limit, int num_moves, int ply)
   {
      if( ply == MAXPLY - 1 )
         return( TRUE );
      else
         {
         if( limit > 0 || Capture != EMPTY || num_moves == 1 )
            return( FALSE );
         else
            return( TRUE );
         }
   }
};

_CLASSDEF(UndoObject)
class UndoObject : public Object
{
   MOVE move;
  public:
   UndoObject(MOVE &m)
   {
      move = m;
   }
   MOVE GetMove()
   {
       return move;
   }
   virtual classType isA() const
   {
		return __firstUserClass;
   }
   virtual Pchar nameOf() const
   {
       return "UndoObject";
   }
   virtual int isEqual(const Object& m) const
   {
      return memcmp(this, &m, sizeof(UndoObject)) == 0;
   }
   virtual hashValueType hashValue() const
   { return 0; }
   virtual void printOn(Rostream) const
   { }
};

struct POSTYPE
{
   Square Sq;
   int What;
};

typedef POSTYPE *PPOSTYPE;

struct REDRAWLIST;
typedef REDRAWLIST *PREDRAWLIST;


struct REDRAWLIST
{
   POINT p;
   PREDRAWLIST next;
};


_CLASSDEF(BOARD)

class BOARD
{
	friend MOVE;
	PTInfoWindow TInfo;     // handle to information window
   PREDRAWLIST Redraw;     // linked list of square to be redrawn
   int  SearchDepth;       // user-selected depth of search
   int  IterFlag;          // flag, TRUE for iterative deepening
   int  KillerFlag;        // flag, TRUE for Killer move table
   int  BoardSize;         // usually 8x8
   int  Material[ 2 ];     // value of each players material
   int  JumpAgain;         // flag, TRUE if human must jump again
   long Nodes;             // number of nodes in the search
   Square LastDest;        // destination square of humans last move
   time_t start_t, end_t;  // start and end times for the search
   time_t ComputerTotalTime;  // total time used by computer to select move
   time_t UserTotalTime;   // total time used by user to select move
   PPiece Man;             // Pointer to array of class Piece
   POSTYPE Board[MAXBDSIZE+2][MAXBDSIZE+2];  // What each square holds and
                                         // its screen location
   int SValue[MAXBDSIZE+1][MAXBDSIZE+1][4];  // Square Values;
   POSTYPE SavedBoard[MAXBDSIZE+2][MAXBDSIZE+2]; // Last position before computers
                                             // search began
	RECT BoardRect;                       // Dimensions of checker board
   BOOL StopSearch;                      // user requests stop of search
   int NumBlackPieces;  // any black pieces left?
   int NumRedPieces;    // any red pieces left?
   BOOL Logging;        // Log moves?
   ofstream *olog;      // log stream
   HBRUSH hRedBrush;    // brush to paint red squares
   HBRUSH hBlackBrush;  // brush to paint black squares;
   Stack UndoStack;
   Stack RedoStack;
   int TotalMoves;
	int Lmg(MOVE *list, SIDE player, int row, int col, int ply);
	int GenJumps(MOVE *list, int player, int row, int col);
	void UnMakeMove( MOVE &m );
	int GenMoves( MOVE *list, int row, int col );
	BOOL CanJump( SIDE player, int row, int col );
   BOOL OnlyOneMove( SIDE player, int *row, int *col );
   void PreEvaluate();
	void MakeMove(MOVE&);
   void MakeActualMove(MOVE&);
   void UnMakeActualMove(MOVE&);
   int Evaluate( int alpha, int beta, SIDE player, int row, int col, int limit, int ply );
   inline void MessageScan();
   void Log(MOVE&, BOOL);
   void Logon();
   void Logoff();
   void ClearRedoStack();
   void ClearUndoStack();
  public:
   BOARD();
   ~BOARD();
	void SetInfoPtr(PTInfoWindow TI)
		{
		TInfo = TI;
		}
   void SetupBoard();
   void DrawBoard(HDC);
   void DrawLastBoard(HDC);
	void DisplaySearchStats(int, int, long, double);
   void DrawPiece(HDC hDC, int what, POINT& p)
   {
   /*
    *  Point p is the i, j point on the board, not
    *  the screen coordinates
    */
      Man[what].DrawPiece(hDC, Board[p.x][p.y].Sq.GetUpperLeftPos());
   }

   void ClearSquare(HDC hDC, POINT& Where)
   {
      Board[ Where.x ][ Where.y ].Sq.ClearSquare(hDC);
   }
   BOOL IsValidSquare(POINT&);
   int GetPieceType(POINT& Where)
   {
      return Board[ Where.x ][ Where.y ].What;
   }
   POINT GetValidSquare(POINT& p, SIDE s);
   POINT GetEmptySquare(POINT& p);
	void DrawCheckersFrame(HDC hDC);
   void RedrawBoard(HDC);
	BOOL UserMove(POINT& from, POINT& to);
   void InsertRedrawPoint(POINT& p);
   void DeleteRedrawPoint(POINT& p);
   void ReleaseRedraw();
   BOOL GetNextRedrawPoint(POINT *);
   BOOL ComputersTurn();
	void DrawAlphaNum(HDC);
   BOOL AnotherJump()
   {
      return JumpAgain;
   }
   void StartUsersTime();
   void EndUsersTime();
   void SaveGame(char *);
   void LoadGame(char *);
   void ToggleIter()
   {
      IterFlag = !IterFlag;
   }
   void ToggleKiller()
   {
      KillerFlag = !KillerFlag;
   }
   void SetSearchDepth(int);
   BOOL NoMoreBlack()
   {
      return (!NumBlackPieces);
   }
   BOOL NoMoreRed()
   {
      return (!NumRedPieces);
   }
   void ToggleLogging()
   {
      if (Logging)
         Logoff();
      else
         Logon();
   }
   BOOL RedoMove();
   BOOL UndoMove();
};

extern void DrawFrame(HDC hDC, RECT& iRect);

#endif  // _BOARD_H


