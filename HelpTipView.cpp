/*

HelpTip View

Author: Sikosis

Released under the MIT license.

(C)2003 BRIE (http://brie.sf.net/)

*/

// Includes ------------------------------------------------------------------------------------------ //
//#include <Alert.h>
#include <Application.h>
#include <Bitmap.h>
//#include <Screen.h>
//#include <stdio.h>
#include <Window.h>
#include <View.h>

#include "BRIEWindows.h"
#include "BRIEViews.h"
// -------------------------------------------------------------------------------------------------- //

// HelpTipView - Constructor
HelpTipView::HelpTipView (BRect frame) : BView (frame, "HelpTipView", B_FOLLOW_ALL_SIDES, B_WILL_DRAW )
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
}
// ------------------------------------------------------------------------------------------------- //

void HelpTipView::Draw(BRect /*updateRect*/)
{
	BRect r;
	r = Bounds();
}
// ------------------------------------------------------------------------------------------------- //


// BRIETipIconView - Constructor
BRIETipIconView::BRIETipIconView (BBitmap* bitmap, BRect frame) : BView (frame, "BRIETipIconView", B_FOLLOW_NONE, B_WILL_DRAW )
{
	icon = bitmap;
}
// ---------------------------------------------------------------------------------------------------------- //


void BRIETipIconView::Draw(BRect /*updateRect*/)
{
	DrawBitmap(icon,BPoint(6,10));
}
// ---------------------------------------------------------------------------------------------------------- //
