/*

BRIEView Header

Coded by Sikosis

Released under the MIT license.

(C) 2002 http://brie.sf.net/

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

#endif
