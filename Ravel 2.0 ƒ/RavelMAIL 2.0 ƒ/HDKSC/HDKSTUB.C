
/*
 * HS/LINK DEVELOPER KIT 1.1
 * APPLICATION STUBS
 *
 * This module provides services required by the main hslink transfer
 * protocol.  Code these functions to take advantage of your operating
 * environment.
 *
 */

/*
 * As this is a preliminary edition of the HDK, please feel free to review
 * what has been provided and to make suggestions for ways to simplify the
 * interface requirements.  I can be reached during normal business hours,
 * tuesday through saturday at (818) 891-4228.   --Samuel H. Smith
 *
 */

#include <stdlib.h>
#include <stdio.h>
//#include <stdarg.h>
//#include <io.h>
//#include <conio.h>
#include <ctype.h>
//#include <dos.h>
//#include <dir.h>
//#include <mem.h>
//#include <alloc.h>
#include <string.h>
#include <fcntl.h>

#include "hspriv.h"
#include "hdk.h"

#include "log.h"
#include "comm.h"
#include "timing.h"

extern unsigned long	cur_baud;				/* Current baud rate   */
extern Boolean			Aborted;

#ifdef __DLL__
	#define cprintf printf
#endif

/*********************************************************************
               * COMM SERVICES PROVIDED BY APPLICATION *
 *********************************************************************/

/* prepare com ports for operation */
void pascal ComOpen(void)
{
//        DebugStr("\pStub: ComOpen");
}

/* shut down com port */
void pascal ComClose(void)
{
//        DebugStr("\pStub: ComClose\n");
}

/* set handshake modes according to option.* values */
void pascal ComSetHandshake(void)
{
//        DebugStr("\pStub: ComSetHandshake\n");
}

/* return current com port speed, if available */
long pascal ComGetSpeed(void)
{
	return cur_baud;
/*
        DebugStr("\pStub: ComGetSpeed\n");
        return 0;
*/
}

/* return hardware handshake status */
int pascal ComGetCts(void)
{
		return !OUT_EMPTY() /*SerialCTS()*/;
/*
        DebugStr("\pStub: ComGetCts\n");
        return 0;
*/
}

/* return carrier status. */
/* must return true when carrier detect monitoring is disabled */
int pascal ComCarrierLost(void)
{
	return !CARRIER;
/*
        printf("Stub: ComCarrierLost\n");
        return 1;
*/
}

/* returns the number of bytes waiting in the receive queue */
int pascal ComReadPending(void)
{
        return CHAR_AVAIL();
/*
        printf("Stub: ComReadPending\n");
        return 0;
*/
}

/* returns 1 character from the receive queue */
int pascal ComReadChar(void)
{
        DebugStr("\pStub: ComReadChar\n");
        return 0;
}

/* reads multiple characters into a buffer, returning number of
   characters actually read, up to bufsiz*/
unsigned int pascal ComReadStr(uchar *dest, unsigned int bufsiz)
{
        int n = 0;
        
        while(CHAR_AVAIL() && n < bufsiz)
        {
            *dest++ = MODEM_IN();
            ++n;
        }
/*
        int n,count;
        n = ComReadPending();
        if (n > bufsiz)
                n = bufsiz;
        count = 0;
        while (n--)
        {
                *dest++ = ComReadChar();
                ++count;
        }
        return count;
*/
		return n;
}

/* enters one character into the transmit queue */
void pascal ComWriteChar(uchar c)
{
	SENDBYTE(c, NULL);
//        printf("Stub: ComWriteChar %c\n",c);
}

/* enters a string of characters into the transmit queue */
void pascal ComWriteStr(uchar *src, unsigned count)
{
	SENDCHARS (src, count, 0, NULL);

//        while (--count)
//                ComWriteChar(*src++);
}

/* returns the number of characters currently waiting to transmit */
int pascal ComWritePending(void)
{
        return OUT_EMPTY() ? 0 : 1;
/*
        printf("Stub: ComWritePending\n");
        return 0;
*/
}

