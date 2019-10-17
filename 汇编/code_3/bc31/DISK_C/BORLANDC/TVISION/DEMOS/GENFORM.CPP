/*------------------------------------------------------------------*/
/*                                                                  */
/*   Turbo Vision 1.0                                               */
/*   Turbo Vision Forms Demo                                        */
/*   Copyright (c) 1991 by Borland International                    */
/*                                                                  */
/*------------------------------------------------------------------*/
/*                                                                  */
/*    This program uses GENPHONE.H and GENPARTS.H to generate forms */
/*  data files which are used by the TVFORMS demo program. Use      */
/*  GENFORMS.MAK to create data files for TVFORMS demo.             */
/*------------------------------------------------------------------*/

#define Uses_fpstream
#define Uses_TResourceFile
#include <tv.h>
__link ( RResourceCollection )

#if defined( PHONENUM )
#include "genphone.h"
#elif defined( PARTS )
#include "genparts.h"
#else
#error Specify PHONENUM or PARTS as a conditional define, compile and then run.
#endif

#if !defined( __FORMS_H )
#include "forms.h"
#endif  // __FORMS_H

#if !defined( __STDLIB_H )
#include <stdlib.h>
#endif  // __STDLIB_H

int main(void)
{
    TSortedCollection *collection;
    int i;
    TForm *f;
    void *p;
    fpstream *s;
    TResourceFile* r;

    cout <<"Creating  " << rezFileName << "\n";

    // Construct stream and resource
    s = new fpstream (rezFileName, ios::out|ios::binary);
    r = new TResourceFile(s);

    // Form
    f = makeForm();
    r->put(f, "FormDialog");

    // Data
    collection = new TDataCollection((dataCount + 10), 5, sizeof(TDataRec),
                          dataKeyType);
    collection->duplicates = allowDuplicates;
    for(i = 0; i < dataCount; ++i)
        {
        p = new TDataRec;
        f->setData((void *)&data[i]);      // move into object
        f->getData(p);                     // move onto heap
        collection->insert(p);             // insert in sorted order
        }
    r->put(collection, "FormData");

    // Done
    TObject::destroy(f);
    TObject::destroy((TCollection *)collection);
    TObject::destroy(r);
    return 0;
}
