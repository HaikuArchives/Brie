/*

BRIE - AboutWindow by Sikosis

Released under the MIT license.

(C)2002

*/


// Includes -------------------------------------------------------------------------------------------------- //
#include <Alert.h>
#include <Application.h>
#include <Bitmap.h>
#include <Button.h>
#include <Font.h>
#include <Screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <StringView.h>
#include <TextControl.h>
#include <Window.h>
#include <View.h>

#include "brieicon.h"
#include "BRIEWindows.h"
#include "BRIEViews.h"
#include "URLView.h"

// Constants ------------------------------------------------------------------------------------------------- //
const uint32 BTN_OKAY = 'BOky';
// ---------------------------------------------------------------------------------------------------------- //


// CenterWindowOnScreen -- Centers the BWindow to the Current Screen
static void CenterWindowOnScreen(BWindow* w)
{
	BRect	screenFrame = (BScreen(B_MAIN_SCREEN_ID).Frame());
	BPoint 	pt;
	pt.x = screenFrame.Width()/2 - w->Bounds().Width()/2;
	pt.y = screenFrame.Height()/2 - w->Bounds().Height()/2;

	if (screenFrame.Contains(pt))
		w->MoveTo(pt);
}
// ---------------------------------------------------------------------------------------------------------- //


// AboutWindow - Constructor
AboutWindow::AboutWindow(BRect frame) : BWindow (frame, "About BRIE ...", B_FLOATING_WINDOW , B_FLOATING_APP_WINDOW_FEEL , 0)
{
	InitWindow();
	CenterWindowOnScreen(this);
	Show();
}


// AboutWindow - Destructor
AboutWindow::~AboutWindow()
{
	//exit(0);
}


// AboutWindow::InitWindow
void AboutWindow::InitWindow(void)
{	
	BRect r;
	r = Bounds(); // the whole view
	
	int LeftMarginTitles = 55;
	int LeftMargin = 6;
	float RightMargin = r.right;
	int DescriptionTop = 80;
	int OkayButtonSize = 130;
	int OkayLeftMargin = (RightMargin / 2) - (OkayButtonSize / 2);
	int WebSiteSize = 126;
	int WebSiteMargin = (RightMargin / 2) - (WebSiteSize / 2);
	
	
	rgb_color AppNameFontColor = { 0,0,0,0 };	
	
	stvAppName = new BStringView(BRect(LeftMarginTitles, 16, LeftMarginTitles+300, 40), "AppName", "BeOS Rapid Integrated Environment (BRIE)");
	stvAppName->SetFont(be_bold_font);
	stvAppName->SetFontSize(18.0);
	stvAppName->SetHighColor(AppNameFontColor);
	
	
	/*
	SetFontAndColor(int32 start, int32 finish, 
      const BFont *font, uint32 properties = B_FONT_ALL, rgb_color *color = NULL) 

	SetFontAndColor(const BFont *font, uint32 properties = B_FONT_ALL, rgb_color *color = NULL)
	*/
	
	stvVersion = new BStringView(BRect(LeftMarginTitles+2, r.top+43, 97, r.top+53), "Version:", "Version:");
	urlVersion = new URLView(BRect(LeftMarginTitles+53, r.top+43, 160, r.top+53), "urlVersion", "0.3", "http://brie.sf.net/");
	
	stvEmail = new BStringView(BRect(LeftMarginTitles+2, r.top+57, 103, r.top+67), "Coded by", "Coded by");
	urlEmail = new URLView(BRect(LeftMarginTitles+53, r.top+57, LeftMarginTitles+85, r.top+67), "urlEmail", "Sikosis", "beos@gravity24hr.com");
	stvEmail2 = new BStringView(BRect(LeftMarginTitles+85, r.top+57, RightMargin, r.top+67), "emailname", "(Phil Greenway)");

	urlEmail->AddAttribute("META:name", "Phil Greenway");
	urlEmail->AddAttribute("META:nickname", "Sikosis");
	urlEmail->AddAttribute("META:company", "Gravity 24 Hour");
	urlEmail->AddAttribute("META:url", "http://www.gravity24hr.com/");
	urlEmail->AddAttribute("META:state", "QLD");
	urlEmail->AddAttribute("META:country", "Australia");
  	
	stvDescription = new BStringView(BRect(LeftMargin, DescriptionTop, RightMargin, DescriptionTop+10), "Description", "BRIE is a IDE environment for rapid development of native BeOS applications.");
	stvDescription2 = new BStringView(BRect(LeftMargin, DescriptionTop+12, RightMargin, DescriptionTop+22), "Description2", "");
	stvDescription3 = new BStringView(BRect(LeftMargin, DescriptionTop+26, RightMargin, DescriptionTop+36), "Description3", "All code is generated in C/C++ using the BeAPI plus a few extras.");
	stvDescription4 = new BStringView(BRect(LeftMargin, DescriptionTop+38, RightMargin, DescriptionTop+48), "Description4", "");
	stvDescription5 = new BStringView(BRect(LeftMargin, DescriptionTop+50, RightMargin, DescriptionTop+60), "Description5", "If you would like to help out with this project or have feedback,");
	stvDescription6 = new BStringView(BRect(LeftMargin, DescriptionTop+68, RightMargin, DescriptionTop+78), "Description6", "please visit our web site or email us.");
		
  	btnOkay = new BButton(BRect (OkayLeftMargin,r.bottom-60,OkayLeftMargin+OkayButtonSize,r.bottom-30),"Okay","Okay", new BMessage(BTN_OKAY), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
  	btnOkay->MakeDefault(true);
	urlWebSite = new URLView(BRect(WebSiteMargin, r.bottom-27, WebSiteMargin+WebSiteSize, r.bottom-7), "urlWebSite", "http://brie.sourceforge.net/", "http://brie.sourceforge.net/");
  	
  	// create icon for About Window
  	BRect IconFrame (BRect(0,0,31,31));
  	BRect IconViewLocation (BRect(LeftMargin+2,r.top+10,LeftMargin+48,r.top+55));
  	BBitmap *brieicon = new BBitmap(IconFrame,B_RGB32);
	brieicon->SetBits(brieimageicon,3072,0,B_RGB32); 
	BRIEIconView* IconView = new BRIEIconView(brieicon,IconViewLocation);
	IconView->SetDrawingMode(B_OP_OVER);
	AddChild(IconView);

	AddChild(urlWebSite);
    AddChild(btnOkay);
    AddChild(urlEmail);
    AddChild(stvEmail);
    AddChild(stvEmail2);
    AddChild(urlVersion);
    AddChild(stvVersion);
    AddChild(stvDescription);
    AddChild(stvDescription2);
    AddChild(stvDescription3);
    AddChild(stvDescription4);
    AddChild(stvDescription5);
    AddChild(stvDescription6);
    
    stvAppName->AttachedToWindow();
    
    stvDescription->AttachedToWindow();
    stvDescription2->AttachedToWindow();
    stvDescription3->AttachedToWindow();
    stvDescription4->AttachedToWindow();
    stvDescription5->AttachedToWindow();
    stvDescription6->AttachedToWindow();
    
    AddChild(stvAppName);
    AddChild(ptrAboutWindowView = new AboutWindowView(r));
}
// ---------------------------------------------------------------------------------------------------------- //


// AboutWindow::MessageReceived -- receives messages
void AboutWindow::MessageReceived (BMessage *message)
{
	switch(message->what)
	{
		case BTN_OKAY:
			Hide(); // Quit(); // exit(0); // change later 
			break;
		default:
			BWindow::MessageReceived(message);
			break;
	}
}
// ---------------------------------------------------------------------------------------------------------- //


