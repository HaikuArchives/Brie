/*

AboutWindowView Header

Coded by Sikosis

Released under the MIT license.

(C)2004 http://sikosis.com/

*/

#ifndef __ABOUTWINDOWVIEW_H__
#define __ABOUTWINDOWVIEW_H__


class AboutIconView : public BView
{
	public:
		AboutIconView(BBitmap* bitmap, BRect r);
		virtual void Draw(BRect drawRect);
	private:
		BBitmap* icon;
};


class AboutWindowView : public BView
{
	public:
    	AboutWindowView(BRect frame);
    	virtual void Draw(BRect drawRect);
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

};

#endif
