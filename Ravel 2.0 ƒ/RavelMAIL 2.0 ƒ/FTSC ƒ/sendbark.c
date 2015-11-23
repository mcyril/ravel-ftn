#include <ctype.h>#include <stdio.h>#include <string.h>#include "PascalStr.h"#include "Ravel_FTN.h"#include "Ravel_Prefs.h"#include "Pathes.h"#include "ftsc.h"//#include "pkthdrs.h"#include "definitions.h"#include "ascii.h"#include "compatible.h"#include "stringutl.h"#include "Scheduler.h"#include "Unattended.h"#include "Attacher.h"#include "Comm.h"#include "Timing.h"#include "xmodem.h"#include "log.h"#include "freq.h"#include "myEnv.h"#include "zfiles.h"#include "state.h"#include "pmain.h"#include "Modem.h"#include "aglcrc.h"#include "log.h"extern	ADDR	called_addr;extern	in_outboundPtr	cur_over;				// current ptrshort Bark_Request (char *where, char *filename, char *pw, char *updtime);void SEA_sendreq (){//	char	fname[256];	char	reqf[256];	char	*reqtime = " 0";	char	*p, *name, *pw;	char	*updtime;	FILE	*fp;//	char	*HoldName;	Str255	flo;	FSSpec	spec;	short	dodo = SUCCESS;	short	t;	long	cnt;//	HoldName = HoldAreaNameMunge(&called_addr);//	sprintf (fname, "%s%s.req", HoldName, Hex_Addr_Str (&called_addr));	LookForOutbound (&called_addr);	PathForOutbound (&called_addr, flo);	pStrConc (flo, "\p.REQ", flo);//��	Create TEMP file for both types of requests	if (cur_over && cur_over->requests)				// virtual requests	{		Create ( flo, 0, 'RvlM', 'TEMP' );		if ( !FSOpen ( flo, 0, &t ) )		{			SetFPos ( t, fsFromLEOF, 0L );	//��	Write "virtual requests" for first			cnt = GetHandleSize ( cur_over->requests );			HLock (cur_over->requests);			FSWrite ( t, &cnt, *cur_over->requests );			HUnlock (cur_over->requests);			FSClose ( t );		}	}	/* If we have file requests, then do them */	if (FSMakeFSSpec (0, 0, flo, &spec) != noErr)	{//		status_line (msgtxt[M_NO_OUT_REQUESTS]);		putlog (lgNOPE, "No outgoing file request(s).");	}	else	{//		status_line (msgtxt[M_OUT_REQUESTS]);		putlog (lgNOPE, "Processing outgoing file request(s).");		flo[flo[0]+1] = 0;				/* Open the .REQ file */		if ((fp = fopen ((char *) &flo[1], "r")) == NULL)		{			Bark_Request ((char *) &inboundPath[1], NULL, NULL, NULL);			return;		}		/* As long as we do not have EOF, read the request */		while ((fgets (reqf, 79, fp) != NULL) && (CARRIER && dodo == SUCCESS))		{			/* Properly format the request */			/* First get rid of the trailing junk */			p = reqf + strlen (reqf) - 1;						while ((p >= reqf) && (isspace (*p)))				*p-- = '\0';			/* Now get rid of the beginning junk */			p = reqf;			while ((*p) && (isspace (*p)))				p++;			/* This is where the name starts */			name = p;			/* If the first char is ; then ignore the line */			if (*name == ';')				continue;			/* Now get to where the name ends */			while ((*p) && (!isspace (*p)))				p++;			updtime = reqtime;             /* Default to request        */			pw = p;                        /* This is or will be a null */				req_scan:					if (*p)			{				*p++ = '\0';				while ((*p) && (*p != '!') && (*p != '-') && (*p != '+'))					p++;				/* Check for a password */				if (*p == '!')				{					*p = ' ';					pw = p++;					/* Now get to where the password ends */					while ((*p) && (!isspace (*p)))						p++;					goto req_scan;				}				/* Try for an update request */				if (*p == '+')				{					*p = ' ';					updtime = p++;					/* Now get to where the update time ends */					while ((*p) && (!isspace (*p)))						p++;					*p = '\0';					/* Request time is last thing we care about on line, so					we just drop out of the loop after finding it.					*/				}				/* Note: since SEAdog doesn't do "backdate" requests, all we				have to do if we see a '-' is to do a full request. Hence				we only process a '+' here.				*/			}			if ((dodo = Bark_Request ((char *) &inboundPath[1], name, pw, updtime)) != SUCCESS)				continue;		}		(void) fclose (fp);		FSDelete (flo, 0);//		status_line (msgtxt[M_END_OUT_REQUESTS]);		putlog (lgNOPE, "Processing outgoing file request(s) complete.");	}	/* Finish the file requests off */	Bark_Request ((char *) &inboundPath[1], NULL, NULL, NULL);}short  SBInit (BARKARGSP, short);short  SBEnd (BARKARGSP, short);short  SBSendBark (BARKARGSP);short  SBAskFile (BARKARGSP);short  SBRcvFile (BARKARGSP);short  SBNxtFile (BARKARGSP);void Build_Bark_Packet (BARKARGSP args);STATES Bark_Sender[] = {   { "SBInit", (ProcPtr) SBInit },   { "SBEnd", (ProcPtr) SBEnd },   { "SB0", (ProcPtr) SBSendBark },   { "SB1", (ProcPtr) SBAskFile },   { "SB2", (ProcPtr) SBRcvFile },   { "SB3", (ProcPtr) SBNxtFile },};void Build_Bark_Packet (BARKARGSP args){   char *p, *q;   unsigned short crc;   p = args->barkpacket;   *p++ = ACK;   crc = 0;   q = args->filename;   while (*q)      {      *p++ = *q;      crc = xcrc (crc, (unsigned char) *q);      ++q;      }   q = args->barktime;   while (*q)      {      *p++ = *q;      crc = xcrc (crc, (unsigned char) *q);      ++q;      }   q = args->barkpw;   while (*q)      {      *p++ = *q;      crc = xcrc (crc, (unsigned char) *q);      ++q;      }   *p++ = ETX;   *p++ = crc;   *p++ = crc >> 8;   args->barklen = (size_t) (p - args->barkpacket);}short  SBInit (BARKARGSP args, short start_state){#pragma unused (args)// XON_DISABLE ();   return (start_state);   /* args; */}short  SBEnd (BARKARGSP args, short cur_state){#pragma unused (args)   return (cur_state);   /* args; */}short  SBSendBark (BARKARGSP args){   if ((args->filename != NULL) && (args->filename[0] != '\0'))      {//    status_line ("%s '%s' %s%s", msgtxt[M_MAKING_FREQ], args->filename, (*(args->barkpw)) ? "with password" : "", args->barkpw);		putlog (lgNOPE, "Making request of '%s' %s%s", args->filename, (*(args->barkpw)) ? "with password" : "", args->barkpw);      args->tries = 0;      Build_Bark_Packet (args);      return (SB1);      }   else      {      SENDBYTE (ETB, NULL);      /* Delay one second */      big_pause (1);      return (SUCCESS);      }}short  SBAskFile (BARKARGSP args){   SENDCHARS ((unsigned char *) args->barkpacket, args->barklen, 1, NULL);   return (SB2);}short  SBRcvFile (BARKARGSP args){   short c;   short ret;   ret = SB2;   while (CARRIER && (ret == SB2))      {      c = TIMED_READ (10, NULL);      if (c == ACK)         {         Batch_Receive (args->inbound);         ret = SB3;         break;         }      if (args->tries > 5)         {/* Report transfer failed */         SENDBYTE (ETB, NULL);         ret = SENDBLOCK_ERR;         break;         }      CLEAR_INBOUND ();      ++(args->tries);      ret = SB1;      }   if (!CARRIER)      return (CARRIER_ERR);   else      return (ret);}short  SBNxtFile (BARKARGSP args){ #pragma unused (args)  short c;   long SB3Timer;   SB3Timer = timerset (4500);   while (CARRIER && !timeup (SB3Timer))      {      if ((c = TIMED_READ (5, NULL)) == 0xffff)         {         SENDBYTE (SUB, NULL);         continue;         }      if (c == ENQ)         return (SUCCESS);      }   if (CARRIER)      return (CARRIER_ERR);   else      return (TIME_ERR);   /* args; */}short Bark_Request (char *where, char *filename, char *pw, char *updtime){   BARKARGS bark;   bark.inbound = where;   bark.filename = filename;   bark.barkpw = pw;   bark.barktime = updtime;   return (state_machine (Bark_Sender, &bark, SB0));}