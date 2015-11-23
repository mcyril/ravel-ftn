#include <Sound.h>#include <stdio.h>#include <string.h>#include <serial.h>#include "PatchNewControl.h"//#include "PopUpLib.h"#include "defines.h"#include "PKT.h"#include "PascalStr.h"#include "Prefs.h"#include "PopUpLib.h"#include "Scheduler.h"#include "stringutl.h"typedef struct {	MenuHandle		mHandle;	short			mID;	char			mPrivate;} popupPrivateData;typedef struct _one_hier_item {	struct _one_hier_item	*next;	struct _one_hier_item	*nested;	short		owner;	short		opened;		Str255		name;	Handle		RefCon;} hier_item, *hier_item_p, **hier_item_h;static	hier_item_p	h_list;extern	homeHndl		homesystem;			//	�	Home system structextern	mailPrefHndl	mailHndl;			//	�	Netmail structextern	short			AreasNumber;		//	�	Areas structs listextern	areaPrefHndl	*areasHndls;extern	short			GroupsNumber;		//	�	AreaGroups structs listextern	groupPrefHndl	*groupsHndls;extern	short			NodesNumber;		//	�	Linked Nodes structs listextern	nodePrefHndl	*nodesHndls;//static	PopUpMenuHandle	linksGroupSet;extern	ListHandle		lst;extern	short			semaphore, sweep;extern	short			wasmove;extern	Rect			clickable;Boolean	ProcessOneArea (areaPrefHndl oneArea);pascal void myldef (short lMessage, Boolean lSelect, Rect *lRect, Cell lCell, short lDataOffset, short lDataLen, ListHandle lHandle);pascal void myLClick (void);/*static void FullLinksMenu ( PopUpMenuHandle mh ){	short	i;	Str255	t;		for ( i = 0; i < NodesNumber; i++ )	{		printaddr ( &(*nodesHndls[i])->Addr, (char *) &t[1] );		t[0] = strlen ((char *) &t[1]);		AppendMenu ( (*mh)->menuHdl, "\pdum" );		SetMenuItemText ( (*mh)->menuHdl, i+1, t );	}}*/static pascal Boolean areaFilter ( DialogPtr theDialog, EventRecord *theEvent, short *itemHit ){	Boolean 	result = false;	Point		localWhere = theEvent->where;	GrafPtr		savePort;	short		initem, part, len, offset;	WindowPtr	window;	Cell		oCell;	short		dataLen;	hier_item_p	celltodraw;	Rect		iRect;	switch (theEvent->what)	{	case updateEvt:			LUpdate (theDialog->visRgn, lst);		iRect = (*lst)->rView;		InsetRect (&iRect, -1, -1);		FrameRect (&iRect);		break;	case keyDown:	case autoKey:			part = theEvent->message & 0x00FF;			if (part == 0x03 || part == 0x0D)		{			*itemHit = 1;			result = true;		}		else			if (part == 0x1B)			{				*itemHit = 2;				result = true;			}			else				if (part < 0x20 && part != 8 && part != 9 && part != 0x1c && part != 0x1d)					result = true;		break;		case mouseDown:			switch ( part = FindWindow (theEvent->where, &window) )		{		case inContent:					if (window != FrontWindow())			{//				SelectWindow(window);				result = false;			}			else			{				GetPort (&savePort);				SetPort (theDialog);				GlobalToLocal (&localWhere);								initem = FindDialogItem (theDialog, localWhere) + 1;				switch (initem)				{				case areaExports:										semaphore = false;					sweep = false;					wasmove = -1;					LClick (localWhere, theEvent->modifiers, lst);					if (sweep)		//	Hit triangle					{						oCell = LLastClick (lst);						LGetCellDataLocation (&offset, &len, oCell, lst);						if (offset != -1)						{							dataLen = sizeof (hier_item_p);							LGetCell (&celltodraw, &dataLen, oCell, lst);														LSetDrawingMode (false, lst);							switch (celltodraw->opened)							{							case 0:															if (theEvent->modifiers & optionKey)									celltodraw->opened = 5;								else									celltodraw->opened = 4;																break;															default:																if (theEvent->modifiers & optionKey)									celltodraw->opened = 5;								else									celltodraw->opened = 0;								break;							}														LSetCell (&celltodraw, dataLen, oCell, lst);															EraseRect (&(*lst)->rView);							LSetDrawingMode (true, lst);							LUpdate (theDialog->visRgn, lst);							LAutoScroll (lst);						}					}					result = false;					break;				}								SetPort (savePort);			}						break;		}				break;	}	return result;}Boolean	ProcessOneArea (areaPrefHndl oneArea){	DialogPtr	linxDlg;	short		iHit, links, markChar;	short		iType, i, j, dummy;	Handle		iHandle;	Rect		iRect, rDataBnds, oldClickable;	MenuHandle	mHandle;	ListHandle	oldList;	Str255		temp, d;	long		lll;	addr		tempaddr;		Cell		cellSize, theCell;		GrafPtr		oldPort;	FontInfo		fi;	hier_item_p		celltodraw, celltodraw1, celltodraw2;		oldList = lst;	oldClickable = clickable;	GetPort (&oldPort);		PatchNewControl ();	linxDlg = GetNewDialog ( 500, NULL, (WindowPtr) -1L );	UnPatchNewControl ();	SetWTitle (linxDlg, "\pArea");		SetPort (linxDlg);	(*(((DialogPeek) linxDlg)->textH))->txFont = 1;	(*(((DialogPeek) linxDlg)->textH))->txSize = 9;	GetFontInfo (&fi);	(*(((DialogPeek) linxDlg)->textH))->lineHeight = fi.ascent + fi.descent + fi.leading;	(*(((DialogPeek) linxDlg)->textH))->fontAscent = fi.ascent;		GetDialogItem (linxDlg, areaExports, &iType, &iHandle, &iRect);	SetRect ( &rDataBnds, 0, 0, 1, 0 );	iRect.right -= 15;	SetPt ( &cellSize, 0, 0 );	TextFont (4);	TextSize (9);	GetFontInfo (&fi);	SetPt ( &cellSize, iRect.right - iRect.left, fi.leading+fi.ascent+fi.descent+2 );	if (cellSize.v < 14)		cellSize.v = 14;		iRect.bottom = iRect.top + ((iRect.bottom - iRect.top) / cellSize.v) * cellSize.v;	lst = LNew ( &iRect, &rDataBnds, cellSize, 111, linxDlg, true, false, false, true );	TextFont ((*(((DialogPeek) linxDlg)->textH))->txFont);	TextSize ((*(((DialogPeek) linxDlg)->textH))->txSize);		clickable = iRect;	clickable.left += 1;//	clickable.right = clickable.left + 15;	InsetRect (&iRect, -1, -1);	FrameRect (&iRect);		SetPt (&((*lst)->indent), 0, 0);	(*lst)->selFlags = 0x82;	(*lst)->lClickLoop = myLClick;		h_list = NULL;		for (i = 0; i < NodesNumber; i++)	{		if (!h_list)			h_list = celltodraw = (hier_item_p) NewPtrClear (sizeof (hier_item));		else		{			celltodraw->next = (hier_item_p) NewPtrClear (sizeof (hier_item));			celltodraw = celltodraw->next;		}		celltodraw->owner = 0;		for (j = 0; j < (*oneArea)->numExports; j++)		{			if ((*oneArea)->Export[j].Export == i)				break;		}		celltodraw->opened = (j < (*oneArea)->numExports) ?								(((*oneArea)->Export[j].Diodes & LINK_DIODE) ? 5 : 4) : 0;		celltodraw->next = NULL;		printaddr (&(*nodesHndls[i])->Addr, (char *) &celltodraw->name[1]);		celltodraw->name[0] = strlen ((char *) &celltodraw->name[1]);				celltodraw->RefCon = (Handle) nodesHndls[i];	}	LSetDrawingMode (false, lst);	LAddRow (NodesNumber, 0, lst);		celltodraw = h_list;	i = 0;		while (celltodraw)	{		SetPt (&theCell, 0, i);		LSetCell (&celltodraw, sizeof (hier_item_p), theCell, lst);		celltodraw = celltodraw->next;		i++;	}	LSetDrawingMode (true, lst);		LUpdate (linxDlg->visRgn, lst);	GetDialogItem ( linxDlg, areaNam, &iType, &iHandle, &iRect );	SetDialogItemText ( iHandle, (*oneArea)->areaName );	GetDialogItem ( linxDlg, areaUseAKA, &iType, &iHandle, &iRect );	mHandle = ((popupPrivateData *)(*(*((ControlHandle) iHandle))->contrlData))->mHandle;		printaddr ( &(*homesystem)->mainAddr.ad, (char *) &temp[1] );	temp[0] = strlen ( (char *) &temp[1] );	AppendMenu ( mHandle, "\pdum" );	SetMenuItemText ( mHandle, 1, temp );	for ( i = 0; i < (*homesystem)->AKAcount; i++ )	{		printaddr ( &(*homesystem)->AKAAddr[i].ad, (char *) &temp[1] );		temp[0] = strlen ( (char *) &temp[1] );		AppendMenu ( mHandle, "\pdum" );		SetMenuItemText ( mHandle, i+2, temp );	}		SetControlMinimum ( (ControlHandle) iHandle, 1 );	SetControlMaximum ( (ControlHandle) iHandle, (*homesystem)->AKAcount + 1 );	SetControlValue ( (ControlHandle) iHandle, (*oneArea)->useAKA + 1 );	GetDialogItem ( linxDlg, areaCompress, &iType, &iHandle, &iRect );	SetControlValue ( (ControlHandle) iHandle, (((*oneArea)->areaflags & AREA_COMPRESSED) >> 4) + 1 );	GetDialogItem ( linxDlg, areaPurger, &iType, &iHandle, &iRect );	NumToString ((*oneArea)->purger, temp);	SetDialogItemText ( iHandle, temp );	GetDialogItem ( linxDlg, areaPass, &iType, &iHandle, &iRect );	SetControlValue ( (ControlHandle) iHandle, ((*oneArea)->areaflags & AREA_PASSTROUGH) != 0 );	GetDialogItem ( linxDlg, areaStrip, &iType, &iHandle, &iRect );	SetControlValue ( (ControlHandle) iHandle, ((*oneArea)->areaflags & AREA_STRIPSEEN) != 0 );	DrawDialog (linxDlg);	do {			ModalDialog ( areaFilter, &iHit );		switch (iHit)		{		case areaPass:		case areaStrip:			GetDialogItem ( linxDlg, iHit, &iType, &iHandle, &iRect );			dummy = GetControlValue ( (ControlHandle) iHandle );			SetControlValue ( (ControlHandle) iHandle, !dummy );			break;				case areaOK:					//	area name						GetDialogItem ( linxDlg, areaNam, &iType, &iHandle, &iRect );			GetDialogItemText ( iHandle, temp );						if (!temp[0])			{				SysBeep (10);				iHit = 0;				break;			}						UprText ((char *) &temp[1], temp[0]);						for (i = 0; i < AreasNumber; i++ )				if (oneArea == areasHndls[i])					continue;				else					if (!pStrComp (temp, (*areasHndls[i])->areaName))						break;						if (i < AreasNumber)			{				SysBeep (10);				iHit = 0;				break;			}						GetDialogItem ( linxDlg, areaPurger, &iType, &iHandle, &iRect );			GetDialogItemText ( iHandle, temp );			StringToNum (temp, &lll);						if (!lll)			{				SysBeep (10);				iHit = 0;				break;			}						break;		}	} while (iHit != areaOK && iHit != areaCancel);		if (iHit == areaOK)	{//	�	Greate OK? Hail eggs? Viva balls?		GetDialogItem ( linxDlg, areaNam, &iType, &iHandle, &iRect );		GetDialogItemText ( iHandle, (*oneArea)->areaName );		UprText ((char *) &(*oneArea)->areaName[1], (*oneArea)->areaName[0]);				(*oneArea)->purger = lll;				(*oneArea)->areaflags = 0;				GetDialogItem ( linxDlg, areaPass, &iType, &iHandle, &iRect );		(*oneArea)->areaflags |= (GetControlValue ( (ControlHandle) iHandle )) ? AREA_PASSTROUGH : 0;		GetDialogItem ( linxDlg, areaStrip, &iType, &iHandle, &iRect );		(*oneArea)->areaflags |= (GetControlValue ( (ControlHandle) iHandle )) ? AREA_STRIPSEEN : 0;		GetDialogItem ( linxDlg, areaUseAKA, &iType, &iHandle, &iRect );		(*oneArea)->useAKA = GetControlValue ( (ControlHandle) iHandle ) - 1;		GetDialogItem ( linxDlg, areaCompress, &iType, &iHandle, &iRect );		(*oneArea)->areaflags |= (GetControlValue ((ControlHandle) iHandle) - 1) << 4;		celltodraw = h_list;		i = 0;				while (celltodraw)		{			if (celltodraw->opened)				i++;						celltodraw = celltodraw->next;		}				SetHandleSize ((Handle) oneArea, sizeof (areaPrefType) + i * sizeof (ExpItem));		(*oneArea)->numExports = i;				celltodraw = h_list;		i = 0;		j = 0;				while (celltodraw)		{			if (celltodraw->opened)			{				(*oneArea)->Export[j].Export = i;				(*oneArea)->Export[j].Diodes = (celltodraw->opened == 5) ? LINK_DIODE : 0;				j++;			}						celltodraw = celltodraw->next;			i++;		}			}		celltodraw = h_list;		i = 0;		while (celltodraw)	{		celltodraw2 = celltodraw->next;		DisposePtr ((Ptr) celltodraw);		celltodraw = celltodraw2;		i++;	}		LDispose (lst);	DisposeDialog (linxDlg);		SetPort (oldPort);	clickable = oldClickable;	lst = oldList;	return (iHit == areaOK);}