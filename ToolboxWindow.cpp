/*

BeOS Rapid Integrated Environment (BRIE)

ToolboxWindow by Sikosis

Released under the MIT license.

(C) 2002-2003 http://brie.sf.net/

*/


// Includes -------------------------------------------------------------------------------------------------- //
//#include <Alert.h>
#include <Application.h>
#include <Bitmap.h>
#include <Button.h>
//#include <Entry.h>
//#include <File.h>
//#include <FilePanel.h>
//#include <ListView.h>
//#include <Path.h>
#include <Picture.h>
#include <PictureButton.h>
#include <Screen.h>
//#include <ScrollView.h>
#include <stdio.h>
//#include <string.h>
//#include <TextControl.h>
#include <Window.h>
#include <View.h>

#include "Bitmaps-ToolboxControls.h"

#include "brie.h"
#include "BRIEWindows.h"
#include "BRIEViews.h"
#include "brieconstants.h"
// ---------------------------------------------------------------------------------------------------------- //
const uint32 TOOLBOX_BTN_STRINGVIEWCONTROL = 'tbsv';
const uint32 TOOLBOX_BTN_TEXTCONTROL = 'tbtc';
const uint32 TOOLBOX_BTN_BUTTONCONTROL = 'tbbc';
const uint32 TOOLBOX_BTN_PICTURECONTROL = 'tbpc';

// TopOfScreen -- Places the BWindow starting from the top of the Current Screen
static void TopOfScreen(BWindow* w)
{
	BRect	screenFrame = (BScreen(B_MAIN_SCREEN_ID).Frame());
	BPoint 	pt;
	pt.x = 5;
	pt.y = 110;

	if (screenFrame.Contains(pt))
		w->MoveTo(pt);
	
	int BottomToolbox = (int) screenFrame.Height() - 314;
	w->ResizeTo(w->Bounds().Width(),BottomToolbox);
}
// ---------------------------------------------------------------------------------------------------------- //


// ToolboxWindow - Constructor
ToolboxWindow::ToolboxWindow(BRect frame) : BWindow (frame, "Toolbox", B_TITLED_WINDOW, B_NOT_RESIZABLE , 0)
{
	ptrToolboxWindow = this;
	InitWindow();
	TopOfScreen(this);
	Show();
}
// ---------------------------------------------------------------------------------------------------------- //


// ToolboxWindow - Destructor
ToolboxWindow::~ToolboxWindow()
{
	//exit(0);
}
// ---------------------------------------------------------------------------------------------------------- //


// ToolboxWindow::InitWindow -- Initialization Commands here
void ToolboxWindow::InitWindow(void)
{
	BRect r;
	r = Bounds();
    // Add Controls
    
    // Toolbar
    //int ToolbarButtonMargin = 2;
    //int ToolbarButtonWidth = 22;
    //int ButtonGap = 1;
	
	// StringView Button
  	BRect BitmapFrame (BRect(0,0,23,23));
  	BPicture *tmpBPicture;
  	BPicture *tmpBPicture2;
  	BView    *tmpBPictureView = new BView(BitmapFrame, "tmpBPictureView",B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
  	rgb_color toolbar_button_background = { 255, 255, 255, 0 };
  	
  	AddChild(tmpBPictureView);
  	
  	BBitmap *stringviewpicture = new BBitmap(BitmapFrame,B_RGB32);
	stringviewpicture->SetBits(stringviewicon,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(stringviewpicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *stringviewpicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	stringviewpicture_state2->SetBits(stringviewiconinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(stringviewpicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnBrieStringViewControl = new BPictureButton(BRect (1,0,24,23),"StringView",tmpBPicture,tmpBPicture2, new BMessage(TOOLBOX_BTN_STRINGVIEWCONTROL),B_ONE_STATE_BUTTON, B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
 	 	
	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
    //--------------------------------------------------------------------//
        
    // TextView Button
    BBitmap *textviewpicture = new BBitmap(BitmapFrame,B_RGB32);
	textviewpicture->SetBits(brietextcontrol,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(textviewpicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *textviewpicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	textviewpicture_state2->SetBits(brietextcontrolinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(textviewpicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  	
  	btnBrieTextControl = new BPictureButton(BRect (26,0,50,23),"TextControl",tmpBPicture,tmpBPicture2, new BMessage(TOOLBOX_BTN_TEXTCONTROL),B_ONE_STATE_BUTTON, B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
 	
	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
	//--------------------------------------------------------------------//
	
	// Button Button
	BBitmap *buttonpicture = new BBitmap(BitmapFrame,B_RGB32);
	buttonpicture->SetBits(stringviewicon,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(buttonpicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *buttonpicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	buttonpicture_state2->SetBits(stringviewiconinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(buttonpicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnBrieButtonControl = new BPictureButton(BRect (1,25,24,48),
 							  "Button",tmpBPicture,tmpBPicture2, new BMessage(TOOLBOX_BTN_BUTTONCONTROL),B_ONE_STATE_BUTTON, B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
 	
	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
    //--------------------------------------------------------------------//
    
    // Picture Button
    BBitmap *picturepicture = new BBitmap(BitmapFrame,B_RGB32);
	picturepicture->SetBits(stringviewicon,1728,0,B_RGB32);
  	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(picturepicture,BPoint(0,0));
  	tmpBPicture = tmpBPictureView->EndPicture();
  	
  	tmpBPictureView->RemoveSelf();
    AddChild(tmpBPictureView);
  	
  	BBitmap *picturepicture_state2 = new BBitmap(BitmapFrame,B_RGB32);
	picturepicture_state2->SetBits(stringviewiconinverse,1728,0,B_RGB32);
	tmpBPictureView->SetLowColor(toolbar_button_background);
  	tmpBPictureView->BeginPicture(new BPicture);
  	tmpBPictureView->DrawBitmap(picturepicture_state2,BPoint(0,0));
  	tmpBPicture2 = tmpBPictureView->EndPicture();
  		
 	btnBriePictureControl = new BPictureButton(BRect (26,25,50,48),
 							  "TextControl",tmpBPicture,tmpBPicture2, new BMessage(TOOLBOX_BTN_PICTURECONTROL),B_ONE_STATE_BUTTON, B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
 	
	tmpBPictureView->RemoveSelf();
	AddChild(tmpBPictureView);
	//--------------------------------------------------------------------//
	
	
    AddChild(btnBriePictureControl);
    AddChild(btnBrieButtonControl);
    AddChild(btnBrieTextControl);
    AddChild(btnBrieStringViewControl);
	
	// Add the Drawing View
	AddChild(ptrToolboxWindowView = new ToolboxWindowView(r));
}
// ---------------------------------------------------------------------------------------------------------- //


// ToolboxWindow::QuitRequested -- Post a message to the app to quit
bool ToolboxWindow::QuitRequested()
{
	return true;
}
// ---------------------------------------------------------------------------------------------------------- //


// ToolboxWindow::MessageReceived -- receives messages
void ToolboxWindow::MessageReceived (BMessage *message)
{
	switch(message->what)
	{
		case TOOLBOX_BTN_STRINGVIEWCONTROL:
			{
				printf("New StringView\n");	
			}
			break;
		case TOOLBOX_BTN_TEXTCONTROL:
			{
				printf("New TextControl\n");	
			}
			break;	
		case TOOLBOX_BTN_BUTTONCONTROL:
			{
				printf("New ButtonControl\n");	
				// Ask if Standard or PictureButton
			}
			break;
		case TOOLBOX_BTN_PICTURECONTROL:
			{
				printf("New PictureControl\n");	
			}
			break;		
		default:
			BWindow::MessageReceived(message);
			break;
	}
}
// ---------------------------------------------------------------------------------------------------------- //
