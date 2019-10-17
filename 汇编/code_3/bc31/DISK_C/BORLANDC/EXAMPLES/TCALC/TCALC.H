/* Turbo C++ - (C) Copyright 1987-1991 by Borland International */

#define S_IREAD	 0x0100	/* from SYS\STAT.H */
#define S_IWRITE 0x0080	/* from SYS\STAT.H */

#define TRUE 1
#define FALSE 0

#define MSGHEADER "TURBOCALC - A Turbo C++ Demonstration Program"
#define MSGKEYPRESS "Press any key to continue."
#define MSGCOMMAND "Press / for the list of commands"
#define MSGMEMORY "Memory Available:"
#define MSGERROR "ERROR"
#define MSGLOMEM "Not enough memory to allocate cell."
#define MSGEMPTY "Empty"
#define MSGTEXT  "Text"
#define MSGVALUE "Value"
#define MSGFORMULA "Formula"
#define MSGAUTOCALC "AutoCalc"
#define MSGFORMDISPLAY "Form"
#define MSGFILENAME "Enter the file name of the spreadsheet:"
#define MSGNAME "Turbo C++ TurboCalc Spreadsheet"
#define MSGCOLWIDTH "Enter the new column width:"
#define MSGNOOPEN "Can't open the file."
#define MSGOVERWRITE "The file exists.  Do you want to overwrite it?"
#define MSGFILELOMEM "Not enough memory for entire spreadsheet."
#define MSGNOTURBOCALC "That is not a Turbo C++ TurboCalc spreadsheet."
#define MSGNOEXIST "The file does not exist."
#define MSGGOTO "Enter the cell to go to:"
#define MSGBADNUMBER "You must enter a number from %d to %d."
#define MSGBADCELL "That is not a legal cell."
#define MSGCELL1 "Enter the first cell to format:"
#define MSGCELL2 "Enter the last cell to format:"
#define MSGDIFFCOLROW "The row or the column must be the same."
#define MSGRIGHTJUST "Do you want the cell right-justified?"
#define MSGDOLLAR "Do you want numbers in a dollar format?"
#define MSGCOMMAS "Do you want commas in numbers?"
#define MSGPLACES "How many decimal places should the number be rounded to?"
#define MSGCOLUMNS "Do you want to print in 132 columns?"
#define MSGPRINT "Enter the file name to print to, or press ENTER to print on the printer."
#define MSGBORDER "Print the border?"
#define MSGLOADING "Loading..."
#define MSGSAVING "Saving..."
#define MSGSAVESHEET "Save current spreadsheet?"
#define MSGSTACKERROR "Parser stack overflow."

#define MENU "Spreadsheet, Format, Delete, Goto, Col, Row, Edit, Utility, Auto, Quit"
#define COMMAND "SFDGCREUAQ"
#define SMENU "Load, Save, Print, Clear"
#define SCOMMAND "LSPC"
#define CMENU "Insert, Delete, Width"
#define CCOMMAND "IDW"
#define RMENU "Insert, Delete"
#define RCOMMAND "ID"
#define UMENU "Recalc, Formula display"
#define UCOMMAND "RF"

#define MAXCOLS 100   /* Maximum is 702 */
#define MAXROWS 100
#define LEFTMARGIN 3
#define MINCOLWIDTH 3
#define MAXCOLWIDTH 80 - LEFTMARGIN
#define SCREENCOLS (80 - LEFTMARGIN) / MINCOLWIDTH + 1
#define SCREENROWS 20
#define DEFAULTWIDTH 10
#define DEFAULTFORMAT 0X42
#define MAXINPUT 79
#define MAXPLACES 8
#define TOPMARGIN 5
#define PARSERSTACKSIZE 20

#define TEXTCOLOR WHITE
#define ERRORCOLOR LIGHTRED + BLINK
#define VALUECOLOR LIGHTCYAN
#define FORMULACOLOR LIGHTMAGENTA
#define BLANKCOLOR BLACK
#define HEADERCOLOR WHITE + (RED << 4)
#define HIGHLIGHTCOLOR WHITE + (BLUE << 4)
#define HIGHLIGHTERRORCOLOR WHITE + (BLUE << 4) + BLINK
#define MSGAUTOCALCCOLOR LIGHTCYAN
#define MSGFORMDISPLAYCOLOR LIGHTMAGENTA
#define MSGMEMORYCOLOR LIGHTGREEN
#define MSGHEADERCOLOR LIGHTCYAN
#define PROMPTCOLOR YELLOW
#define COMMANDCOLOR LIGHTCYAN
#define LOWCOMMANDCOLOR WHITE
#define MEMORYCOLOR LIGHTRED
#define CELLTYPECOLOR LIGHTGREEN
#define CELLCONTENTSCOLOR YELLOW

