#include <Sound.h>#include <stdio.h>#include <stdarg.h>#include <string.h>#include <QDOffscreen.h>#include "log.h"//#include "Comm.h"#include "Ravel_FTN.h"#include "Ravel_Prefs.h"#include "Pathes.h"extern	Boolean		EventsPossible;static	FILE	*mylog;static	char	emsilog[256];	// Offscreen world variablesstatic	GWorldPtr		currPort;static	GDHandle		currDev;static	GWorldPtr		gMyOffG;static	Rect			rBounds, iRect, tRect;extern	DialogPtr		RavelWindow;extern	Boolean			paranoidal_log;extern	Boolean			multiline_flag;extern	short			multiline_line;typedef struct _chat_win {	Boolean			active;	GWorldPtr		g;		Rect			portRect;	Rect			viewRect;		short			pos;} t_chat_win;static	t_chat_win		chat_win[2];static	t_chat_win		node_info;static	char			node_info_str[256];void	init_chat_windows (void);void	create_chat_window (short win);void	dispose_chat_window (short win);void	win_putc (short win, short c);void	win_puts (short win, unsigned char *s);void	put_nodeinfo (StringPtr info);void	DrawEmbossedRect (const Rect *iRect);void openlog ( void ){	Handle	iHandle;	short	iType, hh, ww;	Rect	iiRect, rrBounds;	logPath[logPath[0]+1] = 0;	mylog = fopen ( (char *) &logPath[1], "a" );	if (!mylog)	{		SysBeep (10);		ExitToShell ();	}	fprintf ( mylog, "\n" );	fclose ( mylog );	strcpy (emsilog, (char *) &logPath[1]);	strcat (emsilog, ".emsi");	GetGWorld ( &currPort, &currDev );		GetDialogItem ( RavelWindow, 10, &iType, &iHandle, &iRect );	SetRect ( &rBounds, 0, 0, iRect.right-iRect.left, iRect.bottom-iRect.top );	SetRect ( &tRect, 0, rBounds.bottom-11, rBounds.right, rBounds.bottom );		NewGWorld ( &gMyOffG, 1, &rBounds, nil, nil, 0 );	SetGWorld ( gMyOffG, nil );	SetPort ( (GrafPtr) gMyOffG );	TextFont ( 4 );	TextSize ( 9 );	PenPat ( &qd.black );	ForeColor ( blackColor );	EraseRect ( &rBounds );	SetGWorld (currPort, currDev);	SetPort ( RavelWindow );	CopyBits ( (BitMap *) (*(gMyOffG->portPixMap)),						&((GrafPtr)RavelWindow)->portBits, &rBounds, &iRect, srcCopy, nil);	init_chat_windows ();//	Init small show win		GetDialogItem (RavelWindow, 10, &iType, &iHandle, &iiRect);	hh = 11;	ww = ((iiRect.right-iiRect.left-10) / 6) * 6;	SetRect (&rrBounds, 0, 0, ww+2, hh);	node_info.portRect = rrBounds;	OffsetRect (&rrBounds, iiRect.left+((iiRect.right-iiRect.left) - (rrBounds.right))/2, iiRect.top+3);	node_info.viewRect = rrBounds;	node_info_str[0] = 0;}void _putlog ( char status, char *t){	Rect		ttRect;		RgnHandle	saveClip, newClip, theRgn;		if (status == '~' && !paranoidal_log)		return;		mylog = fopen ( (char *) &logPath[1], "a" );	if (!mylog)	{		SysBeep (10);	}	if (mylog)		fprintf ( mylog, "%s\n", t );		SetGWorld ( gMyOffG, nil );	SetPort ( (GrafPtr) gMyOffG );	ScrollRect ( &rBounds, 0, -11, NULL );	EraseRect ( &tRect );	MoveTo ( rBounds.left, rBounds.bottom-2 );	DrawText ( t, 0, strlen (t) );	SetGWorld (currPort, currDev);	SetPort ( RavelWindow );	saveClip = NewRgn ();	GetClip (saveClip);	newClip = NewRgn ();/*	if (chat_win[0].active)	{		ttRect = chat_win[0].viewRect;		InsetRect (&ttRect, -3, -3);				theRgn = NewRgn ();		RectRgn (theRgn, &ttRect);		UnionRgn (newClip, theRgn, newClip);		DisposeRgn (theRgn);	}*/	if (chat_win[1].active)	{		ttRect = chat_win[1].viewRect;		InsetRect (&ttRect, -3, -3);				theRgn = NewRgn ();		RectRgn (theRgn, &ttRect);		UnionRgn (newClip, theRgn, newClip);		DisposeRgn (theRgn);	}	if (node_info_str[0])	{		ttRect = node_info.viewRect;		InsetRect (&ttRect, -3, -3);				theRgn = NewRgn ();		RectRgn (theRgn, &ttRect);		UnionRgn (newClip, theRgn, newClip);		DisposeRgn (theRgn);	}	theRgn = NewRgn ();	RectRgn (theRgn, &iRect);	if (!EmptyRgn (newClip))	{		XorRgn (theRgn, newClip, theRgn);	}	SetClip (theRgn);		CopyBits ( (BitMap *) (*(gMyOffG->portPixMap)),						&((GrafPtr)RavelWindow)->portBits, &rBounds, &iRect, srcCopy, nil);		SetClip (saveClip);	DisposeRgn (saveClip);	DisposeRgn (theRgn);	DisposeRgn (newClip);/*	if (chat_win[0].active)	{		ttRect = chat_win[0].viewRect;		InsetRect (&ttRect, -3, -3);		EraseRect (&ttRect);		InsetRect (&ttRect, 1, 1);		FrameRect (&ttRect);		CopyBits ( (BitMap *) (*(chat_win[0].g->portPixMap)),							&((GrafPtr)RavelWindow)->portBits, &chat_win[0].portRect, &chat_win[0].viewRect, srcCopy, nil);		}	if (chat_win[1].active)	{		ttRect = chat_win[1].viewRect;		InsetRect (&ttRect, -3, -3);		EraseRect (&ttRect);		InsetRect (&ttRect, 1, 1);		FrameRect (&ttRect);		CopyBits ( (BitMap *) (*(chat_win[1].g->portPixMap)),							&((GrafPtr)RavelWindow)->portBits, &chat_win[1].portRect, &chat_win[1].viewRect, srcCopy, nil);		}*/	if (mylog)		fclose ( mylog );	FlushVol ( NULL, 0 );}void putlog ( char status, char *loginfo, ... ){	DateTimeRec	dtr;	va_list		va;	char		tmp[1024], t[1024];	if (status == '~' && !paranoidal_log)		return;		va_start ( va, loginfo );	vsprintf ( tmp, loginfo, va );	va_end ( va );	GetTime (&dtr);	sprintf ( t, "%1c%1c%.2d/%.2d %.2d:%.2d:%.2d RVL%c %s",											status, (mylog) ? ' ' : '|',											dtr.day, dtr.month,											dtr.hour, dtr.minute,											dtr.second,											(multiline_flag) ? (char)(multiline_line + '0') : ' ',											tmp );	_putlog(status, t);}void putelog ( char status, char *loginfo, ... ){	va_list		va;	char		tmp[1024], t[1024];	DateTimeRec	dtr;	FILE		*mylog;			va_start ( va, loginfo );	vsprintf ( tmp, loginfo, va );	va_end ( va );	GetTime (&dtr);		mylog = fopen ( emsilog, "a" );	if (!mylog)	{		SysBeep (10);		ExitToShell ();	}	sprintf ( t, "%1c %.2d/%.2d %.2d:%.2d:%.2d RVL%c %s",											status, 											dtr.day, dtr.month,											dtr.hour, dtr.minute,											dtr.second,											(multiline_flag) ? (char)(multiline_line + '0') : ' ',											tmp );	fprintf ( mylog, "%s\n", t );		fclose ( mylog );	FlushVol ( NULL, 0 );}void updtlog (){	Rect		ttRect;	RgnHandle	saveClip, newClip, theRgn;			SetPort ( RavelWindow );	saveClip = NewRgn ();	GetClip (saveClip);	newClip = NewRgn ();/*	if (chat_win[0].active)	{		ttRect = chat_win[0].viewRect;		InsetRect (&ttRect, -3, -3);				theRgn = NewRgn ();		RectRgn (theRgn, &ttRect);		UnionRgn (newClip, theRgn, newClip);		DisposeRgn (theRgn);	}*/	if (chat_win[1].active)	{		ttRect = chat_win[1].viewRect;		InsetRect (&ttRect, -3, -3);				theRgn = NewRgn ();		RectRgn (theRgn, &ttRect);		UnionRgn (newClip, theRgn, newClip);		DisposeRgn (theRgn);	}		if (node_info_str[0])	{		ttRect = node_info.viewRect;		InsetRect (&ttRect, -3, -3);				theRgn = NewRgn ();		RectRgn (theRgn, &ttRect);		UnionRgn (newClip, theRgn, newClip);		DisposeRgn (theRgn);	}		theRgn = NewRgn ();	RectRgn (theRgn, &iRect);	if (!EmptyRgn (newClip))	{		XorRgn (theRgn, newClip, theRgn);	}	SetClip (theRgn);		CopyBits ( (BitMap *) (*(gMyOffG->portPixMap)),						&((GrafPtr)RavelWindow)->portBits, &rBounds, &iRect, srcCopy, nil);		SetClip (saveClip);	DisposeRgn (saveClip);	DisposeRgn (theRgn);	DisposeRgn (newClip);	if (chat_win[0].active)	{		RGBColor	color, white = {65535,65535,65535};		GetBackColor (&color);		RGBBackColor (&white);			ttRect = chat_win[0].viewRect;		InsetRect (&ttRect, -3, -3);		EraseRect (&ttRect);		InsetRect (&ttRect, 1, 1);//		FrameRect (&ttRect);		DrawEmbossedRect (&ttRect);		CopyBits ( (BitMap *) (*(chat_win[0].g->portPixMap)),							&((GrafPtr)RavelWindow)->portBits, &chat_win[0].portRect, &chat_win[0].viewRect, srcCopy, nil);			RGBBackColor (&color);	}	if (chat_win[1].active)	{		RGBColor	color, white = {65535,65535,65535};		GetBackColor (&color);		RGBBackColor (&white);		ttRect = chat_win[1].viewRect;		InsetRect (&ttRect, -3, -3);		EraseRect (&ttRect);		InsetRect (&ttRect, 1, 1);//		FrameRect (&ttRect);		DrawEmbossedRect (&ttRect);		CopyBits ( (BitMap *) (*(chat_win[1].g->portPixMap)),							&((GrafPtr)RavelWindow)->portBits, &chat_win[1].portRect, &chat_win[1].viewRect, srcCopy, nil);			RGBBackColor (&color);	}	if (node_info_str[0])	{		RGBColor	color, white = {65535,65535,65535};		GetBackColor (&color);		RGBBackColor (&white);		ttRect = node_info.viewRect;		InsetRect (&ttRect, -3, -3);				EraseRect (&ttRect);		InsetRect (&ttRect, 1, 1);//		FrameRect (&ttRect);		DrawEmbossedRect (&ttRect);		TextFace (bold);		InsetRect (&ttRect, 2, 2);		TETextBox (node_info_str, strlen (node_info_str), &ttRect, teCenter);		TextFace (0);		RGBBackColor (&color);	}}void closelog ( void ){}static	short	num_chars;void init_chat_windows (void){	Handle	iHandle;	short	iType, hh, ww;	Rect	iiRect, rrBounds;	RGBColor	white = {65535,65535,65535};		GetDialogItem ( RavelWindow, 10, &iType, &iHandle, &iiRect );	hh = (((iiRect.bottom-iiRect.top)/2 - 11) / 11) * 11;	ww = ((iiRect.right-iiRect.left-10) / 6) * 6;		SetRect (&rrBounds, 0, 0, ww+2, hh);	NewGWorld ( &chat_win[0].g, 1, &rrBounds, nil, nil, 0 );	NewGWorld ( &chat_win[1].g, 1, &rrBounds, nil, nil, 0 );	chat_win[0].portRect = rrBounds;	chat_win[1].portRect = rrBounds;	num_chars = (rrBounds.right-2) / 6;	chat_win[0].active = false;	chat_win[1].active = false;	chat_win[0].pos = 0;	chat_win[1].pos = 0;	OffsetRect (&rrBounds, iiRect.left+((iiRect.right-iiRect.left) - (rrBounds.right))/2, iiRect.top+3+3+3+11);	chat_win[1].viewRect = rrBounds;	GetDialogItem ( RavelWindow, 9, &iType, &iHandle, &iiRect );	chat_win[0].viewRect = rrBounds;	chat_win[0].viewRect.top = iiRect.top + 4;	chat_win[0].viewRect.bottom = chat_win[0].viewRect.top + (rrBounds.bottom-rrBounds.top);		GetFNum ("\p.m_Ravel_866", &iType);	GetGWorld ( &currPort, &currDev );	SetGWorld ( chat_win[0].g, nil );	SetPort ( (GrafPtr) chat_win[0].g );	TextFont ( iType );	TextSize ( 9 );	PenPat ( &qd.black );	ForeColor ( blackColor );	RGBBackColor (&white);	EraseRect ( &chat_win[0].portRect );	SetGWorld ( chat_win[1].g, nil );	SetPort ( (GrafPtr) chat_win[1].g );	TextFont ( iType );	TextSize ( 9 );	PenPat ( &qd.black );	ForeColor ( blackColor );	RGBBackColor (&white);	EraseRect ( &chat_win[1].portRect );	SetGWorld (currPort, currDev);	SetPort ( RavelWindow );}void create_chat_window (short win){	if (!chat_win[win-1].active)	{		RGBColor	white = {65535,65535,65535};			chat_win[win-1].active = true;		chat_win[win-1].pos = 0;		GetGWorld ( &currPort, &currDev );		SetGWorld ( chat_win[win-1].g, nil );		RGBBackColor (&white);		EraseRect ( &chat_win[win-1].portRect );		SetGWorld (currPort, currDev);		SetPort ( RavelWindow );		updtlog ();	}}void dispose_chat_window (short win){	Rect	ttRect;		if (chat_win[win-1].active)	{		chat_win[win-1].active = false;		if (win == 1)		{			ttRect = chat_win[0].viewRect;			InsetRect (&ttRect, -3, -3);			EraseRect (&ttRect);			InvalRect (&ttRect);		}		else			updtlog ();	}}static void win_scroll (short win){	Rect	ttRect;	GetGWorld ( &currPort, &currDev );	SetGWorld ( chat_win[win-1].g, nil );	SetPort ( (GrafPtr) chat_win[win-1].g );	ScrollRect ( &chat_win[win-1].portRect, 0, -11, NULL );		ttRect = chat_win[win-1].portRect;	ttRect.top = ttRect.bottom - 11;	EraseRect ( &ttRect );	SetGWorld (currPort, currDev);	SetPort ( RavelWindow );}static void hideshow_cursor (short win, Boolean show, Boolean drawed){	Rect	ttRect;	GetGWorld ( &currPort, &currDev );	SetGWorld ( chat_win[win-1].g, nil );	SetPort ( (GrafPtr) chat_win[win-1].g );	ttRect = chat_win[win-1].portRect;	ttRect.top = ttRect.bottom - 11;	ttRect.left = chat_win[win-1].portRect.left+(chat_win[win-1].pos*6)+1;	ttRect.right = ttRect.left + 6;	EraseRect ( &ttRect );		if (show)	{		MoveTo ( chat_win[win-1].portRect.left+(chat_win[win-1].pos*6)+1, chat_win[win-1].portRect.bottom-2);		DrawChar (0xDC);	}		SetGWorld (currPort, currDev);	SetPort ( RavelWindow );		if (drawed)		CopyBits ( (BitMap *) (*(chat_win[win-1].g->portPixMap)),							&((GrafPtr)RavelWindow)->portBits, &chat_win[win-1].portRect, &chat_win[win-1].viewRect, srcCopy, nil);	}void win_putc (short win, short c){	Rect		ttRect;	RGBColor	color, white = {65535,65535,65535};	GetBackColor (&color);	RGBBackColor (&white);	create_chat_window (win);	hideshow_cursor (win, false, false);	if (c == 10)	{		win_scroll (win);		chat_win[win-1].pos = 0;		hideshow_cursor (win, true, false);		CopyBits ( (BitMap *) (*(chat_win[win-1].g->portPixMap)),							&((GrafPtr)RavelWindow)->portBits, &chat_win[win-1].portRect, &chat_win[win-1].viewRect, srcCopy, nil);		}	else		if (c >= ' ' && c != 0x7F)		{			if (chat_win[win-1].pos+1 > num_chars)			{				win_scroll (win);				chat_win[win-1].pos = 0;			}						GetGWorld ( &currPort, &currDev );			SetGWorld ( chat_win[win-1].g, nil );			SetPort ( (GrafPtr) chat_win[win-1].g );			MoveTo ( chat_win[win-1].portRect.left+(chat_win[win-1].pos*6)+1, chat_win[win-1].portRect.bottom-2);			DrawChar (c);			SetGWorld (currPort, currDev);			SetPort ( RavelWindow );						chat_win[win-1].pos++;			hideshow_cursor (win, true, false);			CopyBits ( (BitMap *) (*(chat_win[win-1].g->portPixMap)),								&((GrafPtr)RavelWindow)->portBits, &chat_win[win-1].portRect, &chat_win[win-1].viewRect, srcCopy, nil);			}		else			if (c == 8)			{				if (chat_win[win-1].pos)				{					chat_win[win-1].pos--;										GetGWorld ( &currPort, &currDev );					SetGWorld ( chat_win[win-1].g, nil );					SetPort ( (GrafPtr) chat_win[win-1].g );					ttRect = chat_win[win-1].portRect;					ttRect.top = ttRect.bottom - 11;					ttRect.left = chat_win[win-1].portRect.left+(chat_win[win-1].pos*6)+1;					EraseRect ( &ttRect );					SetGWorld (currPort, currDev);					SetPort ( RavelWindow );					hideshow_cursor (win, true, false);					CopyBits ( (BitMap *) (*(chat_win[win-1].g->portPixMap)),										&((GrafPtr)RavelWindow)->portBits, &chat_win[win-1].portRect, &chat_win[win-1].viewRect, srcCopy, nil);					}			}	RGBBackColor (&color);}void win_puts (short win, unsigned char *s){	unsigned char	buff[512], *p, *q;	RGBColor	color, white = {65535,65535,65535};	short		tobe, m;			while (*s && *s == 8)	{		win_putc (win, *s);		s++;	}	if (!*s)		return;	create_chat_window (win);	hideshow_cursor (win, false, false);		p = s;	q = buff;		while (*p && (((long)(q-buff)) < 500))	{		if (*p == 10)		{			*q = 0;						if (buff[0])			{				tobe = num_chars - chat_win[win-1].pos;								if (tobe <= strlen ((char *) buff))				{					GetGWorld ( &currPort, &currDev );					SetGWorld ( chat_win[win-1].g, nil );					SetPort ( (GrafPtr) chat_win[win-1].g );					MoveTo ( chat_win[win-1].portRect.left+(chat_win[win-1].pos*6)+1, chat_win[win-1].portRect.bottom-2);					DrawText (buff, 0, tobe);					SetGWorld (currPort, currDev);					SetPort ( RavelWindow );					win_scroll (win);										m = tobe;										while (num_chars < strlen ((char *) &buff[m]))					{						GetGWorld ( &currPort, &currDev );						SetGWorld ( chat_win[win-1].g, nil );						SetPort ( (GrafPtr) chat_win[win-1].g );						MoveTo ( chat_win[win-1].portRect.left+1, chat_win[win-1].portRect.bottom-2);						DrawText (buff, m, num_chars);						SetGWorld (currPort, currDev);						SetPort ( RavelWindow );						win_scroll (win);												m += num_chars;					}										if (strlen ((char *) &buff[m]))					{						GetGWorld ( &currPort, &currDev );						SetGWorld ( chat_win[win-1].g, nil );						SetPort ( (GrafPtr) chat_win[win-1].g );						MoveTo ( chat_win[win-1].portRect.left+1, chat_win[win-1].portRect.bottom-2);						DrawText (buff, m, strlen ((char *) &buff[m]));						SetGWorld (currPort, currDev);						SetPort ( RavelWindow );						win_scroll (win);					}					chat_win[win-1].pos = 0;				}				else				{					GetGWorld ( &currPort, &currDev );					SetGWorld ( chat_win[win-1].g, nil );					SetPort ( (GrafPtr) chat_win[win-1].g );					MoveTo ( chat_win[win-1].portRect.left+(chat_win[win-1].pos*6)+1, chat_win[win-1].portRect.bottom-2);					DrawText (buff, 0, strlen ((char *) buff));					SetGWorld (currPort, currDev);					SetPort ( RavelWindow );					win_scroll (win);					chat_win[win-1].pos = 0;				}			}			else			{				win_scroll (win);				chat_win[win-1].pos = 0;			}			q = buff;		}		else			if (*p >= ' ' && *p != 0x7F)			{				*q++ = *p;			}			else				if (*p == 8)				{					if (q > buff)						q--;				}				else					if (*p == 7)						SysBeep (10);			p++;	}		*q = 0;	if (buff[0])	{		tobe = num_chars - chat_win[win-1].pos;				if (tobe <= strlen ((char *) buff))		{			GetGWorld ( &currPort, &currDev );			SetGWorld ( chat_win[win-1].g, nil );			SetPort ( (GrafPtr) chat_win[win-1].g );			MoveTo ( chat_win[win-1].portRect.left+(chat_win[win-1].pos*6)+1, chat_win[win-1].portRect.bottom-2);			DrawText (buff, 0, tobe);			SetGWorld (currPort, currDev);			SetPort ( RavelWindow );			win_scroll (win);						m = tobe;						while (num_chars < strlen ((char *) &buff[m]))			{				GetGWorld ( &currPort, &currDev );				SetGWorld ( chat_win[win-1].g, nil );				SetPort ( (GrafPtr) chat_win[win-1].g );				MoveTo ( chat_win[win-1].portRect.left+1, chat_win[win-1].portRect.bottom-2);				DrawText (buff, m, num_chars);				SetGWorld (currPort, currDev);				SetPort ( RavelWindow );				win_scroll (win);								m += num_chars;			}						if (strlen ((char *) &buff[m]))			{				GetGWorld ( &currPort, &currDev );				SetGWorld ( chat_win[win-1].g, nil );				SetPort ( (GrafPtr) chat_win[win-1].g );				MoveTo ( chat_win[win-1].portRect.left+1, chat_win[win-1].portRect.bottom-2);				DrawText (buff, m, strlen ((char *) &buff[m]));				SetGWorld (currPort, currDev);				SetPort ( RavelWindow );				chat_win[win-1].pos = strlen ((char *) &buff[m]);			}			else				chat_win[win-1].pos = 0;		}		else		{			GetGWorld ( &currPort, &currDev );			SetGWorld ( chat_win[win-1].g, nil );			SetPort ( (GrafPtr) chat_win[win-1].g );			MoveTo ( chat_win[win-1].portRect.left+(chat_win[win-1].pos*6)+1, chat_win[win-1].portRect.bottom-2);			DrawText (buff, 0, strlen ((char *) buff));			SetGWorld (currPort, currDev);			SetPort ( RavelWindow );			chat_win[win-1].pos += strlen ((char *) buff);		}	}	hideshow_cursor (win, true, false);	GetBackColor (&color);	RGBBackColor (&white);	CopyBits ( (BitMap *) (*(chat_win[win-1].g->portPixMap)),						&((GrafPtr)RavelWindow)->portBits, &chat_win[win-1].portRect, &chat_win[win-1].viewRect, srcCopy, nil);		RGBBackColor (&color);}void put_nodeinfo (StringPtr info){	if (info[0])	{		memcpy (node_info_str, &info[1], info[0]);		node_info_str[info[0]] = 0;	}	else		node_info_str[0] = 0;	updtlog ();}