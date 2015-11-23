/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*//*е                                                                                  е*//*е  File:      PKT.h                                                                е*//*е                                                                                  е*//*е  Author:    "Wicked" Cyril Morzin                                                е*//*е  Subject:   Ravel package common data's structures.                              е*//*е  Purpose:   Supported by RavelECHO, RavelQUILL & RavelMAIL appls.                е*//*е                                                                                  е*//*е  Created:   before 15.07.1996 (internal structs was based on qEcho sources)      е*//*е  Revisions:                                                                      е*//*е      15.07.1996 - making revise all data structures by my own understanding.     е*//*е                                                                                  е*//*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*//*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*//***  FTS-1 (FSC-39 compliant) packet definition used by FrontDoor, TosScan,**  and FrontDoor APX among other products to create .PKT files.*/#define CW_2PLUS        0x0001                 /*Support for Type 2+ bundles*/#define CW_N2PLUS       0x0100                     /*Validation for CW_2PLUS*/#define PKTVERSION      2                    /*Current packet revision level*/    /* Packed message, none or more per packet */typedef struct    {    unsigned short int  Version,                        /*Packet version (2)*/	// + 00                        OrigNode,                         /*Originating node*/	// + 02                        DestNode,                         /*Destination node*/	// + 04                        OrigNet,                           /*Originating net*/	// + 06                        DestNet,                           /*Destination net*/	// + 08                        Attr,                                  /*FTS1 status*/	// + 0A                        Cost;                              /*Cost of message*/	// + 0C                        														//   0E    /*    **    The message header follows this but is of variable length ASCIIZ    **    strings in the order:  	  						AsciiDate,  						ToUser,  						FromUser,  						Subject,  						MsgText.      	*/    }    FTS1PKTMSG;/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*//***	Maximum field length in packet's message*/#define	MDate			20#define	MName			36#define	MSubject		72/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*//*char *flnames[18]={ "Pvt", "Crs", "Rcv", "Snt", "Att", "Trn", "Orp", "K/s",					"Loc", "Hld", "Rsv", "Frq", "Rrq", "Rrc", "Arq", "Fup",					"Dir", "Scn" };*//*	FTS-0001      AttributeWord   bit       meaning                      ---       --------------------                        0  +    Private                        1  + s  Crash                        2       Recd                        3       Sent                        4  +    FileAttached                        5       InTransit                        6       Orphan                        7       KillSent                        8       Local                        9    s  HoldForPickup                       10  +    unused                       11    s  FileRequest                       12  + s  ReturnReceiptRequest                       13  + s  IsReturnReceipt                       14  + s  AuditRequest                       15    s  FileUpdateReq                             s - need not be recognized, but it's ok                             + - not zeroed before packeting*//*	FSC-0053     Flag      Brief          Long description     --------------------------------------------------------------------     PVT       Private        Indicates that the message may only be read                              by its addressee and author.     HLD       Hold           Message should be held for pickup by its                              destination system.     CRA       Crash          High-priority mail.     K/S       Kill/Sent      Remove message after it has been success-                              fully sent.     SNT       Sent           Message has been successfully sent (used                              for message without Kill/Sent status).     RCV       Received       Message has been read by its addressee.     A/S       Archive/Sent   Place message in "sent mail" archival                              system after it has been successfully sent.     DIR       Direct         Message must be sent directly to its                              destination and may not be routed.     ZON       Zonegate       Send message through zonegate (if                              possible).     HUB       Hub/Host-route Host- or Hub-route message (as                              appropriate).     FIL       File attach    Message has one or more files attached to                              it.     FRQ       File request   Message has one or more file requests in                              subject field.     IMM       Immediate      NOW!-priority mail. Send at first                              opportunity, override any transmission                              restrictions enforced by events, costs, or                              qualification.     XMA       Xmail          Message has alternate form of compressed                              mail attached.     KFS       Kill file      Remove attached file(s) after they have                              been successfully sent. Only valid for file                              attach message.     TFS       Truncate file  Truncate attached file(s) to zero length                              after they have been successfully sent.                              Only valid for file attach message.                              Primarily used by Conference Mail                              processors.     LOK       Lock           Prevent message from being processed.                              This includes sending, deleting,                              purging, and editing.     RRQ       Receipt REQ    When the mailer/packer at the message's                              final destination unpacks the message, it's                              asked to generate a receipt to the author                              of the message that indicates that the                              message arrived at its final destination.     CFM       Confirm REQ    When message is read by its addressee, a                              Confirmation Receipt should be generated to                              the author of the message.     HIR       HiRes          FAX: Hi-Resolution image.     COV       CoverLetter    FAX: Cover sheet.     SIG       Signature      FAX: Signature.     LET       LetterHead     FAX: LetterHead.|    FAX       Fax image      The filename specified in the message's|                             subject field contains a fax document that|                             should be viewed using software capable of|                             doing so.|    FPU       Force pickup   Treated as a message with an IMM flag. This|                             instructs the mailer to keep calling the|                             destination system, if the connection is|                             aborted for some reason, until a valid "End|                             of files" signal is received (i.e. no more|                             files remain to pick up).*//*	16bit	in flag field (position unique) */#define MSGPRIVATE		0x00000001L		/*Private message*/#define MSGCRASH		0x00000002L		/*High priority*/#define MSGREAD			0x00000004L		/*Read by addressee*/#define MSGSENT			0x00000008L		/*Has been sent*/#define MSGFILE			0x00000010L		/*File attached to msg*/#define MSGTRANSIT		0x00000020L		/*In transit*/#define MSGORPHAN		0x00000040L		/*Unknown node*/#define MSGKILL			0x00000080L		/*Kill after mailing*/#define MSGLOCAL		0x00000100L		/*Message was entered here*/#define MSGHOLD			0x00000200L		/*Hold for pickup*/#define MSGUNUSED		0x00000400L		/*!!*/#define MSGFREQ			0x00000800L		/*File request*/#define MSGRRREQ		0x00001000L		/*Return receipt request !!*/#define MSGISRR			0x00002000L		/*Is return receipt !!*/#define MSGAREQ			0x00004000L		/*Audit request !!*/#define MSGFUPDREQ		0x00008000L		/*File update request !!*//*	32bit	in FLAGS kludge (position as I wish) */#define MSGDIRECT		0x00010000L		/*Direct message и*/#define MSGSCN			0x00020000L		/*SCN и*/#define MSGKFS			0x00040000L		/*KFS и*/#define MSGCFM			0x00080000L		/*CFM и*//*	OBSOLETE	*//*#define	RAVEL_HOLD		0x00100000L#define	RAVEL_DIRECT	0x00200000L#define	RAVEL_CRASH		0x00400000L#define	RAVEL_KILL		0x00800000L#define	RAVEL_RRQ		0x01000000L#define	RAVEL_FRQ		0x02000000L#define	RAVEL_ATT		0x04000000L*//* Message header, one per message */typedef struct    {    char    FromUser[MName],                             /*Name in By: field*/            ToUser[MName],                               /*Name in To: field*/            Subject[MSubject],                           /*Name in Re: field*/            Date[MDate];                              /*ASCIIz creation date*/    unsigned short            TimesRead,                        /*Number of times message read*/            DestNode,                                     /*Destination node*/            OrigNode,                                     /*Originating node*/            Cost,                                     /*Cost to send message*/            OrigNet,                                       /*Originating net*/            DestNet;                                       /*Destination net*/    unsigned long            DateWritten,                          /*Date message was written*/            DateArrived;                        /*Date message was read/sent*/    unsigned short            ReplyTo,                          /*This is a reply to "ReplyTo"*/            Attr,                                /*Attribute bits, see above*/            ReplyNext;                                /*Next reply in thread*/    /*    **    The message follows this but is of variable length ASCIIZ    **    string:			MsgText.      	*/    }    FIDOMSG;/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/	//	еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее	//	е																е	//	е				   Internal Ravel structures					е	//	е																е	//	еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*///	е Addresses note: if net is undefined (==0) address is emptytypedef struct								/* Internal net address storage structure */	{	short				zone,						net,						node,						point;	}	addr;typedef struct								/* Internal net address storage structure with domain */	{	addr				ad;	Str31				domain;	}	daddr;/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/typedef struct								/* Internal packet storage structure */	{	addr				from,						to;//	short				auxnet;	short				pkttype;	short				year,				/* Packet creation date */						month,						day,						hour,						min,						sec;	short				productCode;		/* Product's code */	short				productRev;			/* Product's version/revision */	char				passwd[9];	}	pktheader;/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/typedef struct								/* Internal storage structure of path and seen-by */	{	short				**nets;	short				**nodes;	short				items;	}	juncted;//	е Messages note: if area is undefined (area[0]==0) it is netmailtypedef struct								/* Internal storage of message structure */	{	addr				from,				/* from address */						to,					/* to address */						reply;				/* reply address */							char				fromname[MName],						toname[MName];	char				date[MDate],						subj[MSubject];	long				flags;	char				**text;	char				area[64];	long				msgid;	long				replyid;	long				storedtime;	juncted				seenby,						path;	}	pktmsg;/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*//*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/	//	еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее	//	е																е	//	е				     Ravel's base structures					е	//	е																е	//	еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*///	е	Base header descriptortypedef struct _baseIndexHeader {	short			busy;				// reaserved	unsigned char	AreaName[MName];	// name of area ("NETMAIL" == netmail, not empty!)	long			CRCIndex;			// reserved	long			CRCText;			// reserved	long			lastRead;			// number of last read	long			NumberOfMessages;	// number of messages/*	indexAtomType	indexAtom[NumberOfMessages];*/} baseIndexHeaderType;typedef struct _indexAtom {	short			deleted;			// message is deleted - can purge :)	long			textOffset;			// intext offset from start of file	long			headOffset;			// heders offset		addr			from,				// addresses					to,					//  +++ to field is actually for NetMail only					reply;						long			msgID;				// MSGID unical number copy	long			repID;				// REPLY unical number copy	long			storedTime;	long			flags;	long			BaseReplyTo,		// number of message that was origin for reply					BaseNextReply;		// next reply in base number} indexAtomType, *indexAtomPtr;typedef struct _base {	short			busy;				// reaserved	unsigned char	AreaName[MName];	// name of area ("NETMAIL" == netmail, not empty!)	long			CRCIndex;			// reserved	long			CRCText;			// reserved	long			lastRead;			// number of last read	long			NumberOfMessages;	// number of messages	indexAtomType	indexAtom[];} baseType, *basePtr, **baseHndl;/*	char			fromname[MName],					toname[MName];	char			date[MDate],					subj[MSubject];*/	#define	BADAREA		-2	#define	NOOPENBASE	-1	#define	NETMAIL		0//	#define	OTHERSBASE	>0/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/struct _pkthdr						/* FTS-0001                       */{	short orig_node;				/* originating node               */	short dest_node;				/* destination node               */	short year;						/* 0..99  when packet was created */	short month;					/* 0..11  when packet was created */	short day;						/* 1..31  when packet was created */	short hour;						/* 0..23  when packet was created */	short minute;					/* 0..59  when packet was created */	short second;					/* 0..59  when packet was created */	short rate;						/* destination's baud rate        */	short ver;						/* packet version, must be 2      */	short orig_net;					/* originating network number     */	short dest_net;					/* destination network number     */	unsigned char product;			/* product type                   */	unsigned char serial;			/* serial number (some systems)   */	unsigned char password[8];		/* session/pickup password        */	short orig_zone;				/* originating zone               */	short dest_zone;				/* Destination zone               */	unsigned char B_fill2[16];	long B_fill3;};struct _pkthdr45					/* FSC-0045 (Type 2.2) packet type*/{	short orig_node;				/* originating node               */	short dest_node;				/* destination node               */	short orig_point;				/* originating point              */	short dest_point;				/* destination point              */	unsigned char b_fill1[8];		/* Unused, must be zero           */	short subver;					/* packet subversion, must be 2   */	short ver;						/* packet version, must be 2      */	short orig_net;					/* originating network number     */	short dest_net;					/* destination network number     */	unsigned char product;			/* product type                   */	unsigned char serial;			/* serial number (some systems)   */	unsigned char password[8];		/* session/pickup password        */	short orig_zone;				/* originating zone               */	short dest_zone;				/* Destination zone               */	unsigned char orig_domain[8];	/* originating domain             */	unsigned char dest_domain[8];	/* destination domain             */	long B_fill3;};struct _pkthdr39					/* FSC-0039 (Type 2) packet type  */{	short orig_node;				/* originating node               */	short dest_node;				/* destination node               */	short year;						/* 0..99  when packet was created */	short month;					/* 0..11  when packet was created */	short day;						/* 1..31  when packet was created */	short hour;						/* 0..23  when packet was created */	short minute;					/* 0..59  when packet was created */	short second;					/* 0..59  when packet was created */	short rate;						/* destination's baud rate        */	short ver;						/* packet version, must be 2      */	short orig_net;					/* originating network number     */	short dest_net;					/* destination network number     */	unsigned char product_low;		/* FTSC product type (low unsigned char)   */	unsigned char prod_rev_hi;		/* product rev (low unsigned char)         */	unsigned char password[8];		/* session/pickup password        */	short qm_orig_zone;				/* Zone info from QM software  */	short qm_dest_zone;				/* Zone info from QM software  */	short auxnet;					/* Aux Net (for Type 2+) */	short CapValid;					/* CapWord with bytes swapped.    */	unsigned char product_hi;		/* FTSC product type (high unsigned char)  */	unsigned char prod_rev_low;		/* product rev (hi unsigned char)          */	short CapWord;					/* Capability word                */	short orig_zone;				/* originating zone               */	short dest_zone;				/* Destination zone               */	short orig_point;				/* originating point              */	short dest_point;				/* destination point              */	long ProdData;					/* Product-specific data          */};/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/    /* Packet header, one per packet */typedef struct _miopkt    {    unsigned short int  OrigNode,                         /*Originating node*/	// + 00                        DestNode,                         /*Destination node*/	// + 02                        Year,                     /*Year created (1993-nnnn)*/	// + 04                        Month,                        /*Month created (0-11)*/	// + 06                        Day,                            /*Day created (1-31)*/	// + 08                        Hour,                          /*Hour created (0-23)*/	// + 0A                        Minute,                      /*Minute created (0-59)*/	// + 0C                        Second,                      /*Second created (0-59)*/	// + 0E                        Rate,                            /*Baudrate (unused)*/	// + 10                        Version,                        /*Packet version (2)*/	// + 12                        OrigNet,                           /*Originating net*/	// + 14                        DestNet;                           /*Destination net*/	// + 16    unsigned char       PCodeLo,                  /*Product code (low-order)*/	// + 18                        PRevMajor,                           /*Major version*/	// + 19                        Password[8];          /*Packet password (not ASCIIZ)*/	// + 1A    unsigned short int  QMOrigZone,               /*Originating zone (QMail)*/	// + 22                        QMDestZone,               /*Destination zone (QMail)*/	// + 24                        AuxNet,                     /*Auxillary net (unused)*/	// + 26                        CWValidate;                     /*CapWord validation*/	// + 28    unsigned char       PCodeHi,                 /*Product code (high-order)*/	// + 2A                        PRevMinor;                           /*Minor version*/	// + 2B    unsigned short int  CWCapWord,                            /*Capabilities*/	// + 2C                        OrigZone,                /*Originating zone (FSC-39)*/	// + 2E                        DestZone,                /*Destination zone (FSC-39)*/	// + 30                        OrigPoint,              /*Originating point (FSC-39)*/	// + 32                        DestPoint;              /*Destination point (FSC-39)*/	// + 34    unsigned long       LongData;            /*Product dependent information*/	// + 36    };																			//   38//	FTS1PKTHDR;/*ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/