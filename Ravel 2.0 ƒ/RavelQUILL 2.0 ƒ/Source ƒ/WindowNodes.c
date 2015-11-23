#include <Sound.h>#include <stdio.h>#include <string.h>#include "TE32K.h"#include "DialogLib.h"#include "PopUpLib.h"#include "myTEdit.h"/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*///#include "Ravel_FTN.h"#include "ravel_msg_base.h"#include "Ravel_Prefs.h"#include "Preferences.h"#include "stringutl.h"#include "CommonData.h"#include "WindowsList.h"#include "nodelist.h"#include "WNodes.h"#include "NodeCookie.h"#include "SoundLib.h"#include "Templates.h"/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/#include "rMenus.h"/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/typedef struct _wloc {	Point	topleft;	short	bottom;	} wloc;static	Rect	originalView = {0,0,0,0};pascal void LDEFNodes (short lMessage, Boolean lSelect, Rect *lRect, Cell lCell,				short lDataOffset, short lDataLen, ListHandle lHandle);//	#define cLeftOffset		5pascal void LDEFNodes (short lMessage, Boolean lSelect, Rect *lRect, Cell lCell,				short lDataOffset, short lDataLen, ListHandle lHandle){	short 		leftDraw, topDraw, k;	FontInfo 	fi;	short		i;	Str255		title, temp;	Point		drawpt;	char		tmp[128];	addr		ads;	short		uuu, zzz;		unsigned char	oldMode;	PenState	penState;			if ((lMessage == lInitMsg) || (lMessage == lCloseMsg))		return;		leftDraw = lRect->left+(*lHandle)->indent.h;	topDraw = lRect->top+(*lHandle)->indent.v;		switch (lMessage)	{	case lDrawMsg:			SetPort ((*lHandle)->port);		EraseRect (lRect);			if (lDataLen == 2)		{			TextFont (viewFont);			TextSize (viewSize);			GetFontInfo (&fi);			SetPt ( &drawpt, leftDraw + 5, topDraw+fi.leading+fi.ascent );			memcpy ( (Ptr) &i, *((*lHandle)->cells)+lDataOffset, 2 );						MoveTo ( drawpt.h + 6*0, drawpt.v );			NumToString (i, temp);			DrawString (temp);						ads = (((windowsQElPtr)(((WindowPeek)(*lHandle)->port)->refCon))->common)->cNodelist.nl_addr;						switch ((((windowsQElPtr)(((WindowPeek)(*lHandle)->port)->refCon))->common)->cNodelist.nl_level)			{			case 0:	ads.zone = 0;			case 1:	ads.net = 0;			case 2:	ads.node = 0;			case 3:	ads.point = 0;			}			switch ((((windowsQElPtr)(((WindowPeek)(*lHandle)->port)->refCon))->common)->cNodelist.nl_level)			{			case 0:	ads.zone = i;	break;			case 1:	ads.net = i;	break;			case 2:	ads.node = i;	break;			case 3:	ads.point = i;	break;			}			if ((((windowsQElPtr)(((WindowPeek)(*lHandle)->port)->refCon))->common)->cNodelist.nl_level != 3 &&				hasSequence ((((windowsQElPtr)(((WindowPeek)(*lHandle)->port)->refCon))->common)->cNodelist.nl_level, &ads))			{				MoveTo ( drawpt.h + 6*5, drawpt.v );				DrawChar ( '>' );			}			//			GetNameFromAddr ( &ads, temp );			GetInfoFromAddr ( &ads, temp );			for (uuu = 1; uuu <= temp[0]; uuu++)				if (temp[uuu] == ',')					break;						MoveTo ( drawpt.h + 6*6, drawpt.v );						if (uuu-1 <= 28)				DrawText (&temp[1], 0, uuu-1 );			else			{				DrawText (&temp[1], 0, 25 );				DrawString ( "\p..." );			}			for (zzz = ++uuu; uuu <= temp[0]; uuu++)				if (temp[uuu] == ',')					break;						MoveTo ( drawpt.h + 6*35, drawpt.v );						if (uuu-zzz <= 17)				DrawText (&temp[1], zzz-1, uuu-zzz );			else			{				DrawText (&temp[1], zzz-1, 14 );				DrawString ( "\p..." );			}						for (zzz = ++uuu; uuu <= temp[0]; uuu++)				if (temp[uuu] == ',')					break;						MoveTo ( drawpt.h + 6*53, drawpt.v );			if (uuu-zzz <= 27)				DrawText (&temp[1], zzz-1, uuu-zzz );			else			{				DrawText (&temp[1], zzz-1, 24 );				DrawString ( "\p..." );			}			MoveTo ( drawpt.h + 6*6 + 1, lRect->bottom );			LineTo ( drawpt.h + 6*6 + 1, lRect->top );				MoveTo ( drawpt.h + 6*34 + 2, lRect->bottom );			LineTo ( drawpt.h + 6*34 + 2, lRect->top );				MoveTo ( drawpt.h + 6*52 + 2, lRect->bottom );			LineTo ( drawpt.h + 6*52 + 2, lRect->top );		}				if (!lSelect)			break;		case lHiliteMsg:			oldMode = LMGetHiliteMode();		LMSetHiliteMode(1);		if (((WindowPeek)(*lHandle)->port)->hilited)			InvertRect (lRect);		else		{			GetPenState (&penState);			PenMode (srcXor);			FrameRect (lRect);			SetPenState (&penState);		}		LMSetHiliteMode(oldMode);				break;	}}static void AdjustWinSize (DialogPtr dialog, ListHandle list, short max){	short		iType, ii, dummy, neww, newh, newc;	Handle		iHandle;	Rect		iRect, rView, rDataBnds;	Point		cellSize;	FontInfo	fInfo;		TextFont (viewFont);	TextSize (viewSize);	GetFontInfo (&fInfo);	GetDialogItem ( dialog, 1, &iType, &iHandle, &rView );	newc = (*list)->cellSize.v;	neww = rView.right;	newh = rView.top + (((max - rView.top) / newc) * newc);		SizeWindow ( dialog, neww, newh, true);	originalView.bottom = newh;	LSetDrawingMode ( false, list );		LSize ( neww - 15, ((newh - rView.top) / newc) * newc, list);		SetPt (&cellSize, neww - 15, newc);	LCellSize (cellSize, list);		(*((*list)->vScroll))->contrlRect.bottom -= 15;		LSetDrawingMode ( true, list );}static void DrawNodeList (windowsQElPtr dialogInfo){	short	i, j;	Str15	temp;	Cell	theCell;		for (i=0; ; i++)	{		switch ((dialogInfo->common)->cNodelist.nl_level)		{		case 0:			//	zone					j = ZoneByIndex (i);			break;				case 1:			//	net						j = NetByIndex (i, &(dialogInfo->common)->cNodelist.nl_addr);			break;		case 2:						j = NodeByIndex (i, &(dialogInfo->common)->cNodelist.nl_addr);			break;				case 3:					j = PointByIndex (i, &(dialogInfo->common)->cNodelist.nl_addr);			break;		}			if (j == -1)			break;			temp[0] = 2;			temp[1] = (j >> 8)  & 0xFF;		temp[2] = (j)       & 0xFF;				LAddRow ( 1, 0x7FFF, (dialogInfo->common)->cNodelist.list );		SetPt ( &theCell, 0, i );		LSetCell (&j, sizeof (short), theCell, (dialogInfo->common)->cNodelist.list);	}}static void DrawContents (windowsQElPtr dialogInfo){	char	ttt[128];	Str255	sTemp;	short	iType;	Handle	iHandle;	Rect	iRect;			GetDialogItem (dialogInfo->dialog, 1, &iType, &iHandle, &iRect);		iRect.bottom = iRect.top - 1;	iRect.top = 0;		EraseRect (&iRect);		if ((*(dialogInfo->common)->cNodelist.list)->dataBounds.bottom == 0)		return;		MoveTo (5, 15);	TextFace (bold);		printaddr (&(dialogInfo->common)->cNodelist.nl_addr, ttt);	GetInfoFromAddr (&(dialogInfo->common)->cNodelist.nl_addr, sTemp);	sTemp[sTemp[0]] = 0;	strcat (ttt, (char *) &sTemp[1]);	DrawText (ttt, 0, strlen (ttt));	TextFace (0);}void WNodeEventProcessor (EventRecord *event, windowsQElPtr dialogInfo, long info){	DialogPtr	dialog;	ListHandle	list;	short		iType, ii, dummy, neww, newh, newc, menuItem;	Handle		iHandle;	Rect		iRect, rView, rDataBnds;	Point		cellSize, theCell;	Point		where;			long		lSizeVH, nm, jj;		Str255		stemp;		char		key;		WStateData	*WStDat;	MenuHandle	hMenu;		WindowPtr	window;	windowsQElPtr	dInfo;	commonDataPtr	pcommon;	GrafPtr			oldPort;	BroadcastRec	bc;	register void (*EventProcessor) (EventRecord *event, struct _window *dialogInfo, long info);	switch (info & 0xFFFF)	{	case actionSetSize:				originalView.left = ((wloc *) event)->topleft.h;		originalView.top = ((wloc *) event)->topleft.v;		originalView.bottom = ((wloc *) event)->bottom;				break;		case actionGetSize:				((wloc *) event)->topleft.h = originalView.left;		((wloc *) event)->topleft.v = originalView.top;		((wloc *) event)->bottom = originalView.bottom;				break;		case actionCreate:		if (!yep ())		{			SysBeep (10);			break;		}				if (dInfo = windowsOpened (wtNodelist, 0, 0))		{			SelectWindow (dInfo->dialog);			SetPort (dInfo->dialog);						LDelRow (0, 0, (dInfo->common)->cNodelist.list);						pcommon = dInfo->common;			list = (dInfo->common)->cNodelist.list;						InvalRect (&(dInfo->dialog)->portRect);					goto redo;		}				dialog = GetNewDialog (130, NULL, (WindowPtr) -1);		((WindowPeek)dialog)->windowKind = myKind;		SetPort ( dialog );		if (originalView.bottom)		{			if (!SuchWindow (wtNodelist) || qd.screenBits.bounds.bottom - originalView.top - 20 < originalView.bottom)			{				if (!originalView.top)				{					originalView.top = (*(((WindowPeek)dialog)->contRgn))->rgnBBox.top;					originalView.left = (*(((WindowPeek)dialog)->contRgn))->rgnBBox.left;	//				originalView.bottom = dialog->portRect.bottom;					originalView.top = LMGetMBarHeight () * 2;				}			}			else			{				originalView.left += 20;				originalView.top += 20;			}		}		else		{			originalView = (*(((WindowPeek)dialog)->contRgn))->rgnBBox;			originalView.bottom = dialog->portRect.bottom;			originalView.top = LMGetMBarHeight () * 2;		}				MoveWindow (dialog, originalView.left, originalView.top, false);		SizeWindow (dialog, dialog->portRect.right, originalView.bottom, false);//		TextFont ( 4 );//		TextSize ( 9 );		TextFont (viewFont);		TextSize (viewSize);		GetDialogItem ( dialog, 1, &iType, &iHandle, &rView );		SetRect ( &rDataBnds, 0, 0, 1, 0 );		rView.right -= 15;		SetPt ( &cellSize, 0, 0 );		list = LNew (						&rView,						&rDataBnds,						cellSize,						130,						dialog,						true,						false,						false,						true					);		(*list)->selFlags = 0x82;		(*list)->port->txFont = 4;		(*list)->port->txSize = 9;		(*(*list)->vScroll)->contrlRect.bottom -= 15;//		MoveTo (0, rView.top - 1);//		LineTo (rView.right + 15, rView.top - 1);			AdjustWinSize (dialog, list, dialog->portRect.bottom);		WStDat = (WStateData *) *((WindowPeek) dialog)->dataHandle;				newc = (*list)->cellSize.v;		dummy = rView.top + newc * (*list)->dataBounds.bottom;				SetRect (&(WStDat->stdState),			WStDat->stdState.left + dialog->portRect.left,			WStDat->stdState.top + dialog->portRect.top,			WStDat->stdState.left + dialog->portRect.right,			(qd.screenBits.bounds.bottom < WStDat->stdState.top + dummy) ?				qd.screenBits.bounds.bottom :				((*list)->dataBounds.bottom > 5) ? WStDat->stdState.top + dummy :					WStDat->stdState.top + dialog->portRect.bottom);		ShowWindow ( dialog );		pcommon = (commonDataPtr) NewPtrClear (sizeof (commonNodelist));				pcommon->cNodelist.dialog = dialog;		pcommon->cNodelist.list = list;		windowsAdd (dialog, wtNodelist, pcommon, WNodeEventProcessor, WNodeDialogProcessor);				dInfo = windowsLookUp (dialog);				SetWRefCon (dialog, (long) dInfo);		dInfo->inFront = true;	redo:		pcommon->cNodelist.nl_level = (long) event;		pcommon->cNodelist.fixmode = 0;		pcommon->cNodelist.parrent = NULL;		if (dialogInfo)		{			pcommon->cNodelist.nl_addr = *((addr *) dialogInfo);/*						do {							ii = gotline (pcommon->cNodelist.nl_level, &pcommon->cNodelist.nl_addr);				pcommon->cNodelist.nl_level--;							} while (pcommon->cNodelist.nl_level >= 0 && ii < 0);			pcommon->cNodelist.nl_level++;						if (ii >= 0)				switch (pcommon->cNodelist.nl_level)				{				case 0:	pcommon->cNodelist.nl_addr.net = 0;				case 1:	pcommon->cNodelist.nl_addr.node = 0;				case 2:	pcommon->cNodelist.nl_addr.point = 0;				}*/			for (nm = 0; nm <= pcommon->cNodelist.nl_level; nm++)			{				ii = gotline (nm, &pcommon->cNodelist.nl_addr);								if (ii < 0)					break;			}						if (nm > 0)			{				pcommon->cNodelist.nl_level = nm - 1;				ii = gotline (pcommon->cNodelist.nl_level, &pcommon->cNodelist.nl_addr);				switch (pcommon->cNodelist.nl_level)				{				case 0:	pcommon->cNodelist.nl_addr.net = 0;				case 1:	pcommon->cNodelist.nl_addr.node = 0;				case 2:	pcommon->cNodelist.nl_addr.point = 0;				}			}			else				ii = -1;		}		else			ii = -1;				if (ii < 0)		{			ii = 0;			pcommon->cNodelist.nl_level = 0;			pcommon->cNodelist.nl_addr.zone = ZoneByIndex (0);			pcommon->cNodelist.nl_addr.net = 0;			pcommon->cNodelist.nl_addr.node = 0;			pcommon->cNodelist.nl_addr.point = 0;		}				SetPt (&theCell, 0, ii);/*		switch (pcommon->cNodelist.nl_level)		{		case 0:	pcommon->cNodelist.nl_addr.zone = 0;		case 1:	pcommon->cNodelist.nl_addr.net = 0;		case 2:	pcommon->cNodelist.nl_addr.node = 0;		case 3:	pcommon->cNodelist.nl_addr.point = 0;		}		switch (pcommon->cNodelist.nl_level)		{		case 0:	pcommon->cNodelist.nl_addr.zone =					ZoneByIndex (theCell.v);				break;						case 1:	pcommon->cNodelist.nl_addr.net =					NetByIndex (theCell.v, &pcommon->cNodelist.nl_addr);				break;						case 2:	pcommon->cNodelist.nl_addr.node =					NodeByIndex (theCell.v, &pcommon->cNodelist.nl_addr);				break;						case 3:	pcommon->cNodelist.nl_addr.point =					PointByIndex (theCell.v, &pcommon->cNodelist.nl_addr);				break;		}*/		LActivate ( true, list );		LSetDrawingMode ( false, list );		DrawNodeList (dInfo);		LSetSelect (true, theCell,list);		LAutoScroll (list);		LSetDrawingMode ( true, list );		WNodeEventProcessor (NULL, dInfo, ((long) inMenuBar << 16) | mouseDown);		break;	case actionClose:		originalView = (*(((WindowPeek)(dialogInfo->dialog))->contRgn))->rgnBBox;		originalView.bottom = (dialogInfo->dialog)->portRect.bottom;		LDispose ((dialogInfo->common)->cNodelist.list);				DisposePtr ((Ptr) dialogInfo->common);				DisposeDialog (dialogInfo->dialog);		windowsKill (dialogInfo->dialog);		break;			case actionActive:		DrawOnlyGrowIcon (dialogInfo->dialog);		MoveControl ((*(dialogInfo->common)->cNodelist.list)->vScroll,			(*(dialogInfo->common)->cNodelist.list)->rView.right + ((dialogInfo->inFront) ? 0 : 15),			(*(dialogInfo->common)->cNodelist.list)->rView.top - 1);				SetPt (&theCell, 0, 0);			if ( LGetSelect (true, &theCell, (dialogInfo->common)->cNodelist.list) )		{			LDraw (theCell, (dialogInfo->common)->cNodelist.list);		}				break;	case actionBroadcast:			GetPort (&oldPort);		SetPort (dialogInfo->dialog);		switch (((BroadcastRecPtr) event)->synctype)		{		case broadClose:					WNodeEventProcessor (NULL, dialogInfo, actionClose);			break;		case broadGlobalResync:			((WindowPeek)(dialogInfo->dialog))->windowKind = myKind_top;			(dialogInfo->common)->cNodelist.fixmode = ((BroadcastRecPtr) event)->area;			(dialogInfo->common)->cNodelist.parrent = (Ptr) ((BroadcastRecPtr) event)->message;			break;		}		break;		case actionMenu:		SetPort (dialogInfo->dialog);		menuItem = (info >> 16) & 0xFF;				switch ((info >> 24) & 0xFF)		{		case nodeM:			switch (menuItem)			{			case nWhoIs:								WhoIs (&(dialogInfo->common)->cNodelist.nl_addr);				InvalRect (&(dialogInfo->dialog)->portRect);				break;			}					break;		}		break;		case actionOpen:			break;		case mouseDown:		if ((info >> 16) != inMenuBar)			where = event->where;		switch (info >> 16)		{		case inMenuBar:					recalcWindowMenu ();			hMenu = GetMenuHandle (fileM + 256);			(*hMenu)->enableFlags = 1L | (1L << fClose) | (1L << fQuit);						hMenu = GetMenuHandle (editM + 256);			(*hMenu)->enableFlags = 0;			hMenu = GetMenuHandle (msgM + 256);			(*hMenu)->enableFlags = 0;			hMenu = GetMenuHandle (nodeM + 256);			(*hMenu)->enableFlags = 1L | (1L << nWhoIs);			hMenu = GetMenuHandle (shuffleM + 256);			(*hMenu)->enableFlags = 0;			hMenu = GetMenuHandle (windowM + 256);			(*hMenu)->enableFlags = -1L;			(*hMenu)->enableFlags &= ~(1L << wSubjects);			DrawMenuBar ();			break;		case inContent:					FindWindow (event->where, &window);						if (window != FrontWindow ())			{				if (((WindowPeek)FrontWindow ())->windowKind == myKind_top)					SysBeep (10);				else					SelectWindow (window);			}			else			{				SetPort (dialogInfo->dialog);				GlobalToLocal (&where);								key = LClick (where, event->modifiers, (dialogInfo->common)->cNodelist.list);				SetPt (&theCell, 0, 0);							if ( LGetSelect (true, &theCell, (dialogInfo->common)->cNodelist.list) )				{					switch ((dialogInfo->common)->cNodelist.nl_level)					{					case 0:	(dialogInfo->common)->cNodelist.nl_addr.zone = 0;					case 1:	(dialogInfo->common)->cNodelist.nl_addr.net = 0;					case 2:	(dialogInfo->common)->cNodelist.nl_addr.node = 0;					case 3:	(dialogInfo->common)->cNodelist.nl_addr.point = 0;					}								switch ((dialogInfo->common)->cNodelist.nl_level)					{					case 0:	(dialogInfo->common)->cNodelist.nl_addr.zone =								ZoneByIndex (theCell.v);							break;												case 1:	(dialogInfo->common)->cNodelist.nl_addr.net =								NetByIndex (theCell.v, &(dialogInfo->common)->cNodelist.nl_addr);							break;												case 2:	(dialogInfo->common)->cNodelist.nl_addr.node =								NodeByIndex (theCell.v, &(dialogInfo->common)->cNodelist.nl_addr);							break;												case 3:	(dialogInfo->common)->cNodelist.nl_addr.point =								PointByIndex (theCell.v, &(dialogInfo->common)->cNodelist.nl_addr);							break;					}					DrawContents (dialogInfo);					if (key)					{						if (!(dialogInfo->common)->cNodelist.fixmode)						{							WhoIs (&(dialogInfo->common)->cNodelist.nl_addr);							InvalRect (&(dialogInfo->dialog)->portRect);						}						else						{							EventProcessor = ((windowsQElPtr) (dialogInfo->common)->cNodelist.parrent)->EventProcessor;							bc.synctype = (dialogInfo->common)->cNodelist.fixmode;							bc.area = ((long) (dialogInfo->common)->cNodelist.nl_addr.zone << 16) |										(dialogInfo->common)->cNodelist.nl_addr.net;							bc.message = ((long) (dialogInfo->common)->cNodelist.nl_addr.node << 16) |										(dialogInfo->common)->cNodelist.nl_addr.point;							EventProcessor ((EventRecord *) &bc,								(windowsQElPtr) (dialogInfo->common)->cNodelist.parrent,										actionBroadcast);							WNodeEventProcessor (event, dialogInfo, actionClose);						}					}				}			}			break;		case inZoomIn:		case inZoomOut:			if (TrackBox (dialogInfo->dialog, event->where, info >> 16))			{				ZoomWindow (dialogInfo->dialog, info >> 16, true);				AdjustWinSize (dialogInfo->dialog,						(dialogInfo->common)->cNodelist.list,						(dialogInfo->dialog)->portRect.bottom);								originalView = (*(((WindowPeek)(dialogInfo->dialog))->contRgn))->rgnBBox;				originalView.bottom = (dialogInfo->dialog)->portRect.bottom;//				EraseRect (&(dialogInfo->dialog)->portRect);				InvalRect (&(dialogInfo->dialog)->portRect);			}			break;		case inDrag:			FindWindow (event->where, &window);						if (window != FrontWindow ())			{				if (((WindowPeek)FrontWindow ())->windowKind == myKind_top)					SysBeep (10);				else					SelectWindow (window);			}			else			{				DragWindow ( dialogInfo->dialog, event->where, &qd.screenBits.bounds );				originalView = (*(((WindowPeek)(dialogInfo->dialog))->contRgn))->rgnBBox;				originalView.bottom = (dialogInfo->dialog)->portRect.bottom;			}						break;		case inGoAway:					if (TrackGoAway (dialogInfo->dialog, event->where))				WNodeEventProcessor (event, dialogInfo, actionClose);						break;		case inGrow:					SetPort (dialogInfo->dialog);						GetDialogItem ( dialogInfo->dialog, 1, &iType, &iHandle, &rView );						newc = (*((dialogInfo->common)->cNodelist.list))->cellSize.v;			rDataBnds.top = rView.top + newc * 8;			rDataBnds.bottom = qd.screenBits.bounds.bottom;			rDataBnds.left = (dialogInfo->dialog)->portRect.right;			rDataBnds.right = (dialogInfo->dialog)->portRect.right;			lSizeVH = GrowWindow ( dialogInfo->dialog, event->where, &rDataBnds );						if (lSizeVH)			{				AdjustWinSize (dialogInfo->dialog, (dialogInfo->common)->cNodelist.list, HiWord (lSizeVH));				InvalRect (&(dialogInfo->dialog)->portRect);			}						break;		}			break;		case keyDown:	case autoKey:				SetPort (dialogInfo->dialog);		key = event->message & 0xFF;				switch (key)		{//		case 0x1B://		//			WNodeEventProcessor (event, dialogInfo, actionClose);////			break;						case EnterKey:		case ReturnKey:					SetPt (&theCell, 0, 0);					if ( LGetSelect (true, &theCell, (dialogInfo->common)->cNodelist.list) )			{				if (!(dialogInfo->common)->cNodelist.fixmode)				{					WhoIs (&(dialogInfo->common)->cNodelist.nl_addr);					InvalRect (&(dialogInfo->dialog)->portRect);				}				else				{					EventProcessor = ((windowsQElPtr) (dialogInfo->common)->cNodelist.parrent)->EventProcessor;					bc.synctype = (dialogInfo->common)->cNodelist.fixmode;					bc.area = ((long) (dialogInfo->common)->cNodelist.nl_addr.zone << 16) |								(dialogInfo->common)->cNodelist.nl_addr.net;					bc.message = ((long) (dialogInfo->common)->cNodelist.nl_addr.node << 16) |								(dialogInfo->common)->cNodelist.nl_addr.point;					EventProcessor ((EventRecord *) &bc,						(windowsQElPtr) (dialogInfo->common)->cNodelist.parrent,								actionBroadcast);					WNodeEventProcessor (event, dialogInfo, actionClose);				}			}						break;					case 0x20:						break;		case LeftArrowKey:		//	Left					if ((dialogInfo->common)->cNodelist.nl_level == 0)			{				CallASndPlay (129);				break;			}						switch ((dialogInfo->common)->cNodelist.nl_level)			{			case 0:	(dialogInfo->common)->cNodelist.nl_addr.zone = 0;			case 1:	(dialogInfo->common)->cNodelist.nl_addr.net = 0;			case 2:	(dialogInfo->common)->cNodelist.nl_addr.node = 0;			case 3:	(dialogInfo->common)->cNodelist.nl_addr.point = 0;			}						(dialogInfo->common)->cNodelist.nl_level--;						LDelRow (0, 0, (dialogInfo->common)->cNodelist.list);						LSetDrawingMode ( false, (dialogInfo->common)->cNodelist.list );			DrawNodeList (dialogInfo);						SetPt (&theCell, 0, gotline ((dialogInfo->common)->cNodelist.nl_level,				&(dialogInfo->common)->cNodelist.nl_addr));						LSetSelect (true, theCell, (dialogInfo->common)->cNodelist.list);			LAutoScroll ((dialogInfo->common)->cNodelist.list);			LSetDrawingMode ( true, (dialogInfo->common)->cNodelist.list );						InvalRect (&(dialogInfo->dialog)->portRect);			break;				case RightArrowKey:		//	Right					if ((dialogInfo->common)->cNodelist.nl_level == 3 ||				!hasSequence ((dialogInfo->common)->cNodelist.nl_level,					&(dialogInfo->common)->cNodelist.nl_addr))			{				CallASndPlay (129);				break;			}						(dialogInfo->common)->cNodelist.nl_level++;						LDelRow (0, 0, (dialogInfo->common)->cNodelist.list);						LSetDrawingMode ( false, (dialogInfo->common)->cNodelist.list );			DrawNodeList (dialogInfo);			LSetDrawingMode ( true, (dialogInfo->common)->cNodelist.list );					switch ((dialogInfo->common)->cNodelist.nl_level)			{			case 0:	(dialogInfo->common)->cNodelist.nl_addr.zone =						ZoneByIndex (0);					break;								case 1:	(dialogInfo->common)->cNodelist.nl_addr.net =						NetByIndex (0, &(dialogInfo->common)->cNodelist.nl_addr);					break;								case 2:	(dialogInfo->common)->cNodelist.nl_addr.node =						NodeByIndex (0, &(dialogInfo->common)->cNodelist.nl_addr);					break;								case 3:	(dialogInfo->common)->cNodelist.nl_addr.point =						PointByIndex (0, &(dialogInfo->common)->cNodelist.nl_addr);					break;			}						SetPt (&theCell, 0, 0);			LSetSelect (true, theCell, (dialogInfo->common)->cNodelist.list);			InvalRect (&(dialogInfo->dialog)->portRect);						break;				case UpArrowKey:		//	Up		case DownArrowKey:		//	Down					newh = (*((dialogInfo->common)->cNodelist.list))->dataBounds.bottom;					SetPt (&theCell, 0, 0);					if ( LGetSelect (true, &theCell, (dialogInfo->common)->cNodelist.list) )				newc = theCell.v;			else				newc = (key == UpArrowKey) ? newh : -1;						neww = (key == UpArrowKey) ? newc - 1 : newc + 1;						if (neww >= newh)				neww = 0;			else				if (neww < 0)					neww = newh - 1;						SetPt (&theCell, 0, newc);			LSetSelect (false, theCell, (dialogInfo->common)->cNodelist.list);						SetPt (&theCell, 0, neww);			LSetSelect (true, theCell, (dialogInfo->common)->cNodelist.list);						LAutoScroll ((dialogInfo->common)->cNodelist.list);						switch ((dialogInfo->common)->cNodelist.nl_level)			{			case 0:	(dialogInfo->common)->cNodelist.nl_addr.zone = 0;			case 1:	(dialogInfo->common)->cNodelist.nl_addr.net = 0;			case 2:	(dialogInfo->common)->cNodelist.nl_addr.node = 0;			case 3:	(dialogInfo->common)->cNodelist.nl_addr.point = 0;			}				switch ((dialogInfo->common)->cNodelist.nl_level)			{			case 0:	(dialogInfo->common)->cNodelist.nl_addr.zone =						ZoneByIndex (theCell.v);					break;								case 1:	(dialogInfo->common)->cNodelist.nl_addr.net =						NetByIndex (theCell.v, &(dialogInfo->common)->cNodelist.nl_addr);					break;								case 2:	(dialogInfo->common)->cNodelist.nl_addr.node =						NodeByIndex (theCell.v, &(dialogInfo->common)->cNodelist.nl_addr);					break;								case 3:	(dialogInfo->common)->cNodelist.nl_addr.point =						PointByIndex (theCell.v, &(dialogInfo->common)->cNodelist.nl_addr);					break;			}						DrawContents (dialogInfo);			break;		case PageUpKey:			//	Up		case PageDownKey:		//	Down					GetDialogItem ( dialogInfo->dialog, 1, &iType, &iHandle, &rView );			dummy = ((dialogInfo->dialog)->portRect.bottom - rView.top) / (*((dialogInfo->common)->cNodelist.list))->cellSize.v;			newh = (*((dialogInfo->common)->cNodelist.list))->dataBounds.bottom;			if (dummy < newh)			{				SetPt (&theCell, 0, 0);							if ( LGetSelect (true, &theCell, (dialogInfo->common)->cNodelist.list) )				{					newc = theCell.v;										neww = (key == PageUpKey) ? newc - dummy : newc + dummy;										if (neww >= newh)						neww = newh - 1;					else						if (neww < 0)							neww = 0;										SetPt (&theCell, 0, newc);					LSetSelect (false, theCell, (dialogInfo->common)->cNodelist.list);										SetPt (&theCell, 0, neww);					LSetSelect (true, theCell, (dialogInfo->common)->cNodelist.list);					LAutoScroll ((dialogInfo->common)->cNodelist.list);				}			}			else			{				SetPt (&theCell, 0, 0);							if ( LGetSelect (true, &theCell, (dialogInfo->common)->cNodelist.list) )				{					newc = theCell.v;										neww = (key == PageUpKey) ? 0 : newh - 1;										SetPt (&theCell, 0, newc);					LSetSelect (false, theCell, (dialogInfo->common)->cNodelist.list);										SetPt (&theCell, 0, neww);					LSetSelect (true, theCell, (dialogInfo->common)->cNodelist.list);					LAutoScroll ((dialogInfo->common)->cNodelist.list);				}			}						switch ((dialogInfo->common)->cNodelist.nl_level)			{			case 0:	(dialogInfo->common)->cNodelist.nl_addr.zone = 0;			case 1:	(dialogInfo->common)->cNodelist.nl_addr.net = 0;			case 2:	(dialogInfo->common)->cNodelist.nl_addr.node = 0;			case 3:	(dialogInfo->common)->cNodelist.nl_addr.point = 0;			}				switch ((dialogInfo->common)->cNodelist.nl_level)			{			case 0:	(dialogInfo->common)->cNodelist.nl_addr.zone =						ZoneByIndex (theCell.v);					break;								case 1:	(dialogInfo->common)->cNodelist.nl_addr.net =						NetByIndex (theCell.v, &(dialogInfo->common)->cNodelist.nl_addr);					break;								case 2:	(dialogInfo->common)->cNodelist.nl_addr.node =						NodeByIndex (theCell.v, &(dialogInfo->common)->cNodelist.nl_addr);					break;								case 3:	(dialogInfo->common)->cNodelist.nl_addr.point =						PointByIndex (theCell.v, &(dialogInfo->common)->cNodelist.nl_addr);					break;			}						DrawContents (dialogInfo);			break;		case HomeKey:					SetPt (&theCell, 0, 0);					if ( LGetSelect (true, &theCell, (dialogInfo->common)->cNodelist.list) )			{				newc = theCell.v;				SetPt (&theCell, 0, newc);				LSetSelect (false, theCell, (dialogInfo->common)->cNodelist.list);			}			SetPt (&theCell, 0, 0);			LSetSelect (true, theCell, (dialogInfo->common)->cNodelist.list);			LAutoScroll ((dialogInfo->common)->cNodelist.list);			switch ((dialogInfo->common)->cNodelist.nl_level)			{			case 0:	(dialogInfo->common)->cNodelist.nl_addr.zone = 0;			case 1:	(dialogInfo->common)->cNodelist.nl_addr.net = 0;			case 2:	(dialogInfo->common)->cNodelist.nl_addr.node = 0;			case 3:	(dialogInfo->common)->cNodelist.nl_addr.point = 0;			}				switch ((dialogInfo->common)->cNodelist.nl_level)			{			case 0:	(dialogInfo->common)->cNodelist.nl_addr.zone =						ZoneByIndex (theCell.v);					break;								case 1:	(dialogInfo->common)->cNodelist.nl_addr.net =						NetByIndex (theCell.v, &(dialogInfo->common)->cNodelist.nl_addr);					break;								case 2:	(dialogInfo->common)->cNodelist.nl_addr.node =						NodeByIndex (theCell.v, &(dialogInfo->common)->cNodelist.nl_addr);					break;								case 3:	(dialogInfo->common)->cNodelist.nl_addr.point =						PointByIndex (theCell.v, &(dialogInfo->common)->cNodelist.nl_addr);					break;			}						DrawContents (dialogInfo);			break;		case EndKey:					newh = (*((dialogInfo->common)->cNodelist.list))->dataBounds.bottom;			SetPt (&theCell, 0, 0);					if ( LGetSelect (true, &theCell, (dialogInfo->common)->cNodelist.list) )			{				newc = theCell.v;				SetPt (&theCell, 0, newc);				LSetSelect (false, theCell, (dialogInfo->common)->cNodelist.list);			}			SetPt (&theCell, 0, newh-1);			LSetSelect (true, theCell, (dialogInfo->common)->cNodelist.list);			LAutoScroll ((dialogInfo->common)->cNodelist.list);			switch ((dialogInfo->common)->cNodelist.nl_level)			{			case 0:	(dialogInfo->common)->cNodelist.nl_addr.zone = 0;			case 1:	(dialogInfo->common)->cNodelist.nl_addr.net = 0;			case 2:	(dialogInfo->common)->cNodelist.nl_addr.node = 0;			case 3:	(dialogInfo->common)->cNodelist.nl_addr.point = 0;			}				switch ((dialogInfo->common)->cNodelist.nl_level)			{			case 0:	(dialogInfo->common)->cNodelist.nl_addr.zone =						ZoneByIndex (theCell.v);					break;								case 1:	(dialogInfo->common)->cNodelist.nl_addr.net =						NetByIndex (theCell.v, &(dialogInfo->common)->cNodelist.nl_addr);					break;								case 2:	(dialogInfo->common)->cNodelist.nl_addr.node =						NodeByIndex (theCell.v, &(dialogInfo->common)->cNodelist.nl_addr);					break;								case 3:	(dialogInfo->common)->cNodelist.nl_addr.point =						PointByIndex (theCell.v, &(dialogInfo->common)->cNodelist.nl_addr);					break;			}						DrawContents (dialogInfo);			break;		}		break;			case updateEvt:		SetPort (dialogInfo->dialog);		iRect = (*(((WindowPeek)(dialogInfo->dialog))->updateRgn))->rgnBBox;				GlobalToLocal (&topLeft(iRect));		GlobalToLocal (&botRight(iRect));		if (iRect.right > (*(dialogInfo->common)->cNodelist.list)->rView.right)			iRect.right = (*(dialogInfo->common)->cNodelist.list)->rView.right;		EraseRect (&iRect);		GetDialogItem (dialogInfo->dialog, 1, &iType, &iHandle, &rView );				SetRect (&rDataBnds, 0, 0, (dialogInfo->dialog)->portRect.right, rView.top - 1);		EraseRect (&rDataBnds);				MoveTo (0, rView.top - 1);		LineTo ((dialogInfo->dialog)->portRect.right, rView.top - 1);		BeginUpdate (dialogInfo->dialog);		DrawOnlyGrowIcon (dialogInfo->dialog);		EndUpdate (dialogInfo->dialog);		DrawContents (dialogInfo);		{			RgnHandle	mRgn;						mRgn = NewRgn ();			RectRgn (mRgn, &iRect);			LUpdate ( mRgn, (dialogInfo->common)->cNodelist.list );			if (!(dialogInfo->inFront))			{				iRect = (*(dialogInfo->common)->cNodelist.list)->rView;				iRect.left = iRect.right;				iRect.right += 15;				iRect.bottom -= 15;				EraseRect (&iRect);				MoveTo ((*(dialogInfo->common)->cNodelist.list)->rView.right,						(*(dialogInfo->common)->cNodelist.list)->rView.top);				LineTo ((*(dialogInfo->common)->cNodelist.list)->rView.right,						(*(dialogInfo->common)->cNodelist.list)->rView.bottom);			}			DisposeRgn (mRgn);		}		break;	}}void WNodeDialogProcessor (EventRecord *event, windowsQElPtr dialogInfo, long info){}