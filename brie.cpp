/*

BRIE by the Sikosis

Released under the MIT license.

(C) 2002-2003 http://brie.gravity24hr.com/
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
#include <string.h>
#include <TextControl.h>
#include <Window.h>
#include <View.h>

#include "brieconstants.h"
#include "brie.h"
#include "BRIEWindows.h"
#include "BRIEViews.h"
// ---------------------------------------------------------------------------------------------------------- //

// Constants ------------------------------------------------------------------------------------------------ //
const char *APP_SIGNATURE = "application/x-vnd.BRIE";  // Application Signature and Title

// Default Window Size - even though we centre the form to the current screen size
float FormTopDefault = 30;
float FormLeftDefault = 5;
float FormWidthDefault = 695;
float FormHeightDefault = 25;

float ProjectFormTopDefault = 0;
float ProjectFormLeftDefault = 0;
float ProjectFormWidthDefault = 225;
float ProjectFormHeightDefault = 105;

float ToolboxFormTopDefault = 0;
float ToolboxFormLeftDefault = 0;
float ToolboxFormWidthDefault = 50;
float ToolboxFormHeightDefault = 300;

float PropertiesFormTopDefault = 0;
float PropertiesFormLeftDefault = 0;
float PropertiesFormWidthDefault = 225;
float PropertiesFormHeightDefault = 300;

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


// BRIE Main
int main(void)
{
   BRIE theApp;
   theApp.Run();
   return 0;
}
// end ------------------------------------------------------------------------------------------------------ //
