/*

BeOS Rapid Integrated Environment (BRIE)

MenuCreator by Sikosis

Released under the MIT license.

(C) 2003 http://brie.sf.net/

*/


// Includes -------------------------------------------------------------------------------------------------- //
#include <Application.h>
#include <Alert.h>
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
#include "Bitmaps-MenuCreator-Toolbar.h"

#include "brie.h"
#include "BRIEWindows.h"
#include "BRIEViews.h"
#include "brieconstants.h"

// ---------------------------------------------------------------------------------------------------------- //
const uint32 TOOLBAR_BTN_ADD_MENU_ITEM = 'tbam';
const uint32 TOOLBAR_BTN_REMOVE_MENU_ITEM = 'tbrm';

// CenterWindowOnScreen -- Centers the BWindow to the Current Screen
static void CenterWindowOnScreen(BWindow* w)
{
	BRect	screenFrame = (BScreen(B_MAIN_SCREEN_ID).Frame());	BPoint	pt;
	pt.x = screenFrame.Width()/2 - w->Bounds().Width()/2;
	pt.y = screenFrame.Height()/2 - w->Bounds().Height()/2;

	if (screenFrame.Contains(pt))
		w->MoveTo(pt);
}
// -------------------------------------------------------------------------------------------------- //


// MenuCreator - Constructor
MenuCreator::MenuCreator(BRect frame) : BWindow (frame, "BRIE Simple Menu Creator", B_TITLED_WINDOW , B_NOT_RESIZABLE , 0)
{
	// Set MenuCreator Pointer
	ptrMenuCreator = this;
	InitWindow();
	CenterWindowOnScreen(this);
	Show();
}
// ---------------------------------------------------------------------------------------------------------- //


// MenuCreator - Destructor
MenuCreator::~MenuCreator()
{
	//exit(0);
}
// ---------------------------------------------------------------------------------------------------------- //


// MenuCreator::InitWindow -- Initialization Commands here
void MenuCreator::InitWindow(void)
{
	BRect r;
	r = Bounds();
	int LeftMargin = 6;
	float RightMargin = r.right;
	int TopMargin = 11;
	
    // Add Controls
    //stvProjectName = new BStringView(BRect(LeftMargin+1, TopMargin, RightMargin, TopMargin+10), "Project Name", "Untitled");
    
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
  	
  	BBitmap *menupluspicture = new BBitmap(BitmapFrame,B_RGB32);
	menupluspicture->SetBits(menuplusicon,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(menupluspicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *menupluspicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	menupluspicture_state2->SetBits(menuplusiconinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(menupluspicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnMenuAdd = new BPictureButton(BRect (ToolbarButtonMargin,3,ToolbarButtonMargin+ToolbarButtonWidth,26),
 							  "Add Menu Item",tmpBPicture,tmpBPicture2, new BMessage(TOOLBAR_BTN_ADD_MENU_ITEM),
 							  B_ONE_STATE_BUTTON, B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
 	
	tmpBPictureView->RemoveSelf();
	/*AddChild(tmpBPictureView);
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
    
       
    

    AddChild(btnRemoveFileFromProjectList);
    AddChild(btnAddFileToProjectList);
    AddChild(stvProjectName);
    
    
    //ptrProjectWindowView->AddChild(new BScrollView("ScrollViewProjectFiles",lsvProjectFiles, B_FOLLOW_LEFT | B_FOLLOW_TOP, 0, true, false)); */
	
	lsvMenuItems = new BListView(BRect(6,29,r.right-6,r.bottom-6), "lsvMenuItems",
					  B_SINGLE_SELECTION_LIST, B_FOLLOW_LEFT | B_FOLLOW_TOP,
					  B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS);
		
	// Add the Drawing View
    ptrMenuCreatorView = new MenuCreatorView(r);
    ptrMenuCreatorView->AddChild(lsvMenuItems);
    ptrMenuCreatorView->AddChild(btnMenuAdd);
    
	AddChild(ptrMenuCreatorView);
}
// ---------------------------------------------------------------------------------------------------------- //


// MenuCreator::QuitRequested -- Post a message to the app to quit
bool MenuCreator::QuitRequested()
{
   return true;
}
// ---------------------------------------------------------------------------------------------------------- //


// MenuCreator::AddMenuItem
void MenuCreator::AddMenuItem(BString NewMenuItem)
{
	int32 newselection;
	
	Lock();
	lsvMenuItems->DeselectAll();
	NewMenuItem.Prepend(" ");
	lsvMenuItems->AddItem(new BStringItem(NewMenuItem.String()));
	newselection = lsvMenuItems->CountItems() - 1;
	lsvMenuItems->Select(newselection,true);
	Unlock();
}
// ---------------------------------------------------------------------------------------------------------- //


// MenuCreator::MessageReceived -- receives messages
void MenuCreator::MessageReceived (BMessage *message)
{
	switch(message->what)
	{
		case BTN_OKAY:
		{
			QuitRequested();
		}
			break;
		
		case TOOLBAR_BTN_ADD_MENU_ITEM:
		{
			BString IBTitle;
			BString IBQuestion;
			BString IBDefault;
			BString IBAnswer;
			IBTitle.SetTo("Add Menu Item");
			IBQuestion.SetTo("Enter the Menu Item Name:");
			IBDefault.SetTo("Value"); // debug
			
			printf("About to Create InputBoxWindow\n"); // debug
			ptrInputBoxWindow = new InputBoxWindow(BRect(0,0,350,120));
			printf("Now about to SetTo the InputBoxWindow\n"); // debug
			ptrInputBoxWindow->SetTo(IBTitle, IBQuestion, IBDefault, IBAnswer);
			printf("After InputBoxWindow\n"); // debug
			printf("IBAnswer = %s\n\n",IBAnswer.String()); // debug
			//AddMenuItem(&IBAnswer);
		}
			break;
			
		/*case TOOLBAR_BTN_ADD_FILE_TO_PROJECT:
			{
				// first check that a project exists ...
				if (ProjectName.Length() !=0 && ProjectName.Compare("Untitled") != 0) {
					AddProjectFile("Test.cpp"); // debug
					// popup a modal window asking for type of file to add
					// ie. cpp  - add to list open as new file 
					//     h    - not added to list, just created
					//     templates check the /templates/ directory for cpp templates
					//     to add to your project ... ie. AboutWindow, SimpleDialog
				} else {
					(new BAlert("","You have to create a Project first before you can Add Files.\n\nHint: Select New Project from the Menu or Click on the New Project Icon (first)","Okay"))->Go();
					// open a new project ... maybe later for the time being ppl 
					// can just open it manually.
				}
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
			break;	*/
		default:
			{
				BWindow::MessageReceived(message);
			}	
			break;
	}
}
// ---------------------------------------------------------------------------------------------------------- //

