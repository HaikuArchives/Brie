/*

InputBoxWindow

Author: Sikosis

Released under the MIT license.

(C)2003-2004 BRIE (http://brie.sf.net/)

*/

// Includes ------------------------------------------------------------------------------------------ //
#include <Alert.h>
#include <Application.h>
#include <Button.h>
#include <Message.h>
#include <Screen.h>
#include <ScrollView.h>
#include <stdio.h>
#include <String.h>
#include <StringView.h>
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
	
	Lock();
	txtQuestion->MakeFocus(true);
	Unlock();
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
		
	float LeftMargin = 6;
	float TextTop = 8;
	float RightMargin = r.right - 10;
	float OkayButtonSize = 70;
	float OkayLeftMargin = RightMargin - OkayButtonSize - 10;
	
	stvQuestion = new BStringView(BRect(LeftMargin, TextTop, RightMargin, TextTop+10), "stvQuestion",
					 "Question:", B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
	txtQuestion = new BTextControl(BRect(LeftMargin, TextTop-4, RightMargin, TextTop+10), "txtQuestion",
					"", "", new BMessage(TXT_OKAY), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
	//txtQuestion->SetDivider(0);
	rgb_color whitebackground = { 0, 0, 0, 0 };
	txtQuestion->SetViewColor(whitebackground);
	//txtQuestion->AttachedToWindow();
	
		
  	btnOkay = new BButton(BRect (OkayLeftMargin,r.bottom-35,OkayLeftMargin+OkayButtonSize,r.bottom-15),"Okay",
  					"Okay", new BMessage(BTN_OKAY), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
  	btnOkay->MakeDefault(true);
        
	// Create the Views
	AddChild(ptrInputBoxView = new InputBoxView(r));
	
	ptrInputBoxView->AddChild(stvQuestion);
	ptrInputBoxView->AddChild(txtQuestion);
	ptrInputBoxView->AddChild(btnOkay);
}
// -------------------------------------------------------------------------------------------------- //


void InputBoxWindow::SetTo(BString IBTitle, BString IBQuestion, BString IBDefault, BString IBAnswer)
{
	Lock();
	ptrInputBoxWindow->SetTitle(IBQuestion.String());
	ptrInputBoxWindow->stvQuestion->SetText(IBQuestion.String());
	ptrInputBoxWindow->txtQuestion->SetText(IBDefault.String());
	printf("SetTo %s\n",IBQuestion.String());
	printf("SetTo %s\n",IBDefault.String());
	Unlock();
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
		{
			// send the answer back
			BMessage answer(IB_ANSWER);
			answer.AddString("IB_ANSWER", txtQuestion->Text());
			BMessenger(ptrMenuCreator).SendMessage(&answer);
			Quit();
		}
			break;	
		default:
			BWindow::MessageReceived(message);
			break;
	}
}
// -------------------------------------------------------------------------------------------------- //
