/*

BRIE Header by Sikosis

Released under the MIT license.

(C) 2002-2003 http://brie.gravity24hr.com/

*/

#ifndef __BRIE_H__
#define __BRIE_H__

#include "BRIEWindows.h"

extern const char *APP_SIGNATURE;

class BRIE : public BApplication
{
	public:
    	BRIE();
	    virtual void MessageReceived(BMessage *message);
	    virtual void ReadyToRun (void);
	    virtual void RefsReceived (BMessage *message);
	private:
	    FileWindow			*fileWindow;
		ProjectWindow		*projectWindow;
		ToolboxWindow		*toolboxWindow;
		PropertiesWindow	*propertiesWindow;
};

#endif