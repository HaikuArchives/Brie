/*

InputBoxView

Author: Sikosis

Released under the MIT license.

(C)2003 BRIE (http://brie.sf.net/)

*/

// Includes ------------------------------------------------------------------------------------------ //
//#include <Alert.h>
#include <Application.h>
//#include <Bitmap.h>
//#include <Screen.h>
//#include <stdio.h>
#include <Window.h>
#include <View.h>

#include "BRIEWindows.h"
#include "BRIEViews.h"
// -------------------------------------------------------------------------------------------------- //

// InputBoxView - Constructor
InputBoxView::InputBoxView (BRect frame) : BView (frame, "InputBoxView", B_FOLLOW_ALL_SIDES, B_WILL_DRAW )
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
}
// ------------------------------------------------------------------------------------------------- //

