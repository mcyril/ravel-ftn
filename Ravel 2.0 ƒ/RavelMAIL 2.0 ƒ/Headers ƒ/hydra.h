/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                                                                          */
/*      ------------         Bit-Bucket Software, Co.                       */
/*      \ 10001101 /         Writers and Distributors of                    */
/*       \ 011110 /          Freely Available<tm> Software.                 */
/*        \ 1011 /                                                          */
/*         ------                                                           */
/*                                                                          */
/*              (C) Copyright 1987-96, Bit Bucket Software Co.              */
/*                                                                          */
/*             This header file was written by Michael Buenter              */
/*               Based on original header file by Arjen Lentz               */
/*                Hydra Protocol definitions for BinkleyTerm                */
/*                                                                          */
/*                                                                          */
/*    For complete  details  of the licensing restrictions, please refer    */
/*    to the License  agreement,  which  is published in its entirety in    */
/*    the MAKEFILE and BT.C, and also contained in the file LICENSE.260.    */
/*                                                                          */
/*    USE  OF THIS FILE IS SUBJECT TO THE  RESTRICTIONS CONTAINED IN THE    */
/*    BINKLEYTERM  LICENSING  AGREEMENT.  IF YOU DO NOT FIND THE TEXT OF    */
/*    THIS  AGREEMENT IN ANY OF THE  AFOREMENTIONED FILES,  OR IF YOU DO    */
/*    NOT HAVE THESE FILES,  YOU  SHOULD  IMMEDIATELY CONTACT BIT BUCKET    */
/*    SOFTWARE CO.  AT ONE OF THE  ADDRESSES  LISTED BELOW.  IN NO EVENT    */
/*    SHOULD YOU  PROCEED TO USE THIS FILE  WITHOUT HAVING  ACCEPTED THE    */
/*    TERMS  OF  THE  BINKLEYTERM  LICENSING  AGREEMENT,  OR  SUCH OTHER    */
/*    AGREEMENT AS YOU ARE ABLE TO REACH WITH BIT BUCKET SOFTWARE, CO.      */
/*                                                                          */
/*                                                                          */
/* You can contact Bit Bucket Software Co. at any one of the following      */
/* addresses:                                                               */
/*                                                                          */
/* Bit Bucket Software Co.        FidoNet  1:104/501, 1:343/491             */
/* P.O. Box 460398                AlterNet 7:42/1491                        */
/* Aurora, CO 80046               BBS-Net  86:2030/1                        */
/*                                Internet f491.n343.z1.fidonet.org         */
/*                                                                          */
/* Please feel free to contact us at any time to share your comments about  */
/* our software and/or licensing policies.                                  */
/*                                                                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/

/*=============================================================================

                              HydraCom Version 1.08
                             (+ rev. upto 18 dec 93)

                         A sample implementation of the
                   HYDRA Bi-Directional File Transfer Protocol

                             HydraCom was written by
                   Arjen G. Lentz, LENTZ SOFTWARE-DEVELOPMENT
                  COPYRIGHT (C) 1991-1993; ALL RIGHTS RESERVED

                       The HYDRA protocol was designed by
                 Arjen G. Lentz, LENTZ SOFTWARE-DEVELOPMENT and
                            Joaquim H. Homrighausen
                  COPYRIGHT (C) 1991-1993; ALL RIGHTS RESERVED


  Revision history:
  06 Sep 1991 - (AGL) First tryout
  .. ... .... - Internal development
  11 Jan 1993 - HydraCom version 1.00, Hydra revision 001 (01 Dec 1992)
  13 Mar 1993 - HydraCom version 1.03, Hydra revision 001 (01 Dec 1992)
  ..
  Changes made by Michael Buenter:
  03 Dec 1993 - adapted hydra for BT-EE and BT 2.58, many changes
  ..
  Updated source fixes by Arjen Lentz:
  04 Sep 1993 - HydraCom version 1.08, Hydra revision 001 (01 Dec 1992)
  23 Dec 1993 - updated to post-1.08 revisions upto 18 Dec 1993

  For complete details of the Hydra and HydraCom licensing restrictions,
  please refer to the license agreements which are published in their entirety
  in HYDRACOM.C and LICENSE.DOC, and also contained in the documentation file
  HYDRACOM.DOC

  Use of this file is subject to the restrictions contained in the Hydra and
  HydraCom licensing agreements. If you do not find the text of this agreement
  in any of the aforementioned files, or if you do not have these files, you
  should immediately contact LENTZ SOFTWARE-DEVELOPMENT and/or Joaquim
  Homrighausen at one of the addresses listed below. In no event should you
  proceed to use this file without having accepted the terms of the Hydra and
  HydraCom licensing agreements, or such other agreement as you are able to
  reach with LENTZ SOFTWARE-DEVELOMENT and Joaquim Homrighausen.


  Hydra protocol design and HydraCom driver:         Hydra protocol design:
  Arjen G. Lentz                                     Joaquim H. Homrighausen
  LENTZ SOFTWARE-DEVELOPMENT                         389, route d'Arlon
  Langegracht 7B                                     L-8011 Strassen
  3811 BT  Amersfoort                                Luxembourg
  The Netherlands
  FidoNet 2:283/512, AINEX-BBS +31-33-633916         FidoNet 2:270/17
  arjen_lentz@f512.n283.z2.fidonet.org               joho@ae.lu

  Please feel free to contact us at any time to share your comments about our
  software and/or licensing policies.

=============================================================================*/

