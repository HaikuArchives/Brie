/*

BeOS Rapid Integrated Environment (BRIE)

BRIEWindows Header by Sikosis

Released under the MIT license.

(C) 2002-2003 http://brie.sf.net/

*/

#ifndef __BRIEWINDOWS_H__
#define __BRIEWINDOWS_H__

//#include "brie.h"
#include "BRIEViews.h"
#include "URLView.h"
//#include "brieconstants.h"

class BPictureButton;
class FileWindowView; 
class ProjectWindowView;
class PropertiesWindowView;
class ToolboxWindowView;
class NewProjectWindowView;
class AboutWindowView;
class BRIEIconView;
class HelpTipView;


class ProjectWindow : public BWindow
{
	public:
    	ProjectWindow(BRect frame);
	    ~ProjectWindow();
    	virtual bool QuitRequested();
	    virtual void MessageReceived(BMessage *message);
	    
	    //void SetProjectTitle(const char *title);
	    BStringView        *stvProjectName;
	private:
		
		void InitWindow(void);
	    ProjectWindowView* ptrProjectWindowView;
};


class AboutWindow : public BWindow
{
	public:
		AboutWindow(BRect frame);
		~AboutWindow();
		virtual void MessageReceived(BMessage *message);
	private:
		void InitWindow(void);
	    AboutWindowView*   ptrAboutWindowView;
	    BRIEIconView*      ptrBRIEIconView;
	    BButton            *btnOkay;
	    URLView			   *urlWebSite;
	    URLView			   *urlEmail;
	    URLView			   *urlVersion;
	    URLView            *urlMDR;
	    BStringView        *stvVersion;
	    BStringView        *stvEmail;
	    BStringView        *stvEmail2;
	    BStringView        *stvAppName;
	    BStringView	       *stvDescription;
	    BStringView	       *stvDescription2;
	    BStringView	       *stvDescription3;
	    BStringView	       *stvDescription4;	    
	    BStringView	       *stvDescription5;	
	    BStringView		   *stvDescription6;
};


class FileWindow : public BWindow
{
	public:
    	FileWindow(BRect frame);
	    ~FileWindow();
    	virtual bool QuitRequested();
	    virtual void MessageReceived(BMessage *message);
	    void SaveProject(const char *prjname, const char *prjpath, const char *prjauthor);
	    void GetCurrentPath(void);
	private:
		void InitWindow(void);
	    void CompileGCC(const char *prjname, const char *prjpath, const char *prjauthor);
	    void CreateMakeFile(const char *prjname, const char *prjpath, const char *prjauthor);
	    void SetProject(const char *prjname);
	    
	    FileWindowView* 	ptrFileWindowView;
		
	    FileWindow*			ptrFileWindow;
	    
	    BMenuBar  			*menubar;
	    AboutWindow         *aboutWindow;
	    BPictureButton      *btnNewProject;
	    BPictureButton      *btnLoadProject;
	    BPictureButton      *btnSaveProject;
	    BPictureButton      *btnSaveAsProject;
	    BPictureButton      *btnPrintProject;
	    BFilePanel			*BrowsePanel;
};


class NewProjectWindow : public BWindow
{
	public:
    	NewProjectWindow(BRect frame);
	    ~NewProjectWindow();
	    virtual void MessageReceived(BMessage *message);
	    void ShowTracker(char apath[256],char AppName[256]);
	private:
		void InitWindow(void);
		void CreateNewProject(void);
		void CreateExistingProject(void);
	    NewProjectWindowView*		ptrNewProjectWindowView;
	    	    
	    BButton         		    *btnAdd;  // alias Create
	    BButton         		    *btnCancel;
	    BTextControl                *txtNewProject;
	    BTextControl                *txtAuthor;
	    BMessage					*msg;
};


class PropertiesWindow : public BWindow
{
	public:
    	PropertiesWindow(BRect frame);
	    ~PropertiesWindow();
    	virtual bool QuitRequested();
	    virtual void MessageReceived(BMessage *message);
	private:
		void InitWindow(void);
	    PropertiesWindowView* ptrPropertiesWindowView;
};


class ToolboxWindow : public BWindow
{
	public:
    	ToolboxWindow(BRect frame);
	    ~ToolboxWindow();
    	virtual bool QuitRequested();
	    virtual void MessageReceived(BMessage *message);
	private:
		void InitWindow(void);
	    ToolboxWindowView* ptrToolboxWindowView;
};


class HelpTipWindow : public BWindow
{
	public:
		HelpTipWindow(BRect frame);
		~HelpTipWindow();
		virtual bool QuitRequested();
		virtual void MessageReceived(BMessage *message);
	private:
		void SaveTipSettings(void);
		void InitWindow(void);
		HelpTipView*	ptrHelpTipView;
		
		BButton			*btnOkay;
	    BStringView		*stvTipTitle;
	    BStringView     *stvTipText;
	    BStringView     *stvTipText2;
	    BCheckBox		*chkDontShowAgain;
};

#endif
