/*

BeOS Rapid Integrated Environment (BRIE)

FileWindow by Sikosis

Released under the MIT license.

(C) 2002-2003 http://brie.sf.net/

*/


// Includes -------------------------------------------------------------------------------------------------- //
#include <Alert.h>
#include <Application.h>
#include <Bitmap.h>
#include <Button.h>
#include <Entry.h>
#include <File.h>
#include <FilePanel.h>
#include <ListView.h>
#include <MenuBar.h>
#include <Menu.h> 
#include <MenuItem.h>
#include <Path.h>
#include <Picture.h>
#include <PictureButton.h>
#include <Roster.h>
#include <Screen.h>
#include <ScrollView.h>
#include <StatusBar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TextControl.h>
#include <Window.h>
#include <View.h>

// Toolbar
#include "brie_tool_new.h"
#include "brie_tool_new_inverse.h"
//#include "brie_tool_open.h"

#include "brie.h"
#include "BRIEWindows.h"
#include "BRIEViews.h"
#include "brieconstants.h"

// Constants ------------------------------------------------------------------------------------------------- //
const uint32 MENU_FILE_NEW = 'Mfne';
const uint32 MENU_FILE_LOAD = 'Mflo';
const uint32 MENU_FILE_SAVE = 'Mfsv';
const uint32 MENU_FILE_SAVEAS = 'Mfsa';
const uint32 MENU_FILE_PRINT = 'Mfpr';
const uint32 MENU_FILE_QUIT = 'Mfex';
const uint32 MENU_EDIT_CUT = 'Mect';
const uint32 MENU_EDIT_COPY = 'Mecp';
const uint32 MENU_EDIT_PASTE = 'Mepa';
const uint32 MENU_TOOLS_OPTIONS = 'Mtop';
const uint32 MENU_TOOLS_COMPILE = 'Mtgc';
const uint32 MENU_TOOLS_CREATEJAM = 'Mtja';
const uint32 MENU_WIN_PROJ = 'Mwpj';
const uint32 MENU_HELP_MANUAL = 'Mhma';
const uint32 MENU_HELP_ABOUT = 'Mhab';
// ---------------------------------------------------------------------------------------------------------- //
char *kProjectName = "ProjectName";

// TopOfScreen -- Places the BWindow starting from the top of the Current Screen
static void TopOfScreen(BWindow* w)
{
	BRect	screenFrame = (BScreen(B_MAIN_SCREEN_ID).Frame());
	BPoint 	pt;
	pt.x = 5;
	pt.y = 30;
	if (screenFrame.Contains(pt))
		w->MoveTo(pt);
	
	int NewWidth = (int) screenFrame.Width() - 130;
	w->ResizeTo(NewWidth,50); // resize to the current screen size
}
// ---------------------------------------------------------------------------------------------------------- //


// FileWindow - Constructor
FileWindow::FileWindow(BRect frame) : BWindow (frame, "BeOS Rapid Integrated Environment v0.3", B_TITLED_WINDOW, B_NOT_RESIZABLE , 0)
{
	//ptrFileWindow = this;
	InitWindow();
	TopOfScreen(this);
	Show();
}
// ---------------------------------------------------------------------------------------------------------- //


// BRIEWindow - Destructor
FileWindow::~FileWindow()
{
	exit(0);
}
// ---------------------------------------------------------------------------------------------------------- //


