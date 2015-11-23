
/*
 * COPYRIGHT 1992 SAMUEL H. SMITH
 * ALL RIGHTS RESERVED
 *
 * THIS DOCUMENT CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS
 * PROPRIETARY TO SAMUEL H. SMITH DBA THE TOOL SHOP.
 *
 */


/*********************************************************************
         * MEMORY MANAGEMENT SERVICES PROVIDED BY APPLICATION *
 *********************************************************************/

pascal unsigned int mem_avail(void);
pascal void* mem_alloc(unsigned size);
pascal void mem_free(void *block);
pascal void mem_clear(void *block, unsigned size);
pascal void mem_copy(uchar *dest, uchar *src, unsigned size);

