/*

HelpTipWindow

Author: Sikosis

Released under the MIT license.

(C)2003 BRIE (http://brie.sf.net/)

*/

// Includes ------------------------------------------------------------------------------------------ //
#include <Alert.h>
#include <Application.h>
#include <Bitmap.h>
#include <Button.h>
#include <CheckBox.h>
#include <Entry.h>
#include <File.h>
#include <FindDirectory.h>
#include <Path.h>
//#include <Roster.h>
#include <Screen.h>
#include <ScrollView.h>
#include <stdio.h>
#include <string.h>
#include <TextControl.h>
#include <Window.h>
#include <View.h>

#include "drbe.h"
#include "BRIEWindows.h"
#include "BRIEViews.h"
#include "brieconstants.h"
// Constants ---------------------------------------------------------------------------------------- //
char *kDontShowAgain;
// -------------------------------------------------------------------------------------------------- //


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


// HelpTipWindow - Constructor
HelpTipWindow::HelpTipWindow(BRect frame) : BWindow (frame, "BRIE Help Tips", B_TITLED_WINDOW, B_NORMAL_WINDOW_FEEL , 0)
{
	InitWindow();
	CenterWindowOnScreen(this);
	Show();
}
// -------------------------------------------------------------------------------------------------- //


// HelpTipWindow - Destructor
HelpTipWindow::~HelpTipWindow()
{
	//exit(0);
}
// -------------------------------------------------------------------------------------------------- //


// HelpTipWindow::InitWindow -- Initialization Commands here
void HelpTipWindow::InitWindow(void)
{
	BRect r;
	r = Bounds(); // the whole view
	
	char TipTitle[256];
	char TipDesc[256];
	
	switch(TipNumber)
	{
		case 1:
			sprintf(TipTitle,"BRIE Tip #%i - %s",TipNumber,"Loading Projects");
			sprintf(TipDesc,"%s","Please note we only support the loading of existing BRIE projects.");
			break;
		default:
			strcat(TipTitle,"BRIE Helpful Tips");
			break;	
	}
		
	float LeftMarginTitles = 55;
	float LeftMargin = 6;
	float RightMargin = r.right;
	float OkayButtonSize = 70;
	float OkayLeftMargin = RightMargin - OkayButtonSize - 10;
	rgb_color TipTitleFontColor = { 0,0,255,0 };	
	
	stvTipTitle = new BStringView(BRect(LeftMarginTitles, 14, RightMargin, 28), "TipTitle", TipTitle);
	stvTipTitle->SetFont(be_bold_font);
	stvTipTitle->SetHighColor(TipTitleFontColor);
		
	//stvDescription = new BStringView(BRect(LeftMarginDescription, DescriptionTop, RightMargin, DescriptionTop+10), "Description", "BRIE is an IDE for rapid development of native BeOS applications.");
	//stvDescription2 = new BStringView(BRect(LeftMarginDescription, DescriptionTop+16, RightMargin, DescriptionTop+26), "Description2", "All code is generated in C/C++ using the BeAPI plus a few extras.");

	//chkDontShowAgain = new BCheckBox(BRect frame, "chkDontShowAgain", "Don't Show Again.", new BMessage(CHK_DONTSHOWAGAIN), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
	chkDontShowAgain = new BCheckBox(BRect(LeftMargin+8,r.bottom - 25,RightMargin,r.bottom - 13),"chkDontShowAgain","Don't Show this Tip Again", new BMessage(CHK_DONTSHOWAGAIN), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
		
  	btnOkay = new BButton(BRect (OkayLeftMargin,r.bottom-35,OkayLeftMargin+OkayButtonSize,r.bottom-15),"Okay","Okay", new BMessage(BTN_OKAY), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
  	btnOkay->MakeDefault(true);
  	
  	// create icon of Dr Be ;)
  	BRect IconFrame (BRect(0,0,31,31));
  	BRect IconViewLocation (BRect(LeftMargin+2,r.top+10,LeftMargin+48,r.top+55));
  	BBitmap *drbeicon = new BBitmap(IconFrame,B_RGB32);
	drbeicon->SetBits(drbe,3072,0,B_RGB32); 
	BRIETipIconView* IconView = new BRIETipIconView(drbeicon,IconViewLocation);
	IconView->SetDrawingMode(B_OP_OVER);
	AddChild(IconView);

    AddChild(btnOkay);
	AddChild(stvTipTitle);
	AddChild(chkDontShowAgain);
    //AddChild(stvDescription);
    //AddChild(stvDescription2);
    
    stvTipTitle->AttachedToWindow();
    chkDontShowAgain->AttachedToWindow();
    //stvDescription->AttachedToWindow();
    //stvDescription2->AttachedToWindow();
    
	// Create the Views
	AddChild(ptrHelpTipView = new HelpTipView(r));
}
// -------------------------------------------------------------------------------------------------- //


// HelpTipWindow::QuitRequested -- Post a message to the app to quit
bool HelpTipWindow::QuitRequested()
{
	//be_app->PostMessage(B_QUIT_REQUESTED);
	Hide();
	return true;
}
// -------------------------------------------------------------------------------------------------- //


// HelpTipWindow::SaveTipSettings -- Saves whether you want to see the tip again or not
void HelpTipWindow::SaveTipSettings(void)
{
	BMessage msg;
		
	switch (TipNumber) {
		case 1:
			kDontShowAgain = "Tip #1";
			break;
		case 2:
			kDontShowAgain = "Tip #2";
			break;
	}
	
	msg.AddInt32(kDontShowAgain,chkDontShowAgain->Value());
	
	// check for existence of tip settings file
	
	// if exists search for kDontShowAgain - can we remove it ?
	
	// if it doesnt exist or it doesnt exist in our search
    BPath path;
    status_t result = find_directory(B_USER_SETTINGS_DIRECTORY,&path);
    if (result == B_OK)
    {
	    path.Append("BRIE_Tip_Settings",true);
    	BFile file(path.Path(),B_READ_WRITE | B_CREATE_FILE | B_ERASE_FILE);
	    msg.Flatten(&file);
	}    
}
// -------------------------------------------------------------------------------------------------- //


// HelpTipWindow::MessageReceived -- receives messages
void HelpTipWindow::MessageReceived (BMessage *message)
{
	switch(message->what)
	{
		case BTN_OKAY:
			SaveTipSettings();
			Hide(); // change later if necessary
			break;
		default:
			BWindow::MessageReceived(message);
			break;
	}
}
// -------------------------------------------------------------------------------------------------- //
