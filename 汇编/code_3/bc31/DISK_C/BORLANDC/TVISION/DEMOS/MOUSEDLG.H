/*---------------------------------------------------------*/
/*                                                         */
/*   Turbo Vision 1.0                                      */
/*   Copyright (c) 1991 by Borland International           */
/*                                                         */
/*   Mousedlg.h : Header file for mousedlg.cpp             */
/*---------------------------------------------------------*/

class TClickTester : public TStaticText
{

public:

    TClickTester(TRect& r, char *aText);
    virtual TPalette& getPalette() const;
    virtual void handleEvent(TEvent& event);
    virtual void draw();

private:

    char clicked;

};


class TMouseDialog : public TDialog
{

public:

    TMouseDialog();
    virtual void handleEvent(TEvent& event);

private:

    TScrollBar *mouseScrollBar;
    int oldDelay;

};
