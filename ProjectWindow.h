/*

BeOS Rapid Integrated Environment (BRIE)

ProjectWindow Header by Sikosis

Released under the MIT license.

(C) 2002 http://brie.sf.net/

*/

#ifndef __PROJECTWINDOW_H__
#define __PROJECTWINDOW_H__

class ProjectWindowView; 

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

#endif
