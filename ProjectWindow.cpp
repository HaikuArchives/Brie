/*

BeOS Rapid Integrated Environment (BRIE)

ProjectWindow by Sikosis

Released under the MIT license.

(C) 2002-2003 http://brie.sf.net/

*/


// Includes -------------------------------------------------------------------------------------------------- //
#include <Application.h>
#include <Bitmap.h>
#include <ListView.h>
#include <MenuBar.h>
#include <Menu.h> 
#include <MenuItem.h>
#include <Message.h>
#include <Picture.h>
#include <PictureButton.h>
#include <Screen.h>
#include <StringView.h>
#include <ScrollView.h>
#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <Window.h>
#include <View.h>

// Toolbar
#include "Bitmaps-Project-Toolbar.h"

#include "brie.h"
#include "BRIEWindows.h"
#include "BRIEViews.h"
#include "brieconstants.h"

// ---------------------------------------------------------------------------------------------------------- //
const uint32 TOOLBAR_BTN_ADD_FILE_TO_PROJECT = 'tbaf';
const uint32 TOOLBAR_BTN_REMOVE_FILE_FROM_PROJECT = 'tbrf';


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
	// Set ProjectWindow Pointer
	ptrProjectWindow = this;
	InitWindow();
	TopOfScreen(this);
	Show();
}
// ---------------------------------------------------------------------------------------------------------- //


// ProjectWindow - Destructor
ProjectWindow::~ProjectWindow()
{
	//exit(0);
}
// ---------------------------------------------------------------------------------------------------------- //


