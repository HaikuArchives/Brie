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
#include <Path.h>
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
	
	switch(TipNumber)
	{
		case 1:
			sprintf(TipTitle,"BRIE Tip #%i - %s",TipNumber,"Loading Projects");
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
	//stvDescription3 = new BStringView(BRect(LeftMarginDescription, DescriptionTop+28, RightMargin, DescriptionTop+38), "Description3", "We may look at supporting other languages such as Python/Bethon,");
	//stvDescription4 = new BStringView(BRect(LeftMarginDescription, DescriptionTop+40, RightMargin, DescriptionTop+50), "Description4", "Pascal, BASIC, etc.");
	//stvDescription5 = new BStringView(BRect(LeftMarginDescription, DescriptionTop+58, RightMargin, DescriptionTop+68), "Description5", "If you would like to help out with this project or have feedback,");
	//stvDescription6 = new BStringView(BRect(LeftMarginDescription, DescriptionTop+70, RightMargin, DescriptionTop+80), "Description6", "please visit our web site or email us.");
		
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
    //AddChild(stvDescription);
    //AddChild(stvDescription2);
    //AddChild(stvDescription3);
    //AddChild(stvDescription4);
    //AddChild(stvDescription5);
    //AddChild(stvDescription6);
    
    stvTipTitle->AttachedToWindow();
    
    //stvDescription->AttachedToWindow();
    //stvDescription2->AttachedToWindow();
    //stvDescription3->AttachedToWindow();
    //stvDescription4->AttachedToWindow();
    //stvDescription5->AttachedToWindow();
    //stvDescription6->AttachedToWindow();
    
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


// HelpTipWindow::MessageReceived -- receives messages
void HelpTipWindow::MessageReceived (BMessage *message)
{
	switch(message->what)
	{
		case BTN_OKAY:
			Hide(); // change later if necessary
			break;
		default:
			BWindow::MessageReceived(message);
			break;
	}
}
// -------------------------------------------------------------------------------------------------- //
