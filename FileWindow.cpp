/*

BeOS Rapid Integrated Environment (BRIE)

FileWindow by Sikosis

Released under the MIT license.

(C) 2002-2003 http://brie.sf.net/

*/

#define URL_TYPE "application/x-vnd.Be.URL.http"

// Includes -------------------------------------------------------------------------------------------------- //
#include <Alert.h>
#include <Application.h>
#include <Bitmap.h>
#include <Button.h>
#include <Entry.h>
#include <File.h>
#include <FilePanel.h>
#include <ListView.h>
#include <Message.h>
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
#include <String.h>
#include <TextControl.h>
#include <Window.h>
#include <View.h>

// Toolbar
#include "Bitmaps-Toolbar.h"

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
const uint32 MENU_TOOLS_CREATEMAKE = 'Mtmk';
const uint32 MENU_WIN_PROJ = 'Mwpj';
const uint32 MENU_WIN_PROP = 'Mprp';
const uint32 MENU_WIN_TOOL = 'Mwtl';
const uint32 MENU_HELP_MANUAL = 'Mhma';
const uint32 MENU_HELP_ABOUT = 'Mhab';

const uint32 TOOLBAR_BTN_NEW_PROJECT = 'Tbnp';
const uint32 TOOLBAR_BTN_LOAD_PROJECT = 'Tblp';
const uint32 TOOLBAR_BTN_SAVE_PROJECT = 'Tbsp';
const uint32 TOOLBAR_BTN_SAVEAS_PROJECT = 'Tbsa';
const uint32 TOOLBAR_BTN_PRINT_PROJECT = 'Tbpt';
const uint32 TOOLBAR_BTN_CREATEMAKE = 'Tbcm';
const uint32 TOOLBAR_BTN_CREATEJAM = 'Tbcj';
const uint32 TOOLBAR_BTN_COMPILE = 'Tbcp';
const uint32 TOOLBAR_BTN_OPTIONS = 'Tbop';
const uint32 TOOLBAR_BTN_HELP = 'Tbhp';
// ---------------------------------------------------------------------------------------------------------- //

