/*-----------------------------------------------------------------------*
 * filename - lsearch.c
 *
 * function(s)
 *        _lsearch - searches a table
 *        lsearch  - searches and updates a table
 *        lfind    - perform a linear search
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdlib.h>
#include <mem.h>
#include <stddef.h>

/*---------------------------------------------------------------------*

Name            _lsearch - searches a table

Usage           static void *near
                pascal _lsearch(const void      *key,
                                void            *base,
                                size_t          *nelem,
                                size_t          width,
                                int cdecl     (*fcmp)(const void *, const void *),
                                int             flag)

Description     performs lfind or lsearch depending on the value of flag.
                If flag is 1 it updates the table if no match, if flag
                is 0 it only searches.

Return value    Nothing

*---------------------------------------------------------------------*/
static void *near pascal _lsearch(const void    *key,
                                  register void *base,
                                  size_t        *nelem,
                                  size_t        width,
                                  int cdecl (*fcmp)(const void *, const void *),
                                  int            flag)
{
        register int    Wrk;

        for (Wrk = *nelem; Wrk > 0; Wrk--)
        {
                if (((*fcmp)(key, base)) == 0)
                        return(base);
                ((char *)base) += width;
        }
        if (flag)
        {
                (*nelem)++;
                movmem((void *)key, base, width);
        }
        else
                base = NULL;
        return(base);
}


/*--------------------------------------------------------------------------*

Name            lsearch - searches and updates a table
                lfind   - perform a linear search

Usage           void *lsearch(const void *key,
                              void *base,
                              size_t *nelem,
                              size_t width,
                              int cdecl (*fcmp)(const void *, const void *));

                void *lfind(const void *key,
                            const void *base,
                            size_t *nelem,
                            size_t width,
                            int cdecl (*fcmp)(const void *, const void *));

Prototype in    stdlib.h

Description     lfind and lsearch search  a table for information. Because
                these are linear searches, the table entries do not need to
                be sorted before a call to lfind or lsearch. If the item that
                key  points  to  is  not  in the table, lsearch appends that
                item to the table, but lfind does not.

                . key points to  the item to be searched  for. ("the search
                  key")

                . base points to the base (0th element) of the search table

                . nelem points  to an integer containing  number of entries
                  in the table.

                . width contains the number of bytes in each entry

                . fcmp  points to  a user-written  comparison routine. That
                routine compares 2  items and returns a value  based on the
                comparison.
                On each call to the comparison routine, the search function
                passes 2 arguments: key, a pointer to the item being searched
                for;  and elem,  a pointer   to the  element of  base being
                compared.
                fcmp  is free  to interpret  the search  key and  the table
                entry any way it likes.

Return value    lsearch and lfind return the  address of the first entry in
                the  table that  matches the   search key.  If no  match is
                found, lfind returns 0.

                In lsearch and lfind:

                        If the key is                   fcmp returns
                        -------------                   ------------
                        Not identical to *elem          An integer != 0
                        Identical to *elem              0

*---------------------------------------------------------------------------*/
void * _FARFUNC lsearch(const void *key, void *base, size_t *nelem, size_t width,
              int cdecl (*_FARFUNC fcmp)(const void *, const void *))
{
        return(_lsearch(key,base,nelem,width,fcmp,1));
}


/*---------------------------------------------------------------------*

Name            lfind - performs a linear search

Usage           void *lfind(void *key, void *base, size_t *nelem,
                            size_t width,
                            int (*fcmp)(const void *, const void *) );

Prototype in    stdlib.h

Description     see lsearch above

*---------------------------------------------------------------------*/
void * _FARFUNC lfind(const void *key, const void *base, size_t *nelem, size_t width,
            int cdecl (* _FARFUNC fcmp)(const void *, const void *))
{
        return(_lsearch(key,(void *)base,nelem,width,fcmp,0));
}
