/*

BeOS Rapid Integrated Environment (BRIE)

NewProjectWindow by Sikosis

Released under the MIT license.

(C) 2002-2004 http://brie.sf.net/

*/

// Includes -------------------------------------------------------------------------------------------------- //
#include <Alert.h>
#include <Application.h>
#include <Button.h>
#include <CheckBox.h>
#include <Directory.h>
#include <Message.h>
#include <Path.h>
#include <Roster.h>
#include <Screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TextControl.h>
#include <Window.h>
#include <View.h>
#include <iostream>
#include <fstream>

#include "brie.h"
#include "BRIEWindows.h"
#include "BRIEViews.h"
#include "brieconstants.h"

// Constants ------------------------------------------------------------------------------------------------- //
const uint32 BTN_ADD = 'BAdd';
const uint32 BTN_CANCEL = 'BCnl';
const uint32 TXT_NEW_PROJECT = 'nPrj';
const uint32 TXT_AUTHOR = 'auth';
const uint32 CHK_ADDLOADSAVEPREF = 'cals';
const uint32 CHK_ADDMENUBAR = 'camb';
const uint32 CHK_CUSTOMABOUTBOX = 'cabx';
// ---------------------------------------------------------------------------------------------------------- //


// CenterWindowOnScreen -- Centers the BWindow to the Current Screen
static void CenterWindowOnScreen(BWindow* w)
{
	BRect	screenFrame = (BScreen(B_MAIN_SCREEN_ID).Frame());
	BPoint 	pt;
	pt.x = screenFrame.Width()/2 - w->Bounds().Width()/2;
	pt.y = screenFrame.Height()/2 - w->Bounds().Height()/2;

	if (screenFrame.Contains(pt))
		w->MoveTo(pt);
}
// ---------------------------------------------------------------------------------------------------------- //


// NewProjectWindow - Constructor
NewProjectWindow::NewProjectWindow(BRect frame) : BWindow (frame, "NewProjectWindow", B_MODAL_WINDOW , B_NOT_RESIZABLE , 0)
{
	InitWindow();
	CenterWindowOnScreen(this);
	Show();
}
// ---------------------------------------------------------------------------------------------------------- //


// NewProjectWindow - Destructor
NewProjectWindow::~NewProjectWindow()
{
	//exit(0);
}
// ---------------------------------------------------------------------------------------------------------- //


