#include <Controls.h>#include <Desk.h>#include <StandardFile.h>#include <Events.h>#include <Scrap.h>#include <ToolUtils.h>#include "TE32K.h"#include <stdio.h>#define	INDENT	5extern	WindowPtr		theWPtr;extern	TE32KHandle		theTEH32K;extern	ControlHandle	theVScroll,theHScroll;extern	Cursor			editCursor,waitCursor;extern	char			changed;extern	SFReply			mySFReply;extern	short				defaultFont,defaultFontSize;#if defined(powerc) || defined(__powerc)extern QDGlobals			qd;#endifSetUpCursors(){CursHandle	hCurs;		hCurs = GetCursor(iBeamCursor);	editCursor = **hCurs;		hCurs = GetCursor(watchCursor);	waitCursor = **hCurs;}DoMouseDown(theEvent)EventRecord	*theEvent;{WindowPtr	whichWindow;short			windowCode;	windowCode = FindWindow(theEvent->where,&whichWindow);		switch (windowCode = FindWindow(theEvent->where,&whichWindow)) 	{		case inMenuBar:			DoCommand(MenuSelect(theEvent->where));			break;					case inSysWindow:			SystemClick(theEvent,whichWindow);			break;					case inContent:			if (whichWindow != FrontWindow())				SelectWindow(whichWindow);						else if (IsOurWindow(whichWindow))				DoContent(whichWindow,theEvent);						break;				case inDrag:			if (whichWindow != FrontWindow())				SelectWindow(whichWindow);						else if (IsOurWindow(whichWindow))				DoDrag(whichWindow,theEvent);						break;					case inGrow:			if (whichWindow != FrontWindow())				SelectWindow(whichWindow);						else if (IsOurWindow(whichWindow))				DoGrow(whichWindow,theEvent);						break;				case inZoomIn:		case inZoomOut:			if (whichWindow != FrontWindow())				SelectWindow(whichWindow);						else if (IsOurWindow(whichWindow) && TrackBox(whichWindow,theEvent->where,windowCode))				DoZoom(whichWindow,windowCode);						break;				case inGoAway:			if (whichWindow != FrontWindow())				SelectWindow(whichWindow);						else if (IsOurWindow(whichWindow) && TrackGoAway(whichWindow,theEvent->where))				DoCloseWindow(whichWindow);						break;	}}IsOurWindow(whichWindow)WindowPtr	whichWindow;{	if (theWPtr && whichWindow == theWPtr)		return(true);	else		return(false);}void ActivateScrollbar(ControlHandle scrollbar, Boolean becomingActive){	Rect iRect;		iRect = (**scrollbar).contrlRect;	if (becomingActive) {		(**scrollbar).contrlVis = 255;		Draw1Control(scrollbar);	} else {		(**scrollbar).contrlVis = 0;		InsetRect(&iRect, 1, 1);		EraseRect(&iRect);	}	ValidRect(&iRect);}DoActivateDeactivate(whichWindow,adFlag)WindowPtr	whichWindow;char	adFlag;{GrafPtr			oldPort;	if (whichWindow == theWPtr)	{		GetPort(&oldPort);		SetPort(whichWindow);				ActivateScrollbar(theVScroll, adFlag);		ActivateScrollbar(theHScroll, adFlag);				if (adFlag)			TE32KActivate(theTEH32K);		else			TE32KDeactivate(theTEH32K);				DrawGrowIcon(whichWindow);				SetPort(oldPort);				return(true);	}		else		return(false);}DoCloseWindow(whichWindow)WindowPtr	whichWindow;{short		userChoice;	if (theWPtr && whichWindow==theWPtr)	{		if (changed)		{			userChoice = YesNoCancel("Save changes?",3);						if (userChoice == 3)				return(false);						else if (userChoice == 1 && !SaveTextFile(theTEH32K,&mySFReply))				return(false);		}						if (theVScroll) DisposeControl(theVScroll);		if (theHScroll) DisposeControl(theHScroll);		if (theTEH32K) TE32KDispose(theTEH32K);		if (theWPtr) DisposeWindow(theWPtr);				theWPtr = 0L;		theTEH32K = 0L;		theVScroll = 0L;		theHScroll = 0L;				return(true);	}		else		return(false);}DoGrow(whichWindow,theEvent)WindowPtr	whichWindow;EventRecord	*theEvent;{Rect			tempRect;long			newSize;GrafPtr			oldPort;	if (theWPtr && whichWindow==theWPtr)	{		SetRect(&tempRect,100,50,32767,32767);		newSize = GrowWindow(whichWindow,theEvent->where,&tempRect);		SizeWindow(whichWindow,LoWord(newSize),HiWord(newSize),0xff);		tempRect = whichWindow->portRect;		GetPort(&oldPort);		SetPort(whichWindow);		EraseRect(&tempRect);		InvalRect(&tempRect);				MoveControl(theVScroll,tempRect.right+1-16,tempRect.top-1);		SizeControl(theVScroll,16,whichWindow->portRect.bottom-14-(whichWindow->portRect.top-1));				MoveControl(theHScroll,tempRect.left-1,tempRect.bottom+1-16);		SizeControl(theHScroll,whichWindow->portRect.right-14-(whichWindow->portRect.left-1),16);				AdjustForResizedWindow();				SetPort(oldPort);				return(true);	}		else		return(false);}DoZoom(whichWindow,windowCode)WindowPtr	whichWindow;short windowCode;{Rect			tempRect;GrafPtr			oldPort;	if (theWPtr && whichWindow==theWPtr)	{		GetPort(&oldPort);		SetPort(whichWindow);				tempRect = whichWindow->portRect;		EraseRect(&tempRect);				ZoomWindow(whichWindow, windowCode, 0);				tempRect = whichWindow->portRect;		EraseRect(&tempRect);				MoveControl(theVScroll,tempRect.right+1-16,tempRect.top-1);		SizeControl(theVScroll,16,whichWindow->portRect.bottom-14-(whichWindow->portRect.top-1));				MoveControl(theHScroll,tempRect.left-1,tempRect.bottom+1-16);		SizeControl(theHScroll,whichWindow->portRect.right-14-(whichWindow->portRect.left-1),16);				AdjustForResizedWindow();				tempRect = whichWindow->portRect;		InvalRect(&tempRect);				SetPort(oldPort);				return(true);	}		else		return(false);}DoDrag(whichWindow,theEvent)WindowPtr	whichWindow;EventRecord	*theEvent;{Rect			tempRect;	if (theWPtr && whichWindow == theWPtr)	{		SetRect(&tempRect,qd.screenBits.bounds.left+10,qd.screenBits.bounds.top+25,qd.screenBits.bounds.right-10,qd.screenBits.bounds.bottom-25);		DragWindow(whichWindow,theEvent->where,&tempRect);		return(true);	}		else		return(false);}AdjustScrollBar(){short		ctlVal,screenLines,numLines,oldVal;	ctlVal = ((*theTEH32K)->viewRect.top - (*theTEH32K)->destRect.top)/(*theTEH32K)->lineHeight;	screenLines = ((*theTEH32K)->viewRect.bottom - (*theTEH32K)->viewRect.top)/(**theTEH32K).lineHeight;	numLines = (**theTEH32K).nLines;		if (ctlVal > numLines-screenLines)		SetCtlMax(theVScroll,ctlVal);	else		SetCtlMax(theVScroll,(numLines-screenLines > 0) ? numLines-screenLines : 0);		oldVal = GetCtlValue(theVScroll);		if (oldVal != ctlVal)		SetCtlValue(theVScroll,ctlVal);				ctlVal = ((*theTEH32K)->viewRect.left - (*theTEH32K)->destRect.left)/(*theTEH32K)->lineHeight;	numLines = GetCtlMax(theHScroll);		if (ctlVal < 0)		ctlVal = 0;	else if (ctlVal > numLines)		ctlVal = numLines;		oldVal = GetCtlValue(theHScroll);		if (oldVal != ctlVal)		SetCtlValue(theHScroll,ctlVal);}AdjustForResizedWindow(){Rect		tempRect;	SetRect(&tempRect,(theWPtr)->portRect.left+INDENT,(theWPtr)->portRect.top+INDENT,(theWPtr)->portRect.right-15-INDENT,(theWPtr)->portRect.bottom-16-INDENT);	tempRect.bottom = tempRect.top + ((tempRect.bottom - tempRect.top)/(*theTEH32K)->lineHeight)*(*theTEH32K)->lineHeight;		RectToLongRect(&tempRect,&((*theTEH32K)->viewRect));		RectToLongRect(&tempRect,&((*theTEH32K)->destRect));	(*theTEH32K)->destRect.top -= (long) GetCtlValue(theVScroll)*(*theTEH32K)->lineHeight;	(*theTEH32K)->destRect.left -= (long) GetCtlValue(theHScroll)*(*theTEH32K)->lineHeight;		(**theTEH32K).destRect.right -= 10;		TE32KFromScrap();		SetCursor(&waitCursor);	TE32KCalText(theTEH32K);	InitCursor();		AdjustScrollBar();}pascal void myScrollProc(theControl, theCode)ControlHandle	theControl;short	theCode;{long		scrollAmt,lines;short			controlMax,controlMin,controlVal;RgnHandle	updateRgn;		if (theVScroll && theControl==theVScroll)	{		controlMax = GetCtlMax(theControl);		controlMin = GetCtlMin(theControl);		controlVal = GetCtlValue(theControl);				updateRgn = NewRgn();				switch (theCode) 		{			case inUpButton:				if (controlVal > controlMin)				{					SetCtlValue(theControl,controlVal-1);										TE32KScroll(0L,(long) (**theTEH32K).lineHeight,theTEH32K);				}								break;							case inDownButton: 				if (controlVal < controlMax)				{					SetCtlValue(theControl,controlVal+1);										TE32KScroll(0L,(long) -(**theTEH32K).lineHeight,theTEH32K);				}								break;				case inPageUp: 				if (controlVal > controlMin)				{					lines = ((*theTEH32K)->viewRect.bottom - (*theTEH32K)->viewRect.top)/(**theTEH32K).lineHeight;					scrollAmt = (controlVal-lines < controlMin) ? controlVal-controlMin : lines;					SetCtlValue(theControl,controlVal-scrollAmt);					TE32KScroll(0L,(long) ((long) scrollAmt * (long) (**theTEH32K).lineHeight),theTEH32K);				}								break;				case inPageDown: 				if (controlVal < controlMax)				{					lines = ((**theTEH32K).viewRect.bottom - (**theTEH32K).viewRect.top)/(**theTEH32K).lineHeight;					scrollAmt = (controlVal+lines > controlMax) ? controlMax-controlVal : lines;					SetCtlValue(theControl,controlVal+scrollAmt);					TE32KScroll(0L,(long) ((long) -scrollAmt * (long) (**theTEH32K).lineHeight),theTEH32K);				}								break;		}				AdjustScrollBar();				DisposeRgn(updateRgn);	}		else if (theHScroll && theControl==theHScroll)	{		controlMax = GetCtlMax(theControl);		controlMin = GetCtlMin(theControl);		controlVal = GetCtlValue(theControl);				updateRgn = NewRgn();				switch (theCode) 		{			case inUpButton:				if (controlVal > controlMin)				{					SetCtlValue(theControl,controlVal-1);										TE32KScroll((long) (**theTEH32K).lineHeight,0L,theTEH32K);				}								break;							case inDownButton: 				if (controlVal < controlMax)				{					SetCtlValue(theControl,controlVal+1);										TE32KScroll((long) -(**theTEH32K).lineHeight,0L,theTEH32K);				}								break;				case inPageUp: 				if (controlVal > controlMin)				{					lines = ((*theTEH32K)->viewRect.right - (*theTEH32K)->viewRect.left)/(2 * (**theTEH32K).lineHeight);					scrollAmt = (controlVal-lines < controlMin) ? controlVal-controlMin : lines;					SetCtlValue(theControl,controlVal-scrollAmt);					TE32KScroll((long) ((long) scrollAmt * (long) (**theTEH32K).lineHeight),0L,theTEH32K);				}								break;				case inPageDown: 				if (controlVal < controlMax)				{					lines = ((*theTEH32K)->viewRect.right - (*theTEH32K)->viewRect.left)/(2 * (**theTEH32K).lineHeight);					scrollAmt = (controlVal+lines > controlMax) ? controlMax-controlVal : lines;					SetCtlValue(theControl,controlVal+scrollAmt);					TE32KScroll((long) -((long) scrollAmt * (long) (**theTEH32K).lineHeight),0L,theTEH32K);				}								break;		}				AdjustScrollBar();				DisposeRgn(updateRgn);	}}DoContent(whichWindow,theEvent)WindowPtr	whichWindow;EventRecord	*theEvent;{GrafPtr			oldPort;ControlHandle	whichControl;short				cntlCode;long			oldVal;Rect			tempRect;static	ControlActionUPP scrollProcUPP = nil;	if (!scrollProcUPP)		scrollProcUPP = NewControlActionProc(myScrollProc);	if (theWPtr && whichWindow==theWPtr)	{		GetPort(&oldPort);		SetPort(whichWindow);				LongRectToRect(&((**theTEH32K).viewRect),&tempRect);				GlobalToLocal(&(theEvent->where));				cntlCode = FindControl(theEvent->where,whichWindow,&whichControl);				if (theVScroll && whichControl == theVScroll && cntlCode != 0)		{			if (cntlCode == inThumb)			{				oldVal = GetCtlValue(whichControl);								TrackControl(whichControl,theEvent->where,0L);								TE32KScroll(0L,(long) ((oldVal - (long) GetCtlValue(whichControl)) * (long) (**theTEH32K).lineHeight),theTEH32K);			}						else				TrackControl(whichControl,theEvent->where,scrollProcUPP);		}				else if (theHScroll && whichControl == theHScroll && cntlCode != 0)		{			if (cntlCode == inThumb)			{				oldVal = GetCtlValue(whichControl);								TrackControl(whichControl,theEvent->where,0L);								TE32KScroll((long) ((oldVal - GetCtlValue(whichControl)) * (**theTEH32K).lineHeight),0L,theTEH32K);			}						else				TrackControl(whichControl,theEvent->where,scrollProcUPP);		}				else if (PtInRect(theEvent->where,&tempRect))		{			if (theEvent->modifiers & shiftKey)				TE32KClick(theEvent->where,true,theTEH32K);			else				TE32KClick(theEvent->where,false,theTEH32K);		}				SetPort(oldPort);				return(true);	}		else		return(false);}UpdateWindow(whichWindow)WindowPtr	whichWindow;{GrafPtr			oldPort;Rect			tempRect;LongRect		tempLongRect;RgnHandle		updateRgn;	if (whichWindow != theWPtr)		return(false);	GetPort(&oldPort);	SetPort(whichWindow);		PenNormal();		BeginUpdate(whichWindow);		tempRect = whichWindow->portRect;	EraseRect(&tempRect);		if (whichWindow == theWPtr)	{		DrawGrowIcon(whichWindow);		DrawControls(whichWindow);				updateRgn = ((WindowPeek) theWPtr)->updateRgn;				tempLongRect.left = (**updateRgn).rgnBBox.left;		tempLongRect.top = (**updateRgn).rgnBBox.top;		tempLongRect.right = (**updateRgn).rgnBBox.right;		tempLongRect.bottom = (**updateRgn).rgnBBox.bottom;				RectToLongRect(&tempRect,&tempLongRect);		TE32KUpdate(&tempLongRect,theTEH32K);	}		EndUpdate(whichWindow);		SetPort(oldPort);		return(true);}void MyClicker(){short			controlMax,controlMin,controlVal,lineHeight;Rect		viewRect;Point		mousePoshort;RgnHandle	saveClip;long		hDelta,vDelta;	LongRectToRect(&((**theTEH32K).viewRect),&viewRect);	lineHeight = (**theTEH32K).lineHeight;	hDelta = 0L;	vDelta = 0L;		GetMouse(&mousePoshort);		if (!PtInRect(mousePoshort,&viewRect))	{		controlMax = GetCtlMax(theVScroll);		controlMin = GetCtlMin(theVScroll);		controlVal = GetCtlValue(theVScroll);				if (mousePoshort.v>viewRect.bottom && controlVal<controlMax)		{			vDelta = -lineHeight;			SetCtlValue(theVScroll,controlVal+1);		}				else if (mousePoshort.v<viewRect.top && controlVal>controlMin)		{			vDelta = lineHeight;			SetCtlValue(theVScroll,controlVal-1);		}				controlMax = GetCtlMax(theHScroll);		controlMin = GetCtlMin(theHScroll);		controlVal = GetCtlValue(theHScroll);				if (mousePoshort.h>viewRect.right && controlVal<controlMax)		{			hDelta = -lineHeight;			SetCtlValue(theHScroll,controlVal+1);		}				else if (mousePoshort.h<viewRect.left && controlVal>controlMin)		{			hDelta = lineHeight;			SetCtlValue(theHScroll,controlVal-1);		}	}		if (hDelta || vDelta)	{		saveClip = NewRgn();		GetClip(saveClip);		ClipRect(&(theWPtr->portRect));				TE32KScroll(hDelta,vDelta,theTEH32K);				SetClip(saveClip);		DisposeRgn(saveClip);	}}void MyClickLoop(){	MyClicker();}DoShowWindow(){Rect			tempRect;FontInfo		theFontInfo;LongRect		tempLongRect;	if (theWPtr)		SelectWindow(theWPtr);			else	{		SetRect(&tempRect,20,40,500,320);				theWPtr = NewWindow (0L,&tempRect,"\pUntitled",true,zoomDocProc,(WindowPtr) -1L,true,0L);		if (theWPtr==0L)		{			ErrorAlert("Insufficient memory to open window");			return;		}				SetPort(theWPtr);				TextFont(defaultFont);		TextSize(defaultFontSize);		TextFace(0);		TextMode(srcCopy);				GetFontInfo(&theFontInfo);				SetRect(&tempRect,(theWPtr)->portRect.right-15,(theWPtr)->portRect.top-1,(theWPtr)->portRect.right+1,(theWPtr)->portRect.bottom-14);		theVScroll = NewControl(theWPtr,&tempRect,"\p",true,0,0,0,scrollBarProc,0L);				if (theVScroll==0L)		{			DisposeWindow(theWPtr);			theWPtr = 0L;			theVScroll = 0L;			ErrorAlert("Insufficient memory to open edit record");			return;		}				SetRect(&tempRect,(theWPtr)->portRect.left-1,(theWPtr)->portRect.bottom+1-16,(theWPtr)->portRect.right-14,(theWPtr)->portRect.bottom+1);		theHScroll = NewControl(theWPtr,&tempRect,"\p",true,0,0,255,scrollBarProc,0L);				if (theHScroll==0L)		{			DisposeWindow(theWPtr);			DisposeControl(theVScroll);			theWPtr = 0L;			theVScroll = 0L;			theHScroll = 0L;			ErrorAlert("Insufficient memory to open edit record");			return;		}				SetRect(&(tempRect),(theWPtr)->portRect.left+INDENT,(theWPtr)->portRect.top+INDENT,(theWPtr)->portRect.right-15-INDENT,(theWPtr)->portRect.bottom-16-INDENT);		RectToLongRect(&tempRect,&tempLongRect);		theTEH32K = TE32KNew(&tempLongRect,&tempLongRect);			if (theTEH32K==0L)		{			DisposeControl(theVScroll);			DisposeControl(theHScroll);			DisposeWindow(theWPtr);			theWPtr = 0L;			theVScroll = 0L;			theHScroll = 0L;			ErrorAlert("Insufficient memory to open edit record");			return;		}				(**theTEH32K).destRect.right -= 10;				TE32KFeatureFlag(te32KFOutlineHilite, TE32KBitSet, theTEH32K);		TE32KFeatureFlag(te32KFShowCarridgeReturns, TE32KBitSet, theTEH32K);				TE32KFromScrap();				(*theTEH32K)->destRect.bottom = (*theTEH32K)->destRect.top + (((*theTEH32K)->destRect.bottom - (*theTEH32K)->destRect.top)/(*theTEH32K)->lineHeight)*(*theTEH32K)->lineHeight;		(*theTEH32K)->viewRect.bottom = (*theTEH32K)->viewRect.top + (((*theTEH32K)->viewRect.bottom - (*theTEH32K)->viewRect.top)/(*theTEH32K)->lineHeight)*(*theTEH32K)->lineHeight;				(**theTEH32K).clikLoop = (TE32KProcPtr) MyClickLoop;				changed = false;				mySFReply.good = false;	}}DoKey(theChar)unsigned char	theChar;{	if (theWPtr && theWPtr == FrontWindow())	{		TE32KKey(theChar,theTEH32K);				TE32KSelView(theTEH32K);				changed = true;				AdjustScrollBar();				return(true);	}		else		return(false);}DoIdle(){	if (theWPtr && theWPtr == FrontWindow())	{		TE32KIdle(theTEH32K);				return(true);	}		else		return(false);}MashortainCursor(){Point		pt;GrafPtr		oldPort;Rect		tempRect;	if (theWPtr && FrontWindow() == theWPtr)	{		GetPort(&oldPort);		SetPort(theWPtr);				SetRect(&tempRect,(theWPtr)->portRect.left+INDENT,(theWPtr)->portRect.top+INDENT,(theWPtr)->portRect.right-15-INDENT,(theWPtr)->portRect.bottom-16-INDENT);				GetMouse(&pt);				if (PtInRect(pt,&tempRect))			SetCursor(&editCursor);				else			SetCursor(&qd.arrow);				return(true);				SetPort(oldPort);	}		return(false);}DoCut(){	if (theWPtr && FrontWindow() == theWPtr && theTEH32K)	{		SetCursor(&waitCursor);		TE32KCut(theTEH32K);		ZeroScrap();		TE32KToScrap();		InitCursor();				changed = true;				TE32KSelView(theTEH32K);		AdjustScrollBar();				return(true);	}		else		return(false);}DoCopy(){	if (theWPtr && FrontWindow() == theWPtr && theTEH32K)	{		SetCursor(&waitCursor);		TE32KCopy(theTEH32K);		ZeroScrap();		TE32KToScrap();		InitCursor();				return(true);	}		else		return(false);}DoPaste(){	if (theWPtr && FrontWindow() == theWPtr && theTEH32K)	{		SetCursor(&waitCursor);		TE32KFromScrap();		TE32KPaste(theTEH32K);		InitCursor();				changed = true;				TE32KSelView(theTEH32K);		AdjustScrollBar();				return(true);	}		else		return(false);}DoClear(){	if (theWPtr && FrontWindow() == theWPtr && theTEH32K)	{		SetCursor(&waitCursor);		TE32KDelete(theTEH32K);		InitCursor();				changed = true;				TE32KSelView(theTEH32K);		AdjustScrollBar();				return(true);	}		else		return(false);}DoSelectAll(){	if (theWPtr && FrontWindow() == theWPtr && theTEH32K)	{		SetCursor(&waitCursor);		TE32KSetSelect(0L,(**theTEH32K).teLength,theTEH32K);		AdjustScrollBar();		InitCursor();				return(true);	}		else		return(false);}