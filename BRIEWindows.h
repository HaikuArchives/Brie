/*

BeOS Rapid Integrated Environment (BRIE)

BRIEWindows Header by Sikosis

Released under the MIT license.

(C) 2002 http://brie.sf.net/

*/

#ifndef __BRIEWINDOWS_H__
#define __BRIEWINDOWS_H__

class FileWindowView; 
class ProjectWindowView;
class PropertiesWindowView;
class ToolboxWindowView;
class NewProjectWindowView;

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
