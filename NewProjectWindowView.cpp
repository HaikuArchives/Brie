/*

NewProjectWindowView by Sikosis

Released under the MIT license.

(C) 2002-2003 http://brie.sf.net/

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

// NewProjectWindowView - Constructor
NewProjectWindowView::NewProjectWindowView (BRect frame) : BView (frame, "NewProjectWindowView", B_FOLLOW_ALL_SIDES, B_WILL_DRAW )
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR)); // Set the Background Color
}
// ---------------------------------------------------------------------------------------------------------- //


void NewProjectWindowView::Draw(BRect drawRect)
{
	BRect r;
	r = Bounds();
	
	float LineTop = 66.0;
	float LineBottom = 67.0;
	
	rgb_color whitebar = { 255, 255, 255, 0 };
	rgb_color darkbar = { 160, 160, 160, 0 };
	
	SetHighColor(whitebar);
	StrokeLine(BPoint(8,LineTop),BPoint(r.right-9,LineTop)); // top line
	
	SetHighColor(darkbar);
	StrokeLine(BPoint(8,LineBottom),BPoint(r.right-9,LineBottom)); // bottom line

}
// ---------------------------------------------------------------------------------------------------------- //

