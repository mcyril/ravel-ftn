#include "PopUpLib.h"#include "PascalStr.h"/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/PopUpMenuHandle InitPopUp (DialogPtr dialog, short menuID, 							short popID, short InitialValue, StringPtr title, long initial, void (*FullMenu) (MenuHandle menu)){	PopUpMenuHandle 	mh;	Rect 				itemRect;	short				itemType;	Handle 				itemHdl;			mh = (PopUpMenuHandle) NewHandleClear (sizeof (PopUpMenu));	(**mh).theDialog = dialog;		(**mh).popID = popID;	(**mh).menuID = menuID;	(**mh).menuHdl = GetMenu (menuID);		if (FullMenu)		FullMenu ((**mh).menuHdl);		(**mh).enable = (**((**mh).menuHdl)).enableFlags;	(**mh).theValue = InitialValue;	(**mh).statmenu = initial;		if (menuID & 1)		GetMenuItemText ((**mh).menuHdl, (**mh).theValue, (**mh).title);	else		pStrCopy (title, (**mh).title);		DisposeMenu ((**mh).menuHdl);	return (mh);}short DisposePopUp (PopUpMenuHandle mh){	DisposeHandle ((Handle) mh);}short sicn[16] = {	0,		0, 		0, 		0,	0,		0x7c0,	0x380,	0x100,	0,		0, 		0,		0,	0,		0,		0,		0};static void PlotTriangle (Rect *theRect) {	auto BitMap srcBits;	GrafPtr currPort;	GetPort (&currPort); 	srcBits.baseAddr = (Ptr) sicn;	srcBits.rowBytes = 2;	SetRect(&srcBits.bounds, 0, 0, 16, 16);	CopyBits(&srcBits,&(*currPort).portBits,&srcBits.bounds,theRect,srcOr,nil);}void DrawPopUp (PopUpMenuHandle mh){	Rect 		r, rmain, triangle, textbox;	short		itemType, textlen;	Handle 		itemHandle;	Str255		itemName;	Boolean		hilite;	PenState	ps;	FontInfo	fi;	GrafPtr		oldPort;	RGBColor	color, color1;	GetPort ( &oldPort );	SetPort ( (**mh).theDialog );	hilite = !((**mh).enable & 1);		//	!(Boolean)((**((**mh).menuHdl)).enableFlags & 1);	GetDialogItem ((**mh).theDialog, (**mh).popID, &itemType, &itemHandle, &r);		GetBackColor (&color1);	color.red = color.green = color.blue = 0xFFFF;	RGBBackColor(&color);	r.bottom -= 1;	EraseRect (&r);	r.bottom += 1;//	color.red = color.green = color.blue = 50000;	RGBBackColor(&color1);	rmain = r;//	r.left += 1;	InsetRect (&r, -1, 2);	r.top -= 2;	if (*((short *) 0x0D60) != 1 && hilite)	{		color.red = color.green = color.blue = 30000;		RGBForeColor (&color);	}	FrameRect (&r);	MoveTo (r.right, r.top + 2); 	LineTo (r.right, r.bottom);	LineTo (r.left + 2, r.bottom);	InsetRect (&r, 1, 1);/*	triangle = r;	triangle.left = triangle.right-16;	triangle.bottom = triangle.top+16;	PlotTriangle (&triangle);*/	GetFontInfo (&fi);	SetRect (&textbox, r.left+2, r.top, r.right-2, r.bottom-fi.descent/*-1*/);	pStrCopy ((**mh).title, itemName);	textlen = textbox.right-textbox.left;	MoveTo (textbox.left, textbox.bottom);	if (StringWidth (itemName) > textlen)	{		while (StringWidth (itemName)+StringWidth ("\p╔")>textlen)			itemName[0] -= 1;				DrawString (itemName);		MoveTo (textbox.left+StringWidth(itemName), textbox.bottom);		DrawString ("\p_");	}	else		DrawString (itemName);	if (*((short *) 0x0D60) != 1 && hilite)	{		color.red = color.green = color.blue = 0;		RGBForeColor (&color);	}		if (*((short *) 0x0D60) == 1 && hilite)	{		GetPenState(&ps);		PenMode (patBic);		PenPat (&qd.gray);		InsetRect(&rmain, -1, -1);		rmain.right += 1;		PaintRect (&rmain);		SetPenState(&ps);	}	SetPort ( oldPort );}void GetCItemPopUp (PopUpMenuHandle mh, void (*FullMenu) (MenuHandle menu), StringPtr iName){	(**mh).menuHdl = GetMenu ((**mh).menuID);	if (FullMenu)		FullMenu ((**mh).menuHdl);		GetMenuItemText ((**mh).menuHdl, (**mh).theValue, iName);	DisposeMenu ((**mh).menuHdl);}short HandlePopUp (PopUpMenuHandle mh, void (*FullMenu) (MenuHandle menu)){	short		itemType, numItems, counter; 	Handle 		itemHdl;	Rect 		itemRect;	Point 		popUpLoc;	Boolean 	popUpChoice;	short		markChar, res = false, i, j;	GrafPtr		oldPort;	long		oops;		GetPort ( &oldPort );	SetPort ( (**mh).theDialog );	if ((**mh).enable & 1)	{		GetDialogItem ((**mh).theDialog, (**mh).popID, &itemType, &itemHdl, &itemRect);		popUpLoc.v = itemRect.top;		popUpLoc.h = itemRect.left;				LocalToGlobal(&popUpLoc);				(**mh).menuHdl = GetMenu ((**mh).menuID);		if (FullMenu)			FullMenu ((**mh).menuHdl);				(**((**mh).menuHdl)).enableFlags = (**mh).enable;		j = CountMItems ((**mh).menuHdl);				for (i = 1; i <= j; i++)		{			oops = 1L << i;			SetItemMark ((**mh).menuHdl, i, ((**mh).statmenu & oops) ? 0xA5 : noMark);		}				InsertMenu ((**mh).menuHdl,-1);//	Debugger ();		CalcMenuSize ((**mh).menuHdl);//		(*(**mh).menuHdl)->menuWidth = itemRect.right - itemRect.left + 10;		popUpChoice = PopUpMenuSelect ((**mh).menuHdl, popUpLoc.v, popUpLoc.h, (**mh).theValue);				if (popUpChoice)		{			if ((**mh).menuID & 1)			{		//	one select menu							(**mh).statmenu ^= (1L << (**mh).theValue);				(**mh).theValue = LoWord (popUpChoice);				(**mh).statmenu ^= (1L << (**mh).theValue);								GetMenuItemText ((**mh).menuHdl, (**mh).theValue, (**mh).title);			}			else			{		//	multi select menu do in Edit Window						(**mh).theValue = LoWord (popUpChoice);		//		(**mh).statmenu ^= (1L << (**mh).theValue);			}						res = true;		}				DeleteMenu ((**mh).menuID);		DisposeMenu ((**mh).menuHdl);		DrawPopUp (mh);	}		SetPort ( oldPort );	return res;}void HilitePopUp (PopUpMenuHandle mh, Boolean state){	if (state) 		(**mh).enable |= 1L;	else		(**mh).enable &= ~1L;	DrawPopUp (mh);}