/* HYDRA Some stuff to aid readability of the source and prevent typos ----- */
#define h_crc16test(crc)   (((crc) == CRC16TEST) ? 1 : 0)	/*AGL:10mar93*/
#define h_crc32test(crc)   (((crc) == CRC32TEST) ? 1 : 0)	/*AGL:10mar93*/
#define h_uuenc(c)         (((c) & 0x3f) + '!')
#define h_uudec(c)         (((c) - '!') & 0x3f)
#define h_long1(buf)       (*((long *) (buf)))
#define h_long2(buf)       (*((long *) ((buf) + ((short) sizeof (long)))))
#define h_long3(buf)       (*((long *) ((buf) + (2 * ((short) sizeof (long))))))
typedef unsigned long h_timer;

//	#define h_timer_get()      (unsigned long)(time(NULL))	/*AGL:15jul93*/
#define h_timer_get()      ((unsigned long)(LMGetTime()))	/*AGL:15jul93*/
#define h_timer_set(t)     ((unsigned long)(h_timer_get() + (t)))	/*AGL:15jul93*/
#define h_timer_running(t) (t != 0L)
#define h_timer_expired(t, now) ((now) > (t))	/*AGL:15jul93*/
#define h_timer_reset()    (0L)

/* HYDRA Specification Revision/Timestamp ---------Revision------Date------- */
#define H_REVSTAMP   0x2b1aab00L/* 001           01 Dec 1992 */
#define H_REVISION   1

/* HYDRA Basic Values ------------------------------------------------------ */
#ifndef XON
#define XON          ('Q' - '@')/* Ctrl-Q (^Q) xmit-on character     */
#define XOFF         ('S' - '@')/* Ctrl-S (^S) xmit-off character    */
#endif
#define H_DLE        ('X' - '@')/* Ctrl-X (^X) HYDRA DataLinkEscape  */
#define H_MINBLKLEN    64		/* Min. length of a HYDRA data block */
#define H_MAXBLKLEN  2048		/* Max. length of a HYDRA data block */
#define H_OVERHEAD      8		/* Max. no. control bytes in a pkt   */
#define H_MAXPKTLEN  ((H_MAXBLKLEN + H_OVERHEAD + 5) * 3)	/* Encoded pkt */
#define H_BUFLEN     (H_MAXPKTLEN + 16)	/* Buffer sizes: max.enc.pkt + slack */
#define H_PKTPREFIX    31		/* Max length of pkt prefix string   */
#define H_FLAGLEN       3		/* Length of a flag field            */
#define H_RETRIES      10		/* No. retries in case of an error   */
#define H_MINTIMER     10		/* Minimum timeout period            */
#define H_MAXTIMER     60		/* Maximum timeout period            */
#define H_START         5		/* Timeout for re-sending startstuff */
#define H_IDLE         20		/* Idle? tx IDLE pkt every 20 secs   */
#define H_BRAINDEAD   120		/* Braindead in 2 mins (120 secs)    */

