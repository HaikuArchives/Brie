/*

BRIEConstants by Sikosis

Released under the MIT license.

(C) 2002-2003 http://brie.gravity24hr.com/

*/

#ifndef __BRIECONSTANTS_H__
#define __BRIECONSTANTS_H__

// used for our messaging between windows
extern char *kProjectName;
extern char *kProjectFile;
extern char *kAuthor;
extern bool *kNotSaved;

extern char *kDontShowAgain;

// bmessages
const uint32 SET_PROJECT_TITLE = 'spjt';
//const uint32 SET_PROJECT_NAME = 'spjn';
const uint32 ADD_PROJECT_FILE = 'adpf';
const uint32 BTN_OKAY = 'BOky';
const uint32 CHK_DONTSHOWAGAIN = 'chkd';

// pointers to windows
extern FileWindow*       ptrFileWindow;
extern ToolboxWindow*    ptrToolboxWindow;
extern ProjectWindow*    ptrProjectWindow;
extern PropertiesWindow* ptrPropertiesWindow;

// product name
const char projtitle[]="BeOS Rapid Integrated Environment";
const char projversion[]="v0.37";

extern BString  ProjectName;
extern BString  ProjectPath; // this is the current directory where brie is minus the /projects/
extern BString  ProjectAuthor;
extern BMessage ProjectFiles;
extern int ShowWinProj;
extern int ShowWinProp;
extern int ShowWinTool;
extern int PanelType;

// uses with HelpTipWindow
extern int  TipNumber;

#endif
