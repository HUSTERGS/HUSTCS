// ObjectWindows - (C) Copyright 1992 by Borland International

#include <static.h>
#include "checkers.h"
#include "info.h"
#include "board.h"


const MYFRAMESIZE = 3;
static char buf[ 80 ];
const char *LOGFILE = "checkers.log";
extern HBITMAP RedManBmp, BlackManBmp, RedKingBmp, BlackKingBmp;


static char * CharArray[] = { "A","B", "C", "D", "E", "F", "G", "H" };
static char * NumArray[] = { "1", "2", "3", "4", "5", "6", "7", "8" };

static MOVE BestVar[ MAXPLY + 1 ][ MAXPLY + 1 ];      /* the best variation */
static MOVE Killer[ MAXPLY + 1 ][ 2 ];                /* Killer moves       */


/*
 *  Member function definitions for class Square
 */

void Square::ClearSquare(HDC hDC)
{
   int x, y;
   HANDLE hOldBrush;
   x = UpperLeftPos.x;
   y = UpperLeftPos.y;


   hOldBrush = SelectObject(hDC, hBrush);
   PatBlt(hDC, x, y, SQUARE_SIZE, SQUARE_SIZE, PATCOPY);
   SelectObject(hDC, hOldBrush);
}


/*
 *  Member function definitions for class Piece
 */

void Piece::SetBitmap(HBITMAP hbp)
{
   hBitmap = hbp;
   if (hBitmap != 0)
      GetObject(hBitmap, sizeof(BITMAP), (LPSTR) &Bitmap);
}

void Piece::DrawPiece(HDC hDC, POINT& p)
{
   HDC hMemoryDC;
   HBITMAP hOldBmp;

   if (hBitmap == 0)
      return;
   hMemoryDC = CreateCompatibleDC(hDC);
   hOldBmp = (HBITMAP)SelectObject(hMemoryDC, hBitmap);
   BitBlt(hDC, p.x+PIECE_OFFSET, p.y+PIECE_OFFSET, Bitmap.bmWidth, Bitmap.bmHeight,
      hMemoryDC, 0, 0, SRCCOPY);
   SelectObject(hMemoryDC, hOldBmp);
   DeleteDC(hMemoryDC);
}


/*
 *  Member function definitions for struct MOVE
 */

BOOL MOVE::CompMoves( MOVE &m2 )
{
   if( org.GetRow() == m2.org.GetRow() && org.GetCol() == m2.org.GetCol() )
      {
      if( dest.GetRow() == m2.dest.GetRow() && dest.GetCol() == m2.dest.GetCol() )
         {
         if( Capture == m2.Capture )
            {
            if( Capture != EMPTY )
               {
               if( capt.GetRow() == m2.capt.GetRow() )
                  {
                  if( capt.GetCol() == m2.capt.GetCol() )
                     {
                     if( Crown == m2.Crown )
                        {
                        return( TRUE );
                        }
                     }
                  }
               }
            else
               {
               if( Crown == m2.Crown )
                  {
                  return( TRUE );
                  }
               }
            }
         }
      }
   // all members of 'this' and 'm2' should be equivalent, except
   // the last member, 'value', which is of size int, so its left out
   // THIS MAY FAIL if MOVEs' data structures are changed
//   if (memcmp(this, &m2, sizeof(MOVE) - sizeof(int)) == 0)
//      return TRUE;
   return( FALSE );
}



/*
 *  Utility Functions
 */

#pragma argsused
extern "C" char *getenv(const char *var)
{
   // this effectively shortens the time needed to
   // call the 'time' function.  It happens to call
   // getenv for reasons not important to this app.
   // Thats not the real reason this was originally put
   // here, but its a good enough reason to leave it...
   return NULL;
}

void TimeToStr(char *tstr, time_t time)
{
   int hours, min, secs;
   secs = (int)(time % 60L);
   min = (int) ((time / 60L) % 60L);
   hours = (int) (time / 3600L);
   min = (int)((time / 60L) % 60L);
   sprintf(tstr, "%d:%02d:%02d", hours, min, secs);
}

void UpdateBestVariation( MOVE *m, int ply )
{
   int t1 = ply + 1;
   memcpy( &BestVar[ ply ][ ply ], m, sizeof( MOVE ) );
   MOVE *mptr1, *mptr2;
   for ( mptr1 = &BestVar[t1][t1], mptr2 = &BestVar[ply][t1];
      mptr1->org.GetRow(); mptr1++, mptr2++)
      memcpy(mptr2, mptr1, sizeof(MOVE));

   mptr2->org.SetRow(0);
   BestVar[ t1 ][ t1 ].org.SetRow( 0 );
}

void MemSwap( void *a, void *b, int size )
{
#if defined(__SMALL__) || defined(__MEDIUM__)
   asm {
      mov   bx, a
      mov   di, b
      mov   cx, size

      or    cx, cx
      jne   BEGIN_LOOP
      jmp   END_MEMSWAP
      }

BEGIN_LOOP :
   asm  {
      mov   dl, byte ptr [bx]
      mov   al, byte ptr [di]
      mov   byte ptr [bx], al
      mov   byte ptr [di], dl
      inc   bx
      inc   di

      dec   cx
      jne   BEGIN_LOOP
      }

END_MEMSWAP:
      return;
#else

   asm {
      les   bx, dword ptr a
      push  ds
      lds   di, dword ptr b
      mov   cx, size
      or    cx, cx
      jne   BEGIN_LOOP
      jmp   END_MEMSWAP
      }

BEGIN_LOOP :
   asm  {
      mov   dl, byte ptr es:[bx]
      mov   al, byte ptr ds:[di]
      mov   byte ptr es:[bx], al
      mov   byte ptr ds:[di], dl
      inc   bx
      inc   di

      dec   cx
      jne   BEGIN_LOOP
      }

END_MEMSWAP:
   asm pop ds
      return;
#endif

}

int IsInList( MOVE *list, int num_moves, MOVE &m )
{
   for( int i = 0; i < num_moves; ++i )
      {
      if( (list++)->CompMoves( m ) )
         return( i );
      }
   return( -1 );
}

void UpdateKillerTable( MOVE &m, int ply )
{
   static int i;

   m.Value = 1;

   if( (i = IsInList( Killer[ ply ], 2, m )) != -1 )
      {
      if( ++Killer[ ply ][ i ].Value > 1000 )
         Killer[ ply ][ i ].Value = 1000;
      }
   else           /* add it to the Killer table */
      {
      if( Killer[ ply ][ 0 ].Value <= Killer[ ply ][ 1 ].Value )
         {
         memcpy( &Killer[ ply ][ 0 ], &m, sizeof( MOVE ) );
         }
      else
         {
         memcpy( &Killer[ ply ][ 1 ], &m, sizeof( MOVE ) );
         }
      }
}


/**********************************************
 sorts the moves list
 **********************************************/

int SortMoves( MOVE list[], int num_moves )
{

   for( int i = 0; i < num_moves; ++i )
      {
      if( list[ i ].Capture == EMPTY )
         break;
      }

   for( int j = i + 1; j < num_moves; ++j )
      {
      if( list[ j ].Capture != EMPTY )
         {
         MemSwap( &list[ i ], &list[ j ], sizeof( MOVE ) );
         ++i;
         }
      }

   /* if there is a jump, trim off all non-jump moves */
   if( list[ 0 ].Capture != EMPTY )
      {
      while( list[ num_moves - 1 ].Capture == EMPTY )
         --num_moves;
      }

   return( num_moves );
}

int KillerSortMoves( MOVE list[], int num_moves, int ply )
{
   MOVE *mptr, *endptr, *mptr2;
   int j;
  /* evaluate each move */
   for( mptr = list, endptr = mptr + num_moves; mptr < endptr; mptr++ )
      {
      if( mptr->Capture != EMPTY )
         mptr->Value = 5000;
      else
         mptr->Value = 0;

      if( (j = IsInList( Killer[ ply ], 2, *mptr )) >= 0 )
         {
         mptr->Value += Killer[ ply ][ j ].Value;
         }
      }

  /* sort the list in descending order */
   for( mptr = list, endptr = mptr + num_moves; mptr < endptr - 1; mptr++)
      {
      for( mptr2 = mptr + 1; mptr2 < endptr; mptr2++ )
         {
         if( mptr2->Value > mptr->Value )
            {
            MemSwap( mptr, mptr2, sizeof( MOVE ) );
            }
         }
      }

   /* if there is a jump, trim off all non-jump moves */
   mptr = &list[num_moves-1];
   if( list[ 0 ].Capture != EMPTY )
      {
      while( (mptr--)->Capture == EMPTY )
         --num_moves;
      }

   return( num_moves );
}


/*
 *  Member function definitions for class BOARD
 */

BOARD::BOARD()
{
   BoardSize = 8;
   IterFlag = TRUE;
   KillerFlag = TRUE;
   Man = new Piece[6];
   hRedBrush = CreateSolidBrush(RED);
   hBlackBrush = CreateSolidBrush(BLACK);
   Redraw = NULL;
   Logging = FALSE;
   LastDest.SetRow(0);
   LastDest.SetCol(0);

   Man[REDMAN].SetBitmap(RedManBmp);
   Man[BLACKMAN].SetBitmap(BlackManBmp);
   Man[REDKING].SetBitmap(RedKingBmp);
   Man[BLACKKING].SetBitmap(BlackKingBmp);
   Man[EMPTY].SetBitmap(0);
   Man[OFFBOARD].SetBitmap(0);

   Man[REDMAN].SetSide(Red);
   Man[BLACKMAN].SetSide(Black);
   Man[REDKING].SetSide(Red);
   Man[BLACKKING].SetSide(Black);
   Man[EMPTY].SetSide(Unknown);
   Man[OFFBOARD].SetSide(Unknown);
}

BOARD::~BOARD()
{
   delete Man;
   if (Logging)
      Logoff();
   DeleteObject(hBlackBrush);
   DeleteObject(hRedBrush);
}


