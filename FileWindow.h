/*

BeOS Rapid Integrated Environment (BRIE)

FileWindow Header by Sikosis

Released under the MIT license.

(C) 2002 http://brie.sf.net/

*/

#ifndef __FILEWINDOW_H__
#define __FILEWINDOW_H__

class FileWindowView; 

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

#endif