/* returns the highest possible ComWritePending value before a call to
   ComWrite will block on a transmit queue full condition */
int pascal ComWriteMax(void)
{
	return 4096;

/*
        printf("Stub: ComWriteMax\n");
        return 9999;    // size of transmit queue
*/
}

/* forces a release of xon/xoff handshake */
void pascal ComCancelXoff(void)
{
/*
        printf("Stub: ComCancelXoff\n");
*/
}

/* waits for ComWritePending to reach 0 while disposing of idle time */
void pascal ComFlush(int cancel)
{
	timer (1);
/*
        printf("Stub: ComFlush %d\n",cancel);
*/
}

/* called by hslink prior to any disk i/o activity.  there may be multiple
   calls to ComIoStart before a call to ComIoEnd is reached, so an i/o depth
   variable must be used */
void pascal ComIoStart(int where)
{
/*
        printf("Stub: ComIoStart %d\n",where);
*/
}

/* called by hslink on exit from disk i/o activity. */
void pascal ComIoEnd(int where)
{
/*
        printf("Stub: ComIoEnd %d\n",where);
*/
}

/* called by hslink periodically to see if any comm port errors need to be
   reported to the user */
void pascal ComReportErrors(void)
{
/*
        printf("Stub: ComReportErrors\n");
*/
}

/* called by hslink to display com port status information to the user */
void pascal ComReportStatus(int where)
{
/*
        printf("Stub: ComReportStatus %d\n",where);
*/
}

/* called by hslink when idle - use this to properly dispose of idle time.
   keyboard polling and outgoing chat should also be performed here */
void pascal ComIdle(int where)
{
	timer(1);
	
	if(Aborted)
	{
		set_cancel_link(CANCEL_KEYBOARD);
//		WS.cancel_link = CANCEL_KEYBOARD;
	}
/*
        printf("Stub: ComIdle %d\n",where);
*/
}


/*********************************************************************
        * DISPLAY MANAGEMENT SERVICES PROVIDED BY APPLICATION *
 *********************************************************************/

static char opt_coder;

/* prepare the screen display */
void pascal prepare_display(void)
{
	opt_coder = '_';
/*
        printf("Stub: prepare_display\n");
*/
}

/* prepare for displays in the "Options" portion of the display */
void pascal select_option(void)
{
	opt_coder = 'o';
/*
        printf("Stub: select_option\n");
*/
}

/* prepare for displays in the "Incoming Files" portion of the display */
void pascal select_recv(void)
{
	opt_coder = 'r';
/*
        printf("Stub: select_recv\n");
*/
}

/* prepare for displays in the "Outgoing Files" portion of the display */
void pascal select_send(void)
{
	opt_coder = 's';
/*
        printf("Stub: select_send\n");
*/
}

/* prepare for displays in the "Version/Warning" portion of the display */
void pascal select_version(void)
{
	opt_coder = 'v';
/*
        printf("Stub: select_version\n");
*/
}

/* move to next line in current display area */
void pascal newline(void)
{
/*
        printf("Stub: newline\n");
*/
}

/* protocol finished, close down display management, if any */
void pascal close_display(void)
{
/*
        printf("Stub: close_display\n");
*/
}

/* display a message with variable args */
void disp_message(char *fmt, ...)
{
        char buffer[80];
        va_list argptr;
        va_start(argptr, fmt);
        vsprintf(buffer, fmt, argptr);
        va_end(argptr);
		
		putlog(' ', "%c => %s", opt_coder, buffer);
/*
	printf(buffer);
*/
}

pascal void display_warning(char *what)
{
//		_putlog('@', what);
		putlog('@', "%c => %s", opt_coder, what);
}

/* display incoming chat messages */
void pascal display_chatin(char *s)
{
/*
        printf("Stub: display_chatin %s\n",s);
*/
}

/* display outgoing chat characters */
void pascal display_chatout(register char c)
{
/*
        printf("Stub: display_chatout %c\n",c);
*/
}

/* display current option settings in the "options" window */
void pascal display_settings(void)
{
/*
        printf("Stub: display_settings\n");
*/
}

