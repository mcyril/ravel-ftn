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
/*                  Hydra CRC definitions for BinkleyTerm                   */
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

/*============================================================ Rev. 17 Jan 1993
  Routines for table driven CRC-16 & CRC-32, including building tables
  Refer to CRC.DOC for information and documentation.
  This header file can be used with either CRC.C or its 80x86 ASM equivalent.
  Define CRC_TINY to use with CRC_TINY.C.
  -----------------------------------------------------------------------------

	       Information collected and edited by Arjen G. Lentz
	     Sourcecode in C and 80x86 ASM written by Arjen G. Lentz
		  COPYRIGHT (C) 1992-1993; ALL RIGHTS RESERVED


  CONTACT ADDRESS

  LENTZ SOFTWARE-DEVELOPMENT	Arjen Lentz @
  Langegracht 7B		AINEX-BBS +31-33-633916
  3811 BT  Amersfoort		FidoNet 2:283/512
  The Netherlands		arjen_lentz@f512.n283.z2.fidonet.org


  DISCLAIMER

  This information is provided "as is" and comes with no warranties of any
  kind, either expressed or implied. It's intended to be used by programmers
  and developers. In no event shall the author be liable to you or anyone
  else for any damages, including any lost profits, lost savings or other
  incidental or consequential damages arising out of the use or inability
  to use this information.


  LICENCE

  This package may be freely distributed provided the files remain together,
  in their original unmodified form.
  All files, executables and sourcecode remain the copyrighted property of
  Arjen G. Lentz and LENTZ SOFTWARE-DEVELOPMENT.
  Licence for any use granted, provided this notice & CRC.DOC are included.
  For executable applications, credit should be given in the appropriate
  place in the program and documentation.
  These notices must be retained in any copies of any part of this
  documentation and/or software.

  Any use of, or operation on (including copying/distributing) any of
  the above mentioned files implies full and unconditional acceptance of
  this license and disclaimer.

=============================================================================*/


	/* --------------------------------------------------------------------- */
	/* CRC-16 used by ARC and LH, use crc16___ routines					     */
	/* --------------------------------------------------------------------- */
#define CRC16APOLY	(0xA001)			/* Generator polynomial number	     */
#define CRC16AINIT	(0)					/* Initial CRC value for calculation */
#define CRC16APOST(crc) (crc)			/* CRC Postconditioning before xmit  */
#define CRC16ATEST	(0)					/* Result to test for at receiver    */

	/* --------------------------------------------------------------------- */
	/* CRC-16 CCITT proper												     */
	/* --------------------------------------------------------------------- */
#define CRC16POLY	(0x8408)			/* Generator polynomial number	     */
#define CRC16INIT	(0xFFFF)			/* Initial CRC value for calculation */
#define CRC16POST(crc)	(~(crc))		/* CRC Postconditioning before xmit  */
#define CRC16TEST	(0xF0B8)			/* Result to test for at receiver    */

	/* --------------------------------------------------------------------- */
	/* CRC-16 CCITT upside-down												 */
	/* --------------------------------------------------------------------- */
#define CRC16RPOLY	(0x1021)			/* Generator polynomial number	     */
#define CRC16RINIT	(0)					/* Initial CRC value for calculation */
#define CRC16RPOST(crc) (crc)			/* CRC Postconditioning before xmit  */
#define CRC16RTEST	(0)					/* Result to test for at receiver    */

	/* --------------------------------------------------------------------- */
	/* CRC-32 CCITT 							                             */
	/* --------------------------------------------------------------------- */
#define CRC32POLY      (0xEDB88320L)	/* Generator polynomial number	     */
#define CRC32INIT      (0xFFFFFFFFL)	/* Initial CRC value for calculation */
#define CRC32POST(crc) (~(crc))			/* CRC Postconditioning before xmit  */
#define CRC32TEST      (0xDEBB20E3L)	/* Result to test for at receiver    */

	/* --------------------------------------------------------------------- */
	/* Number of items in CRC table 									     */
	/* --------------------------------------------------------------------- */

#define CRC_TABSIZE (256L)				/* Normal 256-entry table	         */

	/* --------------------------------------------------------------------- */
	/* CRC-16 proper, used for both CCITT and the one used by ARC		     */
	/* --------------------------------------------------------------------- */
	void crc16init (unsigned short *crctab, unsigned short poly);
	unsigned short crc16block (unsigned short *crctab, unsigned short crc, unsigned char *buf, unsigned short len);

#define crc16upd(crctab,crc,c) ((crctab)[((crc) ^ (c)) & 0xff] ^ ((crc) >> 8))

	/* --------------------------------------------------------------------- */
	/* CRC-16 upside-down, transmitted high-unsigned char first						 */
	/* --------------------------------------------------------------------- */
	void crc16rinit (unsigned short *crctab, unsigned short poly);
	unsigned short crc16rblock (unsigned short *crctab, unsigned short crc, unsigned char *buf, unsigned short len);

#define crc16rupd(crctab,crc,c) ((crctab)[(((crc) >> 8) ^ (c)) & 0xff] ^ ((crc) << 8))

	/* --------------------------------------------------------------------- */
	/* CRC-32																 */
	/* --------------------------------------------------------------------- */
	void crc32init (unsigned long *crctab, unsigned long poly);
	unsigned long crc32block (unsigned long *crctab, unsigned long crc, unsigned char *buf, unsigned short len);

#define crc32upd(crctab,crc,c) ((crctab)[((short) (crc) ^ (c)) & 0xff] ^ ((crc) >> 8))


unsigned short crc_block (unsigned char *ptr, short count);

#define updcrc(cp, crc) ( crctab[((crc >> 8) & 255) ^ cp] ^ (crc << 8))
#define xcrc(crc,cp) ( crctab[((crc >> 8) & 255) ^ cp] ^ (crc << 8))

extern unsigned short crctab[];
extern unsigned long cr3tab[];


/* end of crc.h ------------------------------------------------------------ */