char *kProjectName = "ProjectName";
char *kProjectFile = "ProjectFile";
//char *kProjectTitle = "ProjectTitle";
//char *kProjectShortTitle = "ProjectShortTitle";


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
FileWindow::FileWindow(BRect frame) : BWindow (frame, "BeOS Rapid Integrated Environment v0.37", B_TITLED_WINDOW, B_NOT_RESIZABLE , 0)
{
	ptrFileWindow = this;
	InitWindow();
	TopOfScreen(this);
	
	// add load settings here
	
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
	menu->AddItem(new BMenuItem("Create MAKE file", new BMessage(MENU_TOOLS_CREATEMAKE), 'M'));
	menu->AddItem(new BMenuItem("Create JAM file", new BMessage(MENU_TOOLS_CREATEJAM), 'J'));
    menu->AddItem(new BMenuItem("Compile with GCC", new BMessage(MENU_TOOLS_COMPILE), 'R'));
    menubar->AddItem(menu);
    
    menu = new BMenu("Window");
	menu->AddItem(new BMenuItem("Show/Hide Project", new BMessage(MENU_WIN_PROJ), '0'));
	menu->AddItem(new BMenuItem("Show/Hide Properties", new BMessage(MENU_WIN_PROP), '1'));
	menu->AddItem(new BMenuItem("Show/Hide Toolbox", new BMessage(MENU_WIN_TOOL), '2'));
    menubar->AddItem(menu);
    		    
    menu = new BMenu("Help");
    menu->AddItem(new BMenuItem("Help Manual", new BMessage(MENU_HELP_MANUAL), 'H'));
    menu->AddSeparatorItem();
    menu->AddItem(new BMenuItem("About BRIE ...", new BMessage(MENU_HELP_ABOUT)));
    menubar->AddItem(menu);
    
    // Sikosis's Toolbar ;)
    int ToolbarButtonMargin = 6;
    int ToolbarButtonWidth = 24;
    int ButtonGap = 3;
	
	// New Project Button
  	BRect BitmapFrame (BRect(0,0,23,23));
  	BPicture *tmpBPicture;
  	BPicture *tmpBPicture2;
  	BView    *tmpBPictureView = new BView(BitmapFrame, "tmpBPictureView",B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
  	rgb_color toolbar_button_background = { 255, 255, 255, 0 };
  	
  	AddChild(tmpBPictureView);
  	
  	BBitmap *newprojectpicture = new BBitmap(BitmapFrame,B_RGB32);
	newprojectpicture->SetBits(brienew,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(newprojectpicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *newprojectpicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	newprojectpicture_state2->SetBits(brienewinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(newprojectpicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnNewProject = new BPictureButton(BRect (ToolbarButtonMargin,rMenuBar.bottom+4,ToolbarButtonMargin+ToolbarButtonWidth,rMenuBar.bottom+28),"New Project",tmpBPicture,tmpBPicture2, new BMessage(TOOLBAR_BTN_NEW_PROJECT),B_ONE_STATE_BUTTON, B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
 	
	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
	ToolbarButtonMargin = ToolbarButtonMargin + ToolbarButtonWidth + ButtonGap;
    
    // Load Project Button
    BBitmap *loadprojectpicture = new BBitmap(BitmapFrame,B_RGB32);
	loadprojectpicture->SetBits(brieload,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(loadprojectpicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *loadprojectpicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	loadprojectpicture_state2->SetBits(brieloadinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(loadprojectpicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnLoadProject = new BPictureButton(BRect (ToolbarButtonMargin,rMenuBar.bottom+4,ToolbarButtonMargin+ToolbarButtonWidth,rMenuBar.bottom+28),"Load Project",tmpBPicture,tmpBPicture2, new BMessage(TOOLBAR_BTN_LOAD_PROJECT),B_ONE_STATE_BUTTON, B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
 	
	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
	ToolbarButtonMargin = ToolbarButtonMargin + ToolbarButtonWidth + ButtonGap;
	
	// Save Project Button
    BBitmap *saveprojectpicture = new BBitmap(BitmapFrame,B_RGB32);
	saveprojectpicture->SetBits(briesave,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(saveprojectpicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *saveprojectpicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	saveprojectpicture_state2->SetBits(briesaveinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(saveprojectpicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnSaveProject = new BPictureButton(BRect (ToolbarButtonMargin,rMenuBar.bottom+4,ToolbarButtonMargin+ToolbarButtonWidth,rMenuBar.bottom+28),
 					 "Save Project",tmpBPicture,tmpBPicture2, new BMessage(TOOLBAR_BTN_SAVE_PROJECT),B_ONE_STATE_BUTTON,
 					 B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
 	
	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
	ToolbarButtonMargin = ToolbarButtonMargin + ToolbarButtonWidth + ButtonGap;
    
    // SaveAs Project Button
    BBitmap *saveasprojectpicture = new BBitmap(BitmapFrame,B_RGB32);
	saveasprojectpicture->SetBits(briesaveas,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(saveasprojectpicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *saveasprojectpicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	saveasprojectpicture_state2->SetBits(briesaveasinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(saveasprojectpicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnSaveAsProject = new BPictureButton(BRect (ToolbarButtonMargin,rMenuBar.bottom+4,ToolbarButtonMargin+ToolbarButtonWidth,rMenuBar.bottom+28),
 					 "Save As Project",tmpBPicture,tmpBPicture2, new BMessage(TOOLBAR_BTN_SAVEAS_PROJECT),B_ONE_STATE_BUTTON,
 					 B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);

	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
	ToolbarButtonMargin = ToolbarButtonMargin + ToolbarButtonWidth + ButtonGap;
	
    // Print Project Button
    BBitmap *printprojectpicture = new BBitmap(BitmapFrame,B_RGB32);
	printprojectpicture->SetBits(brieprint,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(printprojectpicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *printprojectpicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	printprojectpicture_state2->SetBits(brieprintinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(printprojectpicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnPrintProject = new BPictureButton(BRect (ToolbarButtonMargin,rMenuBar.bottom+4,ToolbarButtonMargin+ToolbarButtonWidth,rMenuBar.bottom+28),
 					 "Print Project",tmpBPicture,tmpBPicture2, new BMessage(TOOLBAR_BTN_PRINT_PROJECT),B_ONE_STATE_BUTTON,
 					 B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);

	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
	ToolbarButtonMargin = ToolbarButtonMargin + ToolbarButtonWidth + ButtonGap;
	
	// Create Make Button
    BBitmap *createmakepicture = new BBitmap(BitmapFrame,B_RGB32);
	createmakepicture->SetBits(briemake,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(createmakepicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *createmakepicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	createmakepicture_state2->SetBits(briemakeinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(createmakepicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnCreateMake = new BPictureButton(BRect (ToolbarButtonMargin,rMenuBar.bottom+4,ToolbarButtonMargin+ToolbarButtonWidth,rMenuBar.bottom+28),
 					 "Create Make",tmpBPicture,tmpBPicture2, new BMessage(TOOLBAR_BTN_CREATEMAKE),B_ONE_STATE_BUTTON,
 					 B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);

	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
	ToolbarButtonMargin = ToolbarButtonMargin + ToolbarButtonWidth + ButtonGap;
	
	// Create Jam Button
    BBitmap *createjampicture = new BBitmap(BitmapFrame,B_RGB32);
	createjampicture->SetBits(briejam,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(createjampicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *createjampicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	createjampicture_state2->SetBits(briejaminverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(createjampicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnCreateJam = new BPictureButton(BRect (ToolbarButtonMargin,rMenuBar.bottom+4,ToolbarButtonMargin+ToolbarButtonWidth,rMenuBar.bottom+28),
 					 "Create Jam",tmpBPicture,tmpBPicture2, new BMessage(TOOLBAR_BTN_CREATEJAM),B_ONE_STATE_BUTTON,
 					 B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);

	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
	ToolbarButtonMargin = ToolbarButtonMargin + ToolbarButtonWidth + ButtonGap;
	
	// Compile Button
    BBitmap *compilepicture = new BBitmap(BitmapFrame,B_RGB32);
	compilepicture->SetBits(briecompile,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(compilepicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *compilepicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	compilepicture_state2->SetBits(briecompileinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(compilepicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnCompile = new BPictureButton(BRect (ToolbarButtonMargin,rMenuBar.bottom+4,ToolbarButtonMargin+ToolbarButtonWidth,rMenuBar.bottom+28),
 					 "Compile",tmpBPicture,tmpBPicture2, new BMessage(TOOLBAR_BTN_COMPILE),B_ONE_STATE_BUTTON,
 					 B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
	ToolbarButtonMargin = ToolbarButtonMargin + ToolbarButtonWidth + ButtonGap;
	
	// Options Button
    BBitmap *optionspicture = new BBitmap(BitmapFrame,B_RGB32);
	optionspicture->SetBits(brieoptions,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(optionspicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *optionspicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	optionspicture_state2->SetBits(brieoptionsinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(optionspicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnOptions = new BPictureButton(BRect (ToolbarButtonMargin,rMenuBar.bottom+4,ToolbarButtonMargin+ToolbarButtonWidth,rMenuBar.bottom+28),
 					 "Options",tmpBPicture,tmpBPicture2, new BMessage(TOOLBAR_BTN_OPTIONS),B_ONE_STATE_BUTTON,
 					 B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
	ToolbarButtonMargin = ToolbarButtonMargin + ToolbarButtonWidth + ButtonGap;
	
	// Help Button
    BBitmap *helppicture = new BBitmap(BitmapFrame,B_RGB32);
	helppicture->SetBits(briehelp,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(helppicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *helppicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	helppicture_state2->SetBits(briehelpinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(helppicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnHelp = new BPictureButton(BRect (ToolbarButtonMargin,rMenuBar.bottom+4,ToolbarButtonMargin+ToolbarButtonWidth,rMenuBar.bottom+28),
 					 "Help",tmpBPicture,tmpBPicture2, new BMessage(TOOLBAR_BTN_HELP),B_ONE_STATE_BUTTON,
 					 B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
	ToolbarButtonMargin = ToolbarButtonMargin + ToolbarButtonWidth + ButtonGap;
	
	delete tmpBPicture;
	delete tmpBPicture2;
	
	//BrowsePanel = new BFilePanel(B_OPEN_PANEL, NULL, NULL,	B_DIRECTORY_NODE, true);
        
    // Add Controls
    AddChild(btnNewProject);
    AddChild(btnLoadProject);
    AddChild(btnSaveProject);
    AddChild(btnSaveAsProject);
    AddChild(btnPrintProject);
    AddChild(btnCreateMake);
    AddChild(btnCreateJam);
    AddChild(btnCompile);
    AddChild(btnOptions);
    AddChild(btnHelp);
    
	// Add the Drawing View
	AddChild(ptrFileWindowView = new FileWindowView(r));
	
	// Check for Existence of Project directory and create it if necessary
	if (ProjectPath.Length() == 0)
	{
		GetCurrentPath();
	}
	
	// change this for a better bstorage function
	char cmd[256];
	sprintf(cmd,"mkdir %s/projects",ProjectPath.String());
	system(cmd);
}
// ---------------------------------------------------------------------------------------------------------- //


void FileWindow::SetProject(const char *prjname)
{
	char newtitle[256];
	sprintf(newtitle,"%s%s - [ %s ]",projtitle,projversion,prjname);
	printf("newtitle - %s\n",newtitle);
	ptrFileWindow->SetTitle(newtitle);
}
// ---------------------------------------------------------------------------------------------------------- //


// FileWindow::QuitRequested -- Post a message to the app to quit
bool FileWindow::QuitRequested()
{
   be_app->PostMessage(B_QUIT_REQUESTED);
   return true;
}
// ---------------------------------------------------------------------------------------------------------- //


void FileWindow::CreateJamFile(void)
{
/*	FILE *f;
	char tmp[256];
	char FileName[256];
	int x;
	printf("Count: %i // Compare: %i\n\n",ProjectName.Length,ProjectName.Compare("Untitled"));
	if (ProjectName.Length !=0)
	{
		if (ProjectName.Compare("Untitled") != 1) {
			printf("CreateJam - %s\n\n",ProjectName.String());
		}	
	}*/
}
// ---------------------------------------------------------------------------------------------------------- //


void FileWindow::CreateMakeFile(void)
{
	FILE *f;
	char tmp[256];
	char FileName[256];
	int x;
	
	if (ProjectName.Length() !=0)
	{
		printf("CreateMake - %s\n\n",ProjectName.String());
		sprintf(FileName,"%s/projects/%s/makefile",ProjectPath.String(),ProjectName.String());
		f = fopen(FileName,"w");
		sprintf(tmp,"## BeOS Makefile for %s ##\n",ProjectName.String());
		x = fputs(tmp,f);
		sprintf(tmp,"## Author: %s\n",ProjectAuthor.String());
		x = fputs(tmp,f);
		x = fputs("## Created by BRIE (http://brie.sf.net/)\n\n",f);
		x = fputs("## Application Specific Settings ---------------------------------------------\n\n",f);
		x = fputs("# specify the name of the binary\n",f);
		sprintf(tmp,"NAME= %s\n",ProjectName.String());
		x = fputs(tmp,f);
		x = fputs("# specify the type of binary\n",f);
		x = fputs("#	APP:	Application\n",f);
		x = fputs("#	SHARED:	Shared library or add-on\n",f);
		x = fputs("#	STATIC:	Static library archive\n",f);
		x = fputs("#	DRIVER: Kernel Driver\n",f);
		x = fputs("TYPE= APP\n\n",f);
		x = fputs("#	specify the source files to use\n",f);
		x = fputs("#	Note that spaces in folder names do not work well with this makefile.\n",f);
		sprintf(tmp,"SRCS= %s.cpp %sWindow.cpp %sView.cpp\n",ProjectName.String(),ProjectName.String(),ProjectName.String());
		x = fputs(tmp,f);
		x = fputs("# end of srcs\n\n",f);
		x = fputs("#	specify the resource files to use\n",f);
		//x = fputs("RSRCS= ../../newproject.rsrc\n\n",f);
		x = fputs("RSRCS= \n\n",f);
		x = fputs("#	specify additional libraries to link against\n",f);
		x = fputs("LIBS= be root\n\n",f);
		x = fputs("#	specify additional paths to directories \n",f);
		x = fputs("LIBPATHS=\n\n",f);
		x = fputs("#	additional paths to look for system headers\n",f);
		x = fputs("SYSTEM_INCLUDE_PATHS =\n\n",f);
		x = fputs("#	additional paths to look for local headers\n",f);
		x = fputs("LOCAL_INCLUDE_PATHS =\n\n",f);
		x = fputs("#	specify the level of optimization that you desire - NONE, SOME, FULL\n",f);
		x = fputs("OPTIMIZE=\n\n",f);
		x = fputs("#	specify any preprocessor symbols to be defined.  \n",f);
		x = fputs("DEFINES=\n\n",f);
		x = fputs("#	specify special warning levels - NONE, ALL\n",f);
		x = fputs("WARNINGS = ALL\n\n",f);
		x = fputs("#	specify whether image symbols will be created\n",f);
		x = fputs("SYMBOLS = TRUE\n\n",f);
		x = fputs("#	specify debug settings\n",f);
		x = fputs("DEBUGGER =\n\n",f);
		x = fputs("#	specify additional compiler flags for all files\n",f);	
		x = fputs("COMPILER_FLAGS =\n\n",f);
		x = fputs("#	specify additional linker flags\n",f);
		x = fputs("LINKER_FLAGS =\n\n",f);
		x = fputs("## include the makefile-engine\n",f);
		x = fputs("include /boot/develop/etc/makefile-engine\n",f);
		fclose(f);
	} else {
		(new BAlert("","You have to create a Project first before you can create a Makefile.","Okay"))->Go();	
	}
}
// ---------------------------------------------------------------------------------------------------------- //


void FileWindow::CompileGCC(void)
{
	/*if (ProjectName.Length() !=0)
	{
		// check to see if the makefile exists
		char cmd[256];
		sprintf(cmd,"%s/projects/%s/makefile",ProjectPath.String(),ProjectName.String());
		FILE *f;	
    	
    	printf("CompileGCC - cmd is %s\n",cmd); //debug
    	if (!(f = fopen(cmd, "r"))) {
			(new BAlert("","No Makefile Found.\n\nWe MUST create a new one.","Okay"))->Go();
			CreateMakeFile();
		}
		fclose(f);
		
		// now run make via our compile.sh
		int x;
		char tmp[256];
		char FileName[256];
		sprintf(FileName,"%s/projects/%s/compile.sh",ProjectPath.String(),ProjectName.String());
		f = fopen(FileName,"w");
		x = fputs("#!/bin/sh\n",f);
		x = fputs("# Compile and Run\n",f);
		sprintf(tmp,"cd %s/projects/%s \n",ProjectPath.String(),ProjectName.String());
		x = fputs(tmp,f);
		x = fputs("make clean\n",f);
		x = fputs("make\n",f);
		x = fputs("cd obj.x86\n",f);
		sprintf(tmp,"%s\n",ProjectPath.String(),ProjectName.String());
		x = fputs(tmp,f);
		fclose(f);
		//sprintf(cmd,"Terminal -t \"Compiling %s\" %s",FileName);
		//printf("now run make %s\n",cmd); //debug
		system(FileName);
	} else {
		(new BAlert("","You have to create a Project first before you can Compile/Run.","Okay"))->Go();	
	}*/
}
// ---------------------------------------------------------------------------------------------------------- //


void FileWindow::SaveProject(void)
{
	if (ProjectName.Length() !=0)
	{
		FILE *f;
		char tmp[256];
		char FileName[256];
		int x;
		
		sprintf(FileName,"%s/projects/%s.bprj",ProjectPath.String(),ProjectName.String());
		f = fopen(FileName,"w");
		sprintf(tmp,"## BRIE Project File for %s ##\n",ProjectName.String());
		x = fputs(tmp,f);
		sprintf(tmp,"ProjectName=%s\n",ProjectName.String());
		x = fputs(tmp,f);
		sprintf(tmp,"ProjectDir=%s/projects/%s\n",ProjectPath.String(),ProjectName.String());
		x = fputs(tmp,f);
		sprintf(tmp,"Author=%s\n",ProjectAuthor.String());
		x = fputs(tmp,f);
		sprintf(tmp,"Language=%s\n","C/C++");
		x = fputs(tmp,f);
		x = fputs("### Files\n",f);
		fclose(f);
	/*	sprintf(tmp,"%s.cpp\n",prjname);
		x = fputs(tmp,f);
		sprintf(tmp,"%sWindow.cpp\n",prjname);
		x = fputs(tmp,f);
		sprintf(tmp,"%sView.cpp\n",prjname);
		x = fputs(tmp,f);
		fclose(f);*/
		/* BListItem *item; 
   int32 selected; 
   while ( (selected = myListView->CurrentSelection(i)) >= 0 ) { 
       item = ItemAt(selected); */
		
		
		//BListItem *item;
		//Lock();
		//for(z=0;z<lsvProjectFiles->CountItems();z++) {
			//item = lsvProjectFiles->ItemAt(z);
		//	lsvProjectFiles->DeselectAll();
		//	lsvProjectFiles->Select(z,true);
			//sprintf(tmp,"%s\n",lsvProjectFiles->);
		//	x = fputs(tmp,f);
		//}
		//Unlock();		
/*		### Properties:TestWindow.cpp
0
0
100
100
###*/
		
		
		// need to loop the array or whatever we store the list
		// of cpp files in
		
		
		
	} else {
		(new BAlert("","You have to create a Project first before you can Save.","Okay"))->Go();	
	}
}
// ---------------------------------------------------------------------------------------------------------- //


void FileWindow::GetCurrentPath(void)
{
	app_info	daInfo;
	be_app->GetAppInfo(&daInfo);
	BEntry	daEntry(&daInfo.ref);
	daEntry.GetParent(&daEntry);
	BPath	pPath(&daEntry);
	char	apath[256];
	::memcpy(apath, pPath.Path(), 256);
	ProjectPath.SetTo(apath);
}
// ---------------------------------------------------------------------------------------------------------- //


// FileWindow::MessageReceived -- receives messages
void FileWindow::MessageReceived (BMessage *message)
{
	BRect aboutwindowRect(0,0,370,230);
	NewProjectWindow* ptrNewProjectWindow;
	
	switch(message->what)
	{
		case TOOLBAR_BTN_NEW_PROJECT:	
		case MENU_FILE_NEW:
			{
				ptrNewProjectWindow = new NewProjectWindow(BRect(367.0, 268.0, 657.0, 500.0));
			}	
			break;
		case TOOLBAR_BTN_LOAD_PROJECT:	
		case MENU_FILE_LOAD:
			{
				TipNumber = 1;
				new HelpTipWindow(BRect(0.0, 0.0, 350.0, 120.0));
				if (ProjectPath.Length() == 0)
				{
					GetCurrentPath();
				} 
				//PanelType = 0;	
				//browsePanel->SetPanelDirectory(ProjectPath.String());
				//browsePanel->Show();
			}
			break;
		case TOOLBAR_BTN_SAVE_PROJECT:	
		case MENU_FILE_SAVE:
			{
				//if (ProjectPath.Length() > 0 ) { GetCurrentPath(); } 	
				//if (ProjectAuthor.Length > 0) { ProjectAuthor.SetTo("DeveloperName"); }
				//printf("Menu Save - %s - %s - %s\n\n",ptrProjectWindow->stvProjectName->Text(),ProjectPath,ProjectAuthor);
				ProjectName.SetTo(ptrProjectWindow->stvProjectName->Text());
				SaveProject();
			}
			break;
		case TOOLBAR_BTN_SAVEAS_PROJECT:	
		case MENU_FILE_SAVEAS:
			{
				if (ProjectPath.Length() == 0)
				{
					GetCurrentPath();
				}
				PanelType = 1;
				// show the panel to get the new name
				//browsePanel->SetPanelDirectory(ProjectPath.String());
				//browsePanel->Show();
				//SaveProject(ptrProjectWindow->stvProjectName->Text(),ProjectPath.String(),ProjectAuthor.String());
				//SetProject(ptrProjectWindow->stvProjectName->Text());
			}
			break;
		case TOOLBAR_BTN_PRINT_PROJECT:	
		case MENU_FILE_PRINT:
			{
				(new BAlert("","Printing is a low priority feature.\n\nComing Soon to a Printer near you ..."," Soonish "))->Go();
			}	
			break;	
		case MENU_FILE_QUIT:
			{
				//SaveConfig();
				Lock();
				QuitRequested();
			}	
			break;
		case TOOLBAR_BTN_OPTIONS:	
		case MENU_TOOLS_OPTIONS:
			{
				(new BAlert("","Coming Soon."," debug "))->Go();
			}
			break;
		case TOOLBAR_BTN_CREATEMAKE:		
		case MENU_TOOLS_CREATEMAKE:
			{
				if (ProjectPath.Length() == 0)
				{
					GetCurrentPath();
				}
				if (ProjectAuthor.Length() == 0) { ProjectAuthor.SetTo("DeveloperName"); }
				ProjectName.SetTo(ptrProjectWindow->stvProjectName->Text());
				CreateMakeFile();
			}
			break;
		case TOOLBAR_BTN_CREATEJAM:		
		case MENU_TOOLS_CREATEJAM:
			{
				if (ProjectPath.Length() == 0)
				{
					GetCurrentPath();
				}
				if (ProjectAuthor.Length() == 0) { ProjectAuthor.SetTo("DeveloperName"); }
				ProjectName.SetTo(ptrProjectWindow->stvProjectName->Text());
				CreateJamFile();
			}
			break;	
		case TOOLBAR_BTN_COMPILE:		
		case MENU_TOOLS_COMPILE:
			{
				if (ProjectPath.Length() == 0)
				{
					GetCurrentPath();
				}
				if (ProjectAuthor.Length() == 0) { ProjectAuthor.SetTo("DeveloperName"); }
				//Save
				ProjectName.SetTo(ptrProjectWindow->stvProjectName->Text());
				CompileGCC();
			}	
			break;	
		case MENU_WIN_PROJ:
			{
				if (ShowWinProj == 1)
				{
					ptrProjectWindow->Hide();
					ShowWinProj = 0;
				} else {
					ptrProjectWindow->Show();
					ShowWinProj = 1;
					Activate();
				}	
			}
			break;
		case MENU_WIN_PROP:
			{
				if (ShowWinProp == 1)
				{
					ptrPropertiesWindow->Hide();
					ShowWinProp = 0;
				} else {
					ptrPropertiesWindow->Show();
					ShowWinProp = 1;
					Activate();
				}	
			}
			break;
		case MENU_WIN_TOOL:
			{
				if (ShowWinTool == 1)
				{
					ptrToolboxWindow->Hide();
					ShowWinTool = 0;
				} else {
					ptrToolboxWindow->Show();
					ShowWinTool = 1;
					Activate();
				}	
			}
			break;
		case TOOLBAR_BTN_HELP:	
		case MENU_HELP_MANUAL:
			{
				// launch browser on local html manual
				if (ProjectPath.Length() == 0)
				{
					GetCurrentPath();
				}
				int  result;
				char path[256];
				::memcpy(path, ProjectPath.String(), 256);
				char *the_url = strcat(path,"/docs/index.html");
				//printf("%s\n",the_url); // debug
				result = be_roster->Launch(URL_TYPE, 1, &the_url);
			}
			break;			
		case MENU_HELP_ABOUT:
			{
				aboutWindow = new AboutWindow(aboutwindowRect);
			}	
			break;	
		case SET_PROJECT_TITLE:
			{
				BString tmp;
				message->FindString(kProjectName, &tmp);
				SetProject(tmp.String());
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