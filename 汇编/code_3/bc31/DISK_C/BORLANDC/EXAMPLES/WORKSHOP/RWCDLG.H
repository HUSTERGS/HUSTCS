// (C) Copyright 1991, 1992 by Borland International

#define fsPathName 80
#define fsExtension 3
#define fsFileSpec fsPathName+fsExtension

class TDialog
{
public:
	HWND hWindow;
	DLGPROC dialogFunc;
        const char far *name;

	TDialog(int DlgName);
	~TDialog();
	virtual BOOL setupDialog() { return TRUE;}
	virtual void retrieveInfo() {};
	virtual int doCommands(int Command, HWND hWndSource, UINT Notification);
	virtual int canClose() {return 1;};
};


class TFileNew : public TDialog
{
public:
  int *fileType;
  TFileNew(int *aFileType) : TDialog(dlg_FileNew) { fileType = aFileType;};
  int canClose();
  BOOL setupDialog();
};

class TFileOpen : public TDialog
{
public:
	char *filePath;
	char pathName[fsPathName + 1];
	char extension[fsExtension + 1];
	char fileSpec[fsFileSpec + 1];
	int *fileType;

	TFileOpen(int *aType, char *aFilePath);
	~TFileOpen() {};
	int canClose();
	int hasWildCards(char *aFilePath) { return strchr(aFilePath, '*') || strchr(aFilePath, '?');};
	char *getExtension(char *aFilePath);
	char *getFileName(char *aFilePath);
	char *getFileFirst(char *aFilePath);
	BOOL setupDialog();
	int doCommands(int Command, HWND hWndSource, UINT Notification);
	void selectFileName();
	void updateFileName();
	void updateButtons();
	int updateListBoxes();
};
