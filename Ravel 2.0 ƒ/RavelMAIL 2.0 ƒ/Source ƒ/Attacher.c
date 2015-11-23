#include <stdio.h>#include <string.h>#include "compatible.h"#include "Ravel_FTN.h"#include "Ravel_Prefs.h"#include "PascalStr.h"#include "Pathes.h"#include "Scheduler.h"#include "Unattended.h"#include "Attacher.h"#include "log.h"#include "zmodem.h"#include "wazoo.h"#include "busy.h"#include "zfiles.h"#include "stringutl.h"extern	homeHndl		homesystem;				//	е	Home system structextern	short			remote_capabilities;extern	in_outboundPtr	cur_over;				// current ptrextern	short			current_link;extern	short			xHydraPhase;	//ееextern	in_outboundPtr	outbound;		// original ptr//	extern	short			NodesNumber;		//	е	Linked Nodes structs list//	extern	nodePrefHndl	*nodesHndls;extern	short			thy_request;			//	reote made file requestextern	short			we_request;				//	we made file request//extern	Boolean		ftsc_session;extern	Boolean			g_wasrefused;static	StringPtr	pollModes[3] = { "\p.CLO", "\p.DLO", "\p.HLO" };static	StringPtr	requestSuffix = "\p.REQ";//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее//е//е Match operatum address in outbound chain//е//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееin_outboundPtr LookForOutbound (ADDR *oper){	if (!(cur_over = outbound))		return NULL;	while (1)	{		if ( cur_over->calladdr.zone == oper->Zone &&			 cur_over->calladdr.net == oper->Net &&			 cur_over->calladdr.node == oper->Node &&			 cur_over->calladdr.point == oper->Point )			return cur_over;		if (cur_over->next)			cur_over = cur_over->next;		else			return (cur_over = NULL);	}}//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее//е//е Synth the path for current outbound (path is storing in globals)//е//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееBoolean PathForOutbound (ADDR *oper, StringPtr flo){	short			iErr;	FSSpec			specDst;	Str255			temp1, attFName;	Str255			tempZone, tempPoint;	//	е	Get zone-folder name	sprintf ( (char *) &temp1[1], "Zone_%.4X:", oper->Zone );	temp1[0] = strlen ( (char *) &temp1[1] );	pStrConc ( outboundPath, temp1, tempZone );	if ( iErr = FSMakeFSSpec ( 0, 0, tempZone, &specDst ) )	{//		putlog (lgATTN, "Nothing to send to this zone");		return false;									// Nothing to send to this zone	}	//	е	Destination node is point?	if ( oper->Point != 0 )	{	//	е	Finding point subfolder╔		sprintf ( (char *) &temp1[1], "%.4X%.4X.PTS:", oper->Net, oper->Node );		temp1[0] = strlen ( (char *) &temp1[1] );		pStrConc ( tempZone, temp1, tempPoint );		if ( iErr = FSMakeFSSpec ( 0, 0, tempPoint, &specDst ) )		{//	putlog (lgATTN, "Nothing to send to this point %s", (char *) &temp1[1]);			return false;								// е nothing to send to this point		}												// е specDst - FSSpec of appr. point ─.		//	е	Generate attachment filename for Point ─ (w/o .?LO terms)		sprintf ( (char *) &attFName[1], "%.8lX", (long) oper->Point );		attFName[0] = strlen ( (char *) &attFName[1] );	}	else	{	//	е	Generate attachment filename for Zonal ─ (w/o .?LO terms)		sprintf ( (char *) &attFName[1], "%.4X%.4X", oper->Net, oper->Node );		attFName[0] = strlen ( (char *) &attFName[1] );	}	pStrConc ( (oper->Point == 0) ? tempZone : tempPoint, attFName, flo );	flo[flo[0]+1] = 0;	return true;}void touch_arcmail_suffix (ADDR *adr, StringPtr filename){	Str255			flo;	char			suffix[32];	addr			adr1;	FILE			*ft;		if (ResolveExtension (filename) != 1)		return;	adr1.zone = adr->Zone;	adr1.net = adr->Net;	adr1.node = adr->Node;	adr1.point = adr->Point;	if (!get_flo_pathname (&adr1, workPath, flo))		return;	pStrConc (flo, "\p.$$$", flo);	flo[flo[0]+1] = 0;		ft = fopen ((char *) &flo[1], "r");	if (!ft)		return;	if (fgets (suffix, 16, ft) == NULL)	{		fclose (ft);		return;	}	fclose (ft);		if (strncasecmp (suffix, (char *) &filename[filename[0]-2], 3))		return;		if (suffix[2] == '9')		suffix[2] = 'A';	else		if (suffix[2] != 'Z')			suffix[2]++;		ft = fopen ((char *) &flo[1], "w");	fprintf ( ft, "%s", suffix );	fclose (ft);		putlog ('~', "ArcMail suffix touched: '%s'", suffix);}//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее//е//е WaZOO operatum//е//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееBoolean do_FLOfile (ADDR *adr, short (*EMSI_callback)(StringPtr) ){	short			i, kaka;	short			attFile;	FSSpec			spec;	Str255			temp1;	Str255			temp, temp2, temp3;	long			dummy;	Handle			att;	Boolean			welldone, wannadel, needkill, wasrefused;	char			*zzz, *signpos;	long			t;	long			cnt;	char			buff[128];	putlog ( '~', "Operate attaches to %d:%d/%d.%d",										adr->Zone, adr->Net, adr->Node, adr->Point );	LookForOutbound (adr);	welldone = true;	if (!PathForOutbound (adr, temp))		return true;	pStrConc ( temp, requestSuffix, temp2 );//	if (!ftsc_session && (remote_capabilities & WZ_FREQ))	//	remote_capabilities == 0 during ftsc	if (xHydraPhase == 0 || xHydraPhase == 1)	{		if (remote_capabilities & WZ_FREQ)		{			Str255		ttt;			short		t;			sprintf ((char *) &ttt[1], "%.4X%.4X.REQ", adr->Net, adr->Node);			ttt[0] = strlen ((char *) &ttt[1]);	//ее	Create TEMP file for both types of requests			Create ( ttt, 0, 'RvlM', 'TEMP' );			if ( !FSOpen ( ttt, 0, &t ) )			{				SetEOF ( t, 0L );				if (cur_over && cur_over->requests)				// virtual requests				{	//ее	Write "virtual requests" for first					cnt = GetHandleSize ( cur_over->requests );					HLock (cur_over->requests);					FSWrite ( t, &cnt, *cur_over->requests );					HUnlock (cur_over->requests);	//				we_request = true;				}				if (FSMakeFSSpec ( 0, 0, temp2, &spec ) == noErr)				{	//ее	Append "usual requests" for second					if (!FSOpen (temp2, 0, &kaka))					{						do {													cnt = 128L;							FSRead (kaka, &cnt, buff);							FSWrite (t, &cnt, buff);						} while (cnt);							//					we_request = true;												FSClose (kaka);					}				}								GetEOF (t, &dummy);								FSClose ( t );				if (dummy != 0)				{	//ее	Send TEMP file with both requests types					if ( (kaka = EMSI_callback ( ttt )) != OK )					{						if (kaka != SPEC_COND)							welldone = false;						else							g_wasrefused = true;						we_request = false;					}					else					{						FSDelete (temp2, 0);						we_request = true;					}				}								FSDelete ( ttt, 0 );		// Clear outbound file by file thats was sent			}			else				putlog ( lgALRT, "Requests failed" );		}	}		if (xHydraPhase == 0 || xHydraPhase == 2)	{		if (welldone && cur_over && cur_over->attaches)				// virtual attaches		{			Str255		ttt;			t = 0;			cnt = GetHandleSize ( cur_over->attaches );			HLock (cur_over->attaches);						zzz = *cur_over->attaches;			while ( t < cnt )			{				strcpy ( (char *) &ttt[1], zzz+1 );				needkill = (*zzz) == '-';				signpos = zzz;				ttt[0] = strlen ( (char *) &ttt[1] );				t += ttt[0]+2;				zzz += ttt[0]+2;								if (*signpos != '~' && FSMakeFSSpec ( 0, 0, ttt, &spec ) == 0 )				{					if ( (kaka = EMSI_callback ( ttt )) != OK )					{						if (kaka != SPEC_COND)						{							welldone = false;							break;						}						else							g_wasrefused = true;					}					else					{						*signpos = '~';												if (needkill)							FSDelete ( ttt, 0 );					}				}			}						HUnlock (cur_over->attaches);		}	//	е	process arcmail attaches		if (welldone)			for (i=0; i<3; i++)			{				wasrefused = false;							pStrConc ( temp, pollModes[i], temp2 );				temp2[temp2[0]+1] = 0;			//	ее		attFile = fopen ( (char *) &temp2[1], "r" );	//	ее		if (attFile == NULL)	//	ее			continue;						if (FSOpen ( temp2, 0, &attFile))					continue;								GetEOF (attFile, &cnt);				att = NewHandleClear (cnt);				if (!att)					DebugStr ("\pSomething wrong in Attacher.c (process arcmail attaches)");								HLock (att);				zzz = *att;								FSRead (attFile, &cnt, zzz);								for (t = 0; t < cnt; t++)					if (zzz[t] == 0x0D)						zzz[t] = 0;				t = 0;					//	ее		while ( fscanf ( attFile, "%[\x20-\x7e]\n", &temp1[1] ) != EOF )								while (t < cnt)				{					strcpy ( (char *) &temp1[1], zzz+1 );					wannadel = (*zzz) == '-';					signpos = zzz;					temp1[0] = strlen ( (char *) &temp1[1] );					t += temp1[0]+2;					zzz += temp1[0]+2;					pStrCopy ( temp1, temp3 );	// file attach with full pathname					temp3[temp3[0]+1] = 0;							if (*signpos != '~' && FSMakeFSSpec ( 0, 0, temp3, &spec ) == 0 )					{						touch_arcmail_suffix (adr, temp3);						if ( (kaka = EMSI_callback ( temp3 )) == OK )						{							*signpos = '~';														if (wannadel)								FSDelete ( temp3, 0 );		// Clear outbound file by file thats was sent						}						else						{							if (kaka == SPEC_COND)							{								wasrefused = true;							}							else							{								welldone = false;								break;							}						}					}				}				if (welldone)				{					FSClose (attFile);										if (!wasrefused)						FSDelete ( temp2, 0 );									g_wasrefused = wasrefused;				}				else				{					SetEOF (attFile,0);					zzz = *att;					for (t = 0; t < cnt; t++)						if (zzz[t] == 0)							zzz[t] = 0x0D;					FSWrite (attFile, &cnt, *att);					FSClose (attFile);					break;				}				DisposeHandle (att);			}	}		if (!welldone)		putlog ( lgATTN, "Sending fault..." );		return welldone;}