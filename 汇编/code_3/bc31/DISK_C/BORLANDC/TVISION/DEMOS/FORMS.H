/*-------------------------------------------------------*/
/*                                                       */
/*   Turbo Vision 1.0                                    */
/*   Turbo Vision Forms Demo                             */
/*   Copyright (c) 1991 by Borland International         */
/*                                                       */
/*   Forms.h: Header file for Forms.cpp                  */
/*            (Support header file for TVFORMS Demo)     */
/*-------------------------------------------------------*/

#if !defined( __FORMS_H )
#define __FORMS_H

#define Uses_TStreamable
#define Uses_TEvent
#define Uses_TRect
#define Uses_TDialog
#define Uses_TView
#include <tv.h>

class TForm : public TDialog
{

public:

    TForm( StreamableInit ) : TDialog (streamableInit), TWindowInit(&TForm::initFrame) {};
    TForm( const TRect&, const char* );
	virtual Boolean changed();
	virtual void handleEvent( TEvent& );
    virtual Boolean valid( ushort );

    TView *listDialog;
    void *prevData;
    ushort keyWidth;

private:

    virtual const char *streamableName() const
        { return name; }

protected:

    virtual void write( opstream& );
    virtual void *read( ipstream& );

public:

    static const char * const name;
    static TStreamable *build();

};

inline ipstream& operator >> ( ipstream& is, TForm& cl )
    { return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TForm*& cl )
    { return is >> (void *&)cl; }
inline opstream& operator << ( opstream& os, TForm& cl )
    { return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TForm* cl )
    { return os << (TStreamable *)cl; }


#endif  // __FORMS_H
