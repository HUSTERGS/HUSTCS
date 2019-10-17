// (C) Copyright 1991, 1992 by Borland International

#include <string.h>
#include <stdlib.h>

class TMDIChildWindow
{
public:
	HWND hWindow;
	HMENU theMenu;
	char *title;
	virtual char *className() const {return "TMDIChildWindow";};
	TMDIChildWindow(char *aTitle);
	virtual ~TMDIChildWindow();
	virtual void create() {};
	virtual char *getPopupTitle() { return NULL; };
	virtual HMENU getPopupMenu() {return 0; };
	virtual void getWindowClass(WNDCLASS *wndClass);
	virtual void lButtonDown(WORD, LONG) {};
	virtual void lButtonUp(WORD, LONG) {};
	virtual void mouseMove(WORD, LONG) {};
	virtual void rButtonDown(LONG);
	virtual void paint(HDC , PAINTSTRUCT *) {};
	void registerWnd();
	virtual void setFocus() {};
	virtual void size(WORD, LONG) {};
};

class  TDocument : public TMDIChildWindow
{
public:
	char *fileName;
	BOOL isNewFile;
	BOOL changed;
	TDocument(char *aFileName);
	~TDocument();
	virtual BOOL canClear();
	virtual void clearWindow() {};
	void clearModify() {};
	virtual BOOL isModified() {return changed;};
	virtual void newFile();
	virtual void read() {};
	void setFileName(char *aFileName);
	virtual BOOL save();
	virtual BOOL saveAs() {return 1;};
	virtual void write() {};
};

class TEditWindow : public TDocument
{
public:
	HWND editor;
	TEditWindow(char *AFilename);
	~TEditWindow(){};
	void create();
	void size(WORD, LONG);
	void setFocus();
	void read(){};
	void write(){};
	BOOL isModified(){return 0;};
	void clearWindow(){};
	void clearModify(){};
	void doSearch(){};
};

class TDragWindow : public TMDIChildWindow
{
public:
	HDC dragDC;
	int buttonDown;
	TDragWindow(char *aTitle) : TMDIChildWindow(aTitle) { buttonDown = 0; };
	~TDragWindow() {};
	void lButtonDown(WORD, LONG);
	void lButtonUp(WORD, LONG);
};

class TScribbleWindow: public TDragWindow
{
public:
	TScribbleWindow(char *aTitle) : TDragWindow(aTitle) {};
	void lButtonDown(WORD wParam, LONG lParam);
	void lButtonUp(WORD wParam, LONG lParam);
	void mouseMove(WORD, LONG lParam);
	char *getPopupTitle() { return "Scribble"; };
	HMENU getPopupMenu();
};

class TGraphObject
{
public:
	int x1, y1, x2, y2;
	TGraphObject(RECT *r) { Assign(r); };
	virtual void Draw(HDC){};
	void DrawRect(HDC HandleDC, RECT R);
	void Assign(RECT *R) {x1 = R->left;x2 = R->right;y1 = R->top;y2 = R->bottom;};
};

class TRectangle : public TGraphObject
{
public:
	TRectangle(RECT *r) :
		TGraphObject(r) {};
	virtual void Draw(HDC HandleDC) { Rectangle(HandleDC, x1, y1, x2, y2);};
};

class TShapeWindow: public TDragWindow
{
	TGraphObject *currentShape;
	int x, y;
	int oldRop;
	RECT R;

public:
	TShapeWindow(char *aTitle) : TDragWindow(aTitle) {};
	char *getPopupTitle() { return "Graphics"; };
	HMENU getPopupMenu();
	void lButtonDown(WORD wParam, LONG lParam);
	void lButtonUp(WORD wParam, LONG lParam);
	void mouseMove(WORD, LONG lParam);

};

LRESULT CALLBACK _export WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
