/*

BeOS Rapid Integrated Environment (BRIE)

PropertiesWindowWindow by Sikosis

Released under the MIT license.

(C) 2002 http://brie.sf.net/

*/


// Includes -------------------------------------------------------------------------------------------------- //
#include <Alert.h>
#include <Application.h>
#include <Button.h>
#include <Entry.h>
#include <File.h>
#include <FilePanel.h>
#include <ListView.h>
#include <MenuBar.h>
#include <Menu.h> 
#include <MenuItem.h>
#include <Path.h>
#include <Screen.h>
#include <ScrollView.h>
#include <StatusBar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TextControl.h>
#include <Window.h>
#include <View.h>

#include "BRIEWindows.h"
#include "BRIEViews.h"
#include "brieconstants.h"

// Constants ------------------------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------- //

// TopOfScreen -- Places the BWindow starting from the top of the Current Screen
static void TopOfScreen(BWindow* w)
{
	BRect	screenFrame = (BScreen(B_MAIN_SCREEN_ID).Frame());
	BPoint 	pt;
	pt.x = screenFrame.Width() - 350;
	pt.y = 246;
	
	if (screenFrame.Contains(pt))
		w->MoveTo(pt);
	
	int BottomProp = (int) screenFrame.Height() - 450;
	/*char tmp[250];
	sprintf(tmp,"BottomProp is %i",BottomProp);
	(new BAlert("",tmp,"debug"))->Go();*/
	w->ResizeTo(225,BottomProp);
	
}
// ---------------------------------------------------------------------------------------------------------- //


// PropertiesWindow - Constructor
PropertiesWindow::PropertiesWindow(BRect frame) : BWindow (frame, "Properties", B_TITLED_WINDOW, B_NOT_RESIZABLE , 0)
{
	InitWindow();
	TopOfScreen(this);
	Show();
}


// PropertiesWindow - Destructor
PropertiesWindow::~PropertiesWindow()
{
	exit(0);
}


// PropertiesWindow::InitWindow -- Initialization Commands here
void PropertiesWindow::InitWindow(void)
{
	BRect r;
	r = Bounds();

    // Add Controls
    
	// Add the Drawing View
	AddChild(aPropertiesWindowView = new PropertiesWindowView(r));
}
// ---------------------------------------------------------------------------------------------------------- //


// PropertiesWindow::QuitRequested -- Post a message to the app to quit
bool PropertiesWindow::QuitRequested()
{
   //be_app->PostMessage(B_QUIT_REQUESTED);
   return true;
}
// ---------------------------------------------------------------------------------------------------------- //


// PropertiesWindow::MessageReceived -- receives messages
void PropertiesWindow::MessageReceived (BMessage *message)
{
	switch(message->what)
	{
		default:
			BWindow::MessageReceived(message);
			break;
	}
}
// ---------------------------------------------------------------------------------------------------------- //