// NewProjectWindow::InitWindow
void NewProjectWindow::InitWindow(void)
{	
	BRect r;
	r = Bounds(); // the whole view
	int LeftMargin = 14;
	int AddButtonSize = 75;
	int CancelButtonSize = 75;
	float AddLeftMargin = r.right - (AddButtonSize + 10);
	float CancelLeftMargin = AddLeftMargin - (CancelButtonSize + 11);
	int NewProjectTop = 10;
	
	if (PanelType == 1) {
		// Existing
		txtNewProject = new BTextControl(BRect(LeftMargin,NewProjectTop,r.right-10,NewProjectTop+10),
						"txtNewProject","Project Name:",ptrProjectWindow->stvProjectName->Text(),new BMessage(TXT_NEW_PROJECT),
						B_FOLLOW_LEFT | B_FOLLOW_TOP , B_WILL_DRAW | B_NAVIGABLE);
	} else {
		// New
		txtNewProject = new BTextControl(BRect(LeftMargin,NewProjectTop,r.right-10,NewProjectTop+10),
						"txtNewProject","Project Name:","Untitled",new BMessage(TXT_NEW_PROJECT),
						B_FOLLOW_LEFT | B_FOLLOW_TOP , B_WILL_DRAW | B_NAVIGABLE);
	}
	txtNewProject->SetDivider(88);
	
	if (PanelType == 1) {
		txtAuthor = new BTextControl(BRect(LeftMargin,NewProjectTop+25,r.right-10,NewProjectTop+35),
		            "txtAuthor","Author:",ProjectAuthor.String(),new BMessage(TXT_AUTHOR), B_FOLLOW_LEFT | B_FOLLOW_TOP,
	    	        B_WILL_DRAW | B_NAVIGABLE);
	} else {
		txtAuthor = new BTextControl(BRect(LeftMargin,NewProjectTop+25,r.right-10,NewProjectTop+35),
		            "txtAuthor","Author:","DeveloperName",new BMessage(TXT_AUTHOR), B_FOLLOW_LEFT | B_FOLLOW_TOP,
	    	        B_WILL_DRAW | B_NAVIGABLE);
	
	}    	        
	txtAuthor->SetDivider(88);
	
	// add special project stuff
	
	chkLoadSavePrefs = new BCheckBox(BRect(LeftMargin,NewProjectTop+65,r.right-10,NewProjectTop+65+12),
						"chkLoadSavePrefs","Add Load/Save Preferences Functions", new BMessage(CHK_ADDLOADSAVEPREF), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
	
	chkMenuBar = new BCheckBox(BRect(LeftMargin,NewProjectTop+85,r.right-10,NewProjectTop+85+12),
						"chkMenuBar","Add MenuBar and MenuItems", new BMessage(CHK_ADDMENUBAR), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
	
	chkCustomAboutBox = new BCheckBox(BRect(LeftMargin,NewProjectTop+105,r.right-10,NewProjectTop+105+12),
						"chkCustomAboutBox","Add a Custom About Box", new BMessage(CHK_CUSTOMABOUTBOX), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
	
	chkCustomAboutBox->SetEnabled(false); // debug - cos I havent finished the code for it ;)
	   	
	btnCancel = new BButton(BRect (CancelLeftMargin,r.bottom-34,CancelLeftMargin+CancelButtonSize,r.bottom-14),"Cancel","Cancel", new BMessage(BTN_CANCEL), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);		
	if (PanelType == 1) {
		btnAdd = new BButton(BRect (AddLeftMargin,r.bottom-34,AddLeftMargin+AddButtonSize,r.bottom-14),
				 "Save","Save", new BMessage(BTN_ADD), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
	} else {
		btnAdd = new BButton(BRect (AddLeftMargin,r.bottom-34,AddLeftMargin+AddButtonSize,r.bottom-14),
				 "Create","Create", new BMessage(BTN_ADD), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
	}
  	
  	btnAdd->MakeDefault(true);
		
	AddChild(ptrNewProjectWindowView = new NewProjectWindowView(r));
	ptrNewProjectWindowView->AddChild(txtNewProject);
	ptrNewProjectWindowView->AddChild(txtAuthor);
	ptrNewProjectWindowView->AddChild(chkLoadSavePrefs);
    ptrNewProjectWindowView->AddChild(chkMenuBar);
    ptrNewProjectWindowView->AddChild(chkCustomAboutBox);
	ptrNewProjectWindowView->AddChild(btnCancel);
    ptrNewProjectWindowView->AddChild(btnAdd);
    txtNewProject->MakeFocus(true);
}
// ---------------------------------------------------------------------------------------------------------- //


void NewProjectWindow::CreateFile(char FileName[256], char FileTitle[256], BString contents) 
{
	int x;
	FILE *f;
	//char AppName[256];
	char tmp[300];
	int CurrentYear = 2004; // fix this later ***********************************************************************
	ProjectName.SetTo(txtNewProject->Text());
	
	f = fopen(FileName,"w");
	x = fputs("/*\n\n",f);
	sprintf(tmp,"%s %s\n\n",ProjectName.String(),FileTitle);
	x = fputs(tmp,f);
	sprintf(tmp,"Author: %s\n\n",txtAuthor->Text());
	x = fputs(tmp,f);
	sprintf(tmp,"(C)%i %s)\n\n",CurrentYear,projcreation);
	x = fputs(tmp,f);
	x = fputs("*/\n\n",f);
	x = fputs(contents.String(),f);
	//sprintf(tmp,"#ifndef __%sCONSTANTS_H__\n",ProjectName.String());
	//x = fputs(tmp,f);
	//sprintf(tmp,"#define __%sCONSTANTS_H__\n\n",ProjectName.String());
	//x = fputs(tmp,f);
	//x = fputs("// Pointers to BWindows\n",f);
	//sprintf(tmp,"extern %sWindow* ptr%sWindow;\n\n",ProjectName.String(),ProjectName.String());
	//x = fputs(tmp,f);
	//x = fputs("#endif\n",f);
	fclose(f);
}
// ---------------------------------------------------------------------------------------------------------- //

// CreateNewProject - create all the text files for the new project
void NewProjectWindow::CreateNewProject(void)
{
	// Set Project Name and Various other settings
	char tmp[300];       // this will be removed when all references are gone 
	char cmd[256];
	int x;               // this will be removed when all references are gone
	FILE *f;             // this will be removed when all references are gone
	char FileName[256];
	char AppName[256];   // this will be removed when all references are gone
	BString FileContents;
	BString UpperProjectName;
	
	ProjectName.SetTo(txtNewProject->Text());
	UpperProjectName.SetTo(ProjectName.String());
	UpperProjectName.ToUpper();
	sprintf(AppName,"%s",ProjectName.String());  // this will be removed when all references are gone
		
	// 1) Get Current Directory
	app_info	daInfo;
	be_app->GetAppInfo(&daInfo);
	BEntry	daEntry(&daInfo.ref);
	daEntry.GetParent(&daEntry);
	BPath	pPath(&daEntry);
	char	apath[256];
	::memcpy(apath, pPath.Path(), 256);			
			
	// 2) Create New Directory
	sprintf(cmd,"mkdir %s/projects/%s",apath,ProjectName.String());
	system(cmd);
			
	// 3) Create Basic Files for a Default App
	
	// Application Header
	sprintf(FileName,"%s/projects/%s/%s.h",apath,ProjectName.String(),ProjectName.String());
	FileContents.SetTo("#ifndef __");
	FileContents.Append(UpperProjectName.String());
	FileContents.Append("_H__\n");
	FileContents.Append("#define __");
	FileContents.Append(UpperProjectName.String());
	FileContents.Append("_H__\n\n");
	FileContents.Append("extern const char *APP_SIGNATURE;\n\n");
	FileContents.Append("class ");
	FileContents.Append(ProjectName.String());
	FileContents.Append(" : public BApplication\n{\n\tpublic:\n\t\t");
	FileContents.Append(ProjectName.String());
	FileContents.Append("();\n");
	FileContents.Append("\t\tvirtual void MessageReceived(BMessage *message);\n");
	FileContents.Append("\tprivate:\n\n};\n\n");
	FileContents.Append("#endif\n");
	CreateFile(FileName,"Header",FileContents);
		
	// Application Constants.h
	sprintf(FileName,"%s/projects/%s/%sConstants.h",apath,ProjectName.String(),ProjectName.String());
	FileContents.SetTo("#ifndef __");
	FileContents.Append(UpperProjectName.String());
	FileContents.Append("CONSTANTS_H__\n");
	FileContents.Append("#define __");
	FileContents.Append(UpperProjectName.String());
	FileContents.Append("CONSTANTS_H__\n\n");
	FileContents.Append("// Pointers to BWindows\n");
	FileContents.Append("extern ");
	FileContents.Append(ProjectName.String());
	FileContents.Append("Window* ptr");
	FileContents.Append(ProjectName.String());
	FileContents.Append("Window;\n\n");
	FileContents.Append("// Product Name and Properties\n");
	FileContents.Append("const char projtitle[]=\"");
	FileContents.Append(ProjectName.String());
	FileContents.Append("\";\nconst char projversion[]=\"v0.1\";\nconst char projauthor[]=\"");
	FileContents.Append(txtAuthor->Text());
	FileContents.Append("\";\n\n");
	
	FileContents.Append("#endif\n");
	CreateFile(FileName,"Constants",FileContents);
	
	// Windows Header
	sprintf(FileName,"%s/projects/%s/%sWindows.h",apath,ProjectName.String(),ProjectName.String());
	FileContents.SetTo("#ifndef __");
	FileContents.Append(UpperProjectName.String());
	FileContents.Append("WINDOWS_H__\n");
	FileContents.Append("#define __");
	FileContents.Append(UpperProjectName.String());
	FileContents.Append("WINDOWS_H__\n\n");
	FileContents.Append("#include \"");
	FileContents.Append(ProjectName.String());
	FileContents.Append(".h\"\n");
	FileContents.Append("#include \"");
	FileContents.Append(ProjectName.String());
	FileContents.Append("Views.h\"\n\n");
	FileContents.Append("class ");
	FileContents.Append(ProjectName.String()); 
	FileContents.Append("View;\n\n");
	FileContents.Append("class ");
	FileContents.Append(ProjectName.String()); 
	FileContents.Append("Window : public BWindow\n");
	FileContents.Append("{\n\tpublic:\n\t\t");
	FileContents.Append(ProjectName.String()); 
	FileContents.Append("Window(BRect frame);\n");
	FileContents.Append("\t\t~");
	FileContents.Append(ProjectName.String()); 
	FileContents.Append("Window();\n");
	FileContents.Append("\t\tvirtual bool QuitRequested();\n");
	FileContents.Append("\t\tvirtual void MessageReceived(BMessage *message);\n");
	FileContents.Append("\tprivate:\n");
	FileContents.Append("\t\tvoid InitWindow(void);\n\n");
	if (chkLoadSavePrefs->Value() == B_CONTROL_ON) {
		FileContents.Append("\t\tvoid LoadSettings(BMessage *msg);\n");
		FileContents.Append("\t\tvoid SaveSettings(void);\n");
	}
	FileContents.Append("\t\t");
	FileContents.Append(ProjectName.String());
	FileContents.Append("View*\t\tptr");
	FileContents.Append(ProjectName.String());
	FileContents.Append("View;\n");
	FileContents.Append("};\n\n");
	FileContents.Append("#endif\n");
	CreateFile(FileName,"Windows Header",FileContents);

//	FileContents.Append("");
	
//	f = fopen(FileName,"w");
//	x = fputs("/*\n\n",f);
//	sprintf(tmp,"%s Windows Header\n\n",ProjectName.String());
//	x = fputs(tmp,f);
//	sprintf(tmp,"Author: %s\n\n",txtAuthor->Text());
//	x = fputs(tmp,f);
//	x = fputs("(C)2003 Created using BRIE (http://brie.sf.net/)\n\n",f);
//	x = fputs("*/\n\n",f);
//	sprintf(tmp,"#ifndef __%sWINDOWS_H__\n",ProjectName.String());
//	x = fputs(tmp,f);
//	sprintf(tmp,"#define __%sWINDOWS_H__\n\n",ProjectName.String());
//	x = fputs(tmp,f);
//	sprintf(tmp,"#include \"%s.h\"\n",ProjectName.String());
//	x = fputs(tmp,f);
//	sprintf(tmp,"#include \"%sViews.h\"\n\n",ProjectName.String());
//	x = fputs(tmp,f);
//	sprintf(tmp,"class %sView;\n\n",ProjectName.String());
//	x = fputs(tmp,f);
//	sprintf(tmp,"class %sWindow : public BWindow\n",ProjectName.String());
//	x = fputs(tmp,f);
//	x = fputs("{\n",f);
//	x = fputs("\tpublic:\n",f);
//	sprintf(tmp,"\t\t%sWindow(BRect frame);\n",ProjectName.String());
//	x = fputs(tmp,f);
//	sprintf(tmp,"\t\t~%sWindow();\n",ProjectName.String());
//	x = fputs(tmp,f);
//	x = fputs("\t\tvirtual bool QuitRequested();\n",f);
//	x = fputs("\t\tvirtual void MessageReceived(BMessage *message);\n",f);
//	x = fputs("\tprivate:\n",f);
//	x = fputs("\t\tvoid InitWindow(void);\n\n",f);
	
	// add load/save pref (if checked)
//	if (chkLoadSavePrefs->Value() == B_CONTROL_ON) {
//		x = fputs("\t\tvoid LoadSettings(BMessage *msg);\n",f);
//		x = fputs("\t\tvoid SaveSettings(void); \n",f);
//	}
//	sprintf(tmp,"\t\t%sView*\t\tptr%sView;\n",ProjectName.String(),ProjectName.String());
//	x = fputs(tmp,f);
//	x = fputs("};\n\n",f);
//	x = fputs("#endif\n",f);
//	fclose(f);
	
	// Views Header
	sprintf(FileName,"%s/projects/%s/%sViews.h",apath,ProjectName.String(),ProjectName.String());
	f = fopen(FileName,"w");
	x = fputs("/*\n\n",f);
	sprintf(tmp,"%s Views Header\n\n",ProjectName.String());
	x = fputs(tmp,f);
	sprintf(tmp,"Author: %s\n\n",txtAuthor->Text());
	x = fputs(tmp,f);
	x = fputs("(C)2003 Created using BRIE (http://brie.sf.net/)\n\n",f);
	x = fputs("*/\n\n",f);
	sprintf(tmp,"#ifndef __%sVIEWS_H__\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"#define __%sVIEWS_H__\n\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"#include \"%s.h\"\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"#include \"%sWindows.h\"\n\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"class %sView : public BView\n",AppName);
	x = fputs(tmp,f);
	x = fputs("{\n",f);
	x = fputs("\tpublic:\n",f);
	sprintf(tmp,"\t\t%sView(BRect frame);\n",AppName);
	x = fputs(tmp,f);
	x = fputs("\t\tvirtual void Draw(BRect updateRect);\n",f);
	x = fputs("};\n\n",f);
	x = fputs("#endif\n",f);
	fclose(f);

	// View CPP
	sprintf(FileName,"%s/projects/%s/%sView.cpp",apath,AppName,AppName);
	f = fopen(FileName,"w");
	x = fputs("/*\n\n",f);
	sprintf(tmp,"%s View\n\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"Author: %s\n\n",txtAuthor->Text());
	x = fputs(tmp,f);
	x = fputs("(C)2003 Created using BRIE (http://brie.sf.net/)\n\n",f);
	x = fputs("*/\n\n",f);
	x = fputs("// Includes ------------------------------------------------------------------------------------------ //\n",f);
	x = fputs("#include <Alert.h>\n",f);
	x = fputs("#include <Application.h>\n",f);
	x = fputs("#include <Screen.h>\n",f);
	x = fputs("#include <stdio.h>\n",f);
	x = fputs("#include <Window.h>\n",f);
	x = fputs("#include <View.h>\n\n",f);
	sprintf(tmp,"#include \"%sWindows.h\"\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"#include \"%sViews.h\"\n",AppName);
	x = fputs(tmp,f);
	x = fputs("// -------------------------------------------------------------------------------------------------- //\n\n",f);
	sprintf(tmp,"// %sView - Constructor\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"%sView::%sView (BRect frame) : BView (frame, \"%sView\", B_FOLLOW_ALL_SIDES, B_WILL_DRAW )\n",AppName,AppName,AppName);
	x = fputs(tmp,f);
	x = fputs("{\n",f);
	x = fputs("\tSetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));\n",f);
	x = fputs("}\n",f);
	x = fputs("// ------------------------------------------------------------------------------------------------- //\n\n",f);
	sprintf(tmp,"void %sView::Draw(BRect /*updateRect*/)\n",AppName);
	x = fputs(tmp,f);
	x = fputs("{\n",f);
	x = fputs("\tBRect r;\n",f);
	x = fputs("\tr = Bounds();\n",f);
	x = fputs("}\n",f);
	x = fputs("// ------------------------------------------------------------------------------------------------- //\n",f);
	fclose(f);
	
	// Main CPP
	sprintf(FileName,"%s/projects/%s/%s.cpp",apath,AppName,AppName);
	f = fopen(FileName,"w");
	x = fputs("/*\n\n",f);
	sprintf(tmp,"%s\n\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"Author: %s\n\n",txtAuthor->Text());
	x = fputs(tmp,f);
	x = fputs("(C)2003 Created using BRIE (http://brie.sf.net/)\n\n",f);
	x = fputs("*/\n\n",f);
	x = fputs("// Includes ------------------------------------------------------------------------------------------ //\n",f);
	x = fputs("#include <Alert.h>\n",f);
	x = fputs("#include <Application.h>\n",f);
	x = fputs("#include <Button.h>\n",f);
	x = fputs("#include <Entry.h>\n",f);
	x = fputs("#include <File.h>\n",f);
	x = fputs("#include <FilePanel.h>\n",f);
	x = fputs("#include <ListView.h>\n",f);
	x = fputs("#include <Path.h>\n",f);
	x = fputs("#include <Screen.h>\n",f);
	x = fputs("#include <ScrollView.h>\n",f);
	x = fputs("#include <stdio.h>\n",f);
	x = fputs("#include <string.h>\n",f);
	x = fputs("#include <TextControl.h>\n",f);
	x = fputs("#include <Window.h>\n",f);
	x = fputs("#include <View.h>\n\n",f);
	sprintf(tmp,"#include \"%s.h\"\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"#include \"%sWindows.h\"\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"#include \"%sViews.h\"\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"#include \"%sConstants.h\"\n",AppName);
	x = fputs(tmp,f);
	//x = fputs("// -------------------------------------------------------------------------------------------------- //\n\n",f);
	x = fputs("// Constants ---------------------------------------------------------------------------------------- //\n\n",f);
	sprintf(tmp,"const char *APP_SIGNATURE = \"application/x-vnd.%s.%s\";  // Application Signature and Title\n\n",txtAuthor->Text(),AppName);
	x = fputs(tmp,f);
	x = fputs("// -------------------------------------------------------------------------------------------------- //\n\n",f);
	sprintf(tmp,"%sWindow\t\t*ptr%sWindow;\n\n",AppName,AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"// %s - Constructor\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"%s::%s() : BApplication (APP_SIGNATURE)\n",AppName,AppName);
	x = fputs(tmp,f);
	x = fputs("{\n",f);
	x = fputs("\t// Default Window Size - Position doesn't matter as we centre the form to the current screen size\n",f);
	x = fputs("\tBRect	screenFrame = (BScreen(B_MAIN_SCREEN_ID).Frame());\n\n",f);
	x = fputs("\tfloat FormTopDefault = 0;\n",f);
	x = fputs("\tfloat FormLeftDefault = 0;\n",f);
	x = fputs("\tfloat FormWidthDefault = screenFrame.Width() - 500;\n",f);
	x = fputs("\tfloat FormHeightDefault = screenFrame.Height() - 500;\n",f);
	sprintf(tmp,"\tBRect %sWindowRect(FormTopDefault,FormLeftDefault,FormLeftDefault+FormWidthDefault,FormTopDefault+FormHeightDefault);\n\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"\tptr%sWindow = new %sWindow(%sWindowRect);\n",AppName,AppName,AppName);
	x = fputs(tmp,f);
	x = fputs("}\n",f);
	x = fputs("// ------------------------------------------------------------------------------------------------- //\n\n",f);
	sprintf(tmp,"// %s::MessageReceived -- handles incoming messages\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"void %s::MessageReceived (BMessage *message)\n",AppName);
	x = fputs(tmp,f);
	x = fputs("{\n",f);
	x = fputs("\tswitch(message->what)\n",f);
	x = fputs("\t{\n",f);
	x = fputs("\t\tdefault:\n",f);
	x = fputs("\t\t\tBApplication::MessageReceived(message); // pass it along ... \n",f);
	x = fputs("\t\t\tbreak;\n",f);
	x = fputs("\t}\n",f);
	x = fputs("}\n",f);
	x = fputs("// ------------------------------------------------------------------------------------------------- //\n\n",f);
	sprintf(tmp,"// %s Main\n",AppName);
	x = fputs(tmp,f);
	x = fputs("int main(void)\n",f);
	x = fputs("{\n",f);
	sprintf(tmp,"\t%s theApp;\n",AppName);
	x = fputs(tmp,f);
	x = fputs("\ttheApp.Run();\n",f);
	x = fputs("\treturn 0;\n",f);
	x = fputs("}\n",f);
	x = fputs("// end --------------------------------------------------------------------------------------------- //\n\n",f);
	fclose(f);
	
	// Window CPP
	sprintf(FileName,"%s/projects/%s/%sWindow.cpp",apath,AppName,AppName);
	f = fopen(FileName,"w");
	x = fputs("/*\n\n",f);
	sprintf(tmp,"%sWindow\n\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"Author: %s\n\n",txtAuthor->Text());
	x = fputs(tmp,f);
	x = fputs("(C)2003 Created using BRIE (http://brie.sf.net/)\n\n",f);
	x = fputs("*/\n\n",f);
	x = fputs("// Includes ------------------------------------------------------------------------------------------ //\n",f);
	x = fputs("#include <Alert.h>\n",f);
	x = fputs("#include <Application.h>\n",f);
	x = fputs("#include <Button.h>\n",f);
	
	// add load/save pref (if checked)
	if (chkLoadSavePrefs->Value() == B_CONTROL_ON) {
		x = fputs("#include <File.h>\n",f);
		x = fputs("#include <FindDirectory.h>\n",f);
	}	
	
	// add menubar includes (if checked)
	if (chkMenuBar->Value() == B_CONTROL_ON) {
		x = fputs("#include <MenuBar.h>\n",f);
		x = fputs("#include <Menu.h>\n",f);
		x = fputs("#include <MenuItem.h>\n",f);
	}
	
	x = fputs("#include <Path.h>\n",f);
	x = fputs("#include <Screen.h>\n",f);
	x = fputs("#include <ScrollView.h>\n",f);
	x = fputs("#include <stdio.h>\n",f);
	x = fputs("#include <string.h>\n",f);
	x = fputs("#include <TextControl.h>\n",f);
	x = fputs("#include <Window.h>\n",f);
	x = fputs("#include <View.h>\n\n",f);
	sprintf(tmp,"#include \"%s.h\"\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"#include \"%sWindows.h\"\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"#include \"%sViews.h\"\n",AppName);
	x = fputs(tmp,f);
	x = fputs("// -------------------------------------------------------------------------------------------------- //\n\n",f);
	x = fputs("// CenterWindowOnScreen -- Centers the BWindow to the Current Screen\n",f);
	x = fputs("static void CenterWindowOnScreen(BWindow* w)\n",f);
	x = fputs("{\n",f);
	x = fputs("\tBRect\tscreenFrame = (BScreen(B_MAIN_SCREEN_ID).Frame());",f);
	x = fputs("\tBPoint\tpt;\n",f);
	x = fputs("\tpt.x = screenFrame.Width()/2 - w->Bounds().Width()/2;\n",f);
	x = fputs("\tpt.y = screenFrame.Height()/2 - w->Bounds().Height()/2;\n\n",f);
	x = fputs("\tif (screenFrame.Contains(pt))\n",f);
	x = fputs("\t\tw->MoveTo(pt);\n",f);
	x = fputs("}\n",f);
	x = fputs("// -------------------------------------------------------------------------------------------------- //\n\n",f);
	sprintf(tmp,"// %sWindow - Constructor\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"%sWindow::%sWindow(BRect frame) : BWindow (frame, \"%s v0.1\", B_TITLED_WINDOW, B_NORMAL_WINDOW_FEEL , 0)\n",AppName,AppName,AppName);
	x = fputs(tmp,f);
	x = fputs("{\n",f);
	x = fputs("\tInitWindow();\n",f);
	x = fputs("\tCenterWindowOnScreen(this);\n",f);
	
	// add load/save pref (if checked)
	if (chkLoadSavePrefs->Value() == B_CONTROL_ON) {
		x = fputs("\n",f);
		x = fputs("\t// Load User Settings \n",f);
		x = fputs("\tBPath path;\n",f);
		x = fputs("\tfind_directory(B_USER_SETTINGS_DIRECTORY,&path);\n",f);
		sprintf(tmp,"\tpath.Append(\"%s_Settings\",true);\n",AppName);
		x = fputs(tmp,f);
		x = fputs("\tBFile file(path.Path(),B_READ_ONLY);\n",f);
		x = fputs("\tBMessage msg;\n",f);
		x = fputs("\tmsg.Unflatten(&file);\n",f);
		x = fputs("\tLoadSettings (&msg);\n",f);
		x = fputs("\n",f);
    }
	
	x = fputs("\tShow();\n",f);
	x = fputs("}\n",f);
	x = fputs("// -------------------------------------------------------------------------------------------------- //\n\n",f);
	sprintf(tmp,"// %sWindow - Destructor\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"%sWindow::~%sWindow()\n",AppName,AppName);
	x = fputs(tmp,f);
	x = fputs("{\n",f);
	x = fputs("\texit(0);\n",f);
	x = fputs("}\n",f);
	x = fputs("// -------------------------------------------------------------------------------------------------- //\n\n",f);
	sprintf(tmp,"// %sWindow::InitWindow -- Initialization Commands here\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"void %sWindow::InitWindow(void)\n",AppName);
	x = fputs(tmp,f);
	x = fputs("{\n",f);
	x = fputs("\tBRect r;\n",f);
	x = fputs("\tr = Bounds(); // the whole view\n",f);
		
	// add MenuBar (if checked)
	if (chkMenuBar->Value() == B_CONTROL_ON) {
		ptrMenuCreator = new MenuCreator(BRect(367.0, 268.0, 657.0, 500.0));
		x = fputs("\n",f);
		x = fputs("\t// MenuBar - Created by BRIE Menu Creator\n",f);
		x = fputs("\tBMenu *menu;\n",f);
		x = fputs("\tBRect rMenuBar;\n\n",f);
		x = fputs("\trMenuBar = Bounds();\n",f);
		x = fputs("\trMenuBar.top = 20;\n\n",f);
		x = fputs("\t// Add the menu bar\n",f);
		x = fputs("\trMenuBar.top = 0;\n",f);
		x = fputs("\trMenuBar.bottom = 19;\n",f);
		x = fputs("\tmenubar = new BMenuBar(rMenuBar, \"menu_bar\");\n",f);
		x = fputs("\tAddChild(menubar);\n",f);
		x = fputs("\n",f);
		x = fputs("\t// ### INSERT MENU HERE FROM MENU CREATOR ### \n",f);
		x = fputs("\n",f);
		x = fputs("\t// EndMenuBar (please do not remove this line)\n\n",f);
	}
	
	x = fputs("\t// Create the Views\n",f);
	sprintf(tmp,"\tAddChild(ptr%sView = new %sView(r));\n",AppName,AppName);
	x = fputs(tmp,f);
	x = fputs("}\n",f);
	x = fputs("// -------------------------------------------------------------------------------------------------- //\n\n",f);
	sprintf(tmp,"// %sWindow::QuitRequested -- Post a message to the app to quit\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"bool %sWindow::QuitRequested()\n",AppName);
	x = fputs(tmp,f);
	x = fputs("{\n",f);
	
	if (chkLoadSavePrefs->Value() == B_CONTROL_ON) {
		x = fputs("\tSaveSettings();\n",f);
	}
	
	x = fputs("\tbe_app->PostMessage(B_QUIT_REQUESTED);\n",f);
	x = fputs("\treturn true;\n",f);
	x = fputs("}\n",f);
	x = fputs("// -------------------------------------------------------------------------------------------------- //\n\n",f);	
	
	// add load/save pref (if checked)
	if (chkLoadSavePrefs->Value() == B_CONTROL_ON) {
		sprintf(tmp,"// %sWindow::LoadSettings -- Loads your current settings\n",AppName);
		x = fputs(tmp,f);
		sprintf(tmp,"void %sWindow::LoadSettings(BMessage *msg)\n",AppName);
		x = fputs(tmp,f);
		x = fputs("{\n",f);
		x = fputs("\tBRect frame;\n\n",f);
		x = fputs("\tif (B_OK == msg->FindRect(\"windowframe\",&frame)) {\n",f);
		x = fputs("\t\tMoveTo(frame.left,frame.top);\n",f);
		x = fputs("\t\tResizeTo(frame.right-frame.left,frame.bottom-frame.top);\n",f);
		x = fputs("\t}\n",f);
		x = fputs("}\n",f);
		x = fputs("// -------------------------------------------------------------------------------------------------- //\n\n",f);		

		sprintf(tmp,"// %sWindow::SaveSettings -- Saves the Users settings\n",AppName);
		x = fputs(tmp,f);
		sprintf(tmp,"void %sWindow::SaveSettings(void)\n",AppName);
		x = fputs(tmp,f);
		x = fputs("{\n",f);
		x = fputs("\tBMessage msg;\n",f);
		x = fputs("\tmsg.AddRect(\"windowframe\",Frame());\n\n",f);
		x = fputs("\tBPath path;\n",f);
		x = fputs("\tstatus_t result = find_directory(B_USER_SETTINGS_DIRECTORY,&path);\n",f);
		x = fputs("\tif (result == B_OK) {\n",f);
		sprintf(tmp,"\t\tpath.Append(\"%s_Settings\",true);\n",AppName);
		x = fputs(tmp,f);
		x = fputs("\t\tBFile file(path.Path(),B_READ_WRITE | B_CREATE_FILE | B_ERASE_FILE);\n",f);
		x = fputs("\t\tmsg.Flatten(&file);\n",f);
		
		x = fputs("\t}\n",f);
		x = fputs("}\n",f);
		x = fputs("// -------------------------------------------------------------------------------------------------- //\n\n",f);
	}
		
	sprintf(tmp,"// %sWindow::MessageReceived -- receives messages\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"void %sWindow::MessageReceived (BMessage *message)\n",AppName);
	x = fputs(tmp,f);
	x = fputs("{\n",f);
	x = fputs("\tswitch(message->what)\n",f);
	x = fputs("\t{\n",f);
	x = fputs("\t\tdefault:\n",f);
	x = fputs("\t\t\tBWindow::MessageReceived(message);\n",f);
	x = fputs("\t\t\tbreak;\n",f);
	x = fputs("\t}\n",f);
	x = fputs("}\n",f);
	x = fputs("// -------------------------------------------------------------------------------------------------- //\n\n",f);	
	fclose(f);
	
	// this step doesnt work - would be nice if rsrc files could be made from text
	// 4) Copy newproject.rsrc to our project folder
	//sprintf(cmd,"cp %s/newproject.rsrc %s/projects/%s/",apath,apath,AppName);
	//system(cmd);
	//sprintf(cmd,"mv %s/projects/%s/newproject.rsrc %s/projects/%s/%s.rsrc",apath,AppName,apath,AppName,AppName);
	//system(cmd);
	
	// 5) Create BRIE Project File - this is required for internal use in this application only
	sprintf(FileName,"%s/projects/%s.bprj",apath,AppName);
	f = fopen(FileName,"w");
	sprintf(tmp,"## BRIE Project File for %s ##\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"ProjectName=%s\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"ProjectDir=%s/projects/%s\n",apath,AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"Author=%s\n",txtAuthor->Text());
	x = fputs(tmp,f);
	sprintf(tmp,"Language=%s\n","C/C++"); // might change later ...
	x = fputs(tmp,f);
	x = fputs("### Files\n",f);
	sprintf(tmp,"%s.cpp\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"%sWindow.cpp\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"%sView.cpp\n",AppName);
	x = fputs(tmp,f);
	fclose(f);
	sprintf(tmp,"%s.bprj",AppName);
	//ptrFileWindow->SetProject(FileName,tmp);
	//ptrProjectWindow->SetProjectTitle(AppName);
	
	//msg = new BMessage(SET_PROJECT_NAME);
	//msg.AddString("ProjectName",AppName);
	//msg.AddBool("NotSaved",true);
	//ptrProjectWindow->PostMessage(&msg);
	
	// Create our ProjectFiles BMessage
	BMessage pfmsg(ADD_PROJECT_FILE);
	BString ProgName;
	ProgName.SetTo(AppName);
	ProgName.Append(".cpp");
	pfmsg.AddString(kProjectFile, ProgName.String());
	BMessenger(ptrProjectWindow).SendMessage(&pfmsg);
	
	pfmsg.MakeEmpty();
	ProgName.SetTo(AppName);
	ProgName.Append("Window.cpp");
	pfmsg.AddString(kProjectFile, ProgName.String());
	BMessenger(ptrProjectWindow).SendMessage(&pfmsg);
	
	pfmsg.MakeEmpty();
	ProgName.SetTo(AppName);
	ProgName.Append("View.cpp");
	pfmsg.AddString(kProjectFile, ProgName.String());
	BMessenger(ptrProjectWindow).SendMessage(&pfmsg);
	
	// 6) Create makefile for compilation
	sprintf(FileName,"%s/projects/%s/makefile",apath,AppName);
	f = fopen(FileName,"w");
	sprintf(tmp,"## BeOS Makefile for %s ##\n",AppName);
	x = fputs(tmp,f);
	sprintf(tmp,"## Author: %s\n",txtAuthor->Text());
	x = fputs(tmp,f);
	x = fputs("## Created by BRIE (http://brie.sf.net/)\n\n",f);
	x = fputs("## Application Specific Settings ---------------------------------------------\n\n",f);
	x = fputs("# specify the name of the binary\n",f);
	sprintf(tmp,"NAME= %s\n",AppName);
	x = fputs(tmp,f);
	x = fputs("# specify the type of binary\n",f);
	x = fputs("#	APP:	Application\n",f);
	x = fputs("#	SHARED:	Shared library or add-on\n",f);
	x = fputs("#	STATIC:	Static library archive\n",f);
	x = fputs("#	DRIVER: Kernel Driver\n",f);
	x = fputs("TYPE= APP\n\n",f);
	x = fputs("#	specify the source files to use\n",f);
	x = fputs("#	Note that spaces in folder names do not work well with this makefile.\n",f);
	sprintf(tmp,"SRCS= %s.cpp %sWindow.cpp %sView.cpp\n",AppName,AppName,AppName);
	x = fputs(tmp,f);
	x = fputs("# end of srcs\n\n",f);
	x = fputs("#	specify the resource files to use\n",f);
	//x = fputs("RSRCS= ../../newproject.rsrc\n\n",f);
	x = fputs("RSRCS= \n\n",f);
	x = fputs("#	specify additional libraries to link against\n",f);
	x = fputs("LIBS= be root\n\n",f);
	x = fputs("#	specify additional paths to directories \n",f);
	x = fputs("LIBPATHS=\n\n",f);
	x = fputs("#	additional paths to look for system headers\n",f);
	x = fputs("SYSTEM_INCLUDE_PATHS =\n\n",f);
	x = fputs("#	additional paths to look for local headers\n",f);
	x = fputs("LOCAL_INCLUDE_PATHS =\n\n",f);
	x = fputs("#	specify the level of optimization that you desire - NONE, SOME, FULL\n",f);
	x = fputs("OPTIMIZE=\n\n",f);
	x = fputs("#	specify any preprocessor symbols to be defined.  \n",f);
	x = fputs("DEFINES=\n\n",f);
	x = fputs("#	specify special warning levels - NONE, ALL\n",f);
	x = fputs("WARNINGS = ALL\n\n",f);
	x = fputs("#	specify whether image symbols will be created\n",f);
	x = fputs("SYMBOLS = TRUE\n\n",f);
	x = fputs("#	specify debug settings\n",f);
	x = fputs("DEBUGGER =\n\n",f);
	x = fputs("#	specify additional compiler flags for all files\n",f);	
	x = fputs("COMPILER_FLAGS =\n\n",f);
	x = fputs("#	specify additional linker flags\n",f);
	x = fputs("LINKER_FLAGS =\n\n",f);
	x = fputs("## include the makefile-engine\n",f);
	x = fputs("DEVEL_DIRECTORY := \\\n",f);
	x = fputs("\t$(shell findpaths -r \"makefile_engine\" B_FIND_PATH_DEVELOP_DIRECTORY)",f);
	x = fputs("include $(DEVEL_DIRECTORY)/etc/makefile-engine",f);
	fclose(f);
	
	// 7) Send Messages to other Windows to update
	BMessage msg(SET_PROJECT_TITLE);
	msg.AddString(kProjectName, AppName);
	//msg.AddBool(kNotSaved, true); // make this false later - true for debug purposes
	BMessenger(ptrFileWindow).SendMessage(&msg);
	BMessenger(ptrProjectWindow).SendMessage(&msg);
	ProjectName.SetTo(AppName);
	ProjectPath = apath;
	
	// set properties window to show current Window from New Project
	ptrPropertiesWindow->ShowProperties("Window",ProjectName.String());
		
	// 8) Show Tracker and/or Continue
	ShowTracker(apath,AppName);
}
// ---------------------------------------------------------------------------------------------------------- //


// ShowTracker -- Asks if you wish to view your project in the Tracker or not after creation
void NewProjectWindow::ShowTracker(char apath[256],char AppName[256]) 
{
	char tmp[256];
	char cmd[256];
	BAlert *alert;
    long result;
    
	sprintf(tmp,"Your Project \"%s\" has now been created.\n\nAll your files are located at:-\n\n%s/%s",AppName,apath,AppName);
    alert = new BAlert("", tmp, "   Tracker   ", "   Continue   ", NULL, B_WIDTH_FROM_WIDEST, B_WARNING_ALERT);
	alert->SetShortcut(0, B_ESCAPE);
	result = alert->Go();
    if (result == B_OK)
   	{
		sprintf(cmd,"$(finddir B_SYSTEM_DIRECTORY)/Tracker %s/projects/%s",apath,AppName);
		system(cmd);	
	}	
}
// ---------------------------------------------------------------------------------------------------------- //


// CreateExistingProject -- Saves only the necessary bits - asks if you to recreate
void NewProjectWindow::CreateExistingProject(void) 
{
	char tmp[256];
	//char cmd[256];
	BAlert *alert;
    long result;
    
	sprintf(tmp,"Would you like to Recreate your Project \"%s\".\n\nPlease note this means all the existing files will be overwritten.\n\nIf you are unsure, click No.",ProjectName.String());
    alert = new BAlert("", tmp, " Yes ", " No ", NULL, B_WIDTH_FROM_WIDEST, B_WARNING_ALERT);
	alert->SetShortcut(0, B_ESCAPE);
	result = alert->Go();
    if (result == B_OK)
    {
    	// right - do the lot
    	CreateNewProject();	
	} else {
		// Only save necessary bits like project
		ptrFileWindow->SaveProject();
	}	
}
// ---------------------------------------------------------------------------------------------------------- //


// NewProjectWindow::MessageReceived -- receives messages
void NewProjectWindow::MessageReceived (BMessage *message)
{
	switch(message->what)
	{
		case BTN_ADD: // aka Create or Save
			{
				//printf ("txtNewProject->Text() - %s\n\n",txtNewProject->Text());
				BString tmp = "Untitled";
				if (tmp.Compare(txtNewProject->Text()) != 0)
				{
					if (PanelType == 1) {
						CreateExistingProject();
					} else {
						CreateNewProject();
					}
					Lock();
					Quit();
				} else {
					// Tip 2 - New Project Name - something other than untitled ;)
					TipNumber = 2;
					new HelpTipWindow(BRect(0.0, 0.0, 350.0, 120.0));
				}
			}
			break;
		case BTN_CANCEL:
			{
				// This Window is no longer needed.
				Lock();
		    	Quit();
		    }
			break;
		default:
			BWindow::MessageReceived(message);
			break;
	}
}
// ---------------------------------------------------------------------------------------------------------- //




