/* Turbo C++ - (C) Copyright 1987-1991 by Borland International */

#include <string.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include "tcalc.h"

#define PLUS 0
#define MINUS 1
#define TIMES 2
#define DIVIDE 3
#define EXP 4
#define COLON 5
#define OPAREN 6
#define CPAREN 7
#define NUM 8
#define CELL 9
#define FUNC 10
#define EOLN 11
#define BAD 12
#define MAXFUNCNAMELEN 5

struct TOKENREC
{
 char state;
 union
 {
  double value;
  struct
  {
   int row, col;
  } c;
  char funcname[MAXFUNCNAMELEN + 1];
 } x;
};

static struct TOKENREC stack[PARSERSTACKSIZE], curtoken;
int stacktop, tokentype, error;
char *input, isformula;

int matherr(struct exception *e)
{
 e->retval = HUGE_VAL;
 return(1);
} /* matherr */

int isfunc(char *s)
/* Returns TRUE if the string is a legal function, FALSE otherwise. */
{
 int len = strlen(s);

 if (strncmp(s, input, len) == 0)
 {
  strncpy(curtoken.x.funcname, input, len);
  curtoken.x.funcname[len] = 0;
  input += len;
  return(TRUE);
 }
 return(FALSE);
} /* isfunc */

int nexttoken(void)
/* Gets the next token from the input stream */
{
 char *start, numstring[80];
 int decimal, len, numlen;

 while (*input == ' ')
  input++;
 if (*input == 0)
  return(EOLN);
 if (strchr("0123456789.", *input))
 {
  start = input;
  len = 0;
  decimal = FALSE;
  while ((isdigit(*input)) ||
   ((*input == '.') && (!decimal)))
  {
   if (*input == '.')
    decimal = TRUE;
   input++;
   len++;
  }
  if ((len == 1) && (start[0] == '.'))
   return(BAD);
  if (*input == 'E')
  {
   input++;
   len++;
   if (strchr("+-", *input) != NULL)
   {
    input++;
    len++;
   }
   numlen = 0;
   while ((isdigit(*input)) && (++numlen <= 3))
   {
    input++;
    len++;
   }
  }
  strncpy(numstring, start, len);
  numstring[len] = 0;
  curtoken.x.value = atof(numstring);
  if (errno == ERANGE)
   return(BAD);
  return(NUM);
 }
 else if (isalpha(*input))
 {
  if
  (isfunc("ABS") ||
   isfunc("ACOS") ||
   isfunc("ASIN") ||
   isfunc("ATAN") ||
   isfunc("COSH") ||
   isfunc("COS") ||
   isfunc("EXP") ||
   isfunc("LOG10") ||
   isfunc("LOG") ||
   isfunc("POW10") ||
   isfunc("ROUND") ||
   isfunc("SINH") ||
   isfunc("SIN") ||
   isfunc("SQRT") ||
   isfunc("SQR") ||
   isfunc("TANH") ||
   isfunc("TAN") ||
   isfunc("TRUNC"))
    return(FUNC);
  if (formulastart(&input, &curtoken.x.c.col, &curtoken.x.c.row))
  {
   isformula = TRUE;
   return(CELL);
  }
  else
   return(BAD);
 }
 else switch(*(input++))
 {
  case '+' : return(PLUS);
  case '-' : return(MINUS);
  case '*' : return(TIMES);
  case '/' : return(DIVIDE);
  case '^' : return(EXP);
  case ':' : return(COLON);
  case '(' : return(OPAREN);
  case ')' : return(CPAREN);
  default  : return(BAD);
 } /* switch */
} /* nexttoken */

void push(struct TOKENREC *token)
/* Pushes a new token onto the stack */
{
 if (stacktop == PARSERSTACKSIZE - 1)
 {
  errormsg(MSGSTACKERROR);
  error = TRUE;
 }
 else
  stack[++stacktop] = *token;
} /* push */

struct TOKENREC pop(void)
/* Pops the top token off of the stack */
{
 return(stack[stacktop--]);
} /* pop */

int gotostate(int production)
/* Finds the new state based on the last production and the top state. */
{
 int state = stack[stacktop].state;

 if (production <= 3)
 {
  switch(state)
  {
   case 0 : return(1);
   case 9 : return(19);
   case 20 : return(28);
  } /* switch */
 }
 else if (production <= 6)
 {
  switch(state)
  {
   case 0 :
   case 9 :
   case 20 : return(2);
   case 12 : return(21);
   case 13 : return(22);
  } /* switch */
 }
 else if (production <= 8)
 {
  switch(state)
  {
   case 0 :
   case 9 :
   case 12 :
   case 13 :
   case 20 : return(3);
   case 14 : return(23);
   case 15 : return(24);
   case 16 : return(25);
  } /* switch */
 }
 else if (production <= 10)
 {
  switch(state)
  {
   case 0 :
   case 9 :
   case 12 :
   case 13 :
   case 14 :
   case 15 :
   case 16 :
   case 20 : return(4);
  } /* switch */
 }
 else if (production <= 12)
 {
  switch(state)
  {
   case 0 :
   case 9 :
   case 12 :
   case 13 :
   case 14 :
   case 15 :
   case 16 :
   case 20 : return(6);
   case 5 : return(17);
  } /* switch */
 }
 else
 {
  switch(state)
  {
   case 0 :
   case 5 :
   case 9 :
   case 12 :
   case 13 :
   case 14 :
   case 15 :
   case 16 :
   case 20 : return(8);
  } /* switch */
 }
 return(30);
} /* gotostate */

