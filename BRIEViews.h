/*

BRIEViews Header

Coded by Sikosis

Released under the MIT license.

(C) 2002-2003 http://brie.sf.net/

*/

#ifndef __BRIEVIEWS_H__
#define __BRIEVIEWS_H__

class FileWindowView : public BView
{
	public:
    	FileWindowView(BRect frame);
};

class ProjectWindowView : public BView
{
	public:
    	ProjectWindowView(BRect frame);
    	virtual void Draw(BRect drawRect);
};

class PropertiesWindowView : public BView
{
	public:
    	PropertiesWindowView(BRect frame);
};

class ToolboxWindowView : public BView
{
	public:
    	ToolboxWindowView(BRect frame);
};

class BRIEIconView : public BView
{
	public:
		BRIEIconView(BBitmap* bitmap, BRect r);
		virtual void Draw(BRect drawRect);
	private:
		BBitmap* icon;
};

class BRIETipIconView : public BView
{
	public:
		BRIETipIconView(BBitmap* bitmap, BRect r);
		virtual void Draw(BRect drawRect);
	private:
		BBitmap* icon;
};

class AboutWindowView : public BView
{
	public:
    	AboutWindowView(BRect frame);
};

class MenuCreatorView : public BView
{
	public:
		MenuCreatorView(BRect frame);
};

class NewProjectWindowView : public BView
{
	public:
		NewProjectWindowView(BRect frame);
		virtual void Draw(BRect drawRect);
};

class HelpTipView : public BView
{
	public:
		HelpTipView(BRect frame);
		virtual void Draw(BRect updateRect);
};

class InputBoxView : public BView
{
	public:
		InputBoxView(BRect frame);
};

#endif
