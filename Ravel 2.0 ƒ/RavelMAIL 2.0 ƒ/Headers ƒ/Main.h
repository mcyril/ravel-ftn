/*	Terminal 2.2	"Main.h"*/#define USECTB		/* Use Communications Toolbox if available */typedef struct {	/* Communication options */	Byte		portName[256];	/* What port to use */	short		portSetup;		/* Serial port setup */	short		handshake;		/* Handshake */	short		dropDTR;		/* Dont' drop DTR when quitting */	short		lockPort;	/* Binary file transfer options */	short		Binary;			/* Use and recognize MacBinary */	Byte		volumeName[28];	/* Volume name (down- & uploads) */	short		volume;			/* Volume reference (down- & uploads) */	long		directory;		/* Directory id (down- & uploads) */	/* ZModem options */	short		ZEscapeCtl;		/* Z-Modem: escape all control characters */	long		ZTimeout;		/* Z-Modem: receive timeout (ticks) */	long		ZBuffer;		/* Z-Modem: receive buffer size (bytes) */	long		ZRetries;		/* Z-Modem: receive maximum retries */	long		ZPacket;		/* Z-Modem: transmit sub-packet length (Bytes) */	long		ZWindow;		/* Z-Modem: transmit window size (Bytes) */	long		Zcrcq;			/* Z-Modem: transmit ZCRCQ spacing (Bytes) */	/* Other options */	long		textCreator;	/* TEXT file creator */	long		binType;		/* Non-MacBinary file type */	long		binCreator;		/* Non-MacBinary file creator */} Options;typedef struct {	short		icon;			/* Application 'ICN#' id (128) */	short		version;		/* Resource id of version data (0) */	long		signature;		/* Application signature ('ET_T') */	long		otype;			/* Options file type ('ET_O') */	long		btype;			/* MacBinary file type ('ET_B') */	long		stype;			/* Script file type ('TEXT') */	long		ztype;			/* Z-modem partial file ('ET_Z') */} Types;typedef struct {				/* 'CNFG' (configuration) resource */	short		font;			/* Font number (should be monospaced) */	short		size;			/* Font size */	short		lines;			/* Lines in terminal window */	short		columns;		/* Columns in terminal window */	long		buffer;			/* Size of terminal buffer (bytes) */	long		input;			/* Size of serial input buffer (bytes) */	long		output;			/* Size of serial output buffer (bytes) */	long		script;			/* Size of script memory (bytes) */	Byte		fontname[];		/* Font name (should be monospaced) */} Configuration;#define HiWrd(a)	(((a) >> 16) & 0xFFFF)#define LoWrd(a)	((a) & 0xFFFF)#define Max(a,b)	((a) > (b) ? (a) : (b))#define Min(a,b)	((a) < (b) ? (a) : (b))extern Options			Settings;		/* Current options */extern Configuration	Config;			/* Configuration parameters */extern Boolean			DTR;extern long				gSleepTime;#define FINE		0		/* No error *///#define TIMEOUT		1		/* Timeout error */#define CANCEL		2		/* Cancel by button or menu */#define ABORT		3		/* Abort by ctrl-X received *///#define ERROR		4		/* Other error */