#define HIGHLIGHT TRUE
#define NOHIGHLIGHT FALSE
#define UPDATE TRUE
#define NOUPDATE FALSE
#define FORMAT TRUE
#define NOFORMAT FALSE
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define TEXT 0
#define VALUE 1
#define FORMULA 2
#define COLADD 0
#define COLDEL 1
#define ROWADD 2
#define ROWDEL 3
#define OVERWRITE 0X80
#define RJUSTIFY 0X40
#define COMMAS 0X20
#define DOLLAR 0X10

struct CELLREC
{
 char attrib;
 union
 {
  char text[MAXINPUT + 1];
  double value;
  struct
  {
   double fvalue;
   char formula[MAXINPUT + 1];
  } f;
 } v;
};

typedef struct CELLREC *CELLPTR;

#if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)

#define memsize coreleft() - 1000
#define textcellsize(s) (((strlen(s) >> 1) + 3) << 1)
#define valuecellsize 12
#define formulacellsize(s) (((strlen(s) >> 1) + 7) << 1)

#else

#define memsize farcoreleft() - 1000
#define textcellsize(s) (((strlen(s) >> 1) + 5) << 1)
#define valuecellsize 16
#define formulacellsize(s) (((strlen(s) >> 1) + 9) << 1)

#endif

#define BS 8
#define FORMFEED 12
#define CR 13
#define ESC 27
#define HOMEKEY 327
#define ENDKEY 335
#define UPKEY 328
#define DOWNKEY 336
#define PGUPKEY 329
#define PGDNKEY 337
#define LEFTKEY 331
#define INSKEY 338
#define RIGHTKEY 333
#define DELKEY 339
#define CTRLLEFTKEY 371
#define CTRLRIGHTKEY 372
#define F1 315
#define F2 316
#define F3 317
#define F4 318
#define F5 319
#define F6 320
#define F7 321
#define F8 322
#define F9 323
#define F10 324

void initcursor(void);
int getkey(void);
int editstring(char *s, char *legal, int maxlength);
int getint(int *number, int low, int high);
void getinput(int c);
void setcolor(int color);
void scroll(int direction, int lines, int x1, int y1, int x2, int y2,
            int attrib);
void setcursor(unsigned int shape);
void writef(int col, int row, int color, int width, char *format, ...);
void printcol(void);
void printrow(void);
void displaycell(int col, int row, int highlighting, int updating);
void displaycol(int col, int updating);
void displayrow(int row, int updating);
void displayscreen(int updating);
void clearinput(void);
void changecursor(int insmode);
void showcelltype(void);
void initcolortable(void);
double parse(char *s, int *att);
int alloctext(int col, int row, char *s);
int allocvalue(int col, int row, double amt);
int allocformula(int col, int row, char *s, double amt);
void deletecell(int col, int row, int display);
void printfreemem(void);
void moverowup(void);
void moverowdown(void);
void movecolleft(void);
void movecolright(void);
void recalc(void);
void changeautocalc(int newmode);
void changeformdisplay(int newmode);
void errormsg(char *s);
void colstring(int col, char *colstr);
void centercolstring(int col, char *colstr);
void setleftcol(void);
void setrightcol(void);
void settoprow(void);
void setbottomrow(void);
void movehighlight(void);
void setlastcol(void);
void setlastrow(void);
void act(char *s);
void initvars(void);
int getcommand(char *msgstr, char *comstr);
void mainmenu(void);
void editcell(CELLPTR ecell);
int setoflags(int col, int row, int display);
void clearoflags(int col, int row, int display);
void updateoflags(int col, int row, int display);
void loadsheet(char *filename);
int getcell(int *col, int *row);
char *cellstring(int col, int row, int *color, int formatting);
void writeprompt(char *prompt);
int getyesno(int *yesno, char *prompt);
void swap(int *val1, int *val2);
void redrawscreen(void);
void checkforsave(void);
void savesheet(void);
int formulastart(char **input, int *col, int *row);
int rowwidth(int row);
void fixformula(int col, int row, int action, int place);
void clearlastcol(void);
void run(void);
void gotocell(void);

#if !defined(MAIN)

extern CELLPTR cell[MAXCOLS][MAXROWS], curcell;
extern unsigned char format[MAXCOLS][MAXROWS];
extern unsigned char colwidth[MAXCOLS];
extern unsigned char colstart[SCREENCOLS];
extern char formdisplay;
extern char changed;
extern char autocalc;
extern int leftcol, rightcol, toprow, bottomrow, curcol, currow, lastcol,
 lastrow, direction;
extern long memleft;
extern char stop;
extern char matherror;
extern unsigned int oldcursor, shortcursor, tallcursor, nocursor;

#endif

