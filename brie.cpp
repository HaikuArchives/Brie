/*

BRIE by the Sikosis

Released under the MIT license.

(C) 2002-2004 http://brie.gravity24hr.com/
*/

// Includes -------------------------------------------------------------------------------------------------- //
#include <Alert.h>
#include <Application.h>
#include <Bitmap.h>
#include <Button.h>
#include <Deskbar.h>
#include <Entry.h>
#include <File.h>
#include <FilePanel.h>
#include <ListView.h>
#include <Path.h>
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
// ---------------------------------------------------------------------------------------------------------- //

// Constants ------------------------------------------------------------------------------------------------ //
const char *APP_SIGNATURE = "application/x-vnd.BRIE";  // Application Signature and Title
int TipNumber = 0;
int ShowWinProj = 1;
int ShowWinProp = 1;
int ShowWinTool = 1;
int PanelType = 0;
PropertiesWindow* ptrPropertiesWindow;
ToolboxWindow*    ptrToolboxWindow;
ProjectWindow*    ptrProjectWindow;
FileWindow*       ptrFileWindow;

MenuCreator*	  ptrMenuCreator; // not sure if this is needed here ... remove later if not
InputBoxWindow*   ptrInputBoxWindow;

BString ProjectName;
BString ProjectPath;
BString ProjectAuthor;
BMessage ProjectFiles(ADD_PROJECT_FILE);

// Default Window Size - even though we centre the form to the current screen size
float FormTopDefault = 30;
float FormLeftDefault = 5;
float FormWidthDefault = 695;
float FormHeightDefault = 24;

float ProjectFormTopDefault = 0;
float ProjectFormLeftDefault = 0;
float ProjectFormWidthDefault = 225;
float ProjectFormHeightDefault = 155;

float ToolboxFormTopDefault = 0;
float ToolboxFormLeftDefault = 0;
float ToolboxFormWidthDefault = 50;
float ToolboxFormHeightDefault = 300;

float PropertiesFormTopDefault = 0;
float PropertiesFormLeftDefault = 0;
float PropertiesFormWidthDefault = 225;
float PropertiesFormHeightDefault = 200; // was 250

BRect windowRect(FormTopDefault,FormLeftDefault,FormLeftDefault+FormWidthDefault,FormTopDefault+FormHeightDefault);
BRect projectwindowRect(ProjectFormTopDefault,ProjectFormLeftDefault,ProjectFormLeftDefault+ProjectFormWidthDefault,ProjectFormTopDefault+ProjectFormHeightDefault);
BRect toolboxwindowRect(ToolboxFormTopDefault,ToolboxFormLeftDefault,ToolboxFormLeftDefault+ToolboxFormWidthDefault,ToolboxFormTopDefault+ToolboxFormHeightDefault);
BRect propertieswindowRect(PropertiesFormTopDefault,PropertiesFormLeftDefault,PropertiesFormLeftDefault+PropertiesFormWidthDefault,PropertiesFormTopDefault+PropertiesFormHeightDefault);
// ---------------------------------------------------------------------------------------------------------- //


// BRIE -- constructor for BRIE Class
BRIE::BRIE() : BApplication (APP_SIGNATURE)
{
	propertiesWindow = new PropertiesWindow(propertieswindowRect);
	projectWindow = new ProjectWindow(projectwindowRect);
	toolboxWindow = new ToolboxWindow(toolboxwindowRect);
	fileWindow = new FileWindow(windowRect);
	
	ProjectName.SetTo("Untitled");
	ProjectPath.SetTo("");
	ProjectAuthor.SetTo("");
}
// ---------------------------------------------------------------------------------------------------------- //


// BRIE::MessageReceived -- handles incoming messages
void BRIE::MessageReceived (BMessage *message)
{
	switch(message->what)
	{
	    default:
    	    BApplication::MessageReceived(message); // pass it along ... 
        	break;
    }
}
// ---------------------------------------------------------------------------------------------------------- //


// BRIE::RefsReceived
void BRIE::RefsReceived (BMessage *message)
{
	uint32 type;
	int32 count;
	entry_ref ref;
	
	message->GetInfo("refs", &type, &count);
	if (type != B_REF_TYPE)
		return;
	for (long i = --count; i >=0; i--)
	{
		if (message->FindRef("refs", i, &ref) == B_OK)
		{
			BFile LocationDir;
			if (LocationDir.SetTo(&ref, B_READ_ONLY) == B_OK)
			{
				BPath LocationDir (&ref);
				
				// need to lock the app and the windows's looper as well ...
				be_app->Lock();
				ptrFileWindow->LockLooper();
				ptrProjectWindow->stvProjectName->SetText(LocationDir.Path());
				ptrFileWindow->UnlockLooper();
				be_app->Unlock();
				ProjectName.SetTo(LocationDir.Path());
			}	
		}	
	}
}
// ------------------------------------------------------------------------------------------------- //


// BRIE Main
int main(void)
{
   BRIE theApp;
   theApp.Run();
   return 0;
}
// end ------------------------------------------------------------------------------------------------------ //