void BOARD::MessageScan()
{
   MSG msg;
   if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
      {
      if (msg.message == WM_SETCURSOR)
         DispatchMessage(&msg);
      else if (msg.message == WM_COMMAND && msg.wParam == CM_STOP)
         StopSearch = TRUE;
      else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}


BOOL BOARD::OnlyOneMove( SIDE player, int *row, int *col )
{
   int RetVal = FALSE;
   MOVE *list = new MOVE[ MAXMOVES ];
   int NumMoves = 0;

   while ( (NumMoves = Lmg( list, player, *row, *col, 0 )) == 1 )
      {
      MakeActualMove( list[ 0 ] );
      RetVal = TRUE;
      if( list[ 0 ].Capture != EMPTY && !list[ 0 ].Crown && CanJump( player, list[ 0 ].dest.GetRow(), list[ 0 ].dest.GetCol() ) )
        {
        *row = list[ 0 ].dest.GetRow();
        *col = list[ 0 ].dest.GetCol();
        }
      else
         goto END_ONLYONE;
      }

END_ONLYONE:
   delete list;
   if (NumMoves > 1) /* In case where there is one required jump, but */
      return FALSE;  /* then two possible jumps after that, return FALSE */
   return   RetVal;
}


void BOARD::PreEvaluate()
{
   int i, j, xman, inside;
   int tBSizeDiv2 = BoardSize >> 1;  // (BoardSize / 2)

   /*********************************************************
   This code gets a rough idea as to who is ahead in Material.
   **********************************************************/
   Material[ Red ]   = 0;
   Material[ Black ] = 0;

   Man[ REDMAN ].SetValue( 100 );
   Man[ BLACKMAN ].SetValue( 100 );
   Man[ REDKING ].SetValue ( 140 );
   Man[ BLACKKING ].SetValue( 140 );
   Man[ EMPTY ].SetValue( 0 );
   Man[ OFFBOARD ].SetValue( 0 );

   for( i = 1; i <= BoardSize; ++i )
      {
      for( j = 1; j <= BoardSize; ++j )
         {
         xman = Board[ i ][ j ].What;
         Material[ Man[ xman ].GetSide() ] += Man[ xman ].GetValue();
         }
      }

   /****************************************************
   Now adjust the Material weights based on who is ahead.
   This is to encourage the fellow who is winning to exchange pieces
   and the fellow who is behind to not exchange pieces.
   If Material is dead even then you shouldn't try to force exchanges
   just on general principles.
   *****************************************************/
   if( Material[ Red ] >= Material[ Black ] )
      {
         --Man[ REDMAN ];
         --Man[ REDKING ];
      }
   else
     {
     --Man[ BLACKMAN ];
     --Man[ BLACKKING ];
     }

   /****************************************************
   Examine each and every square and calculate the bonus values.
   *****************************************************/
   for( i = 1; i <= BoardSize; ++i )
      {
      for( j = 1; j <= BoardSize; ++j )
         {
         inside = (j > 1 && j < BoardSize) ? 1 : 0;

         SValue[ i ][ j ][ REDMAN ]    = Man[ REDMAN ].GetValue() + inside;
         SValue[ i ][ j ][ REDKING ]   = Man[ REDKING ].GetValue() + inside;
         SValue[ i ][ j ][ BLACKMAN ]  = Man[ BLACKMAN ].GetValue() + inside;
         SValue[ i ][ j ][ BLACKKING ] = Man[ BLACKKING ].GetValue() + inside;

         /* bonus points for central squares */
         if( abs( tBSizeDiv2 - i ) < 2 && abs( tBSizeDiv2 - j )  < 3 )
            {
            ++SValue[ i ][ j ][ REDMAN ];
            ++SValue[ i ][ j ][ REDKING ];
            ++SValue[ i ][ j ][ BLACKMAN ];
            ++SValue[ i ][ j ][ BLACKKING ];
            }

         /* bonus for non-Crown piece advancement */
         if( i > 2 )
            {
            SValue[ i ][ j ][ REDMAN ] += i - 2;
            }

         if( i < BoardSize - 2 )
            {
            SValue[ i ][ j ][ BLACKMAN ] += BoardSize - i - 1;
            }

         if( i == 1 )
            ++SValue[ i ][ j ][ REDMAN ];
         if( i == BoardSize )
            ++SValue[ i ][ j ][ BLACKMAN ];
         }
      }

   Material[ Red ]   = 0;
   Material[ Black ] = 0;

   for( i = 1; i <= BoardSize; ++i )
      {
      for( j = 1; j <= BoardSize; ++j )
         {
         xman = Board[ i ][ j ].What;
         Material[ Man[ xman ].GetSide() ] += SValue[ i ][ j ][ xman ];
         }
      }
}


int BOARD::Evaluate( int alpha, int beta, SIDE player, int row, int col, int limit, int ply )
{
   MOVE *list = new MOVE[ MAXMOVES ];

   MOVE *mptr, *endptr;
   int NumMoves, val;
   int num_back = 0;
   int retval = 0;

   int t1 = WIN - 2 - ply;
   int plyp1 = ply + 1;
   if (StopSearch)
      goto END_EVALUATE;

   ++Nodes;
   if( (NumMoves = Lmg( list, player, row, col, ply )) == 0 )
      {
      retval = LOSS + ply;
      goto END_EVALUATE;
      }
   MessageScan();
   if (StopSearch)
      {
      retval = 0;
      goto END_EVALUATE;
      }
   if( list->Quiescent( limit, NumMoves, ply ) )
      {
      retval = ( Material[ player ] - Material[ OPLAYER ] + (NumMoves > 3 ? 1 : 0) );
      goto END_EVALUATE;
      }

   for( mptr = list, endptr = mptr + NumMoves; mptr < endptr && alpha < t1; mptr++ )
      {
      MakeMove( *mptr );

      if( mptr->Capture != EMPTY )
         {
         if( !(mptr->Crown) && CanJump( player, mptr->dest.GetRow(), mptr->dest.GetCol() ) )
            {
            val = Evaluate( alpha, beta, player, mptr->dest.GetRow(), mptr->dest.GetCol(), limit, plyp1 );
            }
         else
            {
            val = Evaluate( -beta, -alpha, OPLAYER, 0, 0, limit, plyp1 ) * -1;
            }
         }
         else
            {
            if( limit == 0 || NumMoves == 1 )
               {
               val = Evaluate( -beta, -alpha, OPLAYER, 0, 0, limit, plyp1 ) * -1;
               }
            else
               {
               val = Evaluate( -beta, -alpha, OPLAYER, 0, 0, limit ? limit - 1 : 0, plyp1 ) * -1;
               }
            }
         UnMakeMove( *mptr );

         if( val > alpha )
            {
            if( val >= beta )
               {
                  if( KillerFlag )
                     UpdateKillerTable( *mptr, ply );
                  retval =  beta ;
                  goto END_EVALUATE;
               }
         else
            {
            alpha = val;
            ++num_back;
            UpdateBestVariation( mptr, ply );
            }
         }
         BestVar[ plyp1 ][ plyp1 ].org.SetRow(0);
      }
   retval = alpha;
END_EVALUATE:

   delete list;
   return   retval;
}

BOOL BOARD::ComputersTurn()
{
   int iter, i, val, row = 0, col = 0;
   double t;
   time_t itime1, itime2;
   long lNodes;
   int alpha = -MAXINT, beta = MAXINT;
   StopSearch = FALSE;
   ClearRedoStack();

   memcpy(SavedBoard, Board, sizeof(Board));

   if( !OnlyOneMove( Black, &row, &col ) )
      {
      Nodes = 0;
      time( &start_t );

      PreEvaluate();

      /* clear out the best-variation table */
      for( i = 0; i <= MAXPLY; ++i )
         {
         BestVar[ i ][ i ].org.SetRow(0);
         BestVar[ 0 ][ i ].org.SetRow(0);
         }

      /* clear out the Killer table */
      for( i = 0; i <= MAXPLY; ++i )
         {
         Killer[ i ][ 0 ].org.SetRow(0);
         Killer[ i ][ 0 ].Value   = -1;
         }

      for( iter = IterFlag ? 1 : SearchDepth; iter <= SearchDepth; ++iter )
         {
         lNodes = Nodes;
         time( &itime1 );

         val = Evaluate( alpha, beta, Black, row, col, iter, 0 );

         if (StopSearch)
            return FALSE;

         if( val >= beta )
            {
            TInfo->SetMessageText("Re-evaluation Necessary");
            val = Evaluate( alpha, MAXINT, Black, row, col, iter, 0 );
            TInfo->SetMessageText("");
            if (StopSearch)
               return FALSE;
            }
         else
            {
            if( val <= alpha )
               {
               TInfo->SetMessageText("Re-evaluation Necessary");
               val = Evaluate( -MAXINT, beta, Black, row, col, iter, 0 );
               TInfo->SetMessageText("");
               if (StopSearch)
                  return FALSE;
               }
            }
         alpha = val - 12;
         beta  = val + 12;

         /* seed the killer table with the best variation */
         for( i = 0; BestVar[ 0 ][ i ].org.GetRow(); ++i )
            {
            memcpy( &Killer[ i ][ 0 ], &BestVar[ 0 ][ i ], sizeof( MOVE ) );
            Killer[ i ][ 0 ].Value = 1;
            /* eliminate the other killer move */
            Killer[ i ][ 1 ].Value = -1;
            Killer[ i ][ 1 ].org.SetRow(0);
            }

         /* clear the rest of the killer table */
         do
            {
            Killer[ i ][ 0 ].org.SetRow(0);
            Killer[ i ][ 1 ].org.SetRow(0);
            }
         while( i++ < MAXPLY );

         time( &itime2 );
         t = difftime( itime2, itime1 );
         DisplaySearchStats( iter, val, Nodes - lNodes, t );
         }

      time( &end_t );
      if( (t = difftime( end_t, start_t )) != 0 )
         {
         sprintf(buf, "%.0f", t);
         TInfo->SetSecondsText(buf);
         sprintf(buf, "%ld", Nodes);
         TInfo->SetNodeText(buf);
         ComputerTotalTime += t;
         }
      else
         {
         TInfo->SetSecondsText("0");
         sprintf(buf, "%ld", Nodes);
         TInfo->SetNodeText(buf);
         }

      for ( i = 0; Man [ Board[ BestVar[0][i].org.GetRow() ]
         [ BestVar[0][i].org.GetCol() ].What ].GetSide() == Black; ++i)
         {
         MakeActualMove( BestVar[ 0 ][ i ] );
         }

      }
      TimeToStr(buf, ComputerTotalTime);
      TInfo->SetBlackInfoText(buf);
   return( TRUE );
}

/********************************************
 generates the list of moves for a given player at a row, col

 returns the number of legal moves found
 ********************************************/

int BOARD::GenMoves( MOVE *list, int row, int col )
{
   int NumMoves;
   int what;
   int trow1 = row + 1,  tcol1 = col + 1, trowm1 = row - 1, tcolm1 = col - 1;
   NumMoves = 0;
   what = Board[ row ][ col ].What;
   if( what == REDKING || what == BLACKKING || what == BLACKMAN )
      {
      if( Board[ trowm1 ][ tcolm1 ].What == EMPTY )
         {
         list->org.SetRow( row );
         list->org.SetCol( col );
         list->dest.SetRow( trowm1 );
         list->dest.SetCol( tcolm1 );
         list->Capture  = EMPTY;
         list->Crown    = ((row == 2) && (what == BLACKMAN));
         ++NumMoves;
         ++list;
         }
      if( Board[ trowm1 ][ tcol1 ].What == EMPTY )
         {
         list->org.SetRow( row );
         list->org.SetCol( col );
         list->dest.SetRow( trowm1 );
         list->dest.SetCol( tcol1 );
         list->Capture  = EMPTY;
         list->Crown    = ((row == 2) && ( what == BLACKMAN ));
         ++NumMoves;
         ++list;
         }
      }

   if( what == REDKING || what == BLACKKING || what == REDMAN )
      {
      if( Board[ trow1 ][ tcolm1 ].What == EMPTY )
         {
         list->org.SetRow( row );
         list->org.SetCol( col );
         list->dest.SetRow( trow1 );
         list->dest.SetCol( tcolm1 );
         list->Capture  = EMPTY;
         list->Crown    = ((row == BoardSize - 1) && (what == REDMAN));
         ++NumMoves;
         ++list;
         }
      if( Board[ trow1 ][ tcol1 ].What == EMPTY )
         {
         list->org.SetRow( row );
         list->org.SetCol( col );
         list->dest.SetRow( trow1 );
         list->dest.SetCol( tcol1 );
         list->Capture  = EMPTY;
         list->Crown    = ((row == BoardSize - 1) && (what == REDMAN));
         ++NumMoves;
         ++list;
         }
      }

   return( NumMoves );
}


void BOARD::MakeMove( MOVE &m)
{
  PPOSTYPE osqu, dsqu, csqu;

  osqu = &Board[ m.org.GetRow() ][ m.org.GetCol() ];
  dsqu = &Board[ m.dest.GetRow() ][ m.dest.GetCol() ];
  csqu = &Board[ m.capt.GetRow() ][ m.capt.GetCol() ];


  Material[ Man[ (*osqu).What ].GetSide() ] -= SValue[ m.org.GetRow() ][ m.org.GetCol() ][ (*osqu).What ];

  (*dsqu).What = (*osqu).What;
  (*osqu).What = EMPTY;

  if( m.Crown )  ++(*dsqu).What;

  Material[ Man[ (*dsqu).What ].GetSide() ] += SValue[ m.dest.GetRow() ][ m.dest.GetCol() ][ (*dsqu).What ];

  if( m.Capture != EMPTY )
    {
    Material[ Man[ m.Capture ].GetSide() ] -= SValue[ m.capt.GetRow() ][ m.capt.GetCol() ][ (*csqu).What ];
    (*csqu).What = EMPTY;
    }

}

void BOARD::UnMakeMove( MOVE &m )
{
   PPOSTYPE osqu, dsqu, csqu;
   osqu = &Board[ m.org.GetRow() ][ m.org.GetCol() ];
   dsqu = &Board[ m.dest.GetRow() ][ m.dest.GetCol() ];
   csqu = &Board[ m.capt.GetRow() ][ m.capt.GetCol() ];

   Material[ Man[ (*dsqu).What ].GetSide() ] -= SValue[ m.dest.GetRow() ][ m.dest.GetCol() ][ (*dsqu).What ];

   (*osqu).What = (*dsqu).What;
   (*dsqu).What = EMPTY;

   if( m.Crown )
      --(*osqu).What;
   Material[ Man[ (*osqu).What ].GetSide() ] += SValue[ m.org.GetRow() ][ m.org.GetCol() ][ (*osqu).What ];
   if( m.Capture != EMPTY )
      {
      (*csqu).What = m.Capture;
      Material[ Man[ m.Capture ].GetSide() ] += SValue[ m.capt.GetRow() ][ m.capt.GetCol() ][ (*csqu).What ];
      }
}


int BOARD::Lmg(MOVE *list, SIDE player, int row, int col, int ply)
{
   int num, NumMoves, HasAJump;

   NumMoves = 0;
   HasAJump = FALSE;

   if( row )          /* examine jumps from this square */
      {
      NumMoves = GenJumps( &list[ NumMoves ], player, row, col );
      }
   else               /* find all legal moves */
      {
      for( row = 1; row <= BoardSize; ++row )
         {
         for( col = 1; col <= BoardSize; ++col )
            {
            if( Man[ Board[ row ][ col ].What ].GetSide() == player )
               {
               if( (num = GenJumps( &list[ NumMoves ], player, row, col )) != 0 )
                  {
                  HasAJump = TRUE;
                  NumMoves += num;
                  }
               if( !HasAJump )
                  {
                  NumMoves += GenMoves( &list[ NumMoves ], row, col );
                  }
               }
            }
         }
      }

   if( KillerFlag )
      {
      NumMoves = KillerSortMoves( list, NumMoves, ply );
      }
   else
      {
      NumMoves = SortMoves( list, NumMoves );
      }

   return( NumMoves );
}

void BOARD::SetupBoard()
{
   int i, j;
   POINT p;
   int tBSizeP1 = BoardSize + 1;
   TotalMoves = 0;
   SearchDepth = 3;
   NumBlackPieces = NumRedPieces = 12;
   TInfo->SetSearchDepthText("3");
   JumpAgain = FALSE;
   ComputerTotalTime = UserTotalTime = 0;
   time(&start_t);
   if (Logging)
      Logoff();
   Logon();
   ClearRedoStack();
   ClearUndoStack();

   for (i = 0; i <= tBSizeP1; ++i)
      {
      p.y = (BoardSize - i) * SQUARE_SIZE;
      for (j = 0; j <= tBSizeP1; ++j)
         {
         Board[i][j].What = OFFBOARD;
         p.x = (j - 1) * SQUARE_SIZE - 1;
         Board[i][j].Sq.SetUpperLeftPos(p);
         }
      }

   for( i = 1; i <= BoardSize; ++i )
      {
      for( j = 1; j <= BoardSize; ++j )
         {
         if( (i % 2) == (j % 2 ) )
            {
            Board[ i ][ j ].What = EMPTY;
            Board[ i ][ j ].Sq.SetColor(hBlackBrush);

            if( i < BoardSize / 2 )
               {
               Board[ i ][ j ].What = REDMAN;
               }

            if( i - 1 > tBSizeP1 / 2 )
               {
               Board[ i ][ j ].What = BLACKMAN;
               }
            }
         else
            Board[ i ][ j ].Sq.SetColor(hRedBrush);
         }
      }


   BoardRect.top = BoardRect.left = BORDERSIZE - MYFRAMESIZE;
   BoardRect.right = BoardRect.bottom = BORDERSIZE + BoardSize * SQUARE_SIZE + MYFRAMESIZE;
}



void BOARD::DrawBoard(HDC hDC)
{
   int i, j;
   int what;
   POINT Point;

   for( i = BoardSize; i; --i )
      {

      for( j = 1; j <= BoardSize; ++j )
         {
         Board[ i ][ j ].Sq.ClearSquare(hDC);
         what = Board[ i ][ j ].What;
         if (what < EMPTY)
            {
            Point.x = i; Point.y = j;
            DrawPiece(hDC, what, Point);
            }
         }
   }
}

POINT BOARD::GetValidSquare(POINT& p, SIDE s)
{
/*
 *  Returns "i" and "j" values of valid square, not
 *  actual screen coordinates
 */
   int i, j;
   SIDE t;
   POINT RetPoint;
   RetPoint.x = 0;
   int what;
/*
 *  this is a very slow algorithm, since it checks all squares.
 *  A better search would only check to see if the point
 *  is in squares that are known to hold a given sides
 *  pieces.  One possibility is to keep a list around
 *  for each side which contains the "i" and "j" values
 *  for each owned square, and just check those.
 */

   for (i = 1; i <= BoardSize; i++)
      for (j = 1; j <= BoardSize; j++)
         {
         what = Board[ i ][ j ].What;
         if (what < EMPTY)
            t = Man[what].GetSide();
         else
            t = Unknown;

         if (Board[ i ][ j ].Sq.HasPoint(p) && t == s)
            {
            RetPoint.x = i;
            RetPoint.y = j;
            return RetPoint;
            }
         }
   return RetPoint;
}

POINT BOARD::GetEmptySquare(POINT& p)
{
   int i,j;
   POINT RetPoint;
   RetPoint.x = 0;

   for (i = 1; i <= BoardSize; i++)
      for (j = 1; j <= BoardSize; j++)
         {
         if (Board[ i ][ j ].Sq.HasPoint(p) && Board[ i ][ j ].What == EMPTY)
            {
            RetPoint.x = i;
            RetPoint.y = j;
            return RetPoint;
            }
         }
   return RetPoint;
}

void BOARD::DrawAlphaNum(HDC hDC)
{
   int i;
   int XPos, YPos;



   XPos = BORDERSIZE/2 - 4;
   YPos = BORDERSIZE + SQUARE_SIZE/2 - 6;

   SetBkColor(hDC, RGB(192, 192, 192));

   for (i = BoardSize - 1; i >= 0; i--)
      {
      TextOut(hDC, XPos, YPos, NumArray[i], 1);
      YPos += SQUARE_SIZE;
      }

   XPos = BORDERSIZE + SQUARE_SIZE / 2 - 4;
   YPos = BORDERSIZE + (BoardSize * SQUARE_SIZE) + (BORDERSIZE / 2) - 6;

   for (i = 0; i < BoardSize; i++)
      {
      TextOut(hDC, XPos, YPos, CharArray[i], 1);
      XPos += SQUARE_SIZE;
      }
}

void BOARD::DrawCheckersFrame(HDC hDC)
{
    DrawFrame(hDC, BoardRect);
}


int BOARD::GenJumps(MOVE *list, int player, int row, int col)
{
   int NumMoves = 0;
   int what;
   int trow1 = row + 1, trowm1 = row - 1;
   int tcol1 = col + 1, tcolm1 = col - 1;

   if (StopSearch)
      return 0;
   what = Board[ row ][ col ].What;

   if(  what == REDKING   || what == BLACKKING   || what == BLACKMAN )
      {
      if( Man[ Board[ trowm1 ][ tcolm1 ].What ].GetSide() == OPLAYER )
         {
         if( Board[ trowm1 - 1 ][ tcolm1 - 1 ].What == EMPTY )
            {
            list->org.SetRow(row);
            list->org.SetCol(col);
            list->dest.SetRow(trowm1 - 1);
            list->dest.SetCol(tcolm1 - 1);
            list->capt.SetRow(trowm1);
            list->capt.SetCol(tcolm1);
            list->Capture  = Board[ trowm1 ][ tcolm1 ].What;
            list->Crown    = ((row == 3) && (what == BLACKMAN));
            ++NumMoves;
            ++list;
            }
         }
      if( Man[ Board[ trowm1 ][ tcol1 ].What ].GetSide() == OPLAYER )
         {
         if( Board[ trowm1 - 1 ][ tcol1 + 1 ].What == EMPTY )
            {
            list->org.SetRow( row );
            list->org.SetCol( col );
            list->dest.SetRow( trowm1 - 1 );
            list->dest.SetCol( tcol1 + 1 );
            list->capt.SetRow( trowm1 );
            list->capt.SetCol( tcol1 );
            list->Capture  = Board[ trowm1 ][ tcol1 ].What;
            list->Crown    = ((row == 3) && (what == BLACKMAN));
            ++NumMoves;
            ++list;
            }
         }
      }

   if( what == REDKING || what == BLACKKING || what == REDMAN )
      {
      if( Man[ Board[ trow1 ][ tcol1 ].What ].GetSide() == OPLAYER )
         {
         if ( Board[ trow1 + 1 ][ tcol1 + 1 ].What == EMPTY )
            {
            list->org.SetRow( row );
            list->org.SetCol( col );
            list->dest.SetRow( trow1 + 1 );
            list->dest.SetCol( tcol1 + 1 );
            list->capt.SetRow( trow1 );
            list->capt.SetCol( tcol1 );
            list->Capture  = Board[ trow1 ][ tcol1 ].What;
            list->Crown    = ((row == BoardSize - 2) && (what == REDMAN));
            ++NumMoves;
            ++list;
            }
         }
      if( Man[ Board[ trow1 ][ tcolm1 ].What ].GetSide() == OPLAYER )
         {
         if( Board[ trow1 + 1 ][ tcolm1 - 1 ].What == EMPTY )
            {
            list->org.SetRow( row );
            list->org.SetCol( col );
            list->dest.SetRow( trow1 + 1 );
            list->dest.SetCol( tcolm1 - 1 );
            list->capt.SetRow( trow1 );
            list->capt.SetCol( tcolm1 );
            list->Capture  = Board[ trow1 ][ tcolm1 ].What;
            list->Crown    = ((row == BoardSize - 2) && (what == REDMAN));
            ++NumMoves;
            ++list;
            }
          }
      }

   return( NumMoves );
}

BOOL BOARD::CanJump( SIDE player, int row, int col )
{
   int what;

   if (!row || row > BoardSize)
      return FALSE;

   int trow1 = row + 1, trowm1 = row - 1;
   int tcol1 = col + 1, tcolm1 = col - 1;

   what = Board[ row ][ col ].What;

   if( what == REDKING || what == BLACKKING || what == BLACKMAN )
      {
      if( Man[ Board[ trowm1 ][ tcolm1 ].What ].GetSide() == OPLAYER )
         {
         if( Board[ trowm1 - 1 ][ tcolm1 - 1 ].What == EMPTY )
            return( TRUE );
         }

      if( Man[ Board[ trowm1 ][ tcol1 ].What ].GetSide() == OPLAYER )
         {
         if( Board[ trowm1 - 1 ][ tcol1 + 1 ].What == EMPTY )
            return( TRUE );
         }
      }

   if( what == REDKING || what == BLACKKING || what == REDMAN )
      {
      if( Man[ Board[ trow1 ][ tcol1 ].What ].GetSide() == OPLAYER )
         {
         if( Board[ trow1 + 1 ][ tcol1 + 1 ].What == EMPTY )
            return( TRUE );
         }

      if( Man[ Board[ trow1 ][ tcolm1 ].What ].GetSide() == OPLAYER )
         {
         if( Board[ trow1 + 1 ][ tcolm1 - 1 ].What == EMPTY )
            return( TRUE );
         }
      }

   return( FALSE );
}

BOOL BOARD::UserMove(POINT& from, POINT& to)
{
   MOVE m;
   int NumMoves;
   int retval = FALSE;
   JumpAgain = FALSE;
   StopSearch = FALSE;

   MOVE *list = new MOVE[MAXMOVES];

   NumMoves = Lmg(list, Red, LastDest.GetRow(), LastDest.GetCol(), 0);

   m.org.SetRow(from.x);
   m.org.SetCol(from.y);
   m.dest.SetRow(to.x);
   m.dest.SetCol(to.y);

   if (abs(m.org.GetRow() - m.dest.GetRow()) == 2)
      {
      m.capt.SetRow( (m.org.GetRow() + m.dest.GetRow()) /2 );
      m.capt.SetCol( (m.org.GetCol() + m.dest.GetCol()) /2 );
      m.Capture = CON( m.capt );
      }
   else
      {
      m.Capture = EMPTY;
      }

   if( CON( m.org) == REDMAN && m.dest.GetRow() == BoardSize )
      m.Crown = TRUE;
   else
      m.Crown = FALSE;

   if( IsInList( list, NumMoves, m ) >= 0 )
      {
      MakeActualMove( m );

      if( m.Capture != EMPTY && !m.Crown )
         {
         if( (JumpAgain = CanJump( Red, m.dest.GetRow(), m.dest.GetCol() )) != 0 )
            {
            LastDest.SetRow(m.dest.GetRow());
            LastDest.SetCol(m.dest.GetCol());
            }
         else
            {
            LastDest.SetRow( 0 );
            LastDest.SetCol( 0 );
            }
         }
      retval = TRUE;
      }

   delete list;
   return retval;
}


void BOARD::InsertRedrawPoint(POINT& inp)
{
   PREDRAWLIST p = new REDRAWLIST;
   p->p = inp;
   p->next = NULL;

   if (Redraw == NULL)
      Redraw = p;
   else
      {
      p->next = Redraw;
      Redraw = p;
      }
}

void BOARD::DeleteRedrawPoint(POINT& p)
{
   PREDRAWLIST cur = Redraw;
   PREDRAWLIST last = NULL;
   BOOL found = 0;

   while (cur != NULL && !found)
      {
      if (memcmp(&(cur->p), &p, sizeof(POINT)) != 0)
         {
         last = cur;
         cur = cur->next;
         }
      else
         found = TRUE;
      }

   if (found)
      {
      if (last == NULL) /* first element */
         {
         last = Redraw->next;
         delete Redraw;
         Redraw = last;
         }
      else
         {
         last->next = cur->next;
         delete cur;
         }
      }
}

void BOARD::ReleaseRedraw()
{
   PREDRAWLIST Next;
   while (Redraw != NULL)
      {
         Next = Redraw->next;
         delete Redraw;
         Redraw = Next;
      }
}

BOOL BOARD::GetNextRedrawPoint(POINT *Pt)
{
   /*
      this removes the next point from the list
      then returns it.  Returns FALSE if
      no more points exist;
    */

   PREDRAWLIST cur;

   if (Redraw != NULL)
      {
      *Pt = Redraw->p;
      cur = Redraw;
      Redraw = Redraw->next;
      delete cur;
      return TRUE;
      }
   else
      return FALSE;
}


void BOARD::RedrawBoard(HDC hDC)
{
   POINT DrawP;
   int what;

   while (GetNextRedrawPoint(&DrawP))
      {
      ClearSquare(hDC, DrawP);
      if ((what = Board[DrawP.x][DrawP.y].What) < EMPTY)
         DrawPiece(hDC, what, DrawP);
      }
}


void BOARD::DisplaySearchStats( int iter, int val, long inodes, double stime )
{
   char temp[40];
   int i;

   sprintf(   buf, "%d", iter);
   TInfo->SetIterationText(buf);
   sprintf(buf, "%d", val);
   TInfo->SetValueText(buf);
   sprintf(buf, "%ld", inodes);
   TInfo->SetNodeText(buf);
   sprintf(buf,"%.0f", stime);
   TInfo->SetSecondsText(buf);

   *buf = 0;
   for( i = 0; BestVar[ 0 ][ i ].org.GetRow(); ++i )
      {
      BestVar[0][i].MoveToStr( temp );
      strcat(buf, temp);
      strcat(buf, " ");
      }
   TInfo->SetBestLineText(buf);
}

void DrawFrame(HDC hDC, RECT& BoardRect)
{
    int x1, y1, x2, y2;
    POINT pArray[3];
    HPEN hPen, hOldPen;
    HBRUSH hOldBrush;

    x1 = BoardRect.left;
    x2 = BoardRect.right;
    y1 = BoardRect.top;
    y2 = BoardRect.bottom;

    hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
    hOldPen = (HPEN)SelectObject(hDC, GetStockObject(WHITE_PEN));

    Rectangle(hDC, x1, y1, x2, y2);

    pArray[0].x = x1 + 2;
    pArray[1].y = pArray[0].y = y2 - 3;
    pArray[2].x = pArray[1].x = x2 - 3;
    pArray[2].y = y1 + 2;

    Polyline(hDC, pArray, 3);
    hPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
    SelectObject(hDC, hPen);
    pArray[0].x = x1;
    pArray[1].y = pArray[0].y = y2-1;
    pArray[2].x = pArray[1].x = x2-1;
    pArray[2].y = y1;

    Polyline(hDC, pArray, 3);
    pArray[1].x = pArray[0].x = x1 + 2;
    pArray[0].y = y2 - 3;
    pArray[2].y = pArray[1].y = y1 + 2;
    pArray[2].x = x2 - 3;
    Polyline(hDC, pArray, 3);
    SelectObject(hDC, hOldBrush);
    DeleteObject(SelectObject(hDC, hOldPen));
}

void BOARD::StartUsersTime()
{
   time(&start_t);
}

void BOARD::EndUsersTime()
{
   time(&end_t);

   UserTotalTime += (time_t)difftime( end_t, start_t );
   TimeToStr(buf, UserTotalTime);
   TInfo->SetRedInfoText(buf);
}

void BOARD::SaveGame( char *name )
{
   int i, j;

   ofstream fout(name);

   if (!fout)
      {
      sprintf(buf, "Cannot open %s", name);
      MessageBox(0, buf, "Error", MB_OK | MB_ICONHAND);
      return;
      }
   fout << BoardSize << ' ';

   for( i = 1; i <= BoardSize; ++i )
      {
      for( j = 1; j <= BoardSize; ++j )
         {
         fout << Board[ i ][ j ].What << ' ';
         }
      }
   fout << Material[Black] << ' ';
   fout << Material[Red] << ' ';
   fout << JumpAgain << ' ';
   fout << ComputerTotalTime << ' ';
   fout << UserTotalTime << ' ';
   fout << SearchDepth << ' ';
   fout << NumBlackPieces << ' ';
   fout << NumRedPieces;
   fout.close();
}

void BOARD::LoadGame( char *name )
{
   int i, j;

   SetupBoard();
   ifstream fin(name);
   if (!fin)
      {
      sprintf(buf, "Cannot open %s", name);
      MessageBox(0, buf, "Error", MB_OK | MB_ICONHAND);
      return;
      }
   fin >> BoardSize;
   for( i = 1; i <= BoardSize; ++i )
      {
      for( j = 1; j <= BoardSize; ++j )
         {
         fin >> Board[ i ][ j ].What;
         }
      }
   fin >> Material[Black];
   fin >> Material[Red];
   fin >> JumpAgain;
   fin >> ComputerTotalTime;
   fin >> UserTotalTime;
   fin >> SearchDepth;
   fin >> NumBlackPieces;
   fin >> NumRedPieces;
   fin.close();
   TInfo->Reset();
   TimeToStr(buf, ComputerTotalTime);
   TInfo->SetBlackInfoText(buf);
   TimeToStr(buf, UserTotalTime);
   TInfo->SetRedInfoText(buf);
   sprintf(buf, "%d", SearchDepth);
   TInfo->SetSearchDepthText(buf);
   TInfo->SetMessageText("Game Loaded");
}


void BOARD::SetSearchDepth(int NewDepth)
{
   if (NewDepth > 0 && NewDepth < MAXPLY )
      {
      SearchDepth = NewDepth;
      sprintf(buf, "%d", SearchDepth);
      TInfo->SetSearchDepthText(buf);
      }
   else
      {
      sprintf(buf, "Search depth must be between 1 and %d", MAXPLY - 1);
      MessageBox(0, buf, "Error", MB_OK | MB_ICONHAND);
      }
}

void BOARD::DrawLastBoard(HDC hDC)
{
   int i, j;
   int what;
   POINT Point;

   for( i = BoardSize; i; --i )
      {
      for( j = 1; j <= BoardSize; ++j )
         {
         SavedBoard[ i ][ j ].Sq.ClearSquare(hDC);
         what = SavedBoard[ i ][ j ].What;
         if (what < EMPTY)
            {
            Point.x = i; Point.y = j;
            DrawPiece(hDC, what, Point);
            }
         }
   }
}


void BOARD::Logon()
{
   olog = new ofstream(LOGFILE);

   if (!(*olog))
      {
      MessageBox(0, "Could not open log file", "Checkers", MB_OK | MB_ICONHAND);
      Logging = FALSE;
      return;
      }
   Logging = TRUE;
   *olog << "Checkers Log File" << endl << endl;

   time_t curtime;
   struct tm *tmtime;
   time(&curtime);
   tmtime = localtime(&curtime);
   static char AMPM[2][3] = { "AM", "PM" };

   sprintf(buf, "DATE: %d-%02d-%02d\t\t", tmtime->tm_mon+1,tmtime->tm_mday,
      (tmtime->tm_year % 100));

   *olog << buf;

   sprintf(buf, "TIME: %d:%02d %s", (tmtime->tm_hour % 12) ? (tmtime->tm_hour % 12)
        : 12, tmtime->tm_min, AMPM[tmtime->tm_hour / 12]);

   *olog << buf << endl << endl;
}

void BOARD::Logoff()
{
   if (olog)
      {
      time_t curtime;
      struct tm *tmtime;
      time(&curtime);
      tmtime = localtime(&curtime);
      static char AMPM[2][3] = { "AM", "PM" };
      sprintf(buf, "%d:%02d %s", (tmtime->tm_hour % 12) ? (tmtime->tm_hour % 12)
        : 12, tmtime->tm_min, AMPM[tmtime->tm_hour / 12]);
      *olog << endl << "Ended logging at " << buf << endl;
      olog->close();
      olog = NULL;
      delete olog;
      }
   Logging = FALSE;
}

void BOARD::Log(MOVE& m, BOOL Undo)
{
   if (olog == NULL)
      {
      MessageBox(0, "Internal error: attempting to write to unopened log file",
         "Checkers", MB_OK | MB_ICONHAND);
      Logging = FALSE;
      }

   m.MoveToStr(buf);
   char *temp = new char[5];
   if (Undo == TRUE)
      strcpy(temp, "UNDO");
   else
      strcpy(temp, "");

   *olog << ++TotalMoves << ". " << buf << temp << endl;
}


void BOARD::MakeActualMove( MOVE &m)
{
   POINT DP;

   MakeMove(m);
   DP.x = m.org.GetRow();
   DP.y = m.org.GetCol();
   InsertRedrawPoint(DP);
   DP.x = m.dest.GetRow();
   DP.y = m.dest.GetCol();
   InsertRedrawPoint(DP);
   if (m.Capture != EMPTY)
      {
      DP.x = m.capt.GetRow();
      DP.y = m.capt.GetCol();
      InsertRedrawPoint(DP);
      (Man[ m.Capture ].GetSide() == Black) ? --NumBlackPieces : --NumRedPieces;
      }
   if (Logging)
      Log(m, FALSE);
   RUndoObject undo = *( new UndoObject(m) );
   UndoStack.push(undo);
}

void BOARD::UnMakeActualMove(MOVE& m)
{
   POINT UDP;

   UnMakeMove(m);
   UDP.x = m.org.GetRow();
   UDP.y = m.org.GetCol();
   InsertRedrawPoint(UDP);
   UDP.x = m.dest.GetRow();
   UDP.y = m.dest.GetCol();
   InsertRedrawPoint(UDP);
   if (m.Capture != EMPTY)
   {
      UDP.x = m.capt.GetRow();
      UDP.y = m.capt.GetCol();
      InsertRedrawPoint(UDP);
      (Man[ m.Capture ].GetSide() == Black) ? ++NumBlackPieces : ++NumRedPieces;
   }
   if (Logging)
       Log(m, TRUE);
   UndoObject &redo = *(new UndoObject(m));
   RedoStack.push(redo);
}

BOOL BOARD::UndoMove()
{
   UndoObject& undo = (UndoObject&)UndoStack.pop();
   MOVE undoMove = undo.GetMove();
   UnMakeActualMove(undoMove);
   delete &undo; // reference does hold the original new'd pointer
   return UndoStack.isEmpty();
}

BOOL BOARD::RedoMove()
{
   UndoObject& redo = (UndoObject&)RedoStack.pop();
   MOVE redoMove = redo.GetMove();
   MakeActualMove(redoMove);
   delete &redo;
   return RedoStack.isEmpty();
}


void BOARD::ClearRedoStack()
{
   while (!RedoStack.isEmpty())
      {
      UndoObject& redo = (UndoObject&)RedoStack.pop();
      delete &redo;
      }
}

void BOARD::ClearUndoStack()
{
   while (!UndoStack.isEmpty())
      {
      UndoObject& undo = (UndoObject&)UndoStack.pop();
      delete &undo;
      }
}

