/*

BeOS Rapid Integrated Environment (BRIE)

PropertiesWindowWindow by Sikosis

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

#include "brie.h"
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
	pt.y = 296;
	
	if (screenFrame.Contains(pt))
		w->MoveTo(pt);
	
	int BottomProp = (int) screenFrame.Height() - 400; // 450
	/*char tmp[250];
	sprintf(tmp,"BottomProp is %i",BottomProp);
	(new BAlert("",tmp,"debug"))->Go();*/
	w->ResizeTo(225,BottomProp);
	
}
// ---------------------------------------------------------------------------------------------------------- //


// PropertiesWindow - Constructor
PropertiesWindow::PropertiesWindow(BRect frame) : BWindow (frame, "Properties", B_TITLED_WINDOW, B_NOT_RESIZABLE , 0)
{
	ptrPropertiesWindow = this;
	InitWindow();
	TopOfScreen(this);
	Show();
}
// ---------------------------------------------------------------------------------------------------------- //


// PropertiesWindow - Destructor
PropertiesWindow::~PropertiesWindow()
{
	exit(0);
}
// ---------------------------------------------------------------------------------------------------------- //


// PropertiesWindow::InitWindow -- Initialization Commands here
void PropertiesWindow::InitWindow(void)
{
	BRect r;
	r = Bounds();
    // Add Controls
    
    lsvProperties = new BListView(BRect(6,6,r.right-6,r.bottom-6), "lsvProperties",
					  B_SINGLE_SELECTION_LIST, B_FOLLOW_LEFT | B_FOLLOW_TOP,
					  B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS);

	// Add the Drawing View
	AddChild(ptrPropertiesWindowView = new PropertiesWindowView(r));
	ptrPropertiesWindowView->AddChild(lsvProperties);
	
	if (ProjectName.Length() == 0)
	{
		ProjectName.SetTo("Untitled");
	}
	ShowProperties("Window",ProjectName.String());
}
// ---------------------------------------------------------------------------------------------------------- //


void PropertiesWindow::ShowProperties(BString currentobject, BString objectname)
{	
	// Clear the Properties List
	Lock();
	lsvProperties->MakeEmpty();
	Unlock();
	
	// Check for New Properties to Show
	if (strcmp(currentobject.String(),"Window") != 1) {
		/*BWindow(BRect frame, 
		      const char *title, 
    		  window_look look, 
		      window_feel feel, 
    		  uint32 flags, 
		      uint32 workspace = B_CURRENT_WORKSPACE) */
		AddPropertyItem("Object Name",objectname.String());
		AddPropertyItem("Left","0");
		AddPropertyItem("Top","0");
		AddPropertyItem("Right","0");
		AddPropertyItem("Bottom","0");
		AddPropertyItem("Title",objectname.String());
	} else {
		AddPropertyItem("No Properties","");
	}

	/*switch (currentobject.String()) {
		case "Window":
			{
			// Window Properties are :-
			
			}
			break;
	}*/
}
// ---------------------------------------------------------------------------------------------------------- //


// PropertiesWindow::AddPropertyItem
void PropertiesWindow::AddPropertyItem(BString propname, BString propvalue)
{
	int32 newselection;
	BString tmp;
	Lock();
	lsvProperties->DeselectAll();
	//tmp.Prepend(" ");
	// this is the temporary look for the listitem
	tmp.SetTo(propname.String());
	tmp.Append(": ");
	tmp.Append(propvalue.String());
	printf("AddPropertyItem - %s\n\n",tmp.String()); // debug
	lsvProperties->AddItem(new BStringItem(tmp.String()));
	newselection = lsvProperties->CountItems() - 1;
	lsvProperties->Select(newselection,true);
	Unlock();
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
