/*

BeOS Rapid Integrated Environment (BRIE)

BRIEWindows Header by Sikosis

Released under the MIT license.

(C) 2002-2003 http://brie.sf.net/

*/

#ifndef __BRIEWINDOWS_H__
#define __BRIEWINDOWS_H__

#include "BRIEViews.h"
#include "URLView.h"

class BPictureButton;

class FileWindowView; 
class ProjectWindowView;
class PropertiesWindowView;
class ToolboxWindowView;
class NewProjectWindowView;
class AboutWindowView;
class BRIEIconView;

class ProjectWindow : public BWindow
{
	public:
    	ProjectWindow(BRect frame);
	    ~ProjectWindow();
    	virtual bool QuitRequested();
	    virtual void MessageReceived(BMessage *message);
	    void SetProjectTitle(const char *title);
	private:
		BStringView *stvProjectName;
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
	    void SetProject(const char *projectname, const char *shortprojectname);
	private:
		void InitWindow(void);
	    FileWindowView* 	ptrFileWindowView;
	    FileWindow*			ptrFileWindow;
	    BMenuBar  			*menubar;
	    AboutWindow         *aboutWindow;
	    BPictureButton      *btnNewProject;
};


class NewProjectWindow : public BWindow
{
	public:
    	NewProjectWindow(BRect frame);
	    ~NewProjectWindow();
	    virtual void MessageReceived(BMessage *message);
	    
	private:
		void InitWindow(void);
		void CreateNewProject(void);
	    NewProjectWindowView*		ptrNewProjectWindowView;
	    FileWindow*					ptrFileWindow;
	    ProjectWindow*				ptrProjectWindow;
	    	    
	    BButton         		    *btnAdd;
	    BButton         		    *btnCancel;
	    BTextControl                *txtNewProject;
	    BTextControl                *txtAuthor;
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

#endif