/* HYDRA Return codes ------------------------------------------------------ */
#define XFER_ABORT    (-1)		/* Failed on this file & abort xfer  */
#define XFER_SKIP       0		/* Skip this file but continue xfer  */
#define XFER_OK         1		/* File was sent, continue transfer  */

/* HYDRA Transmitter States ------------------------------------------------ */
#define HTX_DONE        0		/* All over and done                 */
#define HTX_START       1		/* Send start autostr + START pkt    */
#define HTX_SWAIT       2		/* Wait for any pkt or timeout       */
#define HTX_INIT        3		/* Send INIT pkt                     */
#define HTX_INITACK     4		/* Wait for INITACK pkt              */
#define HTX_RINIT       5		/* Wait for HRX_INIT -> HRX_FINFO    */
#define HTX_FINFO       6		/* Send FINFO pkt                    */
#define HTX_FINFOACK    7		/* Wait for FINFOACK pkt             */
#define HTX_XDATA       8		/* Send next packet with file data   */
#define HTX_DATAACK     9		/* Wait for DATAACK packet           */
#define HTX_XWAIT      10		/* Wait for HRX_END                  */
#define HTX_EOF        11		/* Send EOF pkt                      */
#define HTX_EOFACK     12		/* End of file, wait for EOFACK pkt  */
#define HTX_REND       13		/* Wait for HRX_END && HTD_DONE      */
#define HTX_END        14		/* Send END pkt (finish session)     */
#define HTX_ENDACK     15		/* Wait for END pkt from other side  */

#ifdef HYDRADEV
/* HYDRA Device Packet Transmitter States ---------------------------------- */
#define HTD_DONE        0		/* No device data pkt to send        */
#define HTD_DATA        1		/* Send DEVDATA pkt                  */
#define HTD_DACK        2		/* Wait for DEVDACK pkt              */
#endif

/* HYDRA Receiver States --------------------------------------------------- */
#define HRX_DONE        0		/* All over and done                 */
#define HRX_INIT        1		/* Wait for INIT pkt                 */
#define HRX_FINFO       2		/* Wait for FINFO pkt of next file   */
#define HRX_DATA        3		/* Wait for next DATA pkt            */

/* HYDRA Packet Types ------------------------------------------------------ */
#define HPKT_START     'A'		/* Startup sequence                  */
#define HPKT_INIT      'B'		/* Session initialisation            */
#define HPKT_INITACK   'C'		/* Response to INIT pkt              */
#define HPKT_FINFO     'D'		/* File info (name, size, time)      */
#define HPKT_FINFOACK  'E'		/* Response to FINFO pkt             */
#define HPKT_DATA      'F'		/* File data packet                  */
#define HPKT_DATAACK   'G'		/* File data position ACK packet     */
#define HPKT_RPOS      'H'		/* Transmitter reposition packet     */
#define HPKT_EOF       'I'		/* End of file packet                */
#define HPKT_EOFACK    'J'		/* Response to EOF packet            */
#define HPKT_END       'K'		/* End of session                    */
#define HPKT_IDLE      'L'		/* Idle - just saying I'm alive      */
#ifdef HYDRADEV
#define HPKT_DEVDATA   'M'		/* Data to specified device          */
#define HPKT_DEVDACK   'N'		/* Response to DEVDATA pkt           */
#endif

#define HPKT_HIGHEST   'N'		/* Highest known pkttype in this imp */

