/*

BeOS Rapid Integrated Environment (BRIE)

BRIEWindows Header by Sikosis

Released under the MIT license.

(C) 2002 http://brie.sf.net/

*/

#ifndef __BRIEWINDOWS_H__
#define __BRIEWINDOWS_H__

#include "BRIEViews.h"
#include "URLView.h"

class FileWindowView; 
class ProjectWindowView;
class PropertiesWindowView;
class ToolboxWindowView;
class NewProjectWindowView;
class AboutWindowView;
class BRIEIconView;

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
	    
	private:
		void InitWindow(void);
	    FileWindowView* aFileWindowView;
	    BMenuBar  *menubar;
	    AboutWindow         *aboutWindow;
};

class ProjectWindow : public BWindow
{
	public:
    	ProjectWindow(BRect frame);
	    ~ProjectWindow();
    	virtual bool QuitRequested();
	    virtual void MessageReceived(BMessage *message);
	    
	private:
		void InitWindow(void);
	    ProjectWindowView* aProjectWindowView;
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
	    PropertiesWindowView* aPropertiesWindowView;
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
	    ToolboxWindowView* aToolboxWindowView;
};

class NewProjectWindow : public BWindow
{
	public:
    	NewProjectWindow(BRect frame);
	    ~NewProjectWindow();
    	virtual bool QuitRequested();
	    virtual void MessageReceived(BMessage *message);
	    
	private:
		void InitWindow(void);
	    NewProjectWindowView* aNewProjectWindowView;
};


#endif
