/*

BeOS Rapid Integrated Environment (BRIE)

ProjectWindow by Sikosis

Released under the MIT license.

(C) 2002-2003 http://brie.sf.net/

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
#include <StringView.h>
#include <StatusBar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TextControl.h>
#include <Window.h>
#include <View.h>

//#include "brie.h"
//#include "brieconstants.h"
#include "BRIEWindows.h"
#include "BRIEViews.h"

// Constants ------------------------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------- //

// TopOfScreen -- Places the BWindow starting from the top of the Current Screen
static void TopOfScreen(BWindow* w)
{
	BRect	screenFrame = (BScreen(B_MAIN_SCREEN_ID).Frame());
	BPoint 	pt;
	pt.x = screenFrame.Width() - 350;
	pt.y = 110;

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
// ---------------------------------------------------------------------------------------------------------- //


// ProjectWindow - Destructor
ProjectWindow::~ProjectWindow()
{
	exit(0);
}
// ---------------------------------------------------------------------------------------------------------- //


// ProjectWindow::InitWindow -- Initialization Commands here
void ProjectWindow::InitWindow(void)
{
	BRect r;
	r = Bounds();
	r.top = 20;
	int LeftMargin = 6;
	float RightMargin = r.right;
	int TopMargin = 6;
	
    // Add Controls
    stvProjectName = new BStringView(BRect(LeftMargin, TopMargin, RightMargin, TopMargin+10), "Project Name", "Untitled");
    
	// Add the Drawing View
	AddChild(ptrProjectWindowView = new ProjectWindowView(r));
	AddChild(stvProjectName);
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


//void ProjectWindow::SetProjectTitle(char title[256])
void ProjectWindow::SetProjectTitle(const char *title)
{
	//(new BAlert("",title,"debug"))->Go(); // debug
	printf("%p\n", stvProjectName->Text());
	//stvProjectName->SetText("test"); // segment violated :(
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
