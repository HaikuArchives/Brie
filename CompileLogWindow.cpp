/*

BeOS Rapid Integrated Environment (BRIE)

CompileLogWindow by Sikosis

Released under the MIT license.

(C) 2004 http://brie.sf.net/

*/


// Includes -------------------------------------------------------------------------------------------------- //
#include <Application.h>
//#include <Bitmap.h>
//#include <Button.h>
//#include <Entry.h>
//#include <File.h>
#include <Path.h>
//#include <Picture.h>
//#include <PictureButton.h>
#include <Screen.h>
#include <TextView.h>
//#include <ScrollView.h>
#include <stdio.h>
#include <Window.h>
#include <View.h>

#include "brie.h"
#include "BRIEWindows.h"
#include "BRIEViews.h"
#include "brieconstants.h"
// ---------------------------------------------------------------------------------------------------------- //

// TopOfScreen -- Places the BWindow starting from the top of the Current Screen
static void TopOfScreen(BWindow* w)
{
	BRect	screenFrame = (BScreen(B_MAIN_SCREEN_ID).Frame());
	BPoint 	pt;
	pt.x = 5;
	pt.y = screenFrame.Height() - 175;

	if (screenFrame.Contains(pt))
		w->MoveTo(pt);
	
	int NewWidth = (int) screenFrame.Width() - 130;
	w->ResizeTo(NewWidth,165); // resize to the current screen size
}
// ---------------------------------------------------------------------------------------------------------- //


// CompileLogWindow - Constructor
CompileLogWindow::CompileLogWindow(BRect frame) : BWindow (frame, "Compile Log", B_TITLED_WINDOW, B_NOT_RESIZABLE , 0)
{
	//ptrCompileLogWindow = this; // undefined reference error ???
	InitWindow();
	TopOfScreen(this);
	Show();
}
// ---------------------------------------------------------------------------------------------------------- //


// CompileLogWindow - Destructor
CompileLogWindow::~CompileLogWindow()
{
	//exit(0);
}
// ---------------------------------------------------------------------------------------------------------- //


// CompileLogWindow::InitWindow -- Initialization Commands here
void CompileLogWindow::InitWindow(void)
{
	BRect r;
	r = Bounds();
    // Add Controls
    
    txvLog = new BTextView(BRect(2, 2, r.right-2, r.bottom-2),
						 "Log", BRect(0,0,r.right,r.bottom), B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
	txvLog->SetWordWrap(true);
	txvLog->MakeEditable(true);
	txvLog->SetStylable(true);
    
	// Add the Drawing View
	AddChild(ptrCompileLogView = new CompileLogView(r));
	ptrCompileLogView->AddChild(txvLog);
}
// ---------------------------------------------------------------------------------------------------------- //


// CompileLogWindow::QuitRequested -- Post a message to the app to quit
bool CompileLogWindow::QuitRequested()
{
	return true;
}
// ---------------------------------------------------------------------------------------------------------- //


// CompileLogWindow::MessageReceived -- receives messages
void CompileLogWindow::MessageReceived (BMessage *message)
{
	switch(message->what)
	{
		case LOAD_COMPILE_LOG:
			{
				BString CompileLogFileName;
				CompileLogFileName.SetTo(ProjectPath.String());
				CompileLogFileName.Append("/projects/");
				CompileLogFileName.Append(ProjectName.String());
				CompileLogFileName.Append("/compile.log");
				// one day ill replace this load code with bespecific stuff rather than
				// using generic c/c++ code
				BString CompileLog;
				CompileLog.SetTo(""); // not sure if this is needed
				FILE *f;
				char buffer[4096];
				int x;
				f = fopen(CompileLogFileName.String(),"r");
				if (f == NULL) {
					txvLog->Insert("ERROR: Loading Log File.\n");
				} else {
					while(fgets(buffer,sizeof(buffer),f) !=NULL) {
						//fgets (buffer , sizeof(buffer) , f);
						puts(buffer);
						CompileLog.Append(buffer);
					}
					fclose (f);
   				}
				txvLog->Insert(CompileLog.String());
			}
			break;
		default:
			BWindow::MessageReceived(message);
			break;
	}
}
// ---------------------------------------------------------------------------------------------------------- //


