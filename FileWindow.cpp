/*

BeOS Rapid Integrated Environment (BRIE)

FileWindow by Sikosis

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

/*rgb_color bluebar = {50, 150, 255, 0};
rgb_color yellowbar = {255, 255, 0, 0};
rgb_color orangebar = {255, 150, 50, 0};
rgb_color redbar = {255, 0, 0, 0};
rgb_color greenbar = {0, 255, 0, 0};*/

// CenterWindowOnScreen -- Centers the BWindow to the Current Screen
/*static void CenterWindowOnScreen(BWindow* w)
{
	BRect	screenFrame = (BScreen(B_MAIN_SCREEN_ID).Frame());
	BPoint 	pt;
	pt.x = screenFrame.Width()/2 - w->Bounds().Width()/2;
	pt.y = screenFrame.Height()/2 - w->Bounds().Height()/2;

	if (screenFrame.Contains(pt))
		w->MoveTo(pt);
}*/
// ---------------------------------------------------------------------------------------------------------- //


// TopOfScreen -- Places the BWindow starting from the top of the Current Screen
static void TopOfScreen(BWindow* w)
{
	BRect	screenFrame = (BScreen(B_MAIN_SCREEN_ID).Frame());
	BPoint 	pt;
	pt.x = 5; //screenFrame.Width()/2 - w->Bounds().Width()/2;
	pt.y = 30; //screenFrame.Height()/2 - w->Bounds().Height()/2;
	//w->Bounds().Width()

	if (screenFrame.Contains(pt))
		w->MoveTo(pt);
	
	int NewWidth = (int) screenFrame.Width() - 130;
	//char tmp[250];
	//sprintf(tmp,"NewWidth is %i",NewWidth);
	//(new BAlert("",tmp,"debug"))->Go();
	w->ResizeTo(NewWidth,50); // resize to the current screen size
		
}
// ---------------------------------------------------------------------------------------------------------- //


// FileWindow - Constructor
FileWindow::FileWindow(BRect frame) : BWindow (frame, "BeOS Rapid Integrated Environment v0.2", B_TITLED_WINDOW, B_NOT_RESIZABLE , 0)
{
	InitWindow();
	//CenterWindowOnScreen(this);
	TopOfScreen(this);
	Show();
}


// BRIEWindow - Destructor
FileWindow::~FileWindow()
{
	//delete browsePanel;
	exit(0);
}


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
    menu->AddItem(new BMenuItem("About BRIE ...", new BMessage(MENU_HELP_ABOUT), NULL));
    menubar->AddItem(menu);
    
    // Add Controls
    
	// Add the Drawing View
	AddChild(aFileWindowView = new FileWindowView(r));
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
	switch(message->what)
	{
		/*case BTN_FILE_BROWSE:
			//browsePanel->SetPanelDirectory(txtCVSRoot->Text());
			//browsePanel->Show();
			break;	*/
		case MENU_HELP_ABOUT:
			(new BAlert("","BeOS Rapid Integrated Environment (BRIE) v0.2\n\nCoded by Sikosis\n\nhttp://brie.sf.net/\n\nReleased under the MIT License.","Okay"))->Go();
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
