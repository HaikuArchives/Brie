/*

CompileLogView by Sikosis

Released under the MIT license.

(C) 2004 http://brie.sf.net/

*/

// Includes -------------------------------------------------------------------------------------------------- //
//#include <Alert.h>
#include <Application.h>
//#include <Button.h>
//#include <Entry.h>
//#include <File.h>
//#include <FilePanel.h>
//#include <ListView.h>
//#include <Path.h>
//#include <Screen.h>
//#include <ScrollView.h>
//#include <stdio.h>
//#include <string.h>
//#include <TextControl.h>
#include <Window.h>
#include <View.h>

#include "brie.h"
#include "BRIEWindows.h"
#include "BRIEViews.h"
#include "brieconstants.h"
// ------------------------------------------------------------------------------------------------------------- //


// CompileLogView - Constructor
CompileLogView::CompileLogView (BRect frame) : BView (frame, "CompileLogView", B_FOLLOW_ALL_SIDES, B_WILL_DRAW )
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR)); // Set the Background Color
}
// ---------------------------------------------------------------------------------------------------------- //