double cellvalue(int col, int row)
/* Finds the value of a particular cell */
{
 if (cell[col][row] == NULL)
  return(0);
 if (cell[col][row]->attrib == TEXT)
  return(HUGE_VAL);
 if (cell[col][row]->attrib == FORMULA)
  return(cell[col][row]->v.f.fvalue);
 return(cell[col][row]->v.value);
} /* cellvalue */

void shift(int state)
/* Shifts a token onto the stack */
{
 curtoken.state = state;
 push(&curtoken);
 tokentype = nexttoken();
} /* shift */

void reduce(int reduction)
/* Completes a reduction */
{
 struct TOKENREC token1, token2;
 int counter;

 switch (reduction)
 {
  case 1 :
   token1 = pop();
   pop();
   token2 = pop();
   curtoken.x.value = token1.x.value + token2.x.value;
   break;
  case 2 :
   token1 = pop();
   pop();
   token2 = pop();
   curtoken.x.value = token2.x.value - token1.x.value;
   break;
  case 4 :
   token1 = pop();
   pop();
   token2 = pop();
   curtoken.x.value = token1.x.value * token2.x.value;
   break;
  case 5 :
   token1 = pop();
   pop();
   token2 = pop();
   if (token1.x.value == 0)
    curtoken.x.value = HUGE_VAL;
   else
    curtoken.x.value = token2.x.value / token1.x.value;
   break;
  case 7 :
   token1 = pop();
   pop();
   token2 = pop();
   curtoken.x.value = pow(token2.x.value, token1.x.value);
   break;
  case 9 :
   token1 = pop();
   pop();
   curtoken.x.value = -token1.x.value;
   break;
  case 11 :
   token1 = pop();
   pop();
   token2 = pop();
   curtoken.x.value = 0;
   if (token1.x.c.row == token2.x.c.row)
   {
    if (token1.x.c.col < token2.x.c.col)
     error = TRUE;
    else
    {
     for (counter = token2.x.c.col; counter <= token1.x.c.col; counter++)
      curtoken.x.value += cellvalue(counter, token1.x.c.row);
    }
   }
   else if (token1.x.c.col == token2.x.c.col)
   {
    if (token1.x.c.row < token2.x.c.row)
     error = TRUE;
    else
    {
     for (counter = token2.x.c.row; counter <= token1.x.c.row; counter++)
      curtoken.x.value += cellvalue(token1.x.c.col, counter);
    }
   }
   else
    error = TRUE;
   break;
  case 13 :
   curtoken = pop();
   curtoken.x.value = cellvalue(curtoken.x.c.col, curtoken.x.c.row);
   break;
  case 14 :
   pop();
   curtoken = pop();
   pop();
   break;
  case 16 :
   pop();
   curtoken = pop();
   pop();
   token1 = pop();
   if (strcmp(token1.x.funcname, "ABS") == 0)
    curtoken.x.value = fabs(curtoken.x.value);
   else if (strcmp(token1.x.funcname, "ACOS") == 0)
    curtoken.x.value = acos(curtoken.x.value);
   else if (strcmp(token1.x.funcname, "ASIN") == 0)
    curtoken.x.value = asin(curtoken.x.value);
   else if (strcmp(token1.x.funcname, "ATAN") == 0)
    curtoken.x.value = atan(curtoken.x.value);
   else if (strcmp(token1.x.funcname, "COSH") == 0)
    curtoken.x.value = cosh(curtoken.x.value);
   else if (strcmp(token1.x.funcname, "COS") == 0)
    curtoken.x.value = cos(curtoken.x.value);
   else if (strcmp(token1.x.funcname, "EXP") == 0)
    curtoken.x.value = exp(curtoken.x.value);
   else if (strcmp(token1.x.funcname, "LOG10") == 0)
    curtoken.x.value = log10(curtoken.x.value);
   else if (strcmp(token1.x.funcname, "LOG") == 0)
    curtoken.x.value = log(curtoken.x.value);
   else if (strcmp(token1.x.funcname, "ROUND") == 0)
    curtoken.x.value = (int)(curtoken.x.value + 0.5);
   else if (strcmp(token1.x.funcname, "POW10") == 0)
    curtoken.x.value = pow10(curtoken.x.value);
   else if (strcmp(token1.x.funcname, "SINH") == 0)
    curtoken.x.value = sinh(curtoken.x.value);
   else if (strcmp(token1.x.funcname, "SIN") == 0)
    curtoken.x.value = sin(curtoken.x.value);
   else if (strcmp(token1.x.funcname, "SQRT") == 0)
    curtoken.x.value = sqrt(curtoken.x.value);
   else if (strcmp(token1.x.funcname, "SQR") == 0)
    curtoken.x.value *= curtoken.x.value;
   else if (strcmp(token1.x.funcname, "TANH") == 0)
    curtoken.x.value = tanh(curtoken.x.value);
   else if (strcmp(token1.x.funcname, "TAN") == 0)
    curtoken.x.value = tan(curtoken.x.value);
   else if (strcmp(token1.x.funcname, "TRUNC") == 0)
    curtoken.x.value = (int)curtoken.x.value;
   break;
  case 3 :
  case 6 :
  case 8 :
  case 10 :
  case 12 :
  case 15 :
   curtoken = pop();
   break;
 } /* switch */
 curtoken.state = gotostate(reduction);
 push(&curtoken);
} /* reduce */