/* number of incoming files is now known- update incoming files window */
void pascal display_incoming_files(void)
{
/*
        printf("Stub: display_incoming_files\n");
*/
}

/* number of outgoing files is now known- update outgoing files window */
void pascal display_outgoing_files(void)
{
/*
        printf("Stub: display_outgoing_files\n");
*/
}

/* next file is being sent or received.  Display the filename, number of blocks
   and file size in bytes.  mode is "Receiving" or "Transmissing" */
void pascal display_file_banner(char *mode,char *fname,unsigned int blocks,long bytes)
{
	putlog('>', "mode: %s, fname: %s, %ld, %ld", mode, fname, blocks, bytes);

/*
        printf("Stub: display_file_banner %s %s %u %ld\n",
                        mode,fname,blocks,bytes);
*/
//        putMessage("Stub: display_file_banner %s %s %u %ld\n",
//                        mode,fname,blocks,bytes);
}

/* display a bargraph for the currently selected window (incoming or
   outgoing files)  */
void pascal file_bargraph(long current, long total, unsigned cps)
{
/*
        printf("Stub: file_bargraph %ld %ld %u\n",current,total,cps);
*/
}

/* update the combined thruput and batch estimate display */
void pascal report_combined(void)
{
/*
        printf("Stub: report_combined\n");
*/
}

/* display and optionally log error message */
void disp_error(char *fmt, ...)
{
        char buffer[80];
        va_list argptr;
        va_start(argptr, fmt);
        vsprintf(buffer, fmt, argptr);
        va_end(argptr);

	_putlog('!', buffer);
//        printf(buffer);
//        log_error("Error: %s",buffer);
}

/* log error message */
void log_error(char *fmt, ...)
{
    char buffer[80];
    va_list argptr;
    va_start(argptr, fmt);
    vsprintf(buffer, fmt, argptr);
    va_end(argptr);
    /* stub: log error message to error log file */
    
	_putlog ('!', buffer);
}

/* report an error in the incoming files window */
void pascal report_rx_error( char *what )
{
//	printf("Stub: report_rx_error %s\n",what);
}

/* report an error in the outgoing files window */
void pascal report_tx_error( char *what, block_number block )
{
//	printf("Stub: report_tx_error %s %u\n",what,block);
}

/* report error and shut down when option specified is invalid in command
   line and/or configuration file */
void pascal usage(char *why, char *par)
{
//	printf("Stub: usage %s %s\n",why,par);
//	exit(99);
	DebugStr("\pStub: usage");
}

/* preview each block of receive data before it is written to disk */
void pascal filter_rx_block( char *fname, long offset, unsigned size, char *data )
{
}

/*********************************************************************
   * USER REGISTRATION AND TAMPER DETECTION PROVIDED BY APPLICATION *
 *********************************************************************/

/* determine if the specified remote user id number has been blocked */
int pascal blocked_userid(user_number *uid)
{
	return 0;
}

/* determine the local user id number */
user_number pascal local_userid(void)
{
	return 10000;
}


/*********************************************************************
         * MEMORY MANAGEMENT SERVICES PROVIDED BY APPLICATION *
 *********************************************************************/

/* determine memory available to hslink engine */
pascal unsigned int mem_avail(void)
{
	return 32U * 1024;
}

/* allocate a block of memory and initialize it to zeros */
pascal void* mem_alloc(unsigned size)
{
	return calloc(1,size);
}

/* release a previously allocated block of memory */
pascal void mem_free(void *block)
{
	if (block)
		free(block);
}

/* zero a block of memory */
pascal void mem_clear(void *block, unsigned size)
{
	memset(block, 0, size);
}

pascal void mem_copy(uchar *dest, uchar *src, unsigned int size)
{
	memcpy(dest, src, size);
}

/*********************************************************************
         * TIME MEASUREMENT SERVICES PROVIDED BY APPLICATION *
 *********************************************************************/

hs_clock_t pascal bios_clock(void)
{
	return ((unsigned long)LMGetTicks() * 182UL) / 60UL;
}