// FileWindow::InitWindow -- Initialization Commands here
void FileWindow::InitWindow(void)
{
	BMenu *menu;
    //BMenuItem *item;
	BRect rMenuBar;
	BRect r;
	r = Bounds();
	
    // Add the drawing view
    rMenuBar = Bounds();
    rMenuBar.top = 20;
    
    // Add the menu bar
    rMenuBar.top = 0;
    rMenuBar.bottom = 19;
    menubar = new BMenuBar(rMenuBar, "menu_bar");
    AddChild(menubar);
    
    // BMenu
    menu = new BMenu("File");
    menu->AddItem(new BMenuItem("New Project", new BMessage(MENU_FILE_NEW), 'N'));
    menu->AddSeparatorItem();
    menu->AddItem(new BMenuItem("Load Project...", new BMessage(MENU_FILE_LOAD), 'L'));
    menu->AddItem(new BMenuItem("Save Project", new BMessage(MENU_FILE_SAVE), 'S'));
    menu->AddItem(new BMenuItem("Save Project As...", new BMessage(MENU_FILE_SAVEAS), 'A'));
    menu->AddSeparatorItem();
    menu->AddItem(new BMenuItem("Print", new BMessage(MENU_FILE_PRINT), 'P'));
    menu->AddSeparatorItem();
    menu->AddItem(new BMenuItem("Quit", new BMessage(MENU_FILE_QUIT), 'Q'));
    menubar->AddItem(menu);
    
    menu = new BMenu("Edit");
    menu->AddItem(new BMenuItem("Cut", new BMessage(MENU_EDIT_CUT), 'X'));
    menu->AddItem(new BMenuItem("Copy", new BMessage(MENU_EDIT_COPY), 'C'));
    menu->AddItem(new BMenuItem("Paste", new BMessage(MENU_EDIT_PASTE), 'P'));
    menu->AddSeparatorItem();
    menubar->AddItem(menu);

	menu = new BMenu("Tools");
	menu->AddItem(new BMenuItem("Options", new BMessage(MENU_TOOLS_OPTIONS), 'O'));
	menu->AddSeparatorItem();
	menu->AddItem(new BMenuItem("Create JAM file", new BMessage(MENU_TOOLS_CREATEJAM), 'J'));
    menu->AddItem(new BMenuItem("Compile with GCC", new BMessage(MENU_TOOLS_COMPILE), 'R'));
    menubar->AddItem(menu);
    
    menu = new BMenu("Window");
	menu->AddItem(new BMenuItem("Show/Hide Project", new BMessage(MENU_WIN_PROJ), '0'));
    menubar->AddItem(menu);
    		    
    menu = new BMenu("Help");
    menu->AddItem(new BMenuItem("Help Manual", new BMessage(MENU_HELP_MANUAL), 'H'));
    menu->AddSeparatorItem();
    menu->AddItem(new BMenuItem("About BRIE ...", new BMessage(MENU_HELP_ABOUT)));
    menubar->AddItem(menu);
    
    // Sikosis's Toolbar ;)
    //BRect rToolbar;
    int ToolbarButtonMargin = 4;
    int ToolbarButtonWidth = 36;
	
	// New Email Button
  	BRect BitmapFrame (BRect(0,0,31,31));
  	BPicture *tmpBPicture;
  	BPicture *tmpBPicture2;
  	//BPicture *tmpBPicture3;
  	BView    *tmpBPictureView = new BView(BitmapFrame, "tmpBPictureView",B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
  	//rgb_color toolbar_button_background = { 255, 255, 255, 0 };
  	
  	AddChild(tmpBPictureView);
  	
  	BBitmap *newprojectpicture = new BBitmap(BitmapFrame,B_RGB32);
	newprojectpicture->SetBits(brienew,3072,0,B_RGB32);
  	
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(newprojectpicture,BPoint(3,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *newprojectpicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	newprojectpicture_state2->SetBits(brienewinverse,3072,0,B_RGB32);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(newprojectpicture_state2,BPoint(3,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnNewProject = new BPictureButton(BRect (ToolbarButtonMargin,rMenuBar.bottom+2,ToolbarButtonMargin+ToolbarButtonWidth,rMenuBar.bottom+34),"New Project",tmpBPicture,tmpBPicture2, new BMessage(TOOLBAR_BTN_NEW_PROJECT),B_ONE_STATE_BUTTON, B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
 	
	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
	ToolbarButtonMargin = ToolbarButtonMargin + ToolbarButtonWidth;
    
    // Add Controls
    AddChild(btnNewProject);
    
	// Add the Drawing View
	AddChild(ptrFileWindowView = new FileWindowView(r));
	
	// Check for Existence of Project directory and create it if necessary
	app_info	daInfo;
	be_app->GetAppInfo(&daInfo);
	BEntry	daEntry(&daInfo.ref);
	daEntry.GetParent(&daEntry);
	BPath	pPath(&daEntry);
	char	apath[256];
	::memcpy(apath, pPath.Path(), 256);	
	
	char cmd[256];
	sprintf(cmd,"mkdir %s/projects",apath);
	system(cmd);
}
// ---------------------------------------------------------------------------------------------------------- //

void FileWindow::SetProject(const char *projectname, const char *shortprojectname)
{
	char newtitle[256];
	//sprintf(CurrentProjectName,"%s",projectname);
	sprintf(newtitle,"%s%s - [ %s ]",projtitle,projversion,shortprojectname);
	//(new BAlert("",newtitle,"debug"))->Go();
	//fileWindow->SetTitle(newtitle);
	//ptrFileWindow->
	SetTitle(newtitle);
}
// ---------------------------------------------------------------------------------------------------------- //


// FileWindow::QuitRequested -- Post a message to the app to quit
bool FileWindow::QuitRequested()
{
   be_app->PostMessage(B_QUIT_REQUESTED);
   return true;
}
// ---------------------------------------------------------------------------------------------------------- //


// FileWindow::MessageReceived -- receives messages
void FileWindow::MessageReceived (BMessage *message)
{
	BRect aboutwindowRect(0,0,370,230);
	NewProjectWindow* ptrNewProjectWindow;
	
	switch(message->what)
	{
		/*case BTN_FILE_BROWSE:
			//browsePanel->SetPanelDirectory(txtCVSRoot->Text());
			//browsePanel->Show();
			break;	*/
		case TOOLBAR_BTN_NEW_PROJECT:	
		case MENU_FILE_NEW:
			ptrNewProjectWindow = new NewProjectWindow(BRect(367.0, 268.0, 657.0, 500.0));
			//ptrNewProjectWindow->Show();
			break;	
		case MENU_HELP_ABOUT:
			aboutWindow = new AboutWindow(aboutwindowRect);
			break;	
		case MENU_FILE_PRINT:
			(new BAlert("","Printing is a low priority feature.\n\nComing Soon to a Printer near you ..."," Soonish "))->Go();
			break;	
		case MENU_FILE_QUIT:
			//SaveConfig();
			QuitRequested();
			break;	
		default:
			BWindow::MessageReceived(message);
			break;
	}
}
// ---------------------------------------------------------------------------------------------------------- //
