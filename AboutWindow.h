/*

AboutWindow Header by Sikosis

Released under the MIT license.

(C) 2004 http://sikosis.com/

*/

#ifndef __ABOUTWINDOWS_H__
#define __ABOUTWINDOWS_H__

#include "AboutWindowView.h"

class AboutWindowView;
class AboutIconView;

class AboutWindow : public BWindow
{
	public:
		AboutWindow(BRect frame);
		virtual void MessageReceived(BMessage *message);
	private:
		void InitWindow(void);
	    AboutWindowView*	ptrAboutWindowView;
	    AboutIconView*      ptrAboutIconView;

};

#endif
