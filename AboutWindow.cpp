/*

BRIE - AboutWindow by Sikosis

Released under the MIT license.

(C)2002-2004

*/

// Includes -------------------------------------------------------------------------------------------------- //
#include <Alert.h>
#include <Application.h>
#include <Bitmap.h>
#include <Button.h>
#include <Font.h>
#include <Roster.h>
#include <Screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <StringView.h>
#include <TextControl.h>
#include <Window.h>
#include <View.h>

#include "AboutConstants.h"
#include "BRIEWindows.h"
#include "BRIEViews.h"
// ---------------------------------------------------------------------------------------------------------- //

// CenterWindowOnScreen -- Centers the BWindow to the Current Screen
static void CenterWindowOnScreen(BWindow* w)
{
	BRect	screenFrame = (BScreen(B_MAIN_SCREEN_ID).Frame());
	BPoint 	pt;
	pt.x = screenFrame.Width()/2 - w->Bounds().Width()/2;
	pt.y = screenFrame.Height()/2 - w->Bounds().Height()/2;

	if (screenFrame.Contains(pt))
		w->MoveTo(pt);
}
// ---------------------------------------------------------------------------------------------------------- //


// AboutWindow - Constructor
AboutWindow::AboutWindow(BRect frame) : BWindow (frame, "About BRIE ...", B_FLOATING_WINDOW , B_FLOATING_APP_WINDOW_FEEL , 0)
{
	InitWindow();
	CenterWindowOnScreen(this);
	Show();
}
// ---------------------------------------------------------------------------------------------------------- //


// AboutWindow::InitWindow
void AboutWindow::InitWindow(void)
{	
	BRect r;
	r = Bounds(); // the whole view
	
	AddChild(ptrAboutWindowView = new AboutWindowView(r));
}
// ---------------------------------------------------------------------------------------------------------- //


// AboutWindow::MessageReceived -- receives messages
void AboutWindow::MessageReceived (BMessage *message)
{
	switch(message->what)
	{
		case URL_CLICKED:
			{
				int  result;
				char *the_url = "http://brie.sf.net/";
				result = be_roster->Launch(URL_TYPE, 1, &the_url);
			}
			break;
		case BTN_OKAY:
			Hide(); // change later if necessary
			break;
		default:
			BWindow::MessageReceived(message);
			break;
	}
}
// ---------------------------------------------------------------------------------------------------------- //