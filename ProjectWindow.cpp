/*

BeOS Rapid Integrated Environment (BRIE)

ProjectWindow by Sikosis

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
	//pt.x = 450; //screenFrame.Width()/2 - w->Bounds().Width()/2;
	pt.y = 110; //screenFrame.Height()/2 - w->Bounds().Height()/2;

	if (screenFrame.Contains(pt))
		w->MoveTo(pt);

}
// ---------------------------------------------------------------------------------------------------------- //


// ProjectWindow - Constructor
ProjectWindow::ProjectWindow(BRect frame) : BWindow (frame, "Project Window", B_TITLED_WINDOW, B_NOT_RESIZABLE , 0)
{
	InitWindow();
	TopOfScreen(this);
	Show();
}


// ProjectWindow - Destructor
ProjectWindow::~ProjectWindow()
{
	//delete browsePanel;
	exit(0);
}


// ProjectWindow::InitWindow -- Initialization Commands here
void ProjectWindow::InitWindow(void)
{
	BRect r;
	r = Bounds();
	
	r.top = 20;
	
    // Add Controls
    
	// Add the Drawing View
	AddChild(aProjectWindowView = new ProjectWindowView(r));
}
// ---------------------------------------------------------------------------------------------------------- //


// ProjectWindow::QuitRequested -- Post a message to the app to quit
bool ProjectWindow::QuitRequested()
{
   //be_app->PostMessage(B_QUIT_REQUESTED);
   Minimize(true);
   Hide(); 
   return true;
}
// ---------------------------------------------------------------------------------------------------------- //


// ProjectWindow::MessageReceived -- receives messages
void ProjectWindow::MessageReceived (BMessage *message)
{
	switch(message->what)
	{
		default:
			BWindow::MessageReceived(message);
			break;
	}
}
// ---------------------------------------------------------------------------------------------------------- //
