/*

AboutWindowView by Sikosis

Released under the MIT license.

(C) 2002 http://brie.sf.net/

*/

// Includes -------------------------------------------------------------------------------------------------- //
//#include <Alert.h>
#include <Application.h>
#include <Bitmap.h>
//#include <Button.h>
//#include <Font.h>
//#include <Screen.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <StringView.h>
//#include <TextControl.h>
#include <Window.h>
#include <View.h>

#include "BRIEWindows.h"
#include "BRIEViews.h"
#include "URLView.h"
// ------------------------------------------------------------------------------------------------------------- //

// AboutWindowView - Constructor
AboutWindowView::AboutWindowView (BRect frame) : BView (frame, "AboutWindowView", B_FOLLOW_ALL_SIDES, B_WILL_DRAW )
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR)); // Set the Background Color
}
// ---------------------------------------------------------------------------------------------------------- //

// BRIEIconView - Constructor
BRIEIconView::BRIEIconView (BBitmap* bitmap, BRect frame) : BView (frame, "BRIEIconView", B_FOLLOW_NONE, B_WILL_DRAW )
{
	//SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	icon = bitmap;
}
// ---------------------------------------------------------------------------------------------------------- //

void BRIEIconView::Draw(BRect /*updateRect*/)
{
	DrawBitmap(icon,BPoint(6,10));
}
// ---------------------------------------------------------------------------------------------------------- //
