/*-------------------------------------------------------*/
/*                                                       */
/*   Turbo Vision 1.0                                    */
/*   Turbo Vision Forms Demo                             */
/*   Copyright (c) 1991 by Borland International         */
/*                                                       */
/*   Listdlg.h: Header file for Listdlg.cpp              */
/*              (Support header file for TVFORMS Demo)   */
/*-------------------------------------------------------*/

#if !defined( __LISTDLG_H )
#define __LISTDLG_H

#define Uses_TSortedListBox
#define Uses_TRect
#define Uses_TScrollBar
#define Uses_TDialog
#define Uses_TResourceFile
#include <tv.h>

#if !defined( __DATACOLL_H )
#include "datacoll.h"
#endif  __DATACOLL_H

#if !defined( __FORMS_H )
#include "forms.h"
#endif  __FORMS_H


typedef char * (*ExpandFunc)(char *);

class TListKeyBox :  public TSortedListBox
{

public:
    
    TListKeyBox( const TRect&, ushort, TScrollBar *);

    virtual void getText( char *, short, short );
};


class TListDialog :  public TDialog
{

public:

    TListDialog( char *, char * );
    ~TListDialog(void);

    virtual void close();
    void deleteSelection();
    TForm *editingForm();
    void formOpen( Boolean );
    virtual void handleEvent( TEvent& );
    Boolean openDataFile( char *, TResourceFile *&, int );
    Boolean saveList();
    Boolean saveForm(TDialog *);
    void stackOnPrev(TDialog *);
    virtual Boolean valid( ushort );


    TDataCollection *dataCollection;
    char *fileName;
    TResourceFile *formDataFile;
    Boolean isValid;
    TListKeyBox *list;
    Boolean modified;
};

#endif  // __LISTDLG_H
