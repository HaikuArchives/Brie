/*

BeOS Rapid Integrated Environment (BRIE)

ToolboxWindow by Sikosis

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
	pt.x = 5;
	pt.y = 110;

	if (screenFrame.Contains(pt))
		w->MoveTo(pt);
	
	int BottomToolbox = (int) screenFrame.Height() - 314;
	w->ResizeTo(w->Bounds().Width(),BottomToolbox);
}
// ---------------------------------------------------------------------------------------------------------- //


// ToolboxWindow - Constructor
ToolboxWindow::ToolboxWindow(BRect frame) : BWindow (frame, "Toolbox", B_TITLED_WINDOW, B_NOT_RESIZABLE , 0)
{
	InitWindow();
	TopOfScreen(this);
	Show();
}


// ToolboxWindow - Destructor
ToolboxWindow::~ToolboxWindow()
{
	exit(0);
}


// ToolboxWindow::InitWindow -- Initialization Commands here
void ToolboxWindow::InitWindow(void)
{
	BRect r;
	r = Bounds();
    // Add Controls
    
	// Add the Drawing View
	AddChild(ptrToolboxWindowView = new ToolboxWindowView(r));
}
// ---------------------------------------------------------------------------------------------------------- //


// ToolboxWindow::QuitRequested -- Post a message to the app to quit
bool ToolboxWindow::QuitRequested()
{
   //be_app->PostMessage(B_QUIT_REQUESTED);
   return true;
}
// ---------------------------------------------------------------------------------------------------------- //


// ToolboxWindow::MessageReceived -- receives messages
void ToolboxWindow::MessageReceived (BMessage *message)
{
	switch(message->what)
	{
		default:
			BWindow::MessageReceived(message);
			break;
	}
}
// ---------------------------------------------------------------------------------------------------------- //
