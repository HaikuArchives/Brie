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
    	virtual void MessageReceived(BMessage *message);
    private:
    		    
	    BButton            *btnOkay;
	    //URLView			   *urlWebSite;
	    //URLView			   *urlEmail;
	    //URLView			   *urlVersion;
	    //URLView            *urlMDR;
	    
	    BStringView        *stvMDR;
	    BStringView        *stvWebSiteAddress;
	    BStringView        *stvEmailAddress;
	    BStringView        *stvVersionNumber;
	    BStringView        *stvVersion;
	    BStringView        *stvEmail;
	    BStringView        *stvEmail2;
	    BStringView        *stvAppName;
	    BTextView		   *txvDescription;
	    BStringView	       *stvDescription;
	    BStringView	       *stvDescription2;
	    BStringView	       *stvDescription3;
	    BStringView	       *stvDescription4;	    
	    BStringView	       *stvDescription5;	
	    BStringView		   *stvDescription6;
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
