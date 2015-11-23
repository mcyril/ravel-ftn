#include <stdio.h>#include <string.h>#include <Folders.h>#include "ravel_msg_base.h"#include "ravel_tmp_base.h"#include "Ravel_Prefs.h"#include "PascalStr.h"#include "myEnv.h"#include "log.h"#include "Toss.h"#include "Utils.h"#include "pktparse.h"#include "stringutl.h"#include "AreaUtils.h"#include "NetMailRoute.h"#include "Attaches.h"#include "Exports.h"#include "ZipIt.h"#include "Plug-Ins.h"#include "statistic.h"#define	slProducts		5#include "Pathes.h"extern	homeHndl		homesystem;			//	�	Home system structextern	mailPrefHndl	mailHndl;			//	�	Netmail structextern	short			AreasNumber;		//	�	Areas structs listextern	areaPrefHndl	*areasHndls;extern	short			GroupsNumber;		//	�	AreaGroups structs listextern	groupPrefHndl	*groupsHndls;extern	short			NodesNumber;		//	�	Linked Nodes structs listextern	nodePrefHndl	*nodesHndls;extern	short			wdWorkRefNum;		//	�	WD for bundles spooling�extern	Boolean			StuffItExist;extern	Boolean			ZipItExist;extern	short	type2plus;static	char	*ValidExt[7] = { "mo", "tu", "we", "th", "fr", "sa", "su" };		char 	*arcs[31] = {	"ZIP", "ARC", "LZH",								"ZOO", "ARJ", "bad",								"RAR", "HA",  "bad",								"bad", "bad", "bad",								"bad", "bad", "bad",								"bad", "bad", "bad",								"bad", "bad", "bad",								"bad", "bad", "bad",								"bad", "bad", "bad",								"bad", "bad", "bad", "SIT" };								//static	char 	*pkttypes[3] = { "FTS-0001", "2.0", "2+" };void	DoSlice (void);void	InitProgress (float howmuch);void	DrawProgress (long i);void	putProgressName (Str255 name);void ResolveMessage ( pktmsg *m, addr *from, Boolean toss )			//	m				-	message struct			//	from			-	from packet address			//	toss			-	TRUE if tossing, else scanning{//	addr		tempaddr;	short		aNum, kk;	char		temp1[64], temp2[64];	pktmsg		*m2nd;	if ( toss )				// � COPY TO BASE, BUILD OUTBOUND FROM INBOUND	{		if (!m->area[0])	// � NetMail message arrived		{			if ( IsItMyAddr ( &m->to ) )		// � If my - place it (netmail) in base!			{				putlog ( lgNOPE, "NetMail from %s (%s) to me.", m->fromname,							printaddr ( &m->from, temp1 ));				Stat.NetMailMesages++;								putProgressName ("\pNetMail");				if ( !CallPlugIns (plugTossMsgMail, m, 0) )				{					m2nd = (pktmsg *) NewPtrClear (sizeof (pktmsg));					parse_kludges (PMODE_FORBASE, m, &m2nd, NULL, NULL, NULL);					//	�	Store message as Received						m2nd->flags |= MSGREAD;						tmpbase_add ( m2nd );					FreePktMsg ( m2nd );				}			}			else								// � In transit! Route It!			{				Stat.NetMailDirected++;					if ( !CallPlugIns (plugTossMsgMailTrs, m, 0) )					RouteMessage ( m, true );		// � Route transit message...			}		}		else				// � EchoMail message arrived		{			aNum = LookForAreaNumber ( m->area );						Stat.EchoMesages++;						if ( aNum == -1 )	// � Area absent			{		//	�	Check autocreate				putlog ( lgALRT, "Area %s not exist.", m->area );				for (kk = 0; kk < NodesNumber; kk++)					if ( cmp2addrs ( &(*nodesHndls[kk])->Addr, from ) )						break;				if (kk == NodesNumber || !((*nodesHndls[kk])->nodeflags & NODE_ALLOWAUTOCREATE) || !(*nodesHndls[kk])->GroupsNumber)				{		//	�	Can't autocreate - no such link or existent link has disabled autocreate option							putlog ( lgALRT, "Post it to BADMAIL (%s is unknown link or has disabled autocreate or group not present)", printaddr (from, temp1) );					add_to_other (m, "BADMAIL", from, "Unknown link or has disabled autocreate or group not present.");					return;				}				else				{					areaPrefHndl	*areasHndlsNew;					short			qq;					Boolean			was;					short			prefResNum = OpenResFile ( prefFile );					short			oldResNum = CurResFile ();														areasHndlsNew = (areaPrefHndl *) NewPtr ( (AreasNumber+1) * sizeof (Handle) );										for (qq = 0; qq < AreasNumber; qq++)						areasHndlsNew[qq] = areasHndls[qq];										DisposePtr ( (Ptr) areasHndls );					areasHndls = areasHndlsNew;						//	clear handle for diodes fixing (for first!)								areasHndls[AreasNumber] = (areaPrefHndl) NewHandleClear (sizeof (areaPrefType) +							(*groupsHndls[(*nodesHndls[kk])->group[0]])->numExports * sizeof (ExpItem));			//		MoveHHi ((Handle) areasHndls[AreasNumber]);			//		HLock ((Handle) areasHndls[AreasNumber]);									(*areasHndls[AreasNumber])->areaflags = (*groupsHndls[(*nodesHndls[kk])->group[0]])->areaflags;					(*areasHndls[AreasNumber])->group = (*nodesHndls[kk])->group[0];					(*areasHndls[AreasNumber])->useAKA = (*groupsHndls[(*nodesHndls[kk])->group[0]])->useAKA;					(*areasHndls[AreasNumber])->purger = (*groupsHndls[(*nodesHndls[kk])->group[0]])->purger;					(*areasHndls[AreasNumber])->numExports = (*groupsHndls[(*nodesHndls[kk])->group[0]])->numExports;									was = false;					for (qq = 0; qq < (*areasHndls[AreasNumber])->numExports; qq++)					{						(*areasHndls[AreasNumber])->Export[qq] = (*groupsHndls[(*nodesHndls[kk])->group[0]])->Export[qq];						if ( kk == (*areasHndls[AreasNumber])->Export[qq].Export )							was = true;					}										if (!was)					{						SetHandleSize ( (Handle) areasHndls[AreasNumber], sizeof (areaPrefType) +									((*groupsHndls[(*nodesHndls[kk])->group[0]])->numExports+1) * sizeof (ExpItem) );						(*areasHndls[AreasNumber])->Export[qq].Export = kk;						(*areasHndls[AreasNumber])->Export[qq].Diodes = 0;					}										strcpy ( (char *) &(*areasHndls[AreasNumber])->areaName[1], m->area );					(*areasHndls[AreasNumber])->areaName[0] = strlen ( m->area );					AreasNumber++;					aNum = AreasNumber;										UseResFile (prefResNum);					AddResource ( (Handle) areasHndls[AreasNumber-1], areasRes, AreasNumber, "\pAutocreated�" );					WriteResource ( (Handle) areasHndls[AreasNumber-1] );					UpdateResFile (prefResNum);										DetachResource ( (Handle) areasHndls[AreasNumber-1] );					MoveHHi ((Handle) areasHndls[AreasNumber-1]);					HLock ((Handle) areasHndls[AreasNumber-1]);					UseResFile (oldResNum);					CloseResFile (prefResNum);					pluginscontrol->Preferences.AreasNumber = AreasNumber;					pluginscontrol->Preferences.areasHndls = areasHndls;					putlog ( lgATTN, "Area %s has been autocreated from %s", m->area, printaddr (from, temp1) );									CallPlugIns (plugMisc, m, secondAutocreated);				}			}//	�		Check back address			putProgressName ((*areasHndls[aNum-1])->areaName);			for (kk=0; kk<(*areasHndls[aNum-1])->numExports; kk++)				if ( cmp2addrs ( &(*nodesHndls[(*areasHndls[aNum-1])->Export[kk].Export])->Addr, from ) )					break;						if (kk == (*areasHndls[aNum-1])->numExports)			{				putlog ( lgALRT, "Area %s not exist in export list of this link. Post it to BADMAIL", m->area );				add_to_other (m, "BADMAIL", from, "Area not exist in export list of this link.");				return;			}			// � Area present						if ((*areasHndls[aNum-1])->Export[kk].Diodes & LINK_DIODE)			{				putlog ( lgALRT, "Area %s is read only for this link. Post it to BADMAIL", m->area );				add_to_other (m, "BADMAIL", from, "Area is read only for this link.");				return;			}			if (!CallPlugIns (plugTossMsgEchoExp, m, 0))				ExportEchoes ( m, from );						if (!CallPlugIns (plugTossMsgEcho, m, 0))			{				if ( !((*areasHndls[aNum-1])->areaflags & AREA_PASSTROUGH) )				{					m2nd = (pktmsg *) NewPtr ( sizeof (pktmsg) );					parse_kludges (PMODE_FORBASE, m, &m2nd, NULL, NULL, NULL);					//	�	Store message as Received							m2nd->flags |= MSGREAD;							tmpbase_add ( m2nd );					FreePktMsg ( m2nd );				}				else					Stat.PassThrough++;			}		}	}	else						// � BUILD OUTBOUND FROM BASE	{		if (!m->area[0])	// � NetMail message arrived		{			Stat.NetMailMesages++;			if ( IsItMyAddr ( &m->to ) )		// � If my - place it (netmail) in base!			{				putlog ( lgALRT, "NetMail to myself! Dropped..." );				return;			}			else								// � Out! Route It!			{				RouteMessage ( m, false );		// � Route my message...			}		}		else				// � EchoMail message outer		{			Stat.EchoMesages++;			ExportEchoes ( m, from );		}	}}void ProcessPacket ( StringPtr fname, short fvref ){	short			fp;			// operating file	pktheader		*p;	pktmsg			*m;	char			tmp[64], temp1[64], temp2[64];	long			size;	unsigned short	t;	long			filePos;	fname[fname[0]+1] = 0;	if ( FSOpen ( fname, fvref, &fp ) )	{		putlog ( lgALRT, "Inbound file %s not found.", &fname[1] );		return;	}		Stat.Packets++;		GetEOF ( fp, &size );	InitProgress (size);		p = GetPktHeader ( fp );	if ( !p )	{		putlog ( lgALRT, "%s Bad packet or packet type. Ignoring.", &fname[1] );		goto bad_pkt;	}		t = p->productCode;	if ((t & 0x00FF) == 0x00FF)		GetIndString ( (StringPtr) tmp, slProducts+1, (t >> 8)+1 );	else		GetIndString ( (StringPtr) tmp, slProducts, t+1 );	if (!tmp[0])	{		GetIndString ( (StringPtr) tmp, slProducts, 1 );	}		tmp[tmp[0]+1] = 0;	//	putlog ( lgNOPE, "" );	putlog ( lgATTN, "%s from %s to %s (%s %d.%.2d [#%.4X], %s)", &fname[1],								printaddr ( &p->from, temp1 ),								printaddr ( &p->to, temp2 ),								&tmp[1], p->productRev >> 8, p->productRev & 0xFF, 								t,								(p->pkttype == 0x0000) ? "FTS-0001" : (									(p->pkttype == 0x0200) ? "Type 2" : (										(p->pkttype == 0x0220) ? "Type 2.2" : (											(p->pkttype == 0x0201) ? "QMail" : (												(p->pkttype == 0x02FF) ? "Type 2+" : "BAD")))));		while (1)	{		DoSlice ();				GetFPos (fp, &filePos);		DrawProgress (filePos);				m = GetPktMsg ( fp, p );		if( !m )		{			FSClose (fp);			goto bad_pkt;		}		else			if ( ((long) m) == -1 )				break;				ResolveMessage ( m, &(p->from), TRUE );		// TRUE mean - Tossing		FreePktMsg (m);	}	GetFPos (fp, &filePos);	DrawProgress (filePos);	FreePktHeader (p);	FSClose ( fp );		InitProgress (1.0);	return;	bad_pkt:	sprintf (&tmp[1], "%.8lX.BAD", LMGetTicks ());	tmp[0] = strlen (&tmp[1]);		if (Rename (fname, fvref, (StringPtr)tmp) == noErr)	{		putlog (lgALRT, "Renamed %#s to %#s", fname, tmp);	}		InitProgress (1.0);	return;}/*****************************************************************																**	This function must decompress "fname" file (any	archiver)	**																*****************************************************************/Boolean ProcessArchive ( StringPtr fname, short fwdRefNum ){	FSSpec		fromSpec, toSpec, temp;	short		iErr, wdRefNum, vRefNum, EngResFile, oldRes, arcmail, mmm;	long		module = 0;	long		dirID;	char		buf[8];	Str255		tempStr;			fname[fname[0]+1] = 0;	iErr = FSOpen ( fname, fwdRefNum, &arcmail );	if (iErr)		return;		dirID = 8;	FSRead ( arcmail, &dirID, buf );	FSClose ( arcmail );		if (strncmp(buf,"PK",2) == 0)	{		module = arcZIP;						//	unzip;		mmm = 0;	}	else if (*buf == 0x1a)	{		module = arcARC;						//	unarc;		mmm = 1;	}	else if (strncmp(buf+2,"-l",2) == 0)	{		module = arcLZH;						//	unlzh;		mmm = 2;	}	else if (strncmp(buf,"ZOO",3) == 0)	{		module = arcZOO;						//	unzoo;		mmm = 3;	}	else if (strncmp(buf,"`\352",2) == 0)	{		module = arcARJ;						//	unarj;		mmm = 4;	}	else if (strncmp(buf,"HA",2) == 0)	{		module = arcHA;							//	ha;		mmm = 7;	}	else if (strncmp(buf,"Rar!",4) == 0)	{		module = arcRAR;						//	RAR;		mmm = 6;	}	else if (strncmp(buf,"SIT!",4) == 0)	{		module = arcSIT;						//	stuff it;		mmm = 30;	}	else if (strncmp(buf,"StuffIt (c)1997-",16))	{		module = arcSIT;						//	stuff it;		mmm = 30;	}	else		module = -1L;	iErr = FSMakeFSSpec ( fwdRefNum, 0, fname, &fromSpec );	if (iErr)		return false;			if (module != -1)	{		putlog ( lgATTN, "Unpacking: %s (%s)", &fname[1], arcs[mmm] );				iErr = FSMakeFSSpec ( fwdRefNum, 0, fname, &fromSpec );		if (iErr)			return;				pStrCopy ( tempPath, tempStr );		tempStr[0]--;				iErr = FSMakeFSSpec ( 0, 0, tempStr, &toSpec );		if (iErr)		{			putlog ( lgATTN, "Temp folder not found. Move it to trash." );			goto totrash;		}		if (CallArchiverPlugIns (false, false, module, &fromSpec, &toSpec) == plugRetContinue)		{			FSDelete (fname, fwdRefNum);		}		else		{			putlog ( lgATTN, "(%s) is absent. Move it to trash.", arcs[mmm] );			goto totrash;		}	}	else	{		putlog ( lgATTN, "%s using unknown format. Move it to trash.", &fname[1] );		totrash:			iErr = FindFolder ( kOnSystemDisk, kTrashFolderType, kDontCreateFolder, &vRefNum, &dirID );		if (iErr == noErr)		{			CMovePBRec	cmpb;			OSErr	rc;			cmpb.ioNamePtr = fromSpec.name;		// last : optional			cmpb.ioDirID = fromSpec.parID;		// not needed;  ioNamePtr			cmpb.ioVRefNum = vRefNum;			// has the volume and dir			cmpb.ioNewName = 0;					// not needed;  ioNewDirID given			cmpb.ioNewDirID = dirID;			// 'Hard' ID of root directory			rc = PBCatMoveSync (&cmpb);			if (rc)			{				putlog ( lgATTN, "Can't move to trash." );			}		}		else			putlog ( lgATTN, "Trash not found." );			return false;	}	return true;}/*******************************************************													  **	Searching dir for packets						  **	Process	it										  **													  *******************************************************/void ScanPackets (StringPtr dir){	typedef struct _que {			struct _que	*next;//		short		arcmail;		Str31		name;		unsigned long time;			} que, *pque;	short			mdir;						// working directory reference number�	CInfoPBRec		cipbr;						/* local pb */	HFileInfo		*fpb = (HFileInfo *)&cipbr;	/* to pointers */	short			rc, idx;	Str32			filename, q_name;//	Boolean			alldone;		int		a;	pque			first_que, current_que, oper_que, done_que, prev_que;	unsigned long	q_time, sizer;	Boolean			q_arcmail;			first_que = NULL;	current_que = NULL;	dir[dir[0]+1] = 0;	if ( ( mdir = myOpenWD ( dir ) ) == 0 )	{		putlog ( lgALRT, "Unable to open directory %s", &dir[1] );		return;	}	fpb->ioNamePtr = filename;	fpb->ioVRefNum = mdir;// � Killing loop...	for ( idx=1; TRUE; idx++)	{											/* indexing loop */		fpb->ioDirID = 0L;						/* must set on each loop */		fpb->ioFDirIndex = idx;		filename[0] = 0;				rc = PBGetCatInfoSync (&cipbr);		if (rc) break;							/* exit when no more entries */		if ( !(fpb->ioFlAttrib & 16) && filename[0] == 12 )		{										/* not folder */			filename[filename[0]+1] = 0;			if ( !strcasecmp ( (char *) &filename[filename[0]-3], ".PKT" ) )			{				if ( fpb->ioFlFndrInfo.fdType == 'ZMPT' )					continue;				if (first_que)				{					current_que->next = (pque) NewPtr (sizeof (que));					current_que = current_que->next;				}				else				{					first_que = current_que = (pque) NewPtr (sizeof (que));				}								current_que->next = NULL;//				current_que->arcmail = false;				pStrCopy (filename, current_que->name);				GetInfFile (mdir, filename, &current_que->time, &sizer);			}		}	}//	+++		done_que = NULL;	prev_que = first_que;	while (first_que && first_que->next != done_que && first_que != done_que)	{		oper_que = first_que;				while (oper_que->next != done_que)		{			if (oper_que->time > (oper_que->next)->time)			{				pStrCopy (oper_que->name, q_name);//				q_arcmail = oper_que->arcmail;				q_time = oper_que->time;								pStrCopy ((oper_que->next)->name, oper_que->name);//				oper_que->arcmail = (oper_que->next)->arcmail;				oper_que->time = (oper_que->next)->time;							pStrCopy (q_name, (oper_que->next)->name);//				(oper_que->next)->arcmail = q_arcmail;				(oper_que->next)->time = q_time;			}						prev_que = oper_que;			oper_que = oper_que->next;		}				done_que = prev_que;	}//	+++/*	current_que = first_que;	while (current_que && current_que->next)	{		oper_que = current_que;				while (oper_que && oper_que->next)		{			GetInfFile (mdir, oper_que->name, &first_t, &sizer);			GetInfFile (mdir, (oper_que->next)->name, &second_t, &sizer);					if (first_t > second_t)			{				pStrCopy (oper_que->name, q_name);				q_arcmail = oper_que->arcmail;								pStrCopy ((oper_que->next)->name, oper_que->name);				oper_que->arcmail = (oper_que->next)->arcmail;							pStrCopy (q_name, (oper_que->next)->name);				(oper_que->next)->arcmail = q_arcmail;			}						oper_que = oper_que->next;		}				current_que = current_que->next;	}*/	while (first_que)	{		ProcessPacket ( first_que->name, mdir );		FSDelete ( first_que->name, mdir );				current_que = first_que->next;		DisposePtr ((Ptr) first_que);		first_que = current_que;	}	myCloseWD ( mdir );}/*******************************************************													  **	Searching dir for arcmail &	packets				  **	(arcmail will be decompressed into temp	folder)	  **	Process	it										  **													  *******************************************************/void ScanBundles (StringPtr dir){	typedef struct _que {			struct _que	*next;		short		arcmail;		Str31		name;		unsigned long time;			} que, *pque;	short			mdir;						// working directory reference number�	CInfoPBRec		cipbr;						/* local pb */	HFileInfo		*fpb = (HFileInfo *)&cipbr;	/* to pointers */	short			rc, idx;	Str32			filename, q_name;//	Boolean			alldone;		int		a;	pque			first_que, current_que, oper_que, done_que, prev_que;	unsigned long	q_time, sizer;	Boolean			q_arcmail;			first_que = NULL;	current_que = NULL;	dir[dir[0]+1] = 0;	if ( ( mdir = myOpenWD ( dir ) ) == 0 )	{		putlog ( lgALRT, "Unable to open directory %s", &dir[1] );		return;	}	fpb->ioNamePtr = filename;	fpb->ioVRefNum = mdir;// � Killing loop...	for ( idx=1; TRUE; idx++)	{											/* indexing loop */		fpb->ioDirID = 0L;						/* must set on each loop */		fpb->ioFDirIndex = idx;		filename[0] = 0;				rc = PBGetCatInfoSync (&cipbr);		if (rc) break;							/* exit when no more entries */		if ( !(fpb->ioFlAttrib & 16) && filename[0] == 12 )		{										/* not folder */			filename[filename[0]+1] = 0;						for (a=0;a<7;a++) 				if ( !strncasecmp ( (char *) &filename[10], ValidExt[a], 2) )					break;			if(a!=7)			{				if ( fpb->ioFlFndrInfo.fdType == 'ZMPT' )					continue;							if (first_que)				{					current_que->next = (pque) NewPtr (sizeof (que));					current_que = current_que->next;				}				else				{					first_que = current_que = (pque) NewPtr (sizeof (que));				}								current_que->next = NULL;				current_que->arcmail = true;				pStrCopy (filename, current_que->name);				GetInfFile (mdir, filename, &current_que->time, &sizer);			}			else			{				if ( !strcasecmp ( (char *) &filename[filename[0]-3], ".PKT" ) )				{					if ( fpb->ioFlFndrInfo.fdType == 'ZMPT' )						continue;					if (first_que)					{						current_que->next = (pque) NewPtr (sizeof (que));						current_que = current_que->next;					}					else					{						first_que = current_que = (pque) NewPtr (sizeof (que));					}										current_que->next = NULL;					current_que->arcmail = false;					pStrCopy (filename, current_que->name);					GetInfFile (mdir, filename, &current_que->time, &sizer);				}			}		}	}	//	+++		done_que = NULL;	prev_que = first_que;	while (first_que && first_que->next != done_que && first_que != done_que)	{		oper_que = first_que;				while (oper_que->next != done_que)		{			if (oper_que->time > (oper_que->next)->time)			{				pStrCopy (oper_que->name, q_name);				q_arcmail = oper_que->arcmail;				q_time = oper_que->time;								pStrCopy ((oper_que->next)->name, oper_que->name);				oper_que->arcmail = (oper_que->next)->arcmail;				oper_que->time = (oper_que->next)->time;							pStrCopy (q_name, (oper_que->next)->name);				(oper_que->next)->arcmail = q_arcmail;				(oper_que->next)->time = q_time;			}						prev_que = oper_que;			oper_que = oper_que->next;		}				done_que = prev_que;	}//	+++/*	current_que = first_que;	while (current_que && current_que->next)	{		oper_que = current_que;				while (oper_que && oper_que->next)		{//			GetInfFile (mdir, oper_que->name, &first_t, &sizer);//			GetInfFile (mdir, (oper_que->next)->name, &second_t, &sizer);			if (oper_que->time > (oper_que->next)->time)			{				pStrCopy (oper_que->name, q_name);				q_arcmail = oper_que->arcmail;				q_time = oper_que->time;								pStrCopy ((oper_que->next)->name, oper_que->name);				oper_que->arcmail = (oper_que->next)->arcmail;				oper_que->time = (oper_que->next)->time;							pStrCopy (q_name, (oper_que->next)->name);				(oper_que->next)->arcmail = q_arcmail;				(oper_que->next)->time = q_time;			}						oper_que = oper_que->next;		}				current_que = current_que->next;	}*/	while (first_que)	{		if (first_que->arcmail)		{			Stat.Archives++;			ProcessArchive ( first_que->name, mdir );			ScanPackets ( tempPath );		}		else		{			ProcessPacket ( first_que->name, mdir );			FSDelete ( first_que->name, mdir );		}				current_que = first_que->next;		DisposePtr ((Ptr) first_que);		first_que = current_que;	}		myCloseWD ( mdir );}/****************************************************												   **	Process	Inbound	folder - look for bundles.	   **	Make netmail routing						   **	Make echo area tossing						   **	(in	other level	process	uplinks	& downlinks)   **												   ****************************************************/void Toss (void){//	�	Process with incoming bundles� (aka TOSS)//������������������������������������������������������������������������������	ScanBundles ( inboundPath );	// � Search for all incomings//������������������������������������������������������������������������������	Resolver (MOVE_NETMAIL |			  MOVE_ARCMAIL |			  MOVE_FLOS |			  MOVE_FREQ);				// � Resolve all//������������������������������������������������������������������������������}/****************************************************												   **	Process	Inbound	folder - look for pkts.		   **	Make netmail routing						   **	(in	other level	process	uplinks	& downlinks)   **												   ****************************************************/void NetPack (void){//	�	Process with incoming bundles� (aka TOSS)//������������������������������������������������������������������������������	ScanPackets ( inboundPath );	// � Search for all incomings pkts//������������������������������������������������������������������������������	Resolver (MOVE_NETMAIL);				// � Resolve netmail only//������������������������������������������������������������������������������}