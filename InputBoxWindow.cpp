/*

InputBoxWindow

Author: Sikosis

Released under the MIT license.

(C)2003 BRIE (http://brie.sf.net/)

*/

// Includes ------------------------------------------------------------------------------------------ //
#include <Alert.h>
#include <Application.h>
#include <Button.h>
#include <Screen.h>
#include <ScrollView.h>
#include <stdio.h>
#include <String.h>
#include <TextControl.h>
#include <Window.h>
#include <View.h>

#include "brie.h"
#include "BRIEWindows.h"
#include "BRIEViews.h"
#include "brieconstants.h"

// Constants ---------------------------------------------------------------------------------------- //
const uint32 TXT_OKAY = 'TOky';
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


// InputBoxWindow - Constructor
InputBoxWindow::InputBoxWindow(BRect frame) : BWindow (frame, "InputBox", B_MODAL_WINDOW, B_NORMAL_WINDOW_FEEL , 0)
{
	ptrInputBoxWindow = this;
	InitWindow();
	CenterWindowOnScreen(this);
	Show();
}
// -------------------------------------------------------------------------------------------------- //


// InputBoxWindow - Destructor
InputBoxWindow::~InputBoxWindow()
{
	//exit(0);
}
// -------------------------------------------------------------------------------------------------- //


// InputBoxWindow::InitWindow -- Initialization Commands here
void InputBoxWindow::InitWindow(void)
{
	BRect r;
	r = Bounds(); // the whole view
		
	float LeftMarginTitles = 55;
	float LeftMargin = 6;
	float LeftMarginText = LeftMarginTitles;
	float TextTop = 40;
	float RightMargin = r.right;
	float OkayButtonSize = 70;
	float OkayLeftMargin = RightMargin - OkayButtonSize - 10;
	
	txtQuestion = new BTextControl(BRect(LeftMarginText, TextTop, RightMargin, TextTop+10), "txtQuestion",
					"Your Question:", "Value", new BMessage(TXT_OKAY), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
		
  	btnOkay = new BButton(BRect (OkayLeftMargin,r.bottom-35,OkayLeftMargin+OkayButtonSize,r.bottom-15),"Okay",
  					"Okay", new BMessage(BTN_OKAY), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
  	btnOkay->MakeDefault(true);
  	
  	AddChild(txtQuestion);
    AddChild(btnOkay);
    
	// Create the Views
	AddChild(ptrInputBoxView = new InputBoxView(r));
}
// -------------------------------------------------------------------------------------------------- //

void InputBoxWindow::SetTo(BString IBTitle, BString IBQuestion, BString IBDefault, BString IBAnswer)
{
	ptrInputBoxWindow->txtQuestion->SetText(IBQuestion.String());
	printf("SetTo %s",IBQuestion.String());
}
// -------------------------------------------------------------------------------------------------- //


// InputBoxWindow::QuitRequested -- Post a message to the app to quit
bool InputBoxWindow::QuitRequested()
{
	return true;
}
// -------------------------------------------------------------------------------------------------- //


// InputBoxWindow::MessageReceived -- receives messages
void InputBoxWindow::MessageReceived (BMessage *message)
{
	switch(message->what)
	{
		case BTN_OKAY:
			Quit();
			break;
		default:
			BWindow::MessageReceived(message);
			break;
	}
}
// -------------------------------------------------------------------------------------------------- //
