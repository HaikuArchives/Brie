/*

BeOS Rapid Integrated Environment (BRIE)

PropertiesWindow Header by Sikosis

Released under the MIT license.

(C) 2002 http://brie.sf.net/

*/

#ifndef __PROPERTIESWINDOW_H__
#define __PROPERTIESWINDOW_H__

class PropertiesWindowView; 

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

#endif