// ProjectWindow::InitWindow -- Initialization Commands here
void ProjectWindow::InitWindow(void)
{
	BRect r;
	r = Bounds();
	int LeftMargin = 6;
	float RightMargin = r.right;
	int TopMargin = 11;
	
    // Add Controls
    stvProjectName = new BStringView(BRect(LeftMargin+1, TopMargin, RightMargin, TopMargin+10), "Project Name", "Untitled");
    
    // Toolbar to Add / Remove Project Files
    int ToolbarButtonMargin = 167;
    int ToolbarButtonWidth = 24;
    int ButtonGap = 4;
	
	// New Project Button
  	BRect BitmapFrame (BRect(0,0,23,23));
  	BPicture *tmpBPicture;
  	BPicture *tmpBPicture2;
  	BView    *tmpBPictureView = new BView(BitmapFrame, "tmpBPictureView",B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
  	rgb_color toolbar_button_background = { 255, 255, 255, 0 };
  	
  	AddChild(tmpBPictureView);
  	
  	BBitmap *addfilestoprojectpicture = new BBitmap(BitmapFrame,B_RGB32);
	addfilestoprojectpicture->SetBits(projectplusicon,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(addfilestoprojectpicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *addfilestoprojectpicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	addfilestoprojectpicture_state2->SetBits(projectplusiconinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(addfilestoprojectpicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnAddFileToProjectList = new BPictureButton(BRect (ToolbarButtonMargin,3,ToolbarButtonMargin+ToolbarButtonWidth,26),
 							  "New Project",tmpBPicture,tmpBPicture2, new BMessage(TOOLBAR_BTN_ADD_FILE_TO_PROJECT),B_ONE_STATE_BUTTON, B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
 	
	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
	ToolbarButtonMargin = ToolbarButtonMargin + ToolbarButtonWidth + ButtonGap;
    
    // Remove File from Project
    BBitmap *removefilesfromprojectpicture = new BBitmap(BitmapFrame,B_RGB32);
	removefilesfromprojectpicture->SetBits(projectremoveicon,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(removefilesfromprojectpicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *removefilesfromprojectpicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	removefilesfromprojectpicture_state2->SetBits(projectremoveiconinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(removefilesfromprojectpicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnRemoveFileFromProjectList = new BPictureButton(BRect (ToolbarButtonMargin,3,ToolbarButtonMargin+ToolbarButtonWidth,26),
 							  "Remove Files",tmpBPicture,tmpBPicture2, new BMessage(TOOLBAR_BTN_REMOVE_FILE_FROM_PROJECT),B_ONE_STATE_BUTTON, B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
 	
	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
	ToolbarButtonMargin = ToolbarButtonMargin + ToolbarButtonWidth + ButtonGap;
    
       
    lsvProjectFiles = new BListView(BRect(6,29,r.right-6,r.bottom-6), "ltvProjectFiles",
					  B_SINGLE_SELECTION_LIST, B_FOLLOW_LEFT | B_FOLLOW_TOP,
					  B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS);

    AddChild(btnRemoveFileFromProjectList);
    AddChild(btnAddFileToProjectList);
    AddChild(stvProjectName);

    // Add the Drawing View
    ptrProjectWindowView = new ProjectWindowView(r);
    ptrProjectWindowView->AddChild(lsvProjectFiles);
    //ptrProjectWindowView->AddChild(new BScrollView("ScrollViewProjectFiles",lsvProjectFiles, B_FOLLOW_LEFT | B_FOLLOW_TOP, 0, true, false));
	AddChild(ptrProjectWindowView);
}
// ---------------------------------------------------------------------------------------------------------- //


// ProjectWindow::QuitRequested -- Post a message to the app to quit
bool ProjectWindow::QuitRequested()
{
   return true;
}
// ---------------------------------------------------------------------------------------------------------- //


// ProjectWindow::AddProjectFile
void ProjectWindow::AddProjectFile(BString tmp)
{
	int32 newselection;
	
	Lock();
	lsvProjectFiles->DeselectAll();
	tmp.Prepend(" ");
	lsvProjectFiles->AddItem(new BStringItem(tmp.String()));
	newselection = lsvProjectFiles->CountItems() - 1;
	lsvProjectFiles->Select(newselection,true);
	Unlock();
}
// ---------------------------------------------------------------------------------------------------------- //


//void ProjectWindow::ShowProjectFiles(BMessage *msg)
//{
	// Clear Current List
	//lsvProjectFiles->MakeEmpty();
		
	// Read ProjectFiles BMessage
	//int TotalProjectFiles;
	//msg->FindInt32("FileCount",TotalProjectFiles);
	//printf("%i\n",TotalProjectFiles);
	//ProjectFiles->FindString(kProjectName, &prjname);
	//stvProjectName->SetText(prjname.String());
	
	// Show Files eg.  lsvProjectFiles->AddItem(new BStringItem("Test.cpp"));
//}
// ---------------------------------------------------------------------------------------------------------- //


// ProjectWindow::MessageReceived -- receives messages
void ProjectWindow::MessageReceived (BMessage *message)
{
	switch(message->what)
	{
		case TOOLBAR_BTN_ADD_FILE_TO_PROJECT:
			{
				AddProjectFile("Test.cpp"); // debug
				// popup a modal window asking for type of file to add
				// ie. cpp  - add to list open as new file 
				//     h    - not added to list, just created
				//     templates check the /templates/ directory for cpp templates
				//     to add to your project ... ie. AboutWindow, SimpleDialog
			}
			break;
		case TOOLBAR_BTN_REMOVE_FILE_FROM_PROJECT:
			{
				int32 selected;
				int32 preselected;
				selected = lsvProjectFiles->CurrentSelection(0);
				//printf("removing %i\n",selected);
				lsvProjectFiles->RemoveItem(selected);
				preselected = selected - 1;
				if (preselected < 0) {
					preselected = 0;
				}
				lsvProjectFiles->Select(preselected,true);
			}
			break;	
		case ADD_PROJECT_FILE:
			{
				int32 TotalMessages = message->CountNames(B_ANY_TYPE);
				int32 Counter = 0;
				printf("Total Messages %i\n",TotalMessages);
				while (TotalMessages > Counter)
				{
					BString tmp;
					message->FindString(kProjectFile, Counter, &tmp);
					AddProjectFile(tmp);
					printf("Counter is %i and tmp is %s\n",TotalMessages,tmp.String());	
					Counter++;
				}
			}
			break;	
		case SET_PROJECT_TITLE:
			{
				BString prjname;
				message->FindString(kProjectName, &prjname);
				stvProjectName->SetText(prjname.String());
				//ShowProjectFiles(&ProjectFiles);
			}
			break;
		default:
			{
				BWindow::MessageReceived(message);
			}	
			break;
	}
}
// ---------------------------------------------------------------------------------------------------------- //
