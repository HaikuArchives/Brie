/*

AboutWindowView

Coded by Sikosis

Released under the MIT license.

(C)2004 http://sikosis.com/

*/


// Includes -------------------------------------------------------------------------------------------------- //
#include <Alert.h>
#include <Application.h>
#include <Bitmap.h>
#include <Button.h>
#include <Font.h>
#include <Locker.h>
#include <Screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <StringView.h>
#include <TextControl.h>
#include <Window.h>
#include <View.h>

#include "AboutConstants.h"
#include "brieicon.h"
#include "AboutWindowView.h"
// ------------------------------------------------------------------------------------------------------------- //

// AboutWindowView - Constructor
AboutWindowView::AboutWindowView (BRect frame) : BView (frame, "AboutWindowView", B_FOLLOW_ALL_SIDES, B_WILL_DRAW )
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR)); // Set the Background Color
	
	BRect r;
	r = Bounds(); // the whole view
	
	float LeftMarginTitles = 55;
	float LeftMargin = 6;
	float LeftMarginDescription = 50;
	float RightMargin = r.right - 12;
	float DescriptionTop = 80;
	float OkayButtonSize = 130;
	float OkayLeftMargin = (RightMargin / 2) - (OkayButtonSize / 2) + 23;
	float WebSiteSize = 126;
	float WebSiteMargin = (RightMargin / 2) - (WebSiteSize / 2) + 23;
		
	rgb_color AppNameFontColor = { 0,0,0,0 };	
	stvAppName = new BStringView(BRect(LeftMarginTitles, 16, LeftMarginTitles+300, 40), "AppName", "BeOS Rapid Integrated Environment (BRIE)");
	stvAppName->SetFont(be_bold_font);
	stvAppName->SetFontSize(18.0);
	stvAppName->SetHighColor(AppNameFontColor);
		
	stvVersion = new BStringView(BRect(LeftMarginTitles+2, r.top+43, 97, r.top+53), "Version:", "Version:");
	//urlVersion = new URLView(BRect(LeftMarginTitles+53, r.top+43, 160, r.top+53), "urlVersion", "0.37", "http://brie.sf.net/");
	stvVersionNumber = new BStringView(BRect(LeftMarginTitles+53, r.top+43, 160, r.top+53), "stvVersionNumber", "0.38");
		
	stvEmail = new BStringView(BRect(LeftMarginTitles+2, r.top+57, 103, r.top+67), "Coded by", "Coded by");
	//urlEmail = new URLView(BRect(LeftMarginTitles+53, r.top+57, LeftMarginTitles+85, r.top+67), "urlEmail", "Sikosis", "beos@gravity24hr.com");
	stvEmailAddress = new BStringView(BRect(LeftMarginTitles+53, r.top+57, LeftMarginTitles+185, r.top+67), "brie@g24.com.au", "brie@g24.com.au");
		
	//stvEmail2 = new BStringView(BRect(LeftMarginTitles+85, r.top+57, RightMargin, r.top+67), "emailname", "(Phil Greenway)");

	//urlEmail->AddAttribute("META:name", "Phil Greenway");
	//urlEmail->AddAttribute("META:nickname", "Sikosis");
	//urlEmail->AddAttribute("META:company", "Gravity 24 Hour");
	//urlEmail->AddAttribute("META:url", "http://g24.com.au/");
	//urlEmail->AddAttribute("META:state", "QLD");
	//urlEmail->AddAttribute("META:country", "Australia");
  	
	txvDescription = new BTextView(BRect(LeftMarginDescription, DescriptionTop, RightMargin, DescriptionTop+80),
						 "Description", BRect(0,0,RightMargin-LeftMarginDescription,80), B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
	txvDescription->SetWordWrap(true);
	txvDescription->MakeEditable(true);
	txvDescription->SetStylable(true);
	txvDescription->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	txvDescription->Insert("BRIE is an IDE for rapid development of native BeOS applications. All code is generated in C/C++ using the BeAPI plus a few extras. We may look at supporting other languages such as Python/Bethon, Pascal, BASIC, etc.\nIf you would like to help out with this project or have feedback,\nplease visit our web site or email us.");
			
  	btnOkay = new BButton(BRect (OkayLeftMargin,r.bottom-60,OkayLeftMargin+OkayButtonSize,r.bottom-30),"Okay","Okay", new BMessage(BTN_OKAY), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
  	btnOkay->MakeDefault(true);
	//urlWebSite = new URLView(BRect(WebSiteMargin, r.bottom-27, WebSiteMargin+WebSiteSize, r.bottom-7), "urlWebSite", "http://brie.sourceforge.net/", "http://brie.sourceforge.net/");
  	stvWebSiteAddress = new BStringView(BRect(WebSiteMargin, r.bottom-27, WebSiteMargin+WebSiteSize, r.bottom-7), "http://brie.sourceforge.net", "http://brie.sourceforge.net");
  	
  	// create icon for About Window
  	BRect IconFrame (BRect(0,0,31,31));
  	BRect IconViewLocation (BRect(LeftMargin+7,r.top+10,LeftMargin+53,r.top+55));
  	BBitmap *brieicon = new BBitmap(IconFrame,B_RGB32);
	brieicon->SetBits(brieimageicon,3072,0,B_RGB32); 
	AboutIconView* IconView = new AboutIconView(brieicon,IconViewLocation);
	IconView->SetDrawingMode(B_OP_OVER);
	AddChild(IconView);
	
	AddChild(stvVersionNumber);
	AddChild(stvWebSiteAddress);
	//AddChild(urlWebSite);
    AddChild(btnOkay);
    //AddChild(urlEmail);
    AddChild(stvEmailAddress);
    AddChild(stvEmail);
    //AddChild(stvEmail2);
    //AddChild(urlVersion);
    AddChild(stvVersion);
    
    AddChild(txvDescription);
    AddChild(stvAppName);
	
}
// ---------------------------------------------------------------------------------------------------------- //


void AboutWindowView::Draw(BRect /*updateRect*/)
{
	BRect r = Bounds();
	rgb_color darkbar = { 120, 120, 120, 255 };
	
	SetLowColor(darkbar);
	SetHighColor(darkbar);
	FillRect(BRect(0,0,34,r.bottom), B_SOLID_HIGH);
}
// ---------------------------------------------------------------------------------------------------------- //


// AboutWindowView::MessageReceived -- receives messages
void AboutWindowView::MessageReceived (BMessage *message)
{
	switch(message->what)
	{
		default:
			BView::MessageReceived(message);
			break;
	}
}
// ---------------------------------------------------------------------------------------------------------- //


// AboutIconView - Constructor
AboutIconView::AboutIconView (BBitmap* bitmap, BRect frame) : BView (frame, "AboutIconView", B_FOLLOW_NONE, B_WILL_DRAW )
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR)); // Set the Background Color
	
	icon = bitmap;
}
// ---------------------------------------------------------------------------------------------------------- //


void AboutIconView::Draw(BRect /*updateRect*/)
{
	BRect r = Bounds();
	rgb_color darkbar = { 120, 120, 120, 255 };
	
	SetLowColor(darkbar);
	SetHighColor(darkbar);
	FillRect(BRect(0,0,21,r.bottom), B_SOLID_HIGH);
	
	DrawBitmap(icon,BPoint(6,10));
}
// ---------------------------------------------------------------------------------------------------------- //