/* HYDRA Internal Pseudo Packet Types -------------------------------------- */
#define H_NOPKT         0		/* No packet (yet)                   */
#define H_CANCEL      (-1)		/* Received cancel sequence 5*Ctrl-X */
#define H_CARRIER     (-2)		/* Lost carrier                      */
#define H_SYSABORT    (-3)		/* Aborted by operator on this side  */
#define H_TXTIME      (-4)		/* Transmitter timeout               */
#define H_DEVTXTIME   (-5)		/* Device transmitter timeout        */
#define H_BRAINTIME   (-6)		/* Braindead timeout (quite fatal)   */

/* HYDRA Packet Format: START[<data>]<type><crc>END ------------------------ */
#define HCHR_PKTEND    'a'		/* End of packet (any format)        */
#define HCHR_BINPKT    'b'		/* Start of binary packet            */
#define HCHR_HEXPKT    'c'		/* Start of hex encoded packet       */
#define HCHR_ASCPKT    'd'		/* Start of shifted 7bit encoded pkt */
#define HCHR_UUEPKT    'e'		/* Start of uuencoded packet         */

/* HYDRA Local Storage of INIT Options (Bitmapped) ------------------------- */
#define HOPT_XONXOFF  (0x00000001L)	/* Escape XON/XOFF                   */
#define HOPT_TELENET  (0x00000002L)	/* Escape CR-'@'-CR (Telenet escape) */
#define HOPT_CTLCHRS  (0x00000004L)	/* Escape ASCII 0-31 and 127         */
#define HOPT_HIGHCTL  (0x00000008L)	/* Escape above 3 with 8th bit too   */
#define HOPT_HIGHBIT  (0x00000010L)	/* Escape ASCII 128-255 + strip high */
#define HOPT_CANBRK   (0x00000020L)	/* Can transmit a break signal       */
#define HOPT_CANASC   (0x00000040L)	/* Can transmit/handle ASC packets   */
#define HOPT_CANUUE   (0x00000080L)	/* Can transmit/handle UUE packets   */
#define HOPT_CRC32    (0x00000100L)	/* Packets with CRC-32 allowed       */
#define HOPT_DEVICE   (0x00000200L)	/* DEVICE packets allowed            */
#define HOPT_FPT      (0x00000400L)	/* Can handle filenames with paths   */

/* What we can do */
#ifndef HYDRADEV
#define HCAN_OPTIONS  (HOPT_XONXOFF|HOPT_TELENET|HOPT_CTLCHRS|HOPT_HIGHCTL|HOPT_HIGHBIT|HOPT_CANBRK|HOPT_CANASC|HOPT_CANUUE|HOPT_CRC32)
#else
#define HCAN_OPTIONS  (HOPT_XONXOFF|HOPT_TELENET|HOPT_CTLCHRS|HOPT_HIGHCTL|HOPT_HIGHBIT|HOPT_CANBRK|HOPT_CANASC|HOPT_CANUUE|HOPT_CRC32|HOPT_DEVICE)
#endif
/* Vital options if we ask for any; abort if other side doesn't support them */
#define HNEC_OPTIONS  (HOPT_XONXOFF|HOPT_TELENET|HOPT_CTLCHRS|HOPT_HIGHCTL|HOPT_HIGHBIT|HOPT_CANBRK)
/* Non-vital options; nice if other side supports them, but doesn't matter */
//#define HUNN_OPTIONS  (HOPT_CANASC|HOPT_CANUUE|HOPT_CRC32|HOPT_DEVICE)
#define HUNN_OPTIONS  (HOPT_CRC32)
/* Default options */
#define HDEF_OPTIONS  (0x0L)
/* rxoptions during init (needs to handle ANY link yet unknown at that point */
#define HRXI_OPTIONS  (HOPT_XONXOFF|HOPT_TELENET|HOPT_CTLCHRS|HOPT_HIGHCTL|HOPT_HIGHBIT)
/* ditto, but this time txoptions */
#define HTXI_OPTIONS  (0x0L)

#ifdef HYDRADEV
BOOL hydra_devfree (void);
BOOL hydra_devsend (char *dev, byte * data, word len);
BOOL hydra_devfunc (char *dev, void (*func) (byte * data, word len));

#endif
/* end of hydra.h */