double parse(char *s, int *att)
/* Parses the string s - returns the value of the evaluated string, and puts
   the attribute in att: TEXT = 0, CONSTANT = 1, FORMULA = 2.
*/
{
 struct TOKENREC firsttoken;
 char accepted = FALSE;
 char copy[80];

 error = FALSE;
 isformula = FALSE;
 input = copy;
 strupr(strcpy(copy, s));
 stacktop = -1;
 firsttoken.state = 0;
 firsttoken.x.value = 0;
 push(&firsttoken);
 tokentype = nexttoken();
 do
 {
 switch (stack[stacktop].state)
 {
  case 0 :
  case 9 :
  case 12 :
  case 13 :
  case 14 :
  case 15 :
  case 16 :
  case 20 :
   if (tokentype == NUM)
    shift(10);
   else if (tokentype == CELL)
    shift(7);
   else if (tokentype == FUNC)
    shift(11);
   else if (tokentype == MINUS)
    shift(5);
   else if (tokentype == OPAREN)
    shift(9);
   else
    error = TRUE;
   break;
  case 1 :
   if (tokentype == EOLN)
    accepted = TRUE;
   else if (tokentype == PLUS)
    shift(12);
   else if (tokentype == MINUS)
    shift(13);
   else
    error = TRUE;
   break;
  case 2 :
   if (tokentype == TIMES)
    shift(14);
   else if (tokentype == DIVIDE)
    shift(15);
   else
    reduce(3);
   break;
  case 3 :
   reduce(6);
   break;
  case 4 :
   if (tokentype == EXP)
    shift(16);
   else
    reduce(8);
   break;
  case 5 :
   if (tokentype == NUM)
    shift(10);
   else if (tokentype == CELL)
    shift(7);
   else if (tokentype == FUNC)
    shift(11);
   else if (tokentype == OPAREN)
    shift(9);
   else
    error = TRUE;
   break;
  case 6 :
   reduce(10);
   break;
  case 7 :
   if (tokentype == COLON)
    shift(18);
   else
    reduce(13);
   break;
  case 8 :
   reduce(12);
   break;
  case 10 :
   reduce(15);
   break;
  case 11 :
   if (tokentype == OPAREN)
    shift(20);
   else
    error = TRUE;
   break;
  case 17 :
   reduce(9);
   break;
  case 18 :
   if (tokentype == CELL)
    shift(26);
   else
    error = TRUE;
   break;
  case 19 :
   if (tokentype == PLUS)
    shift(12);
   else if (tokentype == MINUS)
    shift(13);
   else if (tokentype == CPAREN)
    shift(27);
   else
    error = TRUE;
   break;
  case 21 :
   if (tokentype == TIMES)
    shift(14);
   else if (tokentype == DIVIDE)
    shift(15);
   else
    reduce(1);
   break;
  case 22 :
   if (tokentype == TIMES)
    shift(14);
   else if (tokentype == DIVIDE)
    shift(15);
   else
    reduce(2);
   break;
  case 23 :
   reduce(4);
   break;
  case 24 :
   reduce(5);
   break;
  case 25 :
   reduce(7);
   break;
  case 26 :
   reduce(11);
   break;
  case 27 :
   reduce(14);
   break;
  case 28 :
   if (tokentype == PLUS)
    shift(12);
   else if (tokentype == MINUS)
    shift(13);
   else if (tokentype == CPAREN)
    shift(29);
   else
    error = TRUE;
   break;
  case 29 :
   reduce(16);
   break;
  case 30 :
   error = TRUE;
   break;
 } /* switch */
 }
 while ((!accepted) && (!error));
 if (error)
 {
  *att = TEXT;
  return(0);
 }
 if (isformula)
  *att = FORMULA;
 else
  *att = VALUE;
 strcpy(s, copy);
 return(stack[stacktop].x.value);
} /* parse